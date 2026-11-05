# Esercizio 2 - Tavola Hash

## 1. Processo di sviluppo e interazione con l'IA
Per lo sviluppo di questo esercizio abbiamo utilizzato un LLM come supporto per scrivere la struttura dati e i test, controlando passo dopo passo il codice generato. 

Le principali iterazioni e correzioni sono state:
- **Struttura base:** L'IA ha fornito una tabella hash a capacità fissa basata su liste di concatenamento e i prototipi richiesti (`hash_table_create`, `hash_table_put`, ecc.).

- **Problema di complessità:** Ci siamo accorti che una capacità fissa avrebbe fatto degradare le prestazioni da $O(1)$ a $O(N)$ con dataset enormi. Abbiamo quindi introdotto il ridimensionamento dinamico (*rehashing*) per rispettare i vincoli di complessità richiesti.

- **Svolgimento del progetto** Durante lo sviluppo, il progetto ha attraversato tre iterazioni principali. La prima versione prevedeva una hash table di dimensioni ridotte che non superava i test di complessità. Aumentando notevolmente la dimensione fissa, la seconda versione passava tutti i controlli, tuttavia, per evitare cali di prestazioni con file di testo molto più grandi, abbiamo deciso di implementare una tabella a dimensione variabile, garantendo così una complessità fissa in ogni situazione.