#ifndef OUTILS_H
#define OUTILS_H

#include "api.h"

extern const double DOUBLE_MAX;

bool est_dans_chemin(t_cycle * chemin, int ville);

void recopier_chemin(t_cycle * source, t_cycle * destination);

#endif
