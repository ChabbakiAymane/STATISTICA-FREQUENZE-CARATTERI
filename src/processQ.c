#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "processQ.h"
#include "common.h"

int startProcessQ(int M, string filePath[], int firstFilePos, int lastFilePos, int j, int pipeWriteToP[2]) {
    double n, l, cl, s, o;
    string dataString;

    #ifdef DEBUG
    printf("%s: work\n",procName);
    #endif


    //TODO: lettura dati file


    close(pipeWriteToP[READ]); //chiude il canale di lettura -> scrive

    //dati simulati
    n = l = cl = s = o = 0.2;
    dataString = getStringFromData(n, l, cl, s, o);
    writeToPipe(pipeWriteToP[WRITE], dataString);
    close(pipeWriteToP[WRITE]);

    #ifdef DEBUG
    printf("%s: scritto su pipe\n",procName);
    #endif

    return 0;
}