#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <assert.h>
#include <limits.h>

#include "api.h"
#include "outils.h"
#include "temps.h"
#include "pvc_exact.h"
#include "pvc_approche_ppv.h"
#include "opt_locale.h"

/**
 * Fonction main
 */
int main (int argc, char *argv[])
{
  double **distances;
  double *abscisses;
  double *ordonnees;
  unsigned int nb_villes;

  // Initialize timer (compile with -lrt)
  lire_donnees("defi250.csv", &nb_villes, &distances, &abscisses, &ordonnees);

  // Print the distances
  //afficher_distances(nb_villes,distances);

  // Naïve solution
  demarrer_mesure_temps();
  pvc_exact(10, distances);
  afficher_mesure_temps("pvc exact x10");

  // Naïve solution with pruning
  demarrer_mesure_temps();
  pvc_exact_branch_and_bound(10, distances);
  afficher_mesure_temps("pvc exact branch & bound x10");

  // Greedy solution
  demarrer_mesure_temps();
  pvc_approche_ppv(250, distances);
  afficher_mesure_temps("ppv x250");

  demarrer_mesure_temps();
  t_cycle cycle = pvc_approche_ppv(250, distances);
  cycle = opt_cycle(250, distances, cycle);
  afficher_mesure_temps("ppv optimise x250");

  // Kruskall
  // TODO

  // Output (HTML)
  afficher_cycle_html(cycle, abscisses, ordonnees);

  double ** aretes =  trier_aretes(nb_villes, distances);
  // <-- Kruskal Here

  // Clean-up
  supprimer_aretes(nb_villes, aretes);
  supprimer_distances_et_coordonnees(nb_villes, distances, abscisses, ordonnees);
  return 0;
}
