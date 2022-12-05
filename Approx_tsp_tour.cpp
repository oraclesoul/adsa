#include<bits/stdc++.h>
using namespace std;

void primMST(vector<vector<pair<int,int>>> &adj, vector<vector<int>> &mst)
{
    int V = adj.size();
    
    vector<int> parent(V,-1);
    vector<int> key(V,INT_MAX);
    vector<int> visited(V,0);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    key[0] = 0;
    pq.push({0,0});

    while(!pq.empty()){

        pair<int,int> p = pq.top();
        pq.pop();

        int wt = p.first;
        int u = p.second;

        if(visited[u])
            continue;
        
        visited[u] = 1;

        for(auto v : adj[u]){
            if(!visited[v.first] && v.second < key[v.first]){
                key[v.first] = v.second;
                pq.push({key[v.first],v.first});
                parent[v.first] = u;
            }
        }
    }

    for(int i = 1; i < V; i++){
        mst[parent[i]].push_back(i); 
    }


    return;

}

void dfs(vector<vector<int>> &mst, vector<int> &visited, vector<int> &tsp, int u){
    
    visited[u] = true;
    tsp.push_back(u);

    for(auto v : mst[u]){
        if(!visited[v]){
            dfs(mst,visited,tsp,v);
        }
    }
}

int main(){

    #ifndef ONLINE_JUDGE
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    int n,e;
    cin >> n >> e;

    vector<vector<pair<int,int>>> adj(n);

    for(int i = 0; i < e; i++){
        int u,v,w;
        cin >> u >> v >> w;

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<vector<int>> mst(n);

    primMST(adj,mst);

    vector<int> visited(n,0);

    vector<int> tsp;
    dfs(mst,visited,tsp,0);

    tsp.push_back(0);

    for(auto i : tsp){
        cout << i << " ";
    }

}