#include "music.h"

void addNewElement(FILE* f){
    Music music = inputMusic();;
    f = fopen("dat.txt","a");
    fprintf(f, "%s", music.name);
    fprintf(f, "%s", music.artist);
    fprintf(f, "%d\n", music.duration);
    fprintf(f, "%d\n", music.rank);
    fclose(f);
}

Music inputMusic(){
    Music res;
    printf("Name: ");
    fgets(res.name, LEN, stdin);
    printf("Artist: ");
    fgets(res.artist, LEN, stdin);
    printf("Duration: ");
    scanf("%d", &res.duration);
    getchar();
    printf("Rank: ");
    scanf("%d", &res.rank);
    getchar();
    return res;
}


void printFile(FILE* f){
    Music res;
    f = fopen("dat.txt","r");
    fgets(res.name, LEN, f);
    while(!feof(f)){
        fgets(res.artist, LEN, f);
        fscanf(f,"%d", &res.duration);
        fgetc(f);
        fscanf(f,"%d", &res.rank);
        fgetc(f);
        printf("Name: %s", res.name);
        printf("Director: %s", res.artist);
        printf("Duration: %d\n", res.duration);
        printf("Rank: %d\n", res.rank);
        fgets(res.name, LEN, f);
        printf("\n");
    }
    fclose(f);
}

void sortByName(FILE* f){
   int length;
   Music* res = getRecordsFromFile(f, &length);
   if (res){
       sortMusicByName(res, length);
       writeRecordsArrayInFile(f, res, length);
       free(res);
   }
   else
       printf("Error!");
}

Music* getRecordsFromFile(FILE* f, int* count){
    *count = 0;
    f = fopen("dat.txt","r");
    Music* res = malloc(sizeof (Music) * LEN);
    int i;
    if(res){
        for (i = 0; !feof(f) && res; i++){
            *(res + i) = getRecordFromFile(f);
            if(i % LEN == 0){
                res = realloc(res,sizeof (Music) * (LEN + i));
            }
        }
        *count = i - 1;
    }
    fclose(f);
    return res;
}

Music getRecordFromFile(FILE* f){
    Music res;
    fgets(res.name, LEN, f);
    if(!feof(f)){
        fgets(res.artist, LEN, f);
        fscanf(f,"%d", &res.duration);
        fgetc(f);
        fscanf(f,"%d", &res.rank);
        fgetc(f);
    }
    return res;
}

void sortMusicByName(Music* music, int count){
    for (int i = 0; i < count - 1; i++){
        for (int j = i+1; j < count; j++){
            if(strcmp((music+i)->name, (music+j)->name) > 0)
                swap((music+i), (music+j));
        }
    }
}

void swap(Music* music1, Music* music2){
    Music tmp = *music1;
    *music1 = *music2;
    *music2 = tmp;
}

void writeRecordsArrayInFile(FILE* f, Music* music, int count){
    f = fopen("dat.txt","w");
    for (int i = 0; i < count; i++){
        fprintf(f, "%s", (music+i)->name);
        fprintf(f, "%s", (music+i)->artist);
        fprintf(f, "%d\n", (music+i)->duration);
        fprintf(f, "%d\n", (music+i)->rank);
    }
    fclose(f);
}

char* getArtist(){
    char* res = malloc(sizeof(char) * LEN);
    if (res){
        printf("Enter artist\n");
        fgets(res, LEN, stdin);
    }
    return res;
}

int getNumOfMusicWithArtist(Music* music, int length){
    int result = ERROR;
    char* artist = getArtist();
    for(int i = 0; i < length; i++){
        if(!strcmp((music + i)->artist, artist))
            result = i;
    }
    free(artist);
    return result;
}

void deleteElement(FILE* f){
    int length;
    Music* music = getRecordsFromFile(f, &length);
    if (music){
        int num = getNumOfMusicWithArtist(music, length);
        if(num != ERROR){
            for (int i = num; i < length - 1; i++)
                *(music + i) = *(music + i + 1);
            writeRecordsArrayInFile(f, music, length - 1);
        }
        else
            printf("Error! \n");
        free(music);
    }
    else
        printf("Error! \n");
}
