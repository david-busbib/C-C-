#include "cipher.h"
#include "tests.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR 1025
#define FIVE 5
#define TWO 2


int check_test(){//check the test that we did in the other file test.h
    if (test_decode_cyclic_lower_case_special_char_positive_k()==0 && \
        test_encode_cyclic_lower_case_special_char_positive_k()==0 &&\
        test_decode_non_cyclic_lower_case_positive_k()==0 && \
        test_decode_cyclic_lower_case_negative_k()==0 && \
        test_encode_non_cyclic_lower_case_positive_k ()==0 && \
        test_encode_non_cyclic_lower_case_special_char_negative_k () ==0 && \
        test_decode_non_cyclic_lower_case_special_char_negative_k () ==0 && \
        test_decode_cyclic_upper_case_positive_k () ==0 && \
        test_encode_cyclic_upper_case_positive_k () ==0 && \
        test_encode_cyclic_lower_case_negative_k () ==0 ){
        return EXIT_SUCCESS;
    }
    else{
        return  EXIT_FAILURE;
    }
}
int check_1(int argc) {

    if (argc != FIVE && argc != TWO) {
        //check if the argumant num is currect
        fprintf(stderr,"The program receives 1 or 4 arguments only.\n");
        return EXIT_FAILURE;
    }
    return 0;
}
int main (int argc, char *argv[]){
    if(check_1(argc)==1)
    {return EXIT_FAILURE; }
    if (argc == 2){
        if (strcmp(argv[1],"test")!=0)
        {fprintf(stderr,"Usage: cipher test\n");
            return EXIT_FAILURE; }
        { return check_test(); }
        }
    if (strcmp(argv[1],"decode") !=0 && strcmp(argv[1],"encode")!=0){
        fprintf(stderr,"The given command is invalid.\n");
        return EXIT_FAILURE;
    }
    const char *s = argv[2];
    for (int i=0;i< (int)strlen(argv[2]);++i){
        if (i==0 && s[i] == '-'){
            continue;
        }
        if (isdigit(s[i])==0){
            //check if the letter is letter and nut sumthing else
            fprintf(stderr,"The given shift value is invalid.\n");
            return EXIT_FAILURE;
        }
    }
    FILE *fptr;
    FILE *out_f;

    fptr = fopen(argv[3],"r");

    if (!fptr)
    {
      fprintf(stderr,"The given file is invalid.\n");
        return EXIT_FAILURE;
    }
    out_f = fopen(argv[4],"w");
    if (!out_f){
      return NULL;
    }
    int num = strtol(argv[2], NULL, 10);
    char line[MAX_STR]={0};
    while(fgets(line,MAX_STR,fptr))
    {
        if (strcmp(argv[1],"decode") ==0) {
            decode(line, num);
            fputs(line,out_f);
        }
        else {
        encode(line,num);
        fputs(line,out_f);
        }
    }
        fclose(fptr);
        fclose(out_f);
        return 0;
}

