#ifndef PVC_SPANNING_TREE_H
#define PVC_SPANNING_TREE_H

#include "api.h"

t_cycle pvc_mst_euclidian(int n, double ** distances);

t_cycle pvc_mst_hamiltonian(int n, double ** distances);

#endif