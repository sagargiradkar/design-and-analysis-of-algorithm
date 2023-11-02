#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 15; // Maximum number of cities, change this value as needed

// Function to copy temporary solution to the final solution
void copyToFinal(int curr_path[], int final_path[], int N) {
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

// Function to find the minimum edge cost having an end at the vertex i
int firstMin(int adj[][MAX_N], int i, int N) {
    int min = INT_MAX;
    for (int k = 0; k < N; k++)
        if (adj[i][k] < min && i != k)
            min = adj[i][k];
    return min;
}

// Function to find the second minimum edge cost having an end at the vertex i
int secondMin(int adj[][MAX_N], int i, int N) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j)
            continue;
        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] <= second && adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}

// Function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight -> stores the weight of the path so far
// level -> current level while moving in the search space tree
// curr_path[] -> where the solution is being stored which would later be copied to final_path[]
void TSPRec(int adj[][MAX_N], int curr_bound, int curr_weight, int level, int curr_path[], int final_path[], bool visited[], int N, int& final_res) {
    // Base case is when we have reached level N which means we have covered all the nodes once
    if (level == N) {
        // Check if there is an edge from the last vertex in path back to the first vertex
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinal(curr_path, final_path, N);
                final_res = curr_res;
            }
            return;
        }
    }

    // For any other level, iterate for all vertices to build the search space tree recursively
    for (int i = 0; i < N; i++) {
        // Consider the next vertex if it is not the same (diagonal entry in adjacency matrix) and not visited already
        if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            // Different computation of curr_bound for level 2 from the other levels
            if (level == 1)
                curr_bound -= ((firstMin(adj, i, N) + firstMin(adj, curr_path[level - 1], N)) / 2);
            else
                curr_bound -= ((secondMin(adj, i, N) + firstMin(adj, curr_path[level - 1], N)) / 2);

            // curr_bound + curr_weight is the actual lower bound for the node that we have arrived on
            // If the current lower bound < final_res, we need to explore the node further
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path, final_path, visited, N, final_res);
            }

            // Else, we have to prune the node by resetting all changes to curr_weight and curr_bound
            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;

            // Also reset the visited array
            visited[i] = false;
            for (int j = 0; j < level; j++)
                visited[curr_path[j]] = true;
        }
    }
}

// This function sets up final_path[]
void TSP(int adj[][MAX_N], int N) {
    int curr_path[MAX_N + 1];
    bool visited[MAX_N];

    // Initialize final_res to a large value
    int final_res = INT_MAX;
    int final_path[MAX_N + 1];

    // Calculate initial lower bound for the root node
    int curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(visited));

    // Compute initial bound
    for (int i = 0; i < N; i++)
        curr_bound += (firstMin(adj, i, N) + firstMin(adj, i, N));

    // Rounding off the lower bound to an integer
    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    // We start at vertex 0, so the first vertex in curr_path[] is 0
    visited[0] = true;
    curr_path[0] = 0;

    // Call TSPRec for curr_weight equal to 0 and level 1
    TSPRec(adj, curr_bound, 0, 1, curr_path, final_path, visited, N, final_res);

    // Print the result
    cout<<"Minimum cost:"<<final_res;
    cout<<"\nPath That covers cities: ";
    for (int i = 0; i <= N; i++)
        cout<<final_path[i]<<" -> ";
}
int main() {
    int N;
    cout << "Enter the number of cities: ";
    cin >> N;

    // Adjacency matrix for the given graph
    int adj[MAX_N][MAX_N];
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
        	cout<<"Enter for adj["<<i+1<<"]["<<j+1<<"]:";
            cin >> adj[i][j];
        }
        cout<<"\n-----------------------------------------\n";
    }

    // Call the TSP function
    TSP(adj, N);

    return 0;
}

