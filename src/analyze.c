#include <stdio.h>
#include <unistd.h> //pipe()
#include <stdlib.h> //exit()
#include <string.h>
#include <wait.h>

#include "processP.h"
#include "processQ.h"
#include "myTypes.h"
#include "common.h"


/* Prende in input gli argomenti passati al programma ed estrae 
 * n, m e la lista dei path dei file da analizzare (e il loro numero).
 * restituisce:
 *      0 se è andato a buon fine
 *      1 se errore...
 */
int calculateArgs(int argc, string argv[], int *N, int *M, string *filePath, int *numFile);

int main(int argc, string argv[]) {
    int ret = 0;

    //dati percentuali
    double n, l, cl, s, o;
    string dataString;

    int N = 3, M = 4; 
    string *filePath;
    int numFile;
    int result;

    #ifdef DEBUG
    strcpy(procName,"ANALYZER\0");
    printf("%s: begin\n",procName);
    #endif

    result = calculateArgs(argc, argv, &N, &M, filePath, &numFile);

    #ifdef DEBUG
    printf("%s: lista file calcolata\n",procName);
    #endif

    if(result != 0) {
        ret = 1;
        printf("Errore: argomenti errati\n");
        //TODO: messaggio help
    } else {

        #ifdef DEBUG
        printf("%s: creazione processi P\n",procName);
        #endif

        //TODO: problema numFile < n
        int i;
        int pipeReadFromP[N][2]; //comunicazione da Pi a Analyze

        for(i = 0; i < N; i++) {
            //inizializza pipe per comunicazione da figlio Pi
            myPipe(pipeReadFromP[i]);
            if(myFork() == 0) {
                //CODICE FIGLIO Pi

                #ifdef DEBUG
                sprintf(procName,"P%d\0",i);
                printf("%s: begin\n",procName);
                #endif

                int code;
                code = startProcessP(N, M, filePath, numFile, i, pipeReadFromP[i]); //TODO: casi errore

                #ifdef DEBUG
                printf("%s: end\n",procName);
                #endif

                exit(code);
            }
            //PADRE Analyzer
            close(pipeReadFromP[i][WRITE]);//chiude il canale di scrittura -> legge
        }

        //attende i dati da tutti P
        double nPar, lPar, clPar, sPar, oPar; //parziali
        for(i = 0; i < N; i++){

            #ifdef DEBUG
            printf("%s: leggo da pipe di P%d\n",procName,i);
            #endif

            dataString = readFromPipe(pipeReadFromP[i][READ]);
            getDataFromString(dataString, &nPar, &lPar, &clPar, &sPar, &oPar);
            
            #ifdef DEBUG
            printf("%s: letto da pipe di P%d\n",procName,i);
            #endif

            //chiude la pipe, una volta che ha finito di leggere
            close(pipeReadFromP[i][READ]);

            n += nPar/N;
            l += lPar/N;
            cl += clPar/N;
            s += sPar/N;
            o += oPar/N;
        }

        //TODO: output dati / invio dati a Report
        printf("Numeri: %.1f\%\n",n*100);
        printf("Lettere minuscole: %.1f\%\n",l*100);
        printf("Lettere maiuscole: %.1f\%\n",cl*100);
        printf("Spazi: %.1f\%\n",s*100);
        printf("Altri caratteri: %.1f\%\n",o*100);

        //attende la terminazione di tutti i Pi
        for(i = 0; i < N; i++){
            wait(NULL);
        }
    }

    #ifdef DEBUG
    printf("%s: end\n",procName);
    #endif

    return ret;
}

int calculateArgs(int argc, string argv[], int *N, int *M, string *filePath, int *numFile) {
    return 0;
}