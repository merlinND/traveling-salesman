# Mathématiques discrètes - TP1

_Le problème du voyageur de commerce_

par **Merlin Nimier-David & Robin Ricard**, Binôme **B3145**

## 1. Résolution exacte

```C
// Partie commune

void pvc_exact_recursif(int nbVilles, double ** distances, t_cycle * chemin, t_cycle * meilleur, bool bb)
{
  if (chemin->poids > meilleur->poids && bb)
  {
    return;
  }
  else if (chemin->taille == nbVilles)
  {
    double trajetRetour = distances[chemin->c[chemin->taille -1]][0];
    if (chemin->poids + trajetRetour < meilleur->poids)
    {
      chemin->poids += trajetRetour;
      recopier_chemin(chemin, meilleur);
      chemin->poids -= trajetRetour;
    }
  }
  else
  {
    for(int i = 0; i < nbVilles; ++i)
    {
      if(!est_dans_chemin(chemin, i))
      {
        double trajet = distances[chemin->c[chemin->taille - 1]][i];
        chemin->taille++;
        chemin->poids += trajet;
        chemin->c[chemin->taille-1] = i;

        // Appel récursif
        pvc_exact_recursif(nbVilles, distances, chemin, meilleur, bb);

        // "Dépiler" la dernière ville parcourue pour commencer une nouvelle branche
        chemin->taille--;
        chemin->poids -= trajet;
      }
    }
  }
}
```

### 1. PVC exact naif

```C
t_cycle pvc_exact(int nbVilles, double ** distances)
{
   t_cycle meilleur, courant;
   // Solution actuelle : un chemin de poids infini
   meilleur.taille = 0;
   meilleur.poids = DOUBLE_MAX;
   // Par convention, on commence par la ville 0
   courant.taille = 1;
   courant.poids = 0;
   courant.c[0] = 0;
   pvc_exact_recursif(nbVilles, distances, &courant, &meilleur, false);
   return meilleur;
}
```

### 2. PVC exact Branch & Bound

```C
t_cycle pvc_exact_branch_and_bound(int nbVilles, double ** distances)
{
   t_cycle meilleur, courant;
   // Solution actuelle : un chemin de poids infini
   meilleur.taille = 0;
   meilleur.poids = DOUBLE_MAX;
   // Par convention, on commence par la ville 0
   courant.taille = 1;
   courant.poids = 0;
   courant.c[0] = 0;
   pvc_exact_recursif(nbVilles, distances, &courant, &meilleur, true);
   return meilleur;
}
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
t_cycle pvc_approche_ppv(int nbVilles, double ** distances)
{
  // Par convention, on commence par la ville 0
  t_cycle courant;
  courant.poids = 0;
  courant.c[0] = 0;

  // Choix glouton : on choisit toujours la ville la plus proche
  for (courant.taille = 1; courant.taille <= nbVilles; ++courant.taille)
  {
    int ville;
    double d, trajet = DOUBLE_MAX;
    // Trouver la ville la plus proche qui n'est pas dans le chemin
    for (int j = 1; j < nbVilles; ++j) {
      d = distances[courant.c[courant.taille-1]][j];
      if (d < trajet && !est_dans_chemin(&courant, j)) {
        ville = j;
        trajet = d;
      }
    }

    if(trajet != DOUBLE_MAX)
      courant.poids += trajet;
    courant.c[courant.taille] = ville;
  }

  courant.poids += distances[0][courant.c[courant.taille -1]];
  return courant;
}

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
// note : Au lieu de partir du centre a0, on définit juste un index de départ,
// ce qui reste plus simple pour écrire le "désentrelacement".
t_cycle two_opt(int idx, int nbVilles, double ** distances, t_cycle cycle)
{
  // on mesure le gain en entralacant/désentrelacant
  double gain = (
      distances[cycle.c[idx]][cycle.c[idx + 1]] +
      distances[cycle.c[idx + 2]][cycle.c[idx + 3]]
    ) - (
      distances[cycle.c[idx]][cycle.c[idx + 2]] +
      distances[cycle.c[idx + 1]][cycle.c[idx + 3]]
    );
  if(gain > 0) { // on applique l'opération si le gain est positif
    int buffer = cycle.c[idx + 1];
    cycle.c[idx + 1] = cycle.c[idx + 2];
    cycle.c[idx + 2] = buffer;
    cycle.poids -= gain;
  }
  return cycle;
}
```

### 4. Utilisation sur les données

```C
t_cycle opt_cycle(int nbVilles, double ** distances, t_cycle cycle) {
  if(nbVilles > 4) { // il nous faut assez de villes
    for(int i = 0; i < nbVilles - 5; i ++) {
      cycle = two_opt(i, nbVilles, distances, cycle);
    }
  }
  return cycle;
}
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
