#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int src, dest, weight;
};

void bellmanFord(Edge edges[], int V, int E, int src)
{
    int dist[V];
    int parent[V];

    // Initialize distances and parent array
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[src] = 0; // Distance from source to itself is always 0

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            cout << "Graph contains a negative-weight cycle\n";
            return;
        }
    }

    // Print the shortest paths
    cout << "Vertex  Distance  Parent\n";
    for (int i = 0; i < V; i++)
    {
        cout << i << "\t" << dist[i] << "\t";
        if (parent[i] != -1)
            cout << parent[i];
        else
            cout << "N/A";
        cout << endl;
    }
}

int main()
{
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Edge edges[E];

    cout << "Enter the details of each edge (source, destination, weight):\n";
    for (int i = 0; i < E; i++)
    {   
        cout << "Source :" ;
        cin >> edges[i].src ;
        cout << "Destination :";
        cin >> edges[i].dest ;
        cout << "Weight :";
        cin>> edges[i].weight;
        
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    bellmanFord(edges, V, E, src);

    return 0;
}
