#include "cipher.h"
# define UPPER_L_FIRST 'A'
# define UPPER_L_LAST 'Z'
# define LOWER_L_FIRST 'a'
# define LOWER_L_UP 'z'
#include <stdio.h>
#include <string.h>
//the func help to encode and to decode

void encode_decode_help(char *p,int k,int num){
    //help the encode and the decode

    for (int j=0;(j<(int) strlen(p));j+=1){
        char f;
        char l;
        int check =num;
        if (p[j] >= LOWER_L_FIRST && p[j]<=LOWER_L_UP){
                check =2;
        }
        else if (UPPER_L_FIRST<=p[j] && UPPER_L_LAST >= p[j]) {
          check =3;
        }
        const int num=26;
        if (check !=0) {
            if (check==2){
                l=LOWER_L_UP;
                f=LOWER_L_FIRST;
                if (k <= 0) {
                    *(p + j) = - ((-(*(p + j) + k) + l) % num)+ l;
                } else if (k > 0) {
                    *(p + j) = (((*(p + j) + k) - f) % num)+ f ;
                }
            }
            if (check==3){
                l = UPPER_L_LAST;
                f = UPPER_L_FIRST;
                if (k <= 0) {
                    //to change the letter
                    *(p + j) = - ((-(*(p + j) + k) + l) % num)+ l;
                } else if (k > 0) {
                    *(p + j) = (((*(p + j) + k) - f) % num)+ f ;
                }
            }}
    }
}
// See full documentation in header file
void decode (char s[], int k)
{
    int num =0;
    encode_decode_help(s,-k,num);
}
void encode (char s[], int k){
    int num =0;
    encode_decode_help(s,k,num);

}