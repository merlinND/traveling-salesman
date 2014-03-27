#include <stdlib.h>
#include <stdio.h>

#include "pvc_spanning_tree.h"
#include "api.h"
#include "outils.h"

/**
 * A root is a node that has no parent (i.e. parent == -1)
 */
unsigned int get_root(int const * parents, unsigned int i)
{
  while (parents[i] >= 0)
    i = parents[i];
  return i;
}

/**
 * @param [in] n Number of nodes of the graph
 * @param [in] distances Weight function for this graph
 * @param [out] tree The minimum spanning tree will be written there (under the form of a predecessor list)
 */
void minimum_spanning_tree(int n, double ** distances, int * parents)
{
  // Initialization: spanning tree is empty
  unsigned int height[n];
  for (unsigned int i = 0; i < n; ++i) {
    parents[i] = -1;
    height[i] = 0;
  }

  // Examine every edge in increasing order of cost
  double ** edges = trier_aretes(n, distances);
  int numberOfEdges =  (n * (n - 1) / 2);
  // The edges are represented in the following fashion
  // T[a][0] = i;        // The source node
  // T[a][1] = j;        // The destination node
  // T[a][2] = d[i][j];  // The cost of this edge

  int i, j, rootI, rootJ;
  for (unsigned int h = 0; h < numberOfEdges; ++h)
  {
    i = edges[h][0];
    j = edges[h][1];
    rootI = get_root(parents, i);
    rootJ = get_root(parents, j);
    if (rootI != rootJ)
    {
      // Merge trees
      if (height[rootI] > height[rootJ])
        parents[rootJ] = rootI;
      else {
        parents[rootI] = rootJ;
        if (height[rootI] == height[rootJ])
          height[rootJ]++;
      }
    }    
  }

  // Clean-up
  supprimer_aretes(n, edges);
}

/**
 * @param [in] nbVilles
 * @param [in] aretes An adjency-list representation of the graph
 * @return A solution to the traveling salesman problem computed from the minimum spanning tree of the graph.
 */
t_cycle pvc_spanning_tree(int nbVilles, double ** distances)
{
  // By convention, we start at city of index 0
  t_cycle courant;
  courant.taille = 0;
  courant.poids = 0;
  courant.c[0] = 0;

  // // Generate a minimum spanning tree from the graph
  // // The tree will be represented as a simple predecessor list
  int spanning_tree[nbVilles];
  minimum_spanning_tree(nbVilles, distances, spanning_tree);

  // Print tree (debug)
  // for (int i = 0; i < nbVilles; ++i)
  // {
  //   printf("Node %d (of parent %d) has children: ", i, spanning_tree[i]);
  //   for (int j = 0; j < nbVilles; ++j)
  //   {
  //     if (spanning_tree[j] == i)
  //       printf("%d ", j);
  //   }
  //   printf("\n");
  // }

  // From the minimum spanning tree, generate a solution
  // TODO

  return courant;
}
