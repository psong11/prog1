#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

//typedef struct node node;
struct Node
{
    float coord[4];
};

//typedef struct Graph Graph;
struct Graph
{
    Node nodes[];
};

Graph generate_graph(int n, int dim)
{

    srand(time(NULL));

    Graph graph;

    if (dim == 1)
    {
        for (int i = 0; i < n; i++)
        {
            Node node;
            node.coord = [ float(rand() / RAND_MAX), 0, 0, 0 ];
            graph.nodes[i] = node;
        }
    }
    if (dim == 2)
    {
    }
    if (dim == 3)
    {
    }
    if (dim == 4)
    {
    }
    else
    {
    }

    return graph;
}

int main(int argc, char **argv)
{
    int n = int(argv[1]);
    int trials = int(argv[2]);
    int dim = int(argv[3]);

    if (dim < 1 || dim > 4)
    {
        invalid_argument("Please enter a valid dimension.")
    }

    float average;
    Graph mst;

    // For 'trial' number of times...
    for (int i = 0; i < trials; i++)
    {
        // Generate a random graph
        Graph graph = generate_graph(n, dim);

        // Find the MST weight of this random graph

        // Integrate that weight into the average weight
    }

    // return the output in the form: average(average weight of mst over the trials) numpoints numtrials dimension

    /* Let us create the following graph
        2 3
    (0)--(1)--(2)
    | / \ |
    6| 8/ \5 |7
    | / \ |
    (3)-------(4)
            9     */
    int graph[V][V] = {{0, 2, 0, 6, 0},
                       {2, 0, 3, 8, 5},
                       {0, 3, 0, 0, 7},
                       {6, 8, 0, 0, 9},
                       {0, 5, 7, 9, 0}};

    // Print the solution
    primMST(graph);

    return 0;
}