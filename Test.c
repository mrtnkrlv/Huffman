#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

int main(){
    /*FILE* p = fopen("compressed.bin", "rb");
    //buffer
    char* buffer = malloc(2);
    buffer[1] = 0;
    //len
    int len = findSize("compressed.bin")*8;
    //ans
    char* ans = malloc(len+1);
    ans[len] = 0;

    for (int i = 0; i < len; ++i){
        //printf("%c", (*buffer & 1) + '0');
        ans[len-1-i] = (*buffer & 1) + '0';
        *buffer = *buffer >> 1;
        ++tracker;
        if (tracker%8 == 0){
            //printf(" ");
            fread(buffer,1,1,p);
            tracker = 0;
        }
    }

    int acc = 7;
    fread(buffer,1,1,p);
    while (acc < len){
        int temp = acc;
        int trav = 0;
        //int sum = 0;
        for (int i = temp - 7; i < temp+1; ++i){
            //printf("%i\n", temp-trav);
            ans[temp-trav] = (*buffer & 1) + '0';
            *buffer = *buffer >> 1;
            ++trav;
            //if (!(sum%8)) printf(" ");
        }
        acc+=8;
        fread(buffer,1,1,p);
    }

    //printf("\n");
    char* fin = strrev(ans);
    int tracker = 0;
    for (int i = len-1; i > -1; --i){
        printf("%c", fin[i]);
        ++tracker;
        if (tracker%8 == 0){
            printf(" ");
        }
    }

    fclose(p);*/

    exit(0);
}