# Esercizio 3: Coda con Priorità (Heap Ternario) e Scheduler

Questo progetto contiene l'implementazione di una Coda con Priorità, costruita utilizzando un Heap Ternario.

## La Hash Table e il supporto dell'IA
Per assicurarci che le funzioni di ricerca (`contains`) e rimozione (`remove`) abbiano complessità costante, abbiamo collegato all'heap la Hash Table che avevamo già scritto nell'Esercizio 2. 

Poiché far comunicare l'array dell'heap con la mappa generava molti problemi con i puntatori, **abbiamo utilizzato l'Intelligenza Artificiale come strumento di supporto e tutoraggio** per capire come gestire le logiche più complesse. In particolare, grazie a questo aiuto abbiamo capito come implementare:

* **La Sincronizzazione continua:** Ogni volta che l'heap sposta un elemento per mettersi in ordine, la Hash Table viene aggiornata in automatico per ricordarsi la nuova posizione di quel dato.
* **Risoluzione problema puntatore vuoto:** La mappa confondeva l'elemento in cima all'heap (che sta all'indice `0` dell'array) con un puntatore vuoto (`NULL`), causando errori. Per risolvere il problema, quando l'indice viene salvato nella mappa gli viene aggiunto un `+1` fittizio, che poi viene sottratto al momento della lettura.

## Il funzionamento dello Scheduler
Il programma `main` legge una lista di task e simula un processore che li esegue rispettando la loro priorità.

* **Lettura dinamica:** I task vengono letti da un file CSV. Siccome non sappiamo in anticipo quante righe ci siano, l'array si allarga da solo man mano che legge. Finito di leggere, i task vengono messi in fila in base al loro orario di arrivo.
