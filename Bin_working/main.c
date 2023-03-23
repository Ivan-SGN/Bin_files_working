#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Bin_file.h"


int main(){
    int index, number = 0, key = 0;
    FILE* f = fopen("music.bin", "rb+");
    if (f == NULL){
        f = fopen("music.bin", "rb+");
        printf("error");
        fclose(f);
        f = fopen("music.bin", "rb+");
        return 0;
    }
    while (number != 6){
        printf("enter number:\n 1 for add new elem \n 2 for print data \n 3 for sort file \n 4 for delete elem \n 5 for generate data\n 6 for exit\n");
        scanf("%d", &number);
        switch (number){
            case 1:
                printf("Enter student\n");
                AddNewRecordInEnd(f);
                break;
            case 2:
                printf("Print on screen\n");
                printFile(f);
                break;
            case 3:
                printf("Choose: 1 - sort by name ; 2 - sort by duration\n");
                scanf("%d", &key);
                if (key == 1)
                    sortFile(f, compare_by_name);
                else if (key == 2)
                    sortFile(f, compare_by_duration);
                break;
            case 4:
                printf("enter index");
                scanf("%d", &index);
                removeRecordFromFile(f, index);
                break;
            case 5:
                generateData(f);
                printf("data generated:\n");
                break;
        }
    }
    fclose(f);
    getchar();
}
