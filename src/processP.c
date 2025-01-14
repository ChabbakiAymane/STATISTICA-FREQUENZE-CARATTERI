#include <stdlib.h>
#include <stdio.h>

#include "processP.h"
#include "common.h"

int startProcessP(int N, int M, string filePath[], int numFile, int i, int pipeWriteToAnalyze[2]) {
    //dati percentuali
    double n, l, cl, s, o;
    string dataString;
    //con almeno un float la divisione è calcolata come float
    float tmp = ((float)numFile)/N;
    int filePerProc = (int) myRound(tmp);
    int firstFilePos = i*filePerProc;
    int lastFilePos = firstFilePos + filePerProc -1;

    if(i == N-1) { 
        //ultimo P -> deve prendere tutti i file rimanenti
        lastFilePos = numFile -1;
    }

    close(pipeWriteToAnalyze[READ]);//chiude il canale di lettura -> scrive

    #ifdef DEBUG
    printf("%s: creazione processi Q%d\n",procName,i);
    #endif
    //TODO: problema byte file < m
    int pipeReadFromQ[M][2];
    int j;
    for(j = 0; j < M; j++) {
        myPipe(pipeReadFromQ[j]);

        if(myFork() == 0){
            //CODICE FIGLIO Qij
            #ifdef DEBUG
            sprintf(procName,"Q%d-%d\0",i,j);
            printf("%s: begin\n",procName);
            #endif

            int code;
            code = startProcessQ(M, filePath, firstFilePos, lastFilePos, j, pipeReadFromQ[j]);

            #ifdef DEBUG
            printf("%s: end\n",procName);
            #endif

            exit(code);
        }
        //PADRE Pi
        close(pipeReadFromQ[j][WRITE]); //chiude il canale di scrittura -> legge
    }

    //attende i dati da tutti Qi
    double nPar, lPar, clPar, sPar, oPar; //parziali
    for(j = 0; j < M; j++){

        #ifdef DEBUG
        printf("%s: leggo da pipe di Q%d-%d\n",procName,i,j);
        #endif

        dataString = readFromPipe(pipeReadFromQ[j][READ]);
        getDataFromString(dataString, &nPar, &lPar, &clPar, &sPar, &oPar);

        #ifdef DEBUG
        printf("%s: letto da pipe di Q%d-%d\n",procName,i,j);
        #endif

        //chiude tutte la pipe con Q, una volta che ha finito di leggere
        close(pipeReadFromQ[j][READ]);

        n += nPar/M;
        l += lPar/M;
        cl += clPar/M;
        s += sPar/M;
        o += oPar/M;
    }

    //manda dati a analyzer
    dataString = getStringFromData(n, l, cl, s, o);
    writeToPipe(pipeWriteToAnalyze[WRITE], dataString);

    //chiude pipe con Analyze una volta che ha finito di scrivere
    close(pipeWriteToAnalyze[WRITE]);
    
    //attende la terminazione di tutti i Qi
    for(j = 0; j < M; j++){
        wait(NULL);
    }

    return 0; //TODO: gestione casi errore
}