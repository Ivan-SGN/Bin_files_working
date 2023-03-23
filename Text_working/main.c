#include <stdio.h>
#include <stdlib.h>
#include "music.h"
#define ADD 1
#define PRINT 2
#define SORT 3
#define DELETE 4
#define EXIT 5

int main(){
    FILE* f = NULL;
    int number = 0;
    while(number != EXIT){
        printf("enter number:\n 1 for add new elem \n 2 for print data \n 3 for sort file \n 4 for delete elem \n 5 for exit\n");
        scanf("%d", &number);
        getchar();
        switch (number){
            case ADD:
                addNewElement(f);
                break;
            case PRINT:
                printFile(f);
                break;
            case SORT:
                sortByName(f);
                break;
            case DELETE:
                deleteElement(f);
                break;
        }
    }
    return 0;
}

