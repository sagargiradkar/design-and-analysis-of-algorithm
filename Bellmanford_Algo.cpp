#include<iostream>
using namespace std;

struct Node{
    int vertex;
    int weight;
    Node *next;
};

class LinkedList{
    public:
        Node* head;
    public:
        LinkedList(){
            head=NULL;
        }
        void insert(int v, int w);
};

void LinkedList::insert(int v, int w){
    if(head==NULL){
        head = new Node;
        head->vertex = v;
        head->weight = w;
        head->next = NULL;
    }
    else{
        Node* temp = new Node;
        temp->next = head;
        temp->vertex = v;
        temp->weight = w;
        head = temp;
    }
}

struct Table{
    int dist;
    int par;
};

void BellFordAlgo(LinkedList graph[],Table t[], int v, int e){
    bool flag=true;
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            Node* temp = graph[j].head;
            while(temp!=NULL){
                if(t[temp->vertex].dist>(t[j].dist+temp->weight)){

                    if(i==(v-1)){
						cout<<"Cant find shortest distance due to negative weighted cycle"<<endl;
						flag=false;
						break;
					}

                    t[temp->vertex].dist=(t[j].dist+temp->weight);
                    t[temp->vertex].par = j;
                }
                temp = temp->next;
            }
            if(flag==false){
                break;
            }
        }
    }
    if(flag==true){
        cout<<"\nVertex  Distance(V)  Parent(V)"<<endl;
		for(int i=0;i<v;i++){
			cout<<"  "<<i<<"         "<<t[i].dist<<"           "<<t[i].par<<endl;
		}
    }
}

int main()
{
    LinkedList graph[50];
    Table t[50];
    int v,e,source;
    cout<<"Enter number of vertices: ";
	cin>>v;
    cout<<"Enter the number of edges: ";
	cin>>e;
    for(int i=0;i<e;i++){
		int s,d,w; 
        cout<<"Enter details of Edge "<<i+1<<":-"<<endl;
		cout<<"Source: ";
		cin>>s;
        cout<<"Destination: ";
		cin>>d;
        cout<<"Weight: ";
		cin>>w;
        graph[s].insert(d,w);
	}
    cout<<"Enter the source of Graph: ";
    cin>>source;
    for(int i=0;i<v;i++){
        t[i].par=-1;
        t[i].dist=99999;
    }
    t[source].dist=0;

    // v=5;
    // e = 7;
    // graph[0].insert(1,6);
    // graph[0].insert(2,5);
    // graph[2].insert(1,-2);
    // graph[2].insert(3,4);
    // graph[2].insert(4,3);
    // graph[1].insert(3,-1);
    // graph[3].insert(4,3);
    
    // t[0].par=-1;
    // t[1].par=-1;
    // t[2].par=-1;
    // t[3].par=-1;
    // t[4].par=-1;

    // t[0].dist=0;
    // t[1].dist=999999;
    // t[2].dist=999999;
    // t[3].dist=999999;
    // t[4].dist=999999;
    
    // Answer
    // Vertex  Distance(V)  Parent(V)
    //   0         0           -1
    //   1         3           2
    //   2         5           0
    //   3         2           1
    //   4         5           3

    BellFordAlgo(graph,t,v,e);

    return 0;
}