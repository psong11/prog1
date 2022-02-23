#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

// A structure to represent a node in adjacency list
struct AdjListNode
{
    float coord[4];
    int weight;
    struct AdjListNode *next;
};
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head; // pointer to head node of list
};
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct AdjListGraph
{
    int n;
    struct AdjList *array;
};

struct Node
{
    int id;
    vector<float> coord;
};

struct Graph
{
    vector<Node> nodes;
};

mt19937_64 rng;
uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32)};
rng.seed(ss);

uniform_real_distribution<double> unif(0, 1);

Node create_node(int dim)
{
}

Graph generate_graph(int n, int dim)
{
    srand(time(NULL));

    Graph graph;

    for (int i = 0; i < n; i++) // for each node
    {
        Node node;
        for (int j = 0; j < dim; j++) // for each dimension
        {
            graph.nodes.push_back(rand());
        }

        Node node;

        graph.nodes[i] = node;
    }

    return graph;
}

Graph generate_more_nodes(Graph g)
{
}

float prims(Graph graph, Node s)
{
    float weight;

    // for each vertex in the MST set of vertices
    // look at all neighboring vertices that aren't in the MST, and pick the smallest weight
    // add that weight into the weight variable
    // add that corresponding vertex to the MST set of vertices

    return weight;
}

int main(int argc, char **argv)
{
    int n = int(argv[1]);
    int trials = int(argv[2]);
    int dim = int(argv[3]);

    if (dim < 1 || dim > 4)
    {
        invalid_argument("Please enter a valid dimension.");
    }
    //---------^ SETUP STUFF ^---------------------------

    float average;

    // For 'trial' number of times...
    for (int i = 0; i < trials; i++)
    {
        // Generate part of the random graph

        // Find the MST weight of this random graph

        // Integrate that weight into the average weight
    }

    // return the output in the form: average(average weight of mst over the trials) numpoints numtrials dimension

    return 0;
}