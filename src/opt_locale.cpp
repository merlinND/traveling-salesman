#include "opt_locale.h"
#include "outils.h"
#include "pvc_exact.h"

#include <stdlib.h>
#include <stdio.h>

t_cycle two_opt(int indexVilleOpt, int nbVilles, double ** distances, t_cycle cycle)
{
  int taille_locale = 5;
  int debut = 0;
  if(indexVilleOpt == 0) {
    taille_locale = 3;
  } else if(indexVilleOpt == 1) {
    taille_locale = 4;
  } else if(indexVilleOpt == nbVilles - 1) {
    debut = nbVilles - 4;
    taille_locale = 3;
  } else if(indexVilleOpt == nbVilles - 2) {
    debut = nbVilles - 5;
    taille_locale = 4;
  } else {
    debut = indexVilleOpt - 2;
  }

  double ** distances_locales = (double **)malloc(taille_locale * sizeof(double *));
  for(int i = 0; i < taille_locale; i ++)
  {
    distances_locales[i] = (double *)malloc(taille_locale * sizeof(double));
    for(int j = 0; j < taille_locale; j ++) {
      distances_locales[i][j] = distances
                                    [cycle.c[debut + i]]
                                    [cycle.c[debut + j]];
    }
  }
  t_cycle cycle_local = pvc_exact_branch_and_bound(taille_locale, distances_locales);
  for(int i = 0; i < taille_locale; i ++)
  {
    for(int j = 0; j < taille_locale; i ++) {

    }
    free(distances_locales[i]);
  }
  free(distances_locales);

  for(int i = 0; i < taille_locale; i ++) {
    cycle.c[debut + i] = cycle_local.c[i];
  }

  return cycle;
}

t_cycle opt_cycle(int nbVilles, double ** distances, t_cycle cycle) {
  for(int i = 0; i < nbVilles; i ++) {
    cycle = two_opt(i, nbVilles, distances, cycle);
  }
  return cycle;
}
