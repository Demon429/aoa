#include <stdio.h>

#define INF 99999 // A large value to represent infinity
#define MAX 100 // Maximum number of vertices in the graph

// Function to implement Floyd-Warshall algorithm
void floydWarshall(int graph[MAX][MAX], int n) {
    int dist[MAX][MAX];

    // Initialize the distance matrix with the input graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Apply the Floyd-Warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Update the distance if a shorter path is found
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distances matrix
    printf("Shortest distances between all pairs of vertices:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int n;
    int graph[MAX][MAX];

    // Input the number of vertices in the graph
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &n);

    // Input the adjacency matrix of the graph
    printf("Enter the adjacency matrix of the graph (enter %d for no direct path):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Implement Floyd-Warshall algorithm
    floydWarshall(graph, n);

    return 0;
}
