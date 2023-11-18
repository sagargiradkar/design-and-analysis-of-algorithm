#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 15;

void copyToFinal(int curr_path[], int final_path[], int N) {
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

int firstMin(int adj[][MAX_N], int i, int N) {
    int min_cost = INT_MAX;
    for (int k = 0; k < N; k++)
        if (adj[i][k] < min_cost && i != k)
            min_cost = adj[i][k];
    return min_cost;
}

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

void TSPRec(int adj[][MAX_N], int curr_bound, int curr_weight, int level, int curr_path[], int final_path[], bool visited[], int N, int &final_res) {
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinal(curr_path, final_path, N);
                final_res = curr_res;
            }
            return;
        }
    }

    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            if (level == 1)
                curr_bound -= ((firstMin(adj, i, N) + firstMin(adj, curr_path[level - 1], N)) / 2);
            else
                curr_bound -= ((secondMin(adj, i, N) + firstMin(adj, curr_path[level - 1], N)) / 2);

            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path, final_path, visited, N, final_res);
            }

            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;

            visited[i] = false;
            for (int j = 0; j < level; j++)
                visited[curr_path[j]] = true;
        }
    }
}

void TSP(int adj[][MAX_N], int N) {
    int curr_path[MAX_N + 1];
    bool visited[MAX_N];
    int final_res = INT_MAX;
    int final_path[MAX_N + 1];
    int curr_bound = 0;

    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < N; i++)
        curr_bound += (firstMin(adj, i, N) + firstMin(adj, i, N));

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    visited[0] = true;
    curr_path[0] = 0;

    TSPRec(adj, curr_bound, 0, 1, curr_path, final_path, visited, N, final_res);

    cout << "Minimum cost: " << final_res << endl;
    cout << "Path That covers cities: ";
    for (int i = 0; i <= N; i++)
        cout << final_path[i] << " -> ";
}

int main() {
    int N;
    cout << "Enter the number of cities: ";
    cin >> N;

    int adj[MAX_N][MAX_N];
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "Enter for adj[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> adj[i][j];
        }
        cout << "-----------------------------------------\n";
    }

    TSP(adj, N);

    return 0;
}
