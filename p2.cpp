#include<iostream> 
#include <list> 
#include <stack> 
#include <limits.h> 
#include <queue> 
#include <cstring>
#include<time.h>
#include <algorithm>
#include <vector>
#define NIL -1 
using namespace std; 
int max_flow = 0,  V = 0; 
/*typedef struct noddy{
    int in;
    int sup = 0;
    int in;
} node;*/

vector<int> *adjacent;
vector<int> *rGraph;

bool release(int u, int v){
    int x=0;
    bool found = false;
    printf("V: %d\n", v);
    for (x = 0; x < rGraph[u].size(); x++){
        printf("%d\n", rGraph[u].at(x));
    }
    for(x = 0; x < rGraph[u].size(); x++){
        if(rGraph[u][x] == v){
            found = true;
        }
        if (found && x < rGraph[u].size() - 1){
            rGraph[u].at(x) = rGraph[u].at(x+1);
        }
        else if (found && x == rGraph[u].size() - 1){
            rGraph[u].pop_back();
        }
    }
    for (x = 0; x < rGraph[u].size(); x++){
        printf("%d\n", rGraph[u].at(x));
    }
    if (found){
        printf("ENCONTROU\n");
        return true;
    }
    else{
        return false;
    }
}

bool bfs(int s, int t, int parent[]) 
{ 
    // Create a visited array and mark all vertices as not visited 
    bool visited[V]; 
    memset(visited, 0, sizeof(visited)); 
    int u, z;
    queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parent[s] = -1;
    while (!q.empty()) 
    { 
        u = q.front(); 
        q.pop(); 
        for (int &v:rGraph[u]) 
        {
            if (visited[v]==false) 
            { 
                q.push(v); 
                parent[v] = u; 
                visited[v] = true;
            }
        } 
    }
    return (visited[t] == true); 
} 
  
// Returns the maximum flow from s to t in the given graph 
int fordFulkerson() 
{ 
    int u, v, s=0, t=V-1, counter = 0;

    rGraph= new vector<int>[V]; 
    for (u = 0; u < V; u++){
        for (v = 0; v < adjacent[u].size(); v++){
             rGraph[u].push_back(adjacent[u][v]);
        } 
    }
    int parent[V];
    while (bfs(s, t, parent)) 
    {  
        for (v=t; v != s; v=parent[v]) 
        { 
            
            u = parent[v]; 
            /*mandar embora o v do rgraph[u]*/ 
            release(u, v);
        }
        /*if (rGraph[u].size() <= 0){
            counter++;
        }
        if (counter == t){
            break;
        }*/
        max_flow++;
    } 
    return max_flow; 
} 


int main() 
{
    int nrAvs, nrStrts, e, nrSpmrkt, nrCtzn, x1, y1, nrNodes, pos;
    cin>>nrAvs>>nrStrts;
    nrNodes = 2*nrAvs*nrStrts + 2;
    cin>>nrSpmrkt>>nrCtzn;
    adjacent= new vector<int>[nrNodes]; 
    for(e = 0; e<nrNodes; e+=2){ 
        if ((e!=0) && (e != nrNodes)){
            adjacent[e-1].push_back(e);
            if((e-2)/2 > nrStrts){
                adjacent[e].push_back(e-(nrAvs*2) - 1);
            }
            if(e/2 < nrStrts*(nrAvs-1)){
                adjacent[e].push_back(e+(nrAvs*2) - 1);
            }
            if((e-2)/2 % nrAvs!=0){
                adjacent[e].push_back(e-3);
            }
            if(e/2 % nrAvs!=0){
                adjacent[e].push_back(e+1);
            }
        }
    }   
    for(e = 0; e<nrSpmrkt; e++){
        cin>>y1>>x1;
        pos = 2*(y1-1)*nrAvs + 2*(x1-1) + 2;
        adjacent[pos].push_back(nrNodes-1);   
    }
    for(e = 0; e<nrCtzn; e++){
        cin>>y1>>x1;
        pos = 2*(y1-1)*nrAvs + 2*(x1-1) + 2;
        adjacent[0].push_back(pos-1); 
    }
    V = nrNodes;
    /*for(int x = 0; x<adjacent[24].size(); x++){
        printf("%d \n", adjacent[24][x]);
    }*/
    fordFulkerson();
    printf("MaxFlow = %d\n", max_flow);
    
}