#ifndef MUSIC_H
#define MUSIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100
#define ERROR -1

typedef struct musics{
char name[LEN];
char artist[LEN];
int duration;
int rank;
} Music;

void addNewElement(FILE* f);
Music inputMusic(void);
void printFile(FILE* f);
void sortByName(FILE* f);
void sortMusicByName(Music* music, int count);
Music getRecordFromFile(FILE* f);
Music* getRecordsFromFile(FILE* f, int* count);
void swap(Music* music1, Music* music2);
char* getArtist(void);
void writeRecordsArrayInFile(FILE*f, Music* music, int count);
void deleteElement(FILE* f);
int getNumOfMusicWithArtist(Music* music, int length);

#endif // MUSIC_H
