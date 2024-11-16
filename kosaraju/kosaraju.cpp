#include <bits/stdc++.h>

using namespace std;

// Variáveis globais:
vector<vector<int>> adj, adj_reverso;       //grafo e grafo_reverso
vector<bool> visited;                   //vertices de visitados
stack<int> finishStack;                  //pilha 
vector<int> component;                    //componentes fortemente conexos                                          


void dfs1(int v) {
    
    visited[v] = true;  
    
    // Para cada vértice adjacente a v que não foi visitado, chama a DFS recursivamente 
    for (int u : adj[v]) {  
        if (!visited[u]) {
            dfs1(u);
        }
    }
    finishStack.push(v); // Empilha vértices na ordem de término da DFS
}


/*
 Realiza uma busca em profundidade no grafo reverso para 
 identificar todos os vértices do mesmo componente fortemente conexo que v. 
 Marca os vértices visitados e armazena o no vetor "component". 
 processando vértices na ordem da pilha.
 */
void dfs2(int v) {
    
    visited[v] = true;
    
    component.push_back(v); // Armazena os vértices visitados 
    
    for (int u : adj_reverso[v]){   // Para cada vértice adjacente a v que não foi visitado, chama a DFS recursivamente
        
        if (!visited[u]){ 
            dfs2(u);
        }
    }
}

int main(int argc, char* argv[]) {
    string in, out;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            return 0;
        } 
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            out = argv[++i];
        } 
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
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
    adj.resize(n);
    adj_reverso.resize(n);
    visited.resize(n, false);

    for (int i = 0; i < m; i++) {
        
        int u, v;
        inputFile >> u >> v;
        
        u--; // Ajusta para índice zero
        v--; 
        
        adj[u].push_back(v);
        adj_reverso[v].push_back(u);
    }
    inputFile.close();

    // Primeira passagem DFS (Kosaraju parte.1)
    for (int i = 0; i < n; i++) {
        // Se o vértice não foi visitado, chama a DFS
        if (!visited[i]){
            dfs1(i);
        }
    }

    fill(visited.begin(), visited.end(), false);    // Reseta o vetor de visitados 

    // Arquivo de saída
    ofstream outputFile;                            
    if (!out.empty()){
        outputFile.open(out);
        if (!outputFile) {
            cout << "Erro ao abrir o arquivo de saída." << endl;
            return 1;
        }
    }

    ostream &output = out.empty() ? cout : outputFile; // Redireciona a saída para o arquivo ou para a tela

    // Segunda passagem DFS (Kosaraju parte.2)
    while (!finishStack.empty()) {
        
        int v = finishStack.top(); // Pega o vértice do topo da pilha
        finishStack.pop();          // Remove 
        
        
        // Se o vértice não foi visitado, chama a DFS
        // Armazena os vértices visitados em um vetor de componentes
        if (!visited[v]){        
            
            component.clear();  // Limpa o vetor de componentes
            
            dfs2(v);
            
            for (int u : component) {
                output << (u + 1) << " "; // Converte de volta para índice 1
            }
            output << endl;    
        }
    }

    if (outputFile.is_open()) { // Fecha o arquivo de saída
        outputFile.close(); //
    }

    return 0;
}
