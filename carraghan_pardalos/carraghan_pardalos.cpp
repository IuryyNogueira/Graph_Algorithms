#include <bits/stdc++.h>

using namespace std;

// Variáveis globais:
vector<int> maxClique;
size_t tam_cliqueMAX = 0;

// Função principal do Carraghan-Pardalos para explorar os cliques
void branchAndBound(const vector<vector<int>>& graph, vector<int>& Clique_atual, vector<int>& candidatos) {
    
    // Se não houver mais candidatos, verificamos a solução atual
    if (candidatos.empty()){
        
        if (Clique_atual.size() > tam_cliqueMAX){   
            
            maxClique = Clique_atual;
            tam_cliqueMAX = Clique_atual.size();
        }
        return;
    }

    //Exploramos cada candidato recursivamente
    for (size_t i = 0; i < candidatos.size(); ++i) {
       
        int vertice = candidatos[i];

        //Adicionar o vértice ao clique atual
        Clique_atual.push_back(vertice);

        // Gerar o novo conjunto de candidatos
        vector<int> newCandidatos;
        
        for (size_t j = i + 1; j < candidatos.size(); ++j){     
            
            //verifica se é vizinho
            //se 'j' o vertice candidato é vizinho de 'vertice' 
            //a função find retorna o iterador para o elemento se ele for encontrado ou o iterador para o final do vetor caso contrário
            if (find(graph[vertice].begin(), graph[vertice].end(), candidatos[j]) != graph[vertice].end())
            {
                newCandidatos.push_back(candidatos[j]);
            }
        }

        // Recursão com o clique atualizado
        branchAndBound(graph, Clique_atual, newCandidatos);

        // Backtracking: remover o vértice atual
        Clique_atual.pop_back();
    }
}

int main() {
    
    int n, m;
    cin >> n >> m;

    // grafo como uma lista de adjacência
    vector<vector<int>> graph(n);

    //Leitura
    for (int i = 0; i < m; ++i) {
        
        int u, v;
        cin >> u >> v;
        
        u--; v--; // Ajuste para índices baseados em 0
        
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Inicializando o conjunto de candidatos
    vector<int> candidatos;
    
    for (int i = 0; i < n; ++i) {   //vertices
        candidatos.push_back(i);
    }

    vector<int> Clique_atual;
    
    branchAndBound(graph, Clique_atual, candidatos);//
    
    // Imprimindo o tamanho do clique máximo
    cout << "Tamanho do clique máximo: " << tam_cliqueMAX << endl;

    
    // Imprimindo o clique máximo
    cout << "Clique máximo: ";
    for (int v : maxClique){
        cout << v + 1 << " ";  // Ajuste para mostrar como 1-indexed
    }
    cout << endl;

    return 0;
}
