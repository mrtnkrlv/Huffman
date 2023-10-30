#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*int len_file(char* fileName){
    FILE* temp = fopen(fileName, "r");
    int acc = 0;
    if (temp == NULL){
        printf("File not found\n");
        return -1;
    }
    while (!feof(temp)){
        fgetc(temp);
        ++acc;
    }
    return acc;
}*/




int main(){
    FILE* p = fopen("li_def.txt", "r");
    if (p){
        while (!feof(p)){
            char c = (char) fgetc(p);
            printf("%c", c);
        }
    }
    else printf("bla");
    fclose(p);

    exit(0);
}


