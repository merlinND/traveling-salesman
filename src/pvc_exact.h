#ifndef PVC_EXACT_H
#define PVC_EXACT_H

#include "api.h"

void pvc_exact_recursif(int nbVilles, double ** distances, t_cycle * chemin, t_cycle * meilleur);

t_cycle pvc_exact(int nbVilles, double ** distances);

#endif
