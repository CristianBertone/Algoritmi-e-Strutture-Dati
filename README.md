# Progetto di Algoritmi e Strutture Dati

Questo repository contiene quattro progetti sviluppati per il corso di Algoritmi e Strutture Dati. Ogni esercizio si trova in una cartella dedicata (`ex1`, `ex2`, `ex3`, `ex4`), all'interno della quale è presente un `README.md` specifico con l'analisi dettagliata, le scelte implementative e i risultati dei test.

Di seguito una breve panoramica dei progetti e le istruzioni generali per compilarli ed eseguirli.

## Esercizio 1: Algoritmo di Ordinamento Ibrido
Implementazione di un algoritmo di ordinamento generico che combina **QuickSort** e **SelectionSort**. L'algoritmo passa automaticamente da QuickSort a SelectionSort quando la dimensione della porzione di array da ordinare scende sotto una soglia `k` definita dall'utente.

*   **Compilazione:** Entrare in `ex1/` ed eseguire `make all`.
*   **Esecuzione Test:** Dalla cartella `ex1/` eseguire `./bin/test_ex1`
*   **Esecuzione Programma:** Dalla cartella `ex1/` eseguire `./bin/main_ex1 <input_file> <output_file> <field> <k>`
    *   *Esempio:* `./bin/main_ex1 records.bin sorted_output.bin 1 50`

## Esercizio 2: Tavole Hash (con concatenamento)
Sviluppo di una libreria generica per **Tavole Hash** basate sul concatenamento, realizzata con il supporto di un LLM. Il programma principale utilizza questa struttura per trovare la parola più frequente (sopra una certa lunghezza minima) all'interno di un testo (es. l'Iliade).

*   **Compilazione:** Entrare in `ex2/` ed eseguire `make all`.
*   **Esecuzione Test:** Dalla cartella `ex2/` eseguire `./bin/test_ex2`
*   **Esecuzione Programma:** Dalla cartella `ex2/` eseguire `./bin/main_ex2 <percorso_file_testo> <lunghezza_minima>`
    *   *Esempio:* `./bin/main_ex2 /tmp/data/iliade.txt 6`

## Esercizio 3: Heap Ternario e Coda con Priorità
Implementazione di una **Priority Queue** (Coda con Priorità) basata su un **Heap Ternario** (un albero in cui ogni nodo padre ha fino a tre figli). Viene utilizzata per simulare un sistema di scheduling di processi non-preemptive leggendo i task da un file CSV.

*   **Compilazione:** Entrare in `ex3/` ed eseguire `make all`.
*   **Esecuzione Test:** Dalla cartella `ex3/` eseguire `./bin/test_ex3`
*   **Esecuzione Programma:** Dalla cartella `ex3/` eseguire `./bin/main_ex3 <input_file> <output_file>`
    *   *Esempio:* `./bin/main_ex3 tasks.csv risultati.csv`

## Esercizio 4: Grafi Sparsi e Visita in Ampiezza
Realizzazione di una struttura dati **Grafo** ottimizzata per dati sparsi, sfruttando la Tavola Hash implementata nell'Esercizio 2. La libreria gestisce grafi diretti o non diretti, etichettati e non etichettati.
Oltre alla struttura, è implementato l'algoritmo di **Visita in Ampiezza (Breadth-First Search)**. Il programma principale carica un grafo delle distanze tra località italiane da un file CSV e salva su un file di testo l'ordine di visita delle città partendo da un nodo specificato.

*   **Compilazione:** Entrare in `ex4/` ed eseguire `make all`.
*   **Esecuzione Test:** Dalla cartella `ex4/` eseguire `./bin/test_ex4`
*   **Esecuzione Programma:** Dalla cartella `ex4/` eseguire `./bin/main_ex4 <file_csv_input> <città_partenza> <file_output>`
    *   *Esempio:* `./bin/main_ex4 italian_dist_graph.csv torino output.txt`