#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <limits.h>

#include "api.h"
#include "outils.h"
#include "pvc_exact.h"
#include "pvc_approche_ppv.h"
#include "pvc_spanning_tree.h"

void print_cycle(t_cycle const * cycle)
{
  for (int i = 0; i < cycle->taille; ++i)
  {
    printf("%d -> ", cycle->c[i]);
  }
}

/**
 * Fonction main
 */
int main (int argc, char *argv[])
{
  double **distances;
  double *abscisses;
  double *ordonnees;
  unsigned int nb_villes;
  t_cycle solution;

  // Import cities
  lire_donnees("defi250.csv", &nb_villes, &distances, &abscisses, &ordonnees);

  // Initialize timer (compile with -lrt)
  // TODO

  // Print the distances
  //afficher_distances(nb_villes,distances);

  // Naïve solution
  //demarrer_mesure_temps();
  pvc_exact(10, distances);
  //afficher_mesure_temps("pvc exact x10");

  // Naïve solution with pruning
  //demarrer_mesure_temps();
  pvc_exact_branch_and_bound(10, distances);
  //afficher_mesure_temps("pvc exact branch & bound x10");

  // Greedy solution
  //demarrer_mesure_temps();
  pvc_approche_ppv(nb_villes, distances);
  //afficher_mesure_temps("ppv x250");

  // Kruskal only (returns an Euclidian tour)
  //pvc_mst_euclidian(nb_villes, distances);
  // Kruskal + dedoubling
  solution = pvc_mst_hamiltonian(nb_villes, distances);

  // Output (HTML)
  print_cycle(&solution);
  afficher_cycle_html(solution, nb_villes, abscisses, ordonnees);

  // Clean-up
  supprimer_distances_et_coordonnees(nb_villes, distances, abscisses, ordonnees);
  return 0;
}
