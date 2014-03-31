#include "opt_locale.h"
#include "outils.h"
#include "pvc_exact.h"

#include <stdlib.h>
#include <stdio.h>

t_cycle two_opt(int idx, int nbVilles, double ** distances, t_cycle cycle)
{
  double gain = (
      distances[cycle.c[idx]][cycle.c[idx + 1]] +
      distances[cycle.c[idx + 2]][cycle.c[idx + 3]]
    ) - (
      distances[cycle.c[idx]][cycle.c[idx + 2]] +
      distances[cycle.c[idx + 1]][cycle.c[idx + 3]]
    );
  if(gain > 0) {
    int buffer = cycle.c[idx + 1];
    cycle.c[idx + 1] = cycle.c[idx + 2];
    cycle.c[idx + 2] = buffer;
    cycle.poids -= gain;
  }
  return cycle;
}

t_cycle opt_cycle(int nbVilles, double ** distances, t_cycle cycle) {
  if(nbVilles > 4) {
    for(int i = 0; i < nbVilles - 5; i ++) {
      cycle = two_opt(i, nbVilles, distances, cycle);
    }
  }
  return cycle;
}
