# STATISTICA-FREQUENZE-CARATTERI
Sistema che gestisce le statistiche della frequenza dei caratteri all’interno di file(s) di testo distinguendo almeno lettere, cifre, spazi, punteggiatura e altri caratteri, eventualmente realizzando anche dei “cluster” (ad esempio computo con distinzione di maiuscole e minuscole oppure aggregati).

Un processo C (“Counter”) principale tiene traccia dei conteggi (ricevendo quindi i dati) i quali devono essere eseguiti da processi separati da esso generati “P_i”, i ∈ {k|1 ≤ k ≤ n} k, n ∈ ℵ che si occupano di gestire ciascuno un sottoinsieme degli input (partizionato in “n” sottogruppi) creando a sua volta “m” figli “Q_{i,j}”, j ∈ {k|1 ≤ k ≤ m} k, m ∈ ℵ (che sono gli unici ad accedere effettivamente ai file da analizzare):
  - ogni processo Q_{i,j} analizza uno spezzone di ogni file di input a cui accede. “n” ed “m” hanno come valore di default rispettivamente 3 e 4 ma possono essere passati come argomenti.

![alt text](https://github.com/ChabbakiAymane/STATISTICA-FREQUENZE-CARATTERI/blob/main/progettoFrequenzaChar.png)

Ponendo n=3 ed m=4, si analizzano 8 files che sono suddivisi in 3 gruppi dati in gestione ai processi P_1, P_2 e P_3:
  - Ad esempio P1 si occupa di analizzare i files F_1, F_2 e F_3 creando 4 sottoprocessi.

Ogni file di testo è “spezzato” quindi in 4n parti (dall’inizio del file a un quarto della sua lunghezza, dal carattere successivo fino a metà, dal carattere successivo fino a tre quarti della sua lunghezza e la parte restante): 
  - per esempio il file F_1 è suddiviso in F_{1,1}, F_{1,2}, F_{1,3}, e F_{1,4} che sono rispettivamente analizzati dai sottoprocessi Q_{1,1}, Q_{1,2}, Q_{1,3}, e Q_{1,4}.

Ogni sottoprocesso Q_{i,j} analizza dunque singole parti di files e i suoi conteggi devono essere passati a un gestore (può essere direttamente P_i) che ricompone questi risultati parziali che a loro volta sono passati a un gestore “globale” (che può essere il processo principale).
Ovviamente uno dei gruppi del partizionamento dell’input e una delle parti in cui sono suddivisi gli input potrebbe avere dimensione diversa dagli altri, oltre al fatto che alcuni di questi sottoinsiemi possono essere anche vuoti (se ad esempio si hanno solo due files di input ed n è pari a 3). I contenuti da analizzare possono essere forniti dando in input direttamente uno o più file oppure una cartella (per cui se ne deve analizzare il contenuto) sia al momento dell’avvio ma anche successivamente comunicando dati aggiornati.

Occorre poter:
  - passare dati di input al primo avvio (almeno contenuti da analizzare e parametri n ed m).
  - ricevere un feedback ordinato (ad esempio una “stampa a video” a mo’ di tabella) con le statistiche (frequenze dei caratteri e percentuali) e un riepilogo degli input (cartelle/files e conteggi) prevedendo qualche forma di aggregazione in modo da rendere comprensibile il report.
  - passare nuovi input aggiuntivi, rimuovere o forzare un riconteggio di quelli presenti selettivamente e modificare i valori di n ed m dinamicamente
  
Le azioni di analisi (statistica effettiva implementata con il sistema di processi già descritto) e report (richiesta feedback) si dovrebbero svolgere invocando eseguibili distinti che poi interagiscono tra loro. L’intera applicazione dovrebbe essere avviata da un ulteriore processo generale M che funge anche da shell interattiva in cui l’utente può inserire dei comandi testuali per:
  - Presentare la situazione al primo avvio
  - Visualizzare dei report a video in modalità differenti (statistiche generali, per cluster, altro…)
  - Modificare i parametri “on-the-fly”

L’applicazione ideale comprende quindi almeno:
  - Un processo/sottosistema “A” (“Analyzer”) per calcolare le statistiche (che coincide o comprende l’albero descritto con C, P… e Q…)
  - Un processo/sottosistema “R” (“Report”) per recuperare le informazioni
  - Un processo/sottosistema “M” (“Main”) principale per la gestione generale: ha solo funzione di “gateway” e interfaccia-utente. DEVE richiamare gli altri due processi/sottosistemi di seguito indicati (che devono essere utilizzabili anche autonomamente direttamente da cli).

---
Per ulteriori informazioni vedere il file: [*progettoFrequenzaCaratteri.pdf*](https://github.com/ChabbakiAymane/STATISTICA-FREQUENZE-CARATTERI/blob/main/progettoFrequenzaCaratteri.pdf) 
