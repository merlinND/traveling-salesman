#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <limits.h>

#include "api.h"
#include "outils.h"
#include "pvc_exact.h"

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
  struct timespec myTimerStart;
  clock_gettime(CLOCK_REALTIME, &myTimerStart);

  //Exemple de mesure du temps
  lire_donnees("defi250.csv", &nb_villes, &distances, &abscisses, &ordonnees);

  //Récupération du timer et affichage
  struct timespec current;
  clock_gettime(CLOCK_REALTIME, &current); //Linux gettime
  double elapsed_in_ms =    (( current.tv_sec - myTimerStart.tv_sec) *1000 +
          ( current.tv_nsec - myTimerStart.tv_nsec)/1000000.0);
  printf("Temps passé (ms) : %lf\n", elapsed_in_ms);


  //Affichage des distances
  //afficher_distances(nb_villes,distances);

  //naif
  t_cycle cycle = pvc_exact(10, distances);
  afficher_cycle_html(cycle, abscisses, ordonnees);

  double ** Aretes =  trier_aretes(nb_villes, distances);
  /// <-- Kruskal Here
  supprimer_aretes(nb_villes, Aretes);

  supprimer_distances_et_coordonnees(nb_villes, distances, abscisses, ordonnees);
  return 0;
}
