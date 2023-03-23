//
//  Bin_file.h
//  12
//
//  Created by Макаров Иван on 15.12.2021.
//  Copyright © 2021 Макаров Иван. All rights reserved.
//

#ifndef Bin_file_h
#define Bin_file_h
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define LEN 255
#define TEST_RECORD_COUNT 5

typedef struct Musics{
    char Name[LEN];
    char Artist[LEN];
    float Duration;
    int Rank;
}Music;

void writeRecordInFile(FILE* f, const Music* music, int index);
Music readRecordInFile(FILE* f, int index);
void printАile(FILE *pfile);
long getRecordsCountInFile(FILE* f);
void generateData(FILE* f);
void printFile(FILE *pfile);
long getFileSizeInBytes(FILE* f);
void printMusic(Music* music);
void AddNewRecordInEnd(FILE* f);
void removeRecordFromFile(FILE* f, int index);
void setFileSize(FILE* f, long newSize);
void swapRecordsInFile(FILE* f, int index1, int index2);
int compare_by_name(const Music* res1, const Music* res2);
int compare_by_duration(const Music* res1, const Music* res2);
void sortFile(FILE* f, int (*compareRecords)(const Music* record1, const Music* record2));

#endif /* Bin_file_h */
