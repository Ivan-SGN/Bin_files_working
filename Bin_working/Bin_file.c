//
//  Bin_file.c
//  12
//
//  Created by Макаров Иван on 15.12.2021.
//  Copyright © 2021 Макаров Иван. All rights reserved.
//

#include "Bin_file.h"
Music readRecordInFile(FILE* f, int index){
    fseek(f, sizeof(Music) * index, SEEK_SET);
    Music result;
    fread(&result, sizeof(Music), 1, f);
    rewind(f);
    return result;
}

long getRecordsCountInFile(FILE* f){
    return getFileSizeInBytes(f) / sizeof(Music);
}

long getFileSizeInBytes(FILE* f){
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    return size;
}

void printFile(FILE* f){
    rewind(f);
    unsigned long count = getRecordsCountInFile(f);
    for (int i = 0; i < count; i++){
        Music result  = readRecordInFile(f, i);
        printMusic(&result);
        printf("\n");
    }
    rewind(f);
    fflush(f);
}

void generateData(FILE* f){
    Music  music[TEST_RECORD_COUNT] = {
        { "Co2", "Jeembo", 3.26, 1 },
        { "Feelz", "Veeta", 2.12, 2 },
        { "Super Truper", "Abba", 4.11, 3 },
        { "Zabludshiy", "Unnv", 2.02, 4 },
        { "Technologic", "Daft Punk", 4.44, 5 }
    };
    fwrite(music, sizeof(Music), TEST_RECORD_COUNT, f);
    rewind(f);
    fflush(f);
}

void printMusic(Music* music){
    printf("Name: %s\n", music->Name);
    printf("Artist: %s\n", music->Artist);
    printf("Duration: %.2f\n", music->Duration);
    printf("Rank: %d\n", music->Rank);
}

void writeRecordInFile(FILE* f, const Music* music, int index){
    fseek(f, sizeof(Music) * index, SEEK_SET);
    fwrite(music, sizeof(Music), 1, f);
    fflush(f);
    rewind(f);
}

void AddNewRecordInEnd(FILE* f){
    Music res;
    printf("enter Name:\n");
    scanf("%s", res.Name);
    getchar();
    printf("enter Artist:\n");
    scanf("%s", res.Artist);
    getchar();
    printf("enter Duration:\n");
    scanf("%f", &res.Duration);
    int count  = getRecordsCountInFile(f);
    res.Rank = count+1;
    writeRecordInFile(f, &res, count);
    fflush(f);
    rewind(f);
}

void removeRecordFromFile(FILE* f, int index){
    rewind(f);
    int count = getRecordsCountInFile(f);
    for (int i = index + 1; i < count; i++)
    {
        Music music = readRecordInFile(f, i);
        writeRecordInFile(f, &music, i - 1);
    }
    int newFileSize = (count - 2) * sizeof(Music);
    setFileSize(f, newFileSize);
    rewind(f);
}

void setFileSize(FILE* f, long newSize){
    int fileDescriptor = fileno(f);
    truncate(fileDescriptor, newSize);
}

void swapRecordsInFile(FILE* f, int index1, int index2){
    Music m1 = readRecordInFile(f, index1);   // Student s1 = students[index1]
    Music m2 = readRecordInFile(f, index2);   // Student s2 = students[index2]
    writeRecordInFile(f, &m1, index2);          // students[index1] = s2
    writeRecordInFile(f, &m2, index1);          // students[index2] = s1
}

void sortFile(FILE* f, int (*compareRecords)(const Music* record1, const Music* record2)) {
    rewind(f);
    int count = getRecordsCountInFile(f);
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count - i - 1; j++)
        {
            Music record1, record2;
            record1 = readRecordInFile(f, j);
            record2 = readRecordInFile(f, j+1);
            if (compareRecords(&record1, &record2))
                swapRecordsInFile(f, j, j+1);
        }
    
    rewind(f);
}

int compare_by_name(const Music* res1, const Music* res2){
    return (strcmp(res1->Name, res2->Name) > 0) ? (1) : (0);
}

int compare_by_duration(const Music* res1, const Music* res2){
    return (res1->Duration > res2->Duration) ? (1) : (0);
}
