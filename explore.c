#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_MESSAGE__NO_MEM "Not enough memory!"
#define allocator(element, type) _allocator(element, sizeof(type))

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


int hamming_distance(char* hex1, char* hex2)
{
    int count = 0;
    int length=strlen(hex2);
      for(int i=0;i<length;i++)
      {
            if(hex1[i]!=hex2[i])
            {
                  count++;
            }
      }
      return count;
}



// hashes are of the form 08fe3eff1287038303f701c711e570f760c067f093f88ff8dfff01bf000007fc
//08fe3eff1287038303f701c711e570f760c067f093f88ff8dfff01bf000007fc
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


int main(int argc, const char * argv[]){
     char * h1 = convert_hex_to_binary("ffe0ff800c0147f1c1f1c0f0447ffc700c60047e7c3e7d3e7d9e0181ffff0014");


     char * h2 = convert_hex_to_binary("1fc01fc8787c70b687b3c7b1c73185340f001f001f3efe3ffe3f0e3c00017fd8");
    // printf("%s\n",h1);
     //printf("%s\n",h2);
       int hd = hamming_distance(h1,h2);
    printf("%i\n",hd);

   /*

*/
/*
 ffe0ff800c0147f1c1f1c0f0447ffc700c60047e7c3e7d3e7d9e0181ffff0014
 ffe07f80070047f9c0f1c0f04c7ffc700470047e7c3e7d3e3d9e0581ffff0014
 1fc01fc078dc21df0785c791c7918f9e07801f001f3e7f3ffe3f061c00803fdf
 1fc01fc078de219f0789c791c7918f9e07801f001f3e7f3fff3f071c00021fde
 1fc01fc0787c718f07b7c791cf9185940f001f001f3efe3ffe3f0e1c00807fda
 1fc01fc8787c70b687b3c7b1c73185340f001f001f3efe3ffe3f0e3c00017fd8
 3fc01fcc29ce43d89f838f838781859f07800f801f9f3f9f3f9f079d00021fbe

        */
}
