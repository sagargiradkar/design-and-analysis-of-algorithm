#include <bits/stdc++.h>
using namespace std;

struct table
{
    float pw;
    float p;
    float w;
};

void Knapsack(float m, int n)
{
    float x[50], Total = 0;
    table t[50];

    cout << "\n >>> Enter the Profit of Object :- \n";
    for (int i = 0; i < n; i++)
    {
        cout << " >> p[" << i << "] = ";
        cin >> t[i].p;
    }

    cout << "\n >>> Enter the Weight of Object :- \n";
    for (int i = 0; i < n; i++)
    {
        cout << " >> w[" << i << "] = ";
        cin >> t[i].w;
    }

    for (int i = 0; i < n; i++)
    {
        t[i].pw = t[i].p / t[i].w;
    }

    sort(t, t + n, [](const table &a, const table &b) {
        return a.pw > b.pw;
    });

    float u = m;

    for (int i = 0; i < n; i++)
    {
        x[i] = 0.0;

        for (int j = 0; j < n; j++)
        {
            if (t[j].w > u)
            {
                break;
            }
            x[j] = 1.0;
            u = u - t[j].w;
            Total += t[j].p;
            i++;
        }

        if (i < n)
        {
            x[i] = u / t[i].w;
            Total += x[i] * t[i].p;
            u = 0;
        }
    }

    cout << "\n -->  Fixed Solution Vector x = [ ";
    for (int i = 0; i < n; i++)
    {
        cout << x[i] << " ";
    }
    cout << "]";

    cout << "\n\n --> Total Profit Earned = " << Total << " units. \n\n";
}

int main()
{
    int n;
    float m;

    cout << "\n\n \t\t *** Knapsack Problem *** \n\n\n";

    cout << " >> Enter the Knapsack Capacity = ";
    cin >> m;
    cout << endl;
    cout << " >> Enter the No of Objects = ";
    cin >> n;

    Knapsack(m, n);

    return 0;
}
