#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include <vector>
#include <iostream>

using namespace std; 
# define INF 0x3f3f3f3f 

typedef struct vertex
{
    int weight;
    int V;

    bool operator == (const vertex &p) const{
        return (this->weight == p.weight)&&(this->V == p.V);
    }
    bool operator < (const vertex &p) const{
        return weight < p.weight;
    }
    bool operator > (const vertex &p) const{
        return weight > p.weight;
    }

}vertex;

class dijkstra
{
public:
    void encode(int* index, int x, int y, int size_y);
    void decode(int index, int* x, int* y, int size_y);
    void PathAdd(vector <vertex> adj[], int u, 
                                     int v, int wt);
    void CalculatePath(vector<vertex > adj[], vector<pair<int,int> >* path, 
                                    int V, int src);
};
#endif // DIJKSTRA_H