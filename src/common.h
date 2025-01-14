#include <sys/types.h>

#include "myTypes.h"

#ifdef DEBUG
char procName[10];
#endif

pid_t myFork();

int myPipe(int fd[2]);

float myRound(float n);

/**
 * Salva le percentuali sotto forma di stringa (percentuali separate da SEPARATOR, termina con END)
 * n  - %numeri
 * l  - %lettere minuscole
 * cl - %lettere maiuscole
 * s  - %spazi
 * o  - %altri caratteri
 * 
 * return - dati salvati nella stringa
 */
string getStringFromData(double n, double l, double cl, double s, double o);


/**
 * Ottiene le informazioni sulle percentuali dalla stringa codificata (percentuali separate da SEPARATOR, termina con END)
 * dataString - stringa codificata
 * 
 * Output:
 * n  - %numeri
 * l  - %lettere minuscole
 * cl - %lettere maiuscole
 * s  - %spazi
 * o  - %altri caratteri
 */
void getDataFromString(string dataString, double *n, double *l, double *cl, double *s, double *o);

/**
 * Scrive i dati sotto forma di stringa nella pipe.
 * Gestisce errori pipe.
 * 
 * pipeWriteSide - lato in scrittura della pipe
 * dataString    - informazioni da passare
 */
void writeToPipe(int pipeWriteSide, string dataString);

/**
 * Legge i dati sotto forma di stringa nella pipe.
 * Gestisce errori pipe.
 * 
 * pipeReadSide - lato in lettura della pipe
 * 
 * return - informazioni sotto forma di stringa
 */
string readFromPipe(int pipeReadSide);

/**
 * Funzione per la rimozione di una sottostringa
 * 
 * string - stringa in input
 * 
 * sub - sottostringa di cui si vuole la rimozione
 */
void removeSubstr (char *string, char *sub);