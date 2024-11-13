#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> vertice_pesso;


vector <int> dijkstra(int num_v, list<vertice_pesso> * arestas[], int v_init){



}


int main(int argc, char *argv[])
{
    string in = "";
    string out = "";
    bool ans = false;
    int init = 1;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-i: vértice inicial" << endl;
            return 0;
        }
        
        // Atribui o nome do arquivo de saída
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1){
            out = argv[++i];
        }
        
        // Atribui o nome do arquivo de entrada
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1){
            in = argv[++i];
        }
        
        // Atribui o vértice inicial
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1){
            init = atoi(argv[++i]);
        }
    }

    if (in == ""){
        cerr << "Sem input especificado. Use o parametro -f" << endl;
        return 1;
    }

    ifstream fin(in); // Abre o arquivo de entrada
    
    if (!fin){
        cerr << "Não foi possível abrir o arquivo de input: " << in << endl;
        return 1;
    }

    
    int n, m; // n = número de vértices, m = número de arestas
    fin >> n >> m;


    int v1, v2, pesso; // vertice, vertice e pesso.
    
    list<pair<int, int>> arestas[V + 1]; //Array de listas de pares de inteiros 
    
    //ex: Aresta do vértice 1 ao vértice 2 com peso 5 -> arestas[1].push_back(make_pair(2, 5));
    
    for (int i = 0; i < m; i++){  // Lê as arestas 
        
        fin >> v1 >> v2 >> pesso;
        
        arestas[v1].push_back(make_pair(v2, pesso));
        arestas[v2].push_back(make_pair(v1, pesso));
    }
    fin.close(); // Fecha o arquivo de entrada

    
    // Dijkstra
     vector<int> dist_v_inicial = dijkstra(n, arestas, init);

}