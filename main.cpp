#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

const unsigned int max_int = -1;
const int nil = -1;

// Represents nodes in a graph
struct Node
{
    int id;
    float distance;
    vector<float> coord;
    int heap_pos;
};

// for dim >= 2, initialize node with set coordinates
Node create_node(int dim)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1); //uniform distribution between 0 and 1

    Node node;
    for (int j = 0; j < dim; j++) // for each dimension
    {
        node.coord.push_back(dis(gen));
    }
    node.distance = max_int;
    node.heap_pos = nil;
    return node;
};

// trickle node at position "index" in heap upwards
void upheap(int index, Node **heap)
{
    Node *node = heap[index];
    while (heap[(index - 1) / 2]->distance > node->distance)
    {
        heap[index] = heap[(index - 1) / 2];
        heap[index]->heap_pos = index;
        index = (index - 1) / 2; //moving the node up to its parent
        if (index == 0)          // if we are at the source node
            break;
    }
    heap[index] = node;
    node->heap_pos = index;
}

// insert new node into heap
void insert(int numOfNodesInHeap, Node *node, Node **heap)
{
    heap[numOfNodesInHeap] = node;
    upheap(numOfNodesInHeap, heap);
}

// trickle node at position "index" downwards
void downheap(int last, int index, Node **heap)
{
    Node *node = heap[index];
    while (index <= (last - 1) / 2)
    {
        int j = 2 * index + 1;
        if (heap[j]->distance > heap[j + 1]->distance)
            j++;
        if (heap[j]->distance >= node->distance)
            break;
        heap[index] = heap[j];
        heap[index]->heap_pos = index;
        index = j;
    }
    heap[index] = node;
    node->heap_pos = index;
}

// delete minimum distance node from heap, reorganize heap
Node *deleteMin(int lastNode, Node **heap)
{
    Node *r = heap[0];
    r->heap_pos = nil;
    heap[0] = heap[lastNode];
    heap[0]->heap_pos = 0;
    lastNode--;
    downheap(lastNode, 0, heap);
    return r;
}

// decrease distance of node at position "index" reorganize heap
void decreaseDistance(int index, float dist, Node **heap)
{
    heap[index]->distance = dist;
    upheap(index, heap);
}

float prims(int n, int dim, int source);

float edgeWeight(int dim, Node v, Node w);

int main(int argc, char **argv)
{

    int n = atoi(argv[1]);
    int trials = atoi(argv[2]);
    int dim = atoi(argv[3]);

    if (dim != 0 && dim != 2 && dim != 3 && dim != 4)
    {
        throw invalid_argument("Please enter a valid dimension.");
    }
    //---------^ SETUP STUFF ^---------------------------

    float cum_sum = 0;

    // For 'trial' number of times...
    for (int i = 0; i < trials; i++)
    {
        int s = 0;

        // Find the MST weight of a random graph
        cum_sum += prims(n, dim, s);
    }

    printf("Average weight: %f numpoints: %d numtrials: %d dimension: %d\n", cum_sum / trials, n, trials, dim);
    // return the output in the form: average(average weight of mst over the trials) numpoints numtrials dimension

    return 0;
}

float prims(int n, int dim, int source)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1); //uniform distribution between 0 and 1

    Node *nodes = new Node[n]; // create a graph
    bool MST[n];               // this array checks whether or not a node is in the MST.
    Node *heap[n];             // heap of nodes not in the MST.

    for (int i = 0; i < n; i++) // create n nodes, they are all not in the MST.
    {
        nodes[i] = create_node(dim);
        nodes[i].id = i;
        MST[i] = false;
    }
    nodes[source].distance = 0;
    heap[0] = &nodes[source];

    int heap_size = 1;
    // for each vertex in the MST set of vertices
    // look at all neighboring vertices that aren't in the MST, and pick the smallest weight
    // add that weight into the weight variable
    // add that corresponding vertex to the MST set of vertices

    while (heap_size)
    {
        heap_size--;
        Node *v = deleteMin(heap_size, heap); // get the closest vertex v
        MST[v->id] = true;                    // that vertex is now in the MST
        for (int w = 0; w < n; w++)           // for every edge (v, w) where w not in the MST
        {
            if (MST[w] == false) // if not in MST,
            {
                float weight = 0;
                if (!dim)
                {
                    weight = dis(gen);
                }
                else
                {
                    for (int i = 0; i < dim; i++)
                    {
                        weight = weight + pow((nodes[w].coord[i]) - (v->coord[i]), 2.0);
                    }
                    weight = sqrt(weight);
                }
                if (nodes[w].distance > weight) // if our previously recorded distance is greater than what we just calculated: (v, w)
                {
                    nodes[w].distance = weight;   // update that nodes' distance
                    if (nodes[w].heap_pos == nil) // if w was not in the heap
                    {
                        insert(heap_size, &nodes[w], heap); // insert it in
                        heap_size++;                        // heap grows 1
                    }
                    else // if w was already in the heap
                    {
                        upheap(nodes[w].heap_pos, heap);
                    }
                }
            }
        }
    }

    float totalWeight = 0.0;
    for (int i = 0; i < n; i++)
    {
        totalWeight += nodes[i].distance;
    }
    delete[] nodes;
    return totalWeight;
}

float edgeWeight(int dim, Node v, Node w)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1); //uniform distribution between 0 and 1

    float weight = 0;
    if (!dim)
    {
        return dis(gen);
    }
    for (int i = 0; i < dim; i++)
    {
        weight = weight + pow((w.coord[i]) - (v.coord[i]), 2.0);
    }
    return sqrt(weight);
}
