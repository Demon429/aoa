#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
} ;

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Structure to represent a subset for the union-find
struct Subset {
    int parent;
    int rank;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to find the root of a node in the union-find data structure
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent!= i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform the union of two subsets
void unionSubsets(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Comparison function to sort edges based on their weight
int compareEdges(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Function to perform Kruskal's algorithm and find the minimum spanning tree
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge* edges = graph->edges;

    // Sort the edges based on their weight
    qsort(edges, graph->E, sizeof(struct Edge), compareEdges);

    // Allocate memory for the resulting MST
    struct Edge* result = (struct Edge*)malloc(V * sizeof(struct Edge));
    int resultIndex = 0;
    int edgeIndex = 0;

    // Create subsets for the union-find
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Process edges one by one
    while (resultIndex < V - 1 && edgeIndex < graph->E) {
        // Get the next edge from the sorted list
        struct Edge nextEdge = edges[edgeIndex++];

        // Find the roots of the source and destination nodes
        int rootSrc = find(subsets, nextEdge.src);
        int rootDest = find(subsets, nextEdge.dest);

        // If the roots are different, add the edge to the result and perform a union
        if (rootSrc!= rootDest) {
            result[resultIndex++] = nextEdge;
            unionSubsets(subsets, rootSrc, rootDest);
        }
    }

    // Print the edges in the resulting MST
    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < resultIndex; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    }

    // Free allocated memory
    free(result);
    free(subsets);
}

int main() {
    int V, E;

    // Prompt the user to enter the number of vertices and edges
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    // Create a graph with V vertices and E edges
    struct Graph* graph = createGraph(V, E);

    // Prompt the user to enter the edges of the graph
    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    // Find the MST using Kruskal's algorithm
    kruskalMST(graph);

    // Free allocated memory
    free(graph->edges);
    free(graph);

    return 0;
}