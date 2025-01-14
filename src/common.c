#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <fcntl.h>

#include "common.h"
#include "myTypes.h"

pid_t myFork() {
    //TODO: gestione errori fork
    pid_t pid = fork();
    return pid;
}

int myPipe(int fd[2]) {
    //TODO: gestione errori pipe
    return pipe(fd);
}

float myRound(float n){
    int res;
    int integerPart = n; //tronca cifre decimali
    float decimalPart = n - integerPart;

    if(decimalPart >= 0.5) {
        integerPart++;
    }

    return integerPart;
}

string getStringFromData(double n, double l, double cl, double s, double o) {
    //sprintf(stringa,"%f",number); -> convertire double to string, funziona meglio con char[dim] che con string 
    //strcat(stringa1,stringa2); -> concatenare due stringhe(stringa 2 concatenate a stringa1), funziona se stringa1=char[]
    string result;
    //stringa in cui tengo le concatenazioni, uso un vettore di char perche con string la funzione concat non funziona, da cambiare la dim iniziale
    char output[BUFSIZE]="";
    char tmp[50]="";   
    //metto gli input in un array
    double input[5]={n,l,cl,s,o};
    int i;
    for(i=0;i<5;i++){       
        strcpy(tmp,"");
        //converto il double in stringa
        sprintf(tmp,"%1.1f",input[i]);
        //unico modo che ho pensato al momento per evitare di mettere il separatore anche alla fine
        if(i<4) strcat(tmp,SEPARATOR);
        //concateno la stringa ottenuta con la stringa totale
        strcat(output,tmp);
    }
    //aggiungo il carattere di end alla fine della stringa
    strcat(output,END);
    //copio il contenuto in una stringa
    result=output;
    return result;
}

void getDataFromString(string dataString, double *n, double *l, double *cl, double *s, double *o) {
    //double number=atof(stringa); -> converte la stringa in double

   char stringa[50];
   char stringa_mod[50];
   strcpy(stringa,dataString);
   //printf("%s",stringa);
   //vettore di puntatori degli input
   double* input[5]={n,l,cl,s,o};
   string substring;
   double tmp;
   int i;
   for(i=0;i<5;i++){
       strcpy(stringa_mod,stringa);
       //prelevo il carattere fino al primo SEPARATOR trovato
       substring=strtok(stringa_mod,SEPARATOR);
       //converto la sottostringa in double
       tmp=atof(substring);
       //salvo il valore trovato
       *input[i]=tmp;
       //rimuovo la sottostringa
       removeSubstr(stringa,strcat(substring,SEPARATOR));
   }

}

void writeToPipe(int pipeWriteSide, string dataString){
    int res = write(pipeWriteSide,dataString,BUFSIZE);
    if(res == -1){
        #ifdef DEBUG
        printf("%s: Errno: %d\n",procName,errno);
        #endif
        perror("Errore: writeToPipe");
    }
}


string readFromPipe(int pipeReadSide){
    char data[BUFSIZE];
    string dataString = (string) malloc(sizeof(char)*BUFSIZE);
    int res = read(pipeReadSide,data,BUFSIZE);
    if(res == -1){
        #ifdef DEBUG
        printf("%s: Errno: %d\n",procName,errno);
        #endif
        perror("Errore: readFromPipe");
    }
    strcpy(dataString,data);
    return dataString;
}

//funzione per la rimozione di sottostringhe
void removeSubstr (char *string, char *sub) {
    char *match = string;
    int len = strlen(sub);
    while ((match = strstr(match, sub))) {
        *match = '\0';
        strcat(string, match+len);
        match++;
    }
}
