#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

#define MAX 100

// Dijkstra's Algorithm function
void dijkstra(int graph[MAX][MAX], int n, int start) {
    int distance[MAX];
    bool visited[MAX] = {false}; // Track visited nodes

    // Initialize distances
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX; // Set all distances to infinity
    }
    distance[start] = 0; // Distance to the start node is 0

    // Main algorithm loop
    for (int i = 0; i < n; i++) {
        // Find the unvisited vertex with the smallest distance
        int minDist = INT_MAX, nextNode = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && distance[j] < minDist) {
                minDist = distance[j];
                nextNode = j;
            }
        }

        if (nextNode == -1) break; // No accessible nodes left

        visited[nextNode] = true; // Mark the selected node as visited

        // Update distances to neighbors of the selected node
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[nextNode][j] != INT_MAX &&
                distance[nextNode] + graph[nextNode][j] < distance[j]) {
                distance[j] = distance[nextNode] + graph[nextNode][j];
            }
        }
    }

    // Print shortest distances
    cout << "Vertex\tDistance from source\n";
    for (int i = 0; i < n; i++) {
        cout << i << "\t" << (distance[i] == INT_MAX ? -1 : distance[i]) << endl;
    }
}

// Main function
int main() {
    int graph[MAX][MAX], n, start;

    // Uncomment this block for user input
    /*
    do {
        cout << "Enter the number of vertices (1 to " << MAX << "): ";
        cin >> n;
        if (n <= 0 || n > MAX) {
            cout << "Invalid input. Please enter a number between 1 and " << MAX << ".\n";
        }
    } while (n <= 0 || n > MAX);

    cout << "Enter the adjacency matrix (enter " << INT_MAX << " for no connection):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] < 0 && graph[i][j] != INT_MAX) {
                cout << "Invalid input. Weight cannot be negative.\n";
                j--; // Re-enter the value
            }
        }
    }

    do {
        cout << "Enter the starting vertex (0 to " << n - 1 << "): ";
        cin >> start;
        if (start < 0 || start >= n) {
            cout << "Invalid input. Please enter a valid vertex index.\n";
        }
    } while (start < 0 || start >= n);
    */

    // Uncomment this block for hardcoded input
    /*
    n = 4;
    start = 0;
    int hardcodedGraph[MAX][MAX] = {
        {0, 4, INT_MAX, 5},
        {4, 0, 3, INT_MAX},
        {INT_MAX, 3, 0, 1},
        {5, INT_MAX, 1, 0}
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = hardcodedGraph[i][j];
        }
    }
    */

    // Call Dijkstra's algorithm
    dijkstra(graph, n, start);

    return 0;
}
