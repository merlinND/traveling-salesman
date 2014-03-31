# Mathématiques discrètes - TP1

_Le problème du voyageur de commerce_

par **Merlin Nimier-David & Robin Ricard**, Binôme **B3145**

## 1. Résolution exacte

```C
// code here
```

### 1. PVC exact naif

```C
// code here
```

### 2. PVC exact Branch & Bound

```C
// code here
```

### 3. Temps d'execution

| Noeuds | Exact naif | Branch & bound |
|--------|------------|----------------|
| 5      | 9285ns     | 15459ns        |
| 10     | 152ms      | 30ms           |
| 12     | 20s        | 468ms          |

## 2. Approximation : plus proches voisins

### 1. PVC approche PPV

```C
// code here
```

### 2. Complexité

On a un algorithme contenant deux boucles imbriquées parcourant chacune les `n` noeuds.

Comme il n'y a pas de recursivité, on retrouve une complexité `n^2`.

## 3. Approximation : Algorithme Polynomial

### 1. Calcul ACM

```C
// code here
```

### 2. Explications concernant le passage de l'arbre couvrant vers le cycle

_Explications ici ..._

### 3. Cycle hamiltonien ACM

```C
// code here
```

### 4. Relation entre `L(A)` et `L(H)`

_Explications ici ..._

### 5. Relation entre `L(A)` et `L(Opt)`

_Explications ici ..._

### 6. Résultat obtenu sur les données

_Explications ici ..._

## 4. Approximation : Optimisation locale

### 1. Démonstration : `dcycle` est une distance

`dcycle` dénombre toutes les arrêtes inégales entre deux cycles différents. C'est alors un critère de discrimination entre ces deux cycles, on peut mesurer la distance entre ces deux cycles.

_A revoir, semble crapuleux ..._

### 2. Cardinal de `C(a0, 2)`

On dénombre deux cycles hamiltoniens différents : le premier avec deux arrêtes croisées et le second sans arrêtes croisées.

_A revoir, semble crapuleux ..._

### 3. Cycle Opt 2

```C
// code here
```

### 4. Utilisation sur les données

```C
// code here
```

## 5. Analyse

### 1. Mesures

| Approche                             | Noeuds | Temps d'execution | Poids    |
|--------------------------------------|--------|-------------------|----------|
| Naif                                 | 12     | 20s               | 3.31     |
| Branch & Bound                       | 12     | 475ms             | 3.31     |
| Branch & Bound                       | 15     | 45s               | 3.37     |
| PPV                                  | 15     | 0,39ms            | 4,22     |
| PPV                                  | 250    | 2,07ms            | 14,73    |
| PPV + Opt2                           | 250    | 2,21ms            | 14,56    |

### 2. Conclusion

ACM est de loin le meilleur algorithme présenté, à la fois rapide, peu consommateur de mémoire et relativement précis, il est le plus efficace pour résoudre ce genre de problème.

Dans tous les cas, pour n'importe quel algorithme de résolution par approximation, il est toujours intéressant d'ajouter une phase d'optimisation qui coûte très peu pour des améliorations non négligeables au vu du temps passé à optimiser.
