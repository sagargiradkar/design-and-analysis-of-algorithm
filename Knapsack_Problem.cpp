#include<iostream>
using namespace std;

struct table
{
	float pw;
	float p;
	float w;
};

void Merge(table a[], int low, int high, int mid)
{
	int i=low,j=mid+1,k=0;
	table temp[high-low+1];

	while(i<=mid && j<= high)
	{
		if(a[i].pw>a[j].pw)  // comparison step
		{             
		    temp[k++] = a[i++];	    
		}    

		else
		{
		    temp[k++]=a[j++];	    	    
		}    
	}

	while(i<=mid)
    {
        temp[k++]=a[i++];      
    }

	while(j<=high)
    {
        temp[k++]=a[j++];	
    }

	for(i=low;i<=high;i++)
	{
		a[i]=temp[i-low];
	}
}

void MergeSort(table a[], int low, int high)
{
	int mid;

	if(low<high)
	{
	    mid=(low+high)/2;

	    MergeSort(a, low, mid);
	    MergeSort(a, mid+1,high);

	    Merge(a, low, high, mid);
	}
}

void Knapsack(float m, int n)
{
	// Declaration of Arrays
	float x[50], Total = 0;
	table t[50];
	
	// for loop for taking input profit
	cout<<"\n >>> Enter the Profit of Object :- \n";
	for(int i=0; i<n; i++)
	{
		cout<<" >> p["<<i<<"] = ";
		cin>>t[i].p;
	}
	// for loop for taking input weight
	cout<<"\n >>> Enter the Weight of Object :- \n";
	for(int i=0; i<n; i++)
	{
		cout<<" >> w["<<i<<"] = ";
		cin>>t[i].w;
	}
	
	for(int i=0; i<n; i++)
	{
		t[i].pw = t[i].p/t[i].w;
	}	
	
	// Sorting of arrays in descending order 
	MergeSort(t, 0, n);

	float u = m;
	
	for(int i = 0; i<n; i++)
	{
		x[i] = 0.0;
		
		for(int j = 0; j<n; j++)
		{
			if(t[j].w>u)
			{
				break;
			}
			x[j] = 1.0;
			u = u-t[j].w;
			Total += t[j].p;
			i++;
		}	
		
		if(i<n)
		{
			x[i] = u/t[i].w;
			Total += x[i]*t[i].p;
			u = 0;
		}
	}	
	
	cout<<"\n -->  Fixed Solution Vector x = [ ";
	for(int i=0; i<n; i++)
	{
		cout<<x[i]<<" ";
	}
	cout<<"]";

	cout<<"\n\n --> Total Profit Earned = "<<Total<<" units. \n\n";
}

int main()
{
	int n;
	float m;
	
	cout<<"\n\n \t\t *** Knapsack Problem *** \n\n\n";
	
	cout<<" >> Enter the Knapsack Capacity = ";
	cin>>m;
	cout<<endl;
	cout<<" >> Enter the No of Objects = ";
	cin>>n;
	
	Knapsack(m, n);
	

	return 0;
}
