#include<unordered_map>
#include<list>
#include<queue>

using namespace std;

bool checkForCycleBFS(int node, unordered_map<int, bool> &visited, unordered_map<int, list<int> > &adj) {
    unordered_map<int, int> parent;
    visited[node] = 1;
    parent[node] = -1;

    queue<int> q;
    q.push(node);

    while(!q.empty()) {
        int top = q.front();
        q.pop();

        for(auto neighbour : adj[top]) {
            if(visited[neighbour] == true && neighbour != parent[top]) {
                return true;
            }
            else if(!visited[neighbour]) {
                visited[neighbour] = 1;
                parent[neighbour] = top;
                q.push(neighbour);
            }
        }
    }
    return false;
}

bool checkForCycleDFS(int node, int parent, unordered_map<int, bool> &visited,
                        unordered_map<int, list<int> > &adj) {
    visited[node] = true;

    for(auto neighbour : adj[node]) {
        if(!visited[neighbour]) {
            bool cDetected = checkForCycleDFS(neighbour, node, visited, adj);
            if(cDetected) {
                return true;
            }
        }
        else if(neighbour != parent) {
            return true;
        }
    }
    return false;
}

string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    //prepare a adjancy list
    unordered_map<int, list<int> > adj;
    for(int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    unordered_map<int, bool> visited;

    //cycle detection
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            bool ans = checkForCycleDFS(i,-1, visited, adj);
                if(ans) {
                    return "Yes";
            }
        }
    }
    return "No";
}