#include "dijkstra.h"

void dijkstra::encode(int* index, int x, int y, int size_y)
{
    *index = x * size_y + y;
}
void dijkstra::decode(int index, int* x, int* y, int size_y)
{
    *x = index / size_y;
    *y = index % size_y;
}
// 加边
void dijkstra::PathAdd(vector <vertex > adj[], int u, 
                                     int v, int wt) 
{ 
    vertex vertex_u;
    vertex_u.weight = wt;
    vertex_u.V = v;

    vertex vertex_v;
    vertex_v.weight = wt;
    vertex_v.V = u;

    adj[u].push_back(vertex_u); 
    adj[v].push_back(vertex_v); 
} 
   

// 计算最短路
void dijkstra::CalculatePath(vector<vertex > adj[], vector<pair<int,int> >* path, int V, int src) 
{ 
    vector<int> vector_cost(V, INF); 
    vector<bool> passed(V, false);

    priority_queue< vertex, vector <vertex> , greater<vertex> > Q; 

    vertex start;
    start.V = src;
    start.weight = 0;
    Q.push(start); 
    vector_cost[src] = 0; 
  
    while (!Q.empty()) 
    { 
        int u = Q.top().V; 
        Q.pop(); 
        //cout << "now pop u: " << u << endl;
        if (passed[u]) {
            continue;
        }
        passed[u] = true;

        for (int i = 0; i < adj[u].size(); ++i) 
        { 

            int v = adj[u][i].V; 
            int weight = adj[u][i].weight; 
            //cout << "u:" << u << " v:"<< v << " weight:"<<weight<endl;

            if (vector_cost[v] > vector_cost[u] + weight) 
            { 
                vector_cost[v] = vector_cost[u] + weight; 

                vertex relax;
                relax.V = v;
                relax.weight = vector_cost[v];
                Q.push(relax); 
                //cout << " v: " << v << " u " << u << " u.dist " << dist[u] << " weight " << weight << endl;
                //cout << "u to v : " << u << " to " << v << endl;
                (*path)[v].first = v;
                (*path)[v].second = u;
            }
        }
    }
  
    // 打印最短路
    /*printf("Vertex Distance from Source\n"); 
    for (int i = 0; i < V; ++i) 
        printf("%d \t\t %d\n", i, dist[i]); */

} 
