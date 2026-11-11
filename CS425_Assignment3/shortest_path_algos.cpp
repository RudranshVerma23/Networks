#include <bits/stdc++.h>
using namespace std;

vector<string> nodes = {"A", "B", "C", "D", "E", "F", "G", "H", "J", "K"};
size_t V = nodes.size();
vector<vector<int>> graph = {
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 3, 1, 0, 4, 0},
    {0, 0, 0, 0, 5, 0, 0, 1, 2, 1},
    {1, 0, 0, 5, 0, 0, 1, 0, 0, 0},
    {0, 0, 3, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 4, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 0}
};

void dijkstra(vector<vector<pair<int,int>>>& adj, int src, int dest) {
    int V = adj.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V, INT_MAX), parent(V, -1);
    dist[src] = 0;
    pq.emplace(0, src);
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int d = top.first, u = top.second;
        if (d > dist[u]) continue;
        for (auto &p : adj[u]) {
            int v = p.first, w = p.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
    cout << "Dijkstra's shortest path from " << nodes[src] << " to " << nodes[dest] << endl;
    if (dist[dest] == INT_MAX) cout << "No path exists." << endl;
    else cout << "Total cost: " << dist[dest] << endl;
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << nodes[path[i]];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void dijkstra(const vector<vector<pair<int, int>>>& adj, int src, int dest) {
    int V = adj.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(V, 2147483647), parent(V, -1);

    dist[src] = 0;
    pq.emplace(0, src);
    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second; // Structured binding (C++17)
        pq.pop();
        if (d > dist[u]) continue;
        for (auto x : adj[u]) {
            int v=x.first,w=x.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
    cout << "Shortest path from " << nodes[src] << " to " << nodes[dest] << ":" << endl;
    if (dist[dest] == 2147483647) {
        cout<<"Status: No path found."<<endl;
        return;
    }
    string path_str = "";
    for(int v=dest;v !=-1; v= parent[v])
        path_str = nodes[v] + (v==src ? "" : " -> ") + path_str;
    cout << "Cost: " << dist[dest] << endl << "Path: " << path_str << endl;
}

void bellmanFord(const vector<vector<int>>& edges, int src, int dest) {
    const int INF = 1e8;
    vector<int> dist(V, INF);
    vector<int> parent(V, -1);
    
    dist[src] = 0;

    // Run V iterations: V-1 for paths, the last one for cycle detection
    for (int i = 0; i < V; i++) {
        for (const vector<int>& edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];

            if (dist[u]!= INF && dist[u] +wt<dist[v]) {
                if (i==V-1) {
                    cout<<"!!! Negative weight cycle detected !!!"<<endl;
                    return;
                }
                dist[v]=dist[u]+wt,parent[v] = u;
            }
        }
    }
    cout << "Bellman-Ford: " << nodes[src] << " to " << nodes[dest] << endl;
    if (dist[dest] == INF) 
        cout << "Status: No path exists." << endl;
    else {
        cout << "Cost: "<<dist[dest]<<endl;
        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        cout << "Path: ";
        for(int i = 0; i < path.size(); i++) cout<<nodes[path[i]]<<(i == path.size()-1?"":" -> ");
        cout << endl;
    }
}

int main() {
    cout << "=== Shortest Path Finder ===" << endl;
    cout << "Available nodes: ";
    for (int i = 0; i < V; i++) cout << nodes[i] << " ";
    cout << endl;
    string srcName, destName;
    cout << "Enter source node: ";
    cin >> srcName;
    cout << "Enter destination node: ";
    cin >> destName;
    int src = -1, dest = -1;
    for (int i = 0; i < V; i++) {
        if (nodes[i] == srcName) src = i;
        if (nodes[i] == destName) dest = i;
    }
    if (src == -1 || dest == -1) {
        cout << "Invalid node name(s) entered!" << endl;
        return 1;
    }
    int choice;
    cout << "Choose Algorithm:" << endl;
    cout << "1. Dijkstra (Link State)" << endl;
    cout << "2. Bellman-Ford (Distance Vector)" << endl;
    cout << "3. Both" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    if (choice != 1 && choice != 2 && choice != 3) {
        cout << "Invalid choice!" << endl;
        return 1;
    }
    vector<vector<pair<int, int>>> adj(V);
    vector<vector<int>> edges;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j]) {
                adj[i].emplace_back(j, graph[i][j]);
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }
    if (choice == 1 || choice == 3) dijkstra(adj, src, dest);
    if (choice == 2 || choice == 3) bellmanFord(edges, src, dest);
    return 0;
}
