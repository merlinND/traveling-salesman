#include "outils.h"

#include <limits>

const double DOUBLE_MAX = std::numeric_limits<double>::max();

bool est_dans_chemin(t_cycle * chemin, int ville)
{
  for(int i = 0; i < chemin->taille; ++i)
  {
    if (chemin->c[i] == ville)
      return true;
  }
  return false;
}

void recopier_chemin(t_cycle * source, t_cycle * destination)
{
  destination->taille = source->taille;
  destination->poids = source->poids;
  for (int i = 0; i < source->taille; ++i)
  {
    destination->c[i] = source->c[i];
  }
}
