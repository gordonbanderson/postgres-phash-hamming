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

/*
length=strlen(v2);
      for(i=0;i<length;i++)
      {
            if(v1[i]!=v2[i])
            {
                  count++;
            }
      }
      */
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

            printf("%s\n",result);

      }

    return result;
}


int main(int argc, const char * argv[]){
    const char * x = convert_hex_to_binary("08fe3eff1287038303f701c711e570f760c067f093f88ff8dfff01bf000007fc");
    printf("%s\n",x);

/*
    char *input = "Ciao Mondo"; // i am italian :), this is "Hello World"
        char c = '!';
        char *newString;

        newString = append(input, c);
        printf("%s\n",newString);

        free(newString);
        newString = NULL;
        */
}
