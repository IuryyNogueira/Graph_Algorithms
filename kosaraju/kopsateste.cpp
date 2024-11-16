#include <bits/stdc++.h>
using namespace std;

void dfs1(int v, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& finishStack) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs1(u, adj, visited, finishStack);
        }
    }
    finishStack.push(v);
}

void dfs2(int v, vector<vector<int>>& adjT, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int u : adjT[v]) {
        if (!visited[u]) {
            dfs2(u, adjT, visited);
        }
    }
}

int main(int argc, char *argv[]) {
    string in = "";
    string out = "";
    bool ans = false;
    int init = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            out = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            in = argv[++i];
        }
    }

    if (in == "") {
        cout << "Arquivo de entrada não especificado." << endl;
        return 1;
    }

    ifstream inputFile(in);
    if (!inputFile) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int n, m;
    inputFile >> n >> m;
    vector<vector<int>> adj(n), adjT(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        inputFile >> u >> v;
        adj[u].push_back(v);
        adjT[v].push_back(u);
    }

    inputFile.close();

    stack<int> finishStack;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1(i, adj, visited, finishStack);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!finishStack.empty()) {
        int v = finishStack.top();
        finishStack.pop();
        if (!visited[v]) {
            dfs2(v, adjT, visited);
            cout << endl;
        }
    }

    return 0;
}