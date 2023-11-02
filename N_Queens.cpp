// NQueens Problem 

#include<iostream>
using namespace std;
int x[50], p = 1;
char y[50];

bool Place(int k, int i)
{
	for(int j = 0;	j <= k-1; j++)
	{
		if((x[j] == i) || (abs(x[j] - i) == abs(j-k)))
		{
			return false;
		}
	}
	return true;
}

void NQueens(int k, int n)
{		
	int ans;
	
	for(int i = 0; i < n; i++)
	{
		if(Place(k, i))
		{
			x[k] = i;

			if(k == n-1)
			{	
				cout<<"\n >> Answer "<<p<<" : \n\n";
				p++;
				
				cout<<" --> [";

				for(int i = 0; i < n; i++)
				{
					cout<<" "<<x[i] + 1<<" ";
				}
				cout<<"]";
				cout<<"\n\n";

				for(int i = 0; i < n; i++)
				{
					ans = x[i] + 1;

					for(int j = 0; j < n; j++)
					{
						if(ans-1 == j)
						{
							y[j] = 'Q';
						}
						else
						{
							y[j] = '_';
						}
					}

					for(int j = 0; j < n; j++)
					{
						cout<<" "<<y[j]<<" ";	
					}
					cout<<"\n";
				}
				cout<<"\n";
			}
			else
			{	
				NQueens(k+1, n);
			}
		}
	}
}

int main()
{
	int n;
	
	cout<<"\n\n >> Enter the No. of Queens =  ";
	cin>>n;
	
	NQueens(0, n);

	cout<<endl;

	return 0;
}
