#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

//function to return maximum power of 10 that fits into a integer
int max_pow10(int n){
    int acc = 0, store = n;
    while (store){
        ++acc;
        store/=10;
    }
    return acc-1;
}

//function to return char array containing the "byte representation" of an integer
char* itoa(int n){
    char* ans = malloc(max_pow10(n)+1);
    int store = n;
    int i = 0;
    while (store != 2){ //a code will always "start" with 2
        ans[max_pow10(n)-1-i] = store%10 + '0';
        store/=10;
        ++i;
    }
    ans[max_pow10(n)+1] = 0;
    return ans;
}

//function to write a byte into a file based on a code input
void write_byte(FILE* p, char* code, int* buffer, int* fullness){
    int track = 0;
    int len = (int) strlen(code);
    for (char c = *code++; c != 0; c = *code++){
        int bit = c - '0';
        *buffer |= bit << (7 - *fullness);
        ++(*fullness);

        if (*fullness == 8){
            fputc(*buffer, p);
            *fullness = 0;
            *buffer = 0;
        }
        ++track;
    }
}

//function to read a byte from a file and write the corresponding code in another file


/*int main(){
    FILE* p = fopen("test.bin", "wb");
    char* code = "10011010";
    int buffer = 0;
    int fullness = 0;
    write_byte(p, code, &buffer, &fullness);
    fclose(p);

    exit(0);
}*/