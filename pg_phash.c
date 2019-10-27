#include <postgres.h>
#include <fmgr.h>
#include <stdlib.h>
#include <string.h>
#include <utils/datum.h>

#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64 ulong64;
#else
typedef unsigned long long ulong64;
#endif

#define ERR_MESSAGE__NO_MEM "Not enough memory!"
#define allocator(element, type) _allocator(element, sizeof(type))


#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

int32 ph_hamming_distance(const ulong64 hash1, const ulong64 hash2);

PG_FUNCTION_INFO_V1(phash_hamming);
Datum phash_hamming(PG_FUNCTION_ARGS) {
    // Prevent null pointers, which will cause segfault
    if (PG_GETARG_DATUM(0) == 0x00 || PG_GETARG_DATUM(1) == 0x00) {
        PG_RETURN_NULL();
    }

    // Get varchar pointers
    VarChar *ptr1 = PG_GETARG_VARCHAR_P(0);
    VarChar *ptr2 = PG_GETARG_VARCHAR_P(1);

    // Get varchar sizes
    unsigned char size1 = VARSIZE(ptr1) - VARHDRSZ;
    unsigned char size2 = VARSIZE(ptr2) - VARHDRSZ;

    // Extract content to new memory space
    char varchar1[size1 + 1];
    memcpy(varchar1, (void*) VARDATA(ptr1), size1);
    varchar1[size1] = '\0';

    char varchar2[size2 + 1];
    memcpy(varchar2, (void*) VARDATA(ptr2), size2);
    varchar2[size2] = '\0';

    // Convert number strings to ulong64
    ulong64 long1 = strtoull(varchar1, NULL, 16);
    ulong64 long2 = strtoull(varchar2, NULL, 16);

    // Compute hamming distance
    int32 ret = ph_hamming_distance(long1, long2);

    PG_RETURN_INT32(ret);
}

/*
    pHash, the open source perceptual hash library
    Copyright (C) 2009 Aetilius, Inc.
    All rights reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Evan Klinger - eklinger@phash.org
    D Grant Starkweather - dstarkweather@phash.org
*/

int32 ph_hamming_distance(const ulong64 hash1, const ulong64 hash2){
    ulong64 x = hash1^hash2;
    const ulong64 m1  = 0x5555555555555555ULL;
    const ulong64 m2  = 0x3333333333333333ULL;
    const ulong64 h01 = 0x0101010101010101ULL;
    const ulong64 m4  = 0x0f0f0f0f0f0f0f0fULL;
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    return (x * h01)>>56;
}


/** Allocator function (safe alloc) */
void *_allocator(size_t element, size_t typeSize)
{
    void *ptr = NULL;
    /* check alloc */
    if( (ptr = calloc(element, typeSize)) == NULL)
    {printf(ERR_MESSAGE__NO_MEM); exit(1);}
    /* return pointer */
    return ptr;
}

/** Append function (safe mode) */
char *append(const char *input, const char c)
{
    char *newString, *ptr;

    /* alloc */
    newString = allocator((strlen(input) + 2), char);
    /* Copy old string in new (with pointer) */
    ptr = newString;
    for(; *input; input++) {*ptr = *input; ptr++;}
    /* Copy char at end */
    *ptr = c;
    /* return new string (for dealloc use free().) */
    return newString;
}


char* convert_hex_to_binary(char hex[64]) {

    char * result;
        result = malloc(sizeof(char)*256);

    strcpy(result, "");


    int length = strlen(hex);
    for(int i=0;i<length;i++)
      {
        char c = hex[i];

        switch(c) {

           case '0'  :
              strcat(result, "0000");
              break;

            case '1'  :
              strcat(result, "0001");
              break;

            case '2'  :
                strcat(result, "0010");
                break;

            case '3'  :
              strcat(result, "0011");
              break;

           case '4'  :
              strcat(result, "0100");
              break;

            case '5'  :
              strcat(result, "0101");
              break;

            case '6'  :
                strcat(result, "0110");
                break;

            case '7'  :
              strcat(result, "0111");
              break;

           case '8'  :
              strcat(result, "1000");
              break;

            case '9'  :
              strcat(result, "1001");
              break;

            case 'a'  :
                strcat(result, "1010");
                break;

            case 'b'  :
              strcat(result, "1011");
              break;

           case 'c'  :
              strcat(result, "1100");
              break;

            case 'd'  :
              strcat(result, "1101");
              break;

            case 'e'  :
                strcat(result, "1110");
                break;

            case 'f'  :
                strcat(result, "1111");
                break;
        }
      }

    return result;
}
