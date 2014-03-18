#include <limits.h>

#include "pvc_exact.h"

#include "outils.h"
#include "api.h"

void pvc_exact_recursif(int nbVilles, double ** distances, t_cycle * chemin, t_cycle * meilleur, bool bb)
{
  if (chemin->poids > meilleur->poids && bb)
  {
    return;
  }
  else if (chemin->taille == nbVilles)
  {
    double trajetRetour = distances[chemin->c[chemin->taille -1]][0];
    if (chemin->poids + trajetRetour < meilleur->poids)
    {
      chemin->poids += trajetRetour;
      recopier_chemin(chemin, meilleur);
      chemin->poids -= trajetRetour;
    }
  }
  else
  {
    for(int i = 0; i < nbVilles; ++i)
    {
      if(!est_dans_chemin(chemin, i))
      {
        double trajet = distances[chemin->c[chemin->taille - 1]][i];
        chemin->taille++;
        chemin->poids += trajet;
        chemin->c[chemin->taille-1] = i;

        // Appel récursif
        pvc_exact_recursif(nbVilles, distances, chemin, meilleur, bb);

        // "Dépiler" la dernière ville parcourue pour commencer une nouvelle branche
        chemin->taille--;
        chemin->poids -= trajet;
      }
    }
  }
}

t_cycle pvc_exact(int nbVilles, double ** distances)
{
   t_cycle meilleur, courant;
   // Solution actuelle : un chemin de poids infini
   meilleur.taille = 0;
   meilleur.poids = (double)INT_MAX; // TODO: trouver la capacity maximale d'un double
   // Par convention, on commence par la ville 0
   courant.taille = 1;
   courant.poids = 0;
   courant.c[0] = 0;
   pvc_exact_recursif(nbVilles, distances, &courant, &meilleur, false);
   return meilleur;
}

t_cycle pvc_exact_branch_and_bound(int nbVilles, double ** distances)
{
   t_cycle meilleur, courant;
   // Solution actuelle : un chemin de poids infini
   meilleur.taille = 0;
   meilleur.poids = (double)INT_MAX; // TODO: trouver la capacity maximale d'un double
   // Par convention, on commence par la ville 0
   courant.taille = 1;
   courant.poids = 0;
   courant.c[0] = 0;
   pvc_exact_recursif(nbVilles, distances, &courant, &meilleur, true);
   return meilleur;
}
