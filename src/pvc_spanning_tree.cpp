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
 * @param [out] tree The minimum spanning tree as an array of boolean:
 * each edge from <edges> is either included or not in the tree
 */
void minimum_spanning_tree(int n, double ** edges, int * parents)
{
  // Initialization: spanning tree is empty
  unsigned int height[n];
  for (unsigned int i = 0; i < n; ++i) {
    parents[i] = -1;
    height[i] = 0;
  }

  // Examine every edge in increasing order of cost
  unsigned int i, j, rootI, rootJ;
  unsigned int h = 0, size = 1;
  while (size < n)
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

      size++;
    }
    // Next edge
    h++;
  }

  // Clean-up
  supprimer_aretes(n, edges);
}

/**
 * Print tree (debug function)
 */
void print_tree(unsigned int n, int * tree)
{
  for (int i = 0; i < n; ++i)
  {
    printf("Node %d (of parent %d) has children: ", i, tree[i]);
    for (int j = 0; j < n; ++j)
    {
      if (tree[j] == i)
        printf("%d ", j);
    }
    printf("\n");
  }
}

/*
 * Recursively visit the subtree of <tree> using the given node as root.
 * @param [in] tree A predecessor list representation of the tree
 * @param [in] size The number of nodes of the tree
 * @param [in] root
 * @param [in] visited A boolean array marking the visited nodes
 * @param [out] tour The tour completed with the nodes from this subtree. Note that the cost is NOT computed in the cycle
 */
void visit_subtree(int const * tree, unsigned int size, unsigned int root, char * visited, t_cycle * tour)
{
  if(!visited[root])
  {
    // Visit the subtree's root node
    // TODO: add the cost
    visited[root] = 1;
    tour->c[tour->taille] = root;
    tour->taille++;

    // Visit each child node
    for (unsigned int i = 0; i < size; ++i)
    {
      if (!visited[i] && tree[i] == root)
      {
        visit_subtree(tree, size, i, visited, tour);

        // Return to the root
        tour->c[tour->taille] = root;
        tour->taille++;
      }
    }
  }
}

/**
 * @param [in] n Number of nodes
 * @param [in] aretes An adjency-list representation of the graph
 * @return A sub-optimal solution to the traveling salesman problem computed from the minimum spanning tree of the graph.
 */
t_cycle pvc_mst_euclidian(int n, double ** distances)
{
  // Generate a minimum spanning tree from the graph
  // The tree will be represented as a simple predecessor list
  int spanning_tree[n];
  double ** edges = trier_aretes(n, distances);
  // The edges are represented in the following fashion
  // T[a][0] = i;        // The source node
  // T[a][1] = j;        // The destination node
  // T[a][2] = d[i][j];  // The cost of this edge
  minimum_spanning_tree(n, edges, spanning_tree);

  // Generate an Euclidian graph from the minmum spanning tree (i.e. allowing repetitions)
  // (simply double each edge of the MSP to obtain an Euclidian cycle)
  t_cycle tour;
  tour.taille = 0;
  tour.poids = 0;
  char visited[n];
  for (unsigned int i = 0; i < n; ++i)
    visited[i] = 0;
  // Start exploring from the root
  unsigned int root = get_root(spanning_tree, 0);
  visit_subtree(spanning_tree, n, root, visited, &tour);

  return tour;
}

/**
 * @param [in] n Number of nodes
 * @param [in] aretes An adjency-list representation of the graph
 * @return A solution to the traveling salesman problem computed from the minimum spanning tree of the graph.
 */
t_cycle pvc_mst_hamiltonian(int n, double ** distances)
{
  // Simply dedouble the steps from the euclidian solution
  t_cycle euclidian = pvc_mst_euclidian(n, distances);
  t_cycle hamiltonian;
  hamiltonian.c[0] = euclidian.c[0];
  hamiltonian.taille = 1;

  unsigned char seen[n];
  for (unsigned int i = 0; i < n; ++i)
    seen[i] = 0;

  seen[hamiltonian.c[0]] = 1;
  unsigned int number_seen = 1, k = 0;
  double delta;
  while (number_seen < n)
  {
    if (!seen[euclidian.c[k]]) {
      hamiltonian.c[number_seen] = euclidian.c[k];
      
      delta = distances[hamiltonian.c[number_seen-1]][hamiltonian.c[number_seen]];
      hamiltonian.poids += delta;
      hamiltonian.taille++;

      seen[hamiltonian.c[number_seen-1]] = 1;
      number_seen++;
    }
    k++;
  }

  return hamiltonian;
}
