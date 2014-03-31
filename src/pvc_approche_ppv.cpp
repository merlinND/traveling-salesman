#include "pvc_approche_ppv.h"
#include "outils.h"

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

    courant.poids += trajet;
    courant.c[courant.taille] = ville;
  }
  
  return courant;
}
