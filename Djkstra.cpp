#include <iostream>
#include <climits>
#include <string>
using namespace std;

const int MAX_NODES = 100;
int adj[MAX_NODES][MAX_NODES];
string nodes[MAX_NODES];
int size = 0;

int find(string name) {
    for (int i = 0; i < size; i++) {
        if (nodes[i] == name) return i;
    }
    cout << "Node not found!\n";
    return -1;
}

int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < size; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printSolution(int dist[], int src) {
    cout << "\nShortest distances from node " << nodes[src] << ":\n";
    for (int i = 0; i < size; i++) {
        cout << nodes[src] << " -> " << nodes[i] << " = ";
        if (dist[i] == INT_MAX)
            cout << "INF";
        else
            cout << dist[i];
        cout << endl;
    }
}

void dijkstra() {
    string start;
    cout << "Start node: ";
    cin >> start;

    int src = find(start);
    if (src == -1) return;

    int dist[MAX_NODES];
    bool visited[MAX_NODES] = {false};
    fill(dist, dist + MAX_NODES, INT_MAX);
    dist[src] = 0;

    for (int count = 0; count < size - 1; count++) {
        int u = minDistance(dist, visited);
        if (u == -1) break;

        visited[u] = true;
        for (int v = 0; v < size; v++) {
            if (!visited[v] && adj[u][v] && dist[u] != INT_MAX
                && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    printSolution(dist, src);
}

int main() {
    cout << "Enter number of nodes: ";
    cin >> size;

    cout << "Enter names of nodes:\n";
    for (int i = 0; i < size; i++) {
        cin >> nodes[i];
    }

    cout << "Enter adjacency matrix (0 if no edge):\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> adj[i][j];
        }
    }

    dijkstra();

    return 0;
}
