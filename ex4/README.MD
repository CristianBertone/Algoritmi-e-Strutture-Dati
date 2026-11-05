## Esercizio 4: Struttura del Grafo e Visita in Ampiezza

### Scelte Implementative
L'implementazione richiede una struttura dati che sia **ottimizzata per grafi sparsi** (evitando sprechi di memoria per archi inesistenti) ma che garantisca operazioni di ricerca con **complessità O(1)**. 

Le strutture viste a lezione presentano dei limiti in questo caso:
* **Matrice di adiacenza:** Garantisce tempi di accesso O(1), ma alloca spazio per ogni possibile collegamento (creando una matrice N x N). Su una mappa reale, questo comporterebbe un enorme spreco di memoria per memorizzare archi nulli (paesi che non hanno una connessione).
* **Liste di adiacenza:** Ottimizzano la memoria allocando solo gli archi realmente esistenti. Tuttavia, la ricerca di uno specifico arco richiede lo scorrimento della lista, portando la complessità a O(N).

###  Hash Table Annidate
Per unire i vantaggi di entrambe le soluzioni, abbiamo sostituito le liste di adiacenza con l'implementazione della **Hash Table** (sviluppata nell'Esercizio 2), creando una struttura annidata:

1. **Hash Table Principale:** Agisce da contenitore per tutti i nodi del grafo.
2. **Hash Table Secondarie:** Il valore associato a ogni nodo nella tabella principale è un'ulteriore Hash Table, contenente  i vicini di quel nodo e la relativa etichetta (i km di distanza tra id ue paesi).

### Gestione dei Grafi Orientati e Non Orientati
La struttura di base implementa un grafo orientato. Per supportare i grafi non orientati (necessari per analizzare il dataset `italian_dist_graph.csv`), il codice inserisce automaticamente un arco di ritorno simmetrico (da B ad A, copiando il peso originario) ogni volta che viene aggiunto un nuovo arco da A a B, mantenendo la coerenza dei dati in modo trasparente.