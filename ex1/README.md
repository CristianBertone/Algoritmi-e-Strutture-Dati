# Relazione Esercizio 1 - Algoritmo Ibrido (QuickSort + SelectionSort)

## Tabella dei tempi
I test sono stati fatti su 20 milioni di record. Dove non c'è il tempo significa che siamo finiti fuori tempo massimo (i 5 minuti) o ci sono stati problemi.

| k | Field 1 (ID) | Field 2 (Float) | Field 3 (Int64) | Field 4 (Stringhe) |
|---|---|---|---|---|
| 0 | 0.923 s | 2.866 s | 2.566 s | Crash / Timeout |
| 10 | 1.102 s | 3.100 s | 2.800 s | Crash / Timeout |
| 50 | 1.500 s | 3.760 s | 3.120 s | Crash / Timeout |
| 500 | 12.565 s | 20.800 s | 15.800 s | Crash / Timeout |
| 1000 | ~45.2 s | ~62.1 s | ~51.0 s | Crash / Timeout |
| 5000 | ~180 s | Timeout | Timeout | Crash / Timeout |
| 10000 | 418.251 s | Timeout | Timeout | Crash / Timeout |
| 1000000 | Timeout (>5 min) | Timeout | Timeout | Crash / Timeout |

---

## Analisi e considerazioni

### I risultati rispettano la teoria?
 Con k basso il QuickSort riduce di molto i tempi di attesa, soprattutto sugli interi. Però appena alziamo k (da 500 a salire), il SelectionSort con la sua complessità $O(n^2)$ riduce le prestazioni e i tempi si allungano molto, fino a superare il limite dei 5 minuti.

### C'è un valore di k ottimale?
Dai nostri test il QuickSort ($k=0$) con il pivot calcolato al centro è quasi sempre la scelta più veloce. L'approccio ibrido non ci ha dato grossi vantaggi sul tempo totale.
### Il vantaggio dell'ibrido si nota?
Sui numeri grandi no, per esempio su 20 milioni di record da gestire non si vedono grossi vantaggi sul tempo totale. Mentre per array piccoli la differenza è minima.

### Problemi di tempo e casi pessimi
Per evitare che il QuickSort si piantasse su dati già ordinati (andando in $O(n^2)$), abbiamo messo il pivot al centro. Però sul campo 4 la gestione delle stringhe e la memoria ci hanno dato filo da torcere, facendoci sforare il limite dei 5 minuti imposto dalla consegna.

## Analisi del problema sul Field 4 (Stringhe)

Durante i test con 20 milioni di record, il campo 4 (relativo alle stringhe) ha riscontrato problemi:
- **Segmentation Fault:** Dopo alcuni minuti di esecuzione, il programma è andato in crash a causa di errori di memoria.
- **Superamento del limite temporale:** L'ordinamento ha sforato il vincolo dei 5 minuti imposto dalla consegna.

Questo comportamento secondo noi è dovuto  all'elevato costo  della funzione `strcmp()`, che deve confrontare le stringhe byte a byte.