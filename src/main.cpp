#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <assert.h>
#include <limits.h>

#include "api.h"
#include "outils.h"
#include "pvc_exact.h"
#include "temps.h"

/**
 * Fonction main.
 */
int main (int argc, char *argv[])
{
  double **distances;
  double *abscisses;
  double *ordonnees;
  unsigned int nb_villes;

  //Initialisation du timer pour mesurer des temps (compiler avec -lrt)

  //Exemple de mesure du temps
  lire_donnees("defi250.csv", &nb_villes, &distances, &abscisses, &ordonnees);

  demarrer_mesure_temps();
  pvc_exact(10, distances);
  afficher_mesure_temps("pvc exact x10");

  demarrer_mesure_temps();
  t_cycle cycle = pvc_exact_branch_and_bound(10, distances);
  afficher_mesure_temps("pvc exact branch & bound x10");
  //naif

  afficher_cycle_html(cycle, abscisses, ordonnees);

  double ** Aretes =  trier_aretes(nb_villes, distances);
  /// <-- Kruskal Here
  supprimer_aretes(nb_villes, Aretes);

  supprimer_distances_et_coordonnees(nb_villes, distances, abscisses, ordonnees);
  return 0;
}
