#include <bits/stdc++.h>
using namespace std;

struct chart
{
    int weight;
    int profit;
};

int findMax(int a, int b)
{
    return (a > b) ? a : b;
}

void Knapsack(chart c[], int n, int w)
{
    int table[n + 1][w + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= w; j++)
        {
            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
            }
            else if (c[i - 1].weight <= j)
            {
                table[i][j] = findMax(c[i - 1].profit + table[i - 1][j - c[i - 1].weight], table[i - 1][j]);
            }
            else
            {
                table[i][j] = table[i - 1][j];
            }
        }
    }

    cout << "\n --> Fixed Solution Vector x = [ ";
    vector<int> selectedItems;

    int maxProfit = table[n][w];
    int remainingWeight = w;

    for (int i = n; i > 0 && maxProfit > 0; i--)
    {
        // Use std::find from the algorithm header
        if (std::find(selectedItems.begin(), selectedItems.end(), i) != selectedItems.end())
            continue;
        else
        {
            selectedItems.push_back(i);
            maxProfit -= c[i - 1].profit;
            remainingWeight -= c[i - 1].weight;
        }
    }

    // Output the solution vector
    for (int i = n; i > 0; i--)
    {
        if (std::find(selectedItems.begin(), selectedItems.end(), i) != selectedItems.end())
            cout << "1 ";
        else
            cout << "0 ";
    }
    cout << "]";

    cout << "\n\n --> Total Profit Earned = " << table[n][w] << " units. \n\n";
}

int main()
{
    int n, w;
    chart c[50];
    cout << "\n\n \t\t *** Knapsack Problem *** \n\n";
    cout << " >> Enter the Knapsack Capacity = ";
    cin >> w;
    cout << "\n >> Enter the No of Objects = ";
    cin >> n;

    cout << "\n >>> Enter the Profit of Object :- \n";
    for (int i = 0; i < n; i++)
    {
        cout << " >> p[" << i << "] = ";
        cin >> c[i].profit;
    }

    cout << "\n >>> Enter the Weight of Object :- \n";
    for (int i = 0; i < n; i++)
    {
        cout << " >> w[" << i << "] = ";
        cin >> c[i].weight;
    }

    Knapsack(c, n, w);

    cout << endl;
    return 0;
}
