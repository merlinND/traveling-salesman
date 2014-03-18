#ifndef PVC_EXACT_H
#define PVC_EXACT_H

#include "api.h"

t_cycle pvc_exact(int nbVilles, double ** distances);

t_cycle pvc_exact_branch_and_bound(int nbVilles, double ** distances);

#endif
