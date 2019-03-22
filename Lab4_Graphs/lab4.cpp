#include <iostream>
#include <string>

using namespace std;

#define V 10
# define INF 9999

class Prim
{
    private:
        int num_edges;
        int num_vertices;
        int graph[V][V];
        int visited[V];
        int mindDistance[V];
        string mstResults;

    public:
        void input(int _num_vertices, int _num_edges, int _graph[V][V]);
        void printAdjMatrix();
        void findMST();
        void printMST();

    Prim()
    {
        num_edges = 0;
        num_vertices = 0;
        for(int i=0; i<V; i++) {

            visited[i] = 0;
            mindDistance[i] = 0;

            for(int j=0; j<V; j++) {
            graph[i][j] = 0;
            }
        }
    }
};

// pass V,E and Matrix
void Prim::input(int _num_vertices, int _num_edges, int _graph[V][V]) {

    num_edges =  _num_edges;
    num_vertices = _num_vertices;

    // copy adjacency matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = _graph[i][j];
        }
    }
}

void Prim::printAdjMatrix() {
    for (int i = 0; i < num_vertices; i++) {

        cout<<endl;
        for (int j = 0; j < num_vertices; j++) {
            cout.width(4);
            cout<<graph[i][j];
        }
        cout<<endl;
    }
}

void Prim::findMST() {
    
    int min = INF; // assign all to INF
    int row, col, index = 0;

    for (int i = 0; i < num_vertices; i++) {
        // traverse the graph
        for (int j = i; j < num_vertices; j++) {

            if(graph[i][j] < min && graph[i][j] != 0) {
                min = graph[i][j];
                row = i;
                col = j;
            }
        }
    }
    visited[row] = 1;
    visited[col] = 1;
    mindDistance[index++] = min;
    mstResults += 
            to_string(row) + " --- " +
            to_string(col) + " === " +
            to_string(min) + "\n";


    for(int i = 0; i < num_vertices-2; i++) {
        min = INF;
        for (int j = 0; j < num_vertices; j++) {
            if(visited[j] == 1) {
                // traverse the graph
                for (int k = 0; k < num_vertices; k++) {

                    if(graph[j][k] < min && graph[j][k] != 0 && visited[k]==0) {
                        min = graph[j][k];
                        row = j;
                        col = k;
                    }
                }
            }  
        }
        mindDistance[index++] = min;
        visited[row] = 1;
        visited[col] = 1;
        mstResults += 
            to_string(row) + " --- " +
            to_string(col) + " == " +
            to_string(min) + "\n";
    }
}

void Prim::printMST() {
    int total = 0;
    cout<<endl;
    cout<<"The edges in the minimum spanning tree are:"<<endl;
    cout<<mstResults;

    for(int i=0; i<num_vertices-1;i++) 
    {
        total = total + mindDistance[i];
    }
    cout<<"Total weight is: " <<total<<endl;
}

/*Given a graph as input, write an algorithm 
  to determine a minimum spanning tree.
  
  Create the following graph and a second graph 
  you define it yourself.

        5
    0−−−−−−−−1
    |  \     |
  3 |   2\   | 7
    |      \ |
    2−−−−−−−−3
        2 
*/

int main()
{
    cout<< "=============================================\n";
    cout<< "=============================================\n";

    int v = 4;
    int e = 5;
    int graph[V][V] = {
        {0,5,3,2},
        {5,0,0,7},
        {3,0,0,2},
        {2,7,2,0},
    };

    Prim obj;
    obj.input(v,e,graph);
    obj.printAdjMatrix();
    obj.findMST();
    obj.printMST();

    cout<< "=============================================\n";
    cout<< "=============================================\n";
    int v2 = 5;
    int e2 = 8;
    int graph2[V][V] = {
        {0, 9, 75, 0, 0},
        {9, 0, 95, 19, 42},
        {75, 95, 0, 51, 66},
        {0, 19, 51, 0, 31},
        {0, 42, 66, 31, 0}
    };
    
    Prim obj2;
    obj2.input(v2,e2,graph2);
    obj2.printAdjMatrix();
    obj2.findMST();
    obj2.printMST();

    cout<< "=============================================\n";
    cout<< "=============================================\n";

    return 0;
}