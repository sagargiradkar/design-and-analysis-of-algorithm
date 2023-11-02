#include<iostream>
using namespace std;

struct chart
{
	int weight;
	int profit;
};

int findMax(int a, int b)
{
    if(a>b)
    {
        return a;
    }
    return b;
}

void Knapsack(chart c[], int n, int w)
{
    int table[n+1][w+1];

    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=w;j++)
        {
            if(i==0 || j==0)
            {
                table[i][j]=0;  
            }

            else if(c[i-1].weight <= j)
            {
                table[i][j] = findMax(c[i-1].profit + table[i-1][j - c[i-1].weight],table[i-1][j]);
            }

            else
            {
                table[i][j] = table[i-1][j];
            }
        }
    }

    cout<<"\n --> Maximum Profit = "<<table[n][w]<<endl;

    int max = table[n][w], W = w;

    for (int i = n; i > 0 && max > 0; i--) 
    {
        if (max == table[i - 1][W])
            continue;    
        else 
        {
            cout<<"\n --> Item with weight "<<c[i - 1].weight<<" is selected";
            max = max - c[i - 1].profit;
            W = W - c[i - 1].weight;
        }
    }
}

int main()
{
    int n,w;
    chart c[50];
    cout<<"\n\n \t\t ***** 0-1 Knapsack Problem ***** \n\n";
    cout<<"\n >> Enter the number of items = ";
	cin>>n;
	cout<<"\n >> Enter the capacity of knapsack = ";
	cin>>w;

    // for loop for taking input profit
	cout<<"\n >>> Enter the Profit of Object :- \n";
	for(int i=0; i<n; i++)
	{
		cout<<" >> p["<<i<<"] = ";
		cin>>c[i].profit;
	}
	// for loop for taking input weight
	cout<<"\n >>> Enter the Weight of Object :- \n";
	for(int i=0; i<n; i++)
	{
		cout<<" >> w["<<i<<"] = ";
		cin>>c[i].weight;
	}

    Knapsack(c,n,w);

    cout<<endl;
}