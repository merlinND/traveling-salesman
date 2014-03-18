#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <limits.h>

#include "api.h"

void lire_donnees(const char *f, unsigned int *nb_villes, double ***dist,  double **absc, double **ord)
{
  //double *absc; ///tableau des ordonnées
  //double *ord;  /// tableau des abscisses
  char ligne[MAXMOT];
  FILE * fin = fopen(f,"r");

  if(fin != NULL)
    {
      //On recupere le nombre de villes
      fgets(ligne, MAXMOT, fin);
      *nb_villes = atoi(ligne);
      (*dist) = (double**)malloc(*nb_villes * sizeof(double*));
      (*absc) = (double*)malloc(*nb_villes * sizeof(double));
      (*ord) = (double*)malloc(*nb_villes * sizeof(double));
      int i = 0;
      while (fgets(ligne, MAXMOT, fin) != NULL)
        {
          char *p = strchr(ligne, ';');
          ligne[strlen(ligne) - strlen(p)]='\0';
          p = &p[1];
          (*absc)[i] = atof(ligne);
          (*ord)[i] = atof(p);
          i = i + 1;
        }
    }
  else
    {
      printf("Erreur de lecture du fichier.\n");
      exit(2);
    }
  fclose(fin);
  int i,j;

  //Calclul des distances
  for(i = 0; i < *nb_villes; i++)
    {
      (*dist)[i] = (double*) malloc(*nb_villes * sizeof(double));
      for(j = 0; j < *nb_villes; j++)
        {
          (*dist)[i][j] = sqrt( ((*absc)[i] - (*absc)[j])* ((*absc)[i] - (*absc)[j]) + ((*ord)[i] - (*ord)[j]) * ((*ord)[i] - (*ord)[j]) );
        }
    }
}

void supprimer_distances_et_coordonnees(const int nb_villes, double **distances, double *abscisses, double *ordonnees)
{
  int i;
  for(i = 0; i < nb_villes; i++)
    {
      free(distances[i]);
    }
 free(distances);
 free(abscisses);
 free(ordonnees);
}

void afficher_cycle_html(const t_cycle cycle, double *posX, double *posY)
{
  FILE * fout = fopen("DisplayTsp.html","w");
  if(fout != NULL)
    {
      int i;
      fprintf(fout, "<html>\n <applet codebase=\".\" code=\"DisplayTsp.class\" width=800 height=600>\n");
      fprintf(fout, "<param name = Problem value = \"custom\">\n");
      fprintf(fout, "<param name = Problem CitiesPosX value = \"");
      for(i = 0; i < cycle.taille; i++)
        fprintf(fout,"%f;",posX[i]);
      fprintf(fout, "\">\n");
      fprintf(fout, "<param name = Problem CitiesPosY value = \"");
      for(i = 0; i < cycle.taille; i++)
        fprintf(fout,"%f;",posY[i]);
      fprintf(fout, "\">\n");
      fprintf(fout, "<param name = Parcours value = \"");
      fprintf(fout,"%d",cycle.c[0]);
      for(i = 1; i < cycle.taille; i++)
        fprintf(fout,"-%d",cycle.c[i]);
      fprintf(fout,"\">\n</applet>\n </html>\n");
    }
  fclose(fout);
}

void afficher_distances(const int nb, double **distances)
{
  unsigned int i ;
  unsigned int j ;
  for(i = 0  ; i < nb; i++)
    {
      for(j = 0 ; j < nb ; j++)
        printf("%f ", distances[i][j]);
      printf("\n");
    }
  printf("\n");
}

int comparer(const void *v1, const void *v2)
{
  double **px1 = (double **) v1;
  double **px2 = (double **) v2;

  double *x1 = *px1;
  double *x2 = *px2;
  if(x1[2] - x2[2] < 0)
    return -1;
  else
    {
      if(x1[2] - x2[2] == 0)
        return 0;
      else
        return 1;
    }
}

double **trier_aretes(const int n, double **d)
{
  assert(d);

  int nb_aretes = n * (n - 1) / 2;
  double **T = (double **)malloc(nb_aretes * sizeof(double *));
  int i, j;
  int a = 0;

  //On initialise la structure d'arêtes
  for(i = 0; i < n-1; i++)
    {
      for(j = i+1; j < n; j++)
        {
          T[a] = (double *)malloc(3 * sizeof(double));
          T[a][0] = i;
          T[a][1] = j;
          T[a][2] = d[i][j];
          a++;
        }
    }

  //Appel au quicksort avec la bonne fonction de comparaison
  qsort(T, a, sizeof(T[0]), comparer);


  //Decommenter pour vérifier le tri
  /*
  for(i = 0; i < a; i++)
    printf("%f ", T[i][2]);
  printf("\n");
  */
  return T;
}

void supprimer_aretes(const int nb_villes, double **T)
{
  assert(T);

  int nb_aretes = nb_villes*(nb_villes - 1 ) / 2;
  unsigned int i;
  for( i = 0; i < nb_aretes ; ++i)
    free( T[i] );

  free(T);
}
