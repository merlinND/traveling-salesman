#ifndef API_H
#define API_H

#define MAXMOT 256
#define MAXS 1500

/**
 * Structure pour representer un cycle
 */
typedef struct t_cycle
{
  int taille;   //la taille du cycle en construction
  double poids; //le coût du cycle
  int c[MAXS];  //liste des "taille" sommets
} t_cycle;


/**
 * Charge le CSV des coordonnées des villes.
 *
 * @param [in] f le fichier
 * @param [out] nb_villes le nombre de villes de l'instance
 * @param [out] dist le tableau des nb_villes*nb_villes distances
 * @param [out] absc le tableau des abscisses des villes
 * @param [out] ord le tableau des ordonnées des villes
 */
void lire_donnees(const char *f, unsigned int *nb_villes, double ***dist,  double **absc, double **ord);


/**
 * Supprime la structure des distances
 *
 * @param [in] nb_villes le nombre de villes.
 * @param [in,out] distances le tableau à supprimer.
 * @param [in,out] abscisses un autre tableau à supprimer.
 * @param [in,out] ordonnees encore un autre tableau à supprimer.
 */
void supprimer_distances_et_coordonnees(const int nb_villes, double **distances, double *abscisses, double *ordonnees);


/**
 * Export le cycle dans un fichier HTML pour pouvoir être visualisé
 * dans l'applet.
 *
 * @param [in] cycle le cycle à afficher
 */
void afficher_cycle_html(const t_cycle cycle, unsigned int n, double *posX, double *posY);

/**
 * Affiche le tableau des distances.
 *
 * @param [in] nb le nombre de villes
 * @param [in] distances le tableau
 */
void afficher_distances(const int nb, double **distances);


/**
 * Fonction de comparaison pour le trie des arêtes par leur poids.
 *
 * @param [in] v1 pointeur vers un triplet (i,j,poids)
 * @param [in] v2 pointeur verts un triplet (i,j,poids)
 * @return vrai si poid v1 < poids v2
 */
int comparer(const void *v1, const void *v2);

/**
 * Construit un tableau de n*(n-1)/2 arêtes triées selon leur poids.
 *
 * @note utile pour le Kruskal
 *
 * @param [in] n le nombre de villes
 * @param [in] d tableau des n x n distances.
 * @return tableau d'arêtes triées T[a][2] = poids entre les arrêtes t[a][0] et t[a][1]
 */
double **trier_aretes(const int n, double **d);


/**
 * Supprime le tableau des arêtes.
 *
 * @param [in] nb_villes le nombre de villes
 * @param [in,out] T le tableau à supprimer
 */
void supprimer_aretes(const int nb_villes, double **T);


#endif
