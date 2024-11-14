#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> distancia_vertice; 


vector <int> dijkstra(int num_v, list<distancia_vertice> * arestas, int v_init){
        
    // Inicializa as distâncias com infinito
    vector<int> dist(num_v + 1, INT_MAX);
    
    dist[v_init] = 0; // Distância do vértice inicial para ele mesmo é 0

    // Fila de prioridade para processar os vértices pelo menor caminho
    priority_queue<distancia_vertice, vector<distancia_vertice>, greater<distancia_vertice>> pq;
    
    pq.push(make_pair(0, v_init)); // (distância, vértice) 

    while (!pq.empty()) {
        
        int dist_atual = pq.top().first;     // distância até o vértice atual
        int vertice_atual = pq.top().second; // vértice atual
       
        pq.pop();

        // Ignora se a distância armazenada na fila não é a mais curta / evita processamento desnecessário
        if (dist_atual > dist[vertice_atual]) continue;
            
        // Atualiza as distâncias para os vizinhos
        for (auto vizinho : arestas[vertice_atual]) {
            
            int proximo_vertice = vizinho.first;
            int peso_aresta = vizinho.second;

            // Se a nova distância for menor, atualiza
            if (dist[vertice_atual] + peso_aresta < dist[proximo_vertice]) {
                
                dist[proximo_vertice] = dist[vertice_atual] + peso_aresta;
                
                pq.push(make_pair(dist[proximo_vertice], proximo_vertice));
            }
        }
    }

    return dist;
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
    
    list<pair<int, int>> arestas[n + 1]; //Array de listas de pares de inteiros 
    
    //ex: Aresta do vértice 1 ao vértice 2 com peso 5 -> arestas[1].push_back(make_pair(2, 5));
    
    for (int i = 0; i < m; i++){  // Lê as arestas 
        
        fin >> v1 >> v2 >> pesso;
        
        arestas[v1].push_back(make_pair(v2, pesso));
        arestas[v2].push_back(make_pair(v1, pesso));
    }
    fin.close(); // Fecha o arquivo de entrada

    
    // Dijkstra -> vai retorna um vetor com as distâncias mínimas de um vértice inicial para todos os outros
     vector<int> dist_v_inicial = dijkstra(n, arestas, init);

    if (!(out == "")) { // Se o arquivo de saída foi especificado
        
        ofstream fout(out); 
        
        if (!fout) {
            cerr << "Não foi possível abrir o arquivo de output: " << out << endl;
            return 1;
        }
        
        // Imprime as distâncias mínimas no arquivo de saída
        for (int i = 1; i <= n; ++i) 
        {
            if(dist_v_inicial[i] != INT_MAX){

             fout << i << ":" << dist_v_inicial[i] << " "; // Se a distância for diferente de infinito, imprime
            }   
            else{ 
                fout << i << ":" << -1 << " ";
            }
        }
        
        fout << endl; 
        fout.close();
        }

        // Imprime as distâncias mínimas na saída padrão
        for (int i = 1; i <= n; ++i) 
        {
            if(dist_v_inicial[i] != INT_MAX )  cout << i << ":" << dist_v_inicial[i] << " ";
            
            else cout << i << ":" << -1 << " ";
        }
        cout << endl;
        
        return 0;
    }