#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string.h>
using namespace std;

// Classe para a solução do algoritmo de Prim
class Solucao {
public:
    pair<int, vector<pair<int, int>>> algoritmoPrim(int numVertices, vector<vector<pair<int, int>>> &grafo, int verticeInicial) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;
        vector<int> visitado(numVertices, 0);
        vector<int> pai(numVertices, -1);

        // Inserindo o vértice inicial na fila com peso 0
        filaPrioridade.push(make_pair(0, verticeInicial));

        int somaPesos = 0;
        vector<pair<int, int>> arestasMST;

        while (!filaPrioridade.empty()) {
            auto topo = filaPrioridade.top();
            filaPrioridade.pop();

            int verticeAtual = topo.second;
            int pesoAtual = topo.first;

            if (visitado[verticeAtual] == 1) continue;
            visitado[verticeAtual] = 1;
            somaPesos += pesoAtual;

            if (verticeAtual != verticeInicial) {
                arestasMST.push_back(make_pair(pai[verticeAtual], verticeAtual));
            }

            // Iterando sobre os vizinhos do vértice atual
            for (auto vizinho : grafo[verticeAtual]) {
                int verticeVizinho = vizinho.first;
                int pesoAresta = vizinho.second;
                if (!visitado[verticeVizinho]) {
                    pai[verticeVizinho] = verticeAtual;
                    filaPrioridade.push(make_pair(pesoAresta, verticeVizinho));
                }
            }
        }

        return make_pair(somaPesos, arestasMST);
    }
};

int main(int argc, char *argv[]) {
    string arquivoEntrada = "";
    string arquivoSaida = "";
    string opcaoSaida = "peso";
    int verticeInicial = 1;

    // Processando os argumentos de linha de comando
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Ajuda:\n";
            cout << "-h: mostra este menu de ajuda\n";
            cout << "-o <arquivo>: redireciona a saída para o arquivo\n";
            cout << "-f <arquivo>: lê o grafo do arquivo\n";
            cout << "-s : mostra as arestas da solução\n";
            cout << "-i <vertice>: define o vértice inicial (1-indexado)\n";
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            arquivoSaida = argv[i + 1];
            opcaoSaida = "nenhuma";
        } else if (strcmp(argv[i], "-f") == 0) {
            arquivoEntrada = argv[i + 1];
        } else if (strcmp(argv[i], "-s") == 0) {
            opcaoSaida = "arestas";
        } else if (strcmp(argv[i], "-i") == 0) {
            verticeInicial = atoi(argv[i + 1]) - 1; // Convertendo para 0-indexado
        }
    }

    if (arquivoEntrada == "") {
        cout << "Nenhum arquivo de entrada especificado. Use o parâmetro -f.\n";
        return 1;
    }

    ifstream entrada(arquivoEntrada);
    if (!entrada) {
        cerr << "Não foi possível abrir o arquivo de entrada: " << arquivoEntrada << endl;
        return 1;
    }

    int numVertices, numArestas;
    entrada >> numVertices >> numArestas;

    vector<vector<pair<int, int>>> grafo(numVertices);

    // Lendo as arestas do grafo
    for (int i = 0; i < numArestas; i++) {
        int vertice1, vertice2, peso;
        entrada >> vertice1 >> vertice2 >> peso;
        grafo[vertice1 - 1].push_back(make_pair(vertice2 - 1, peso));
        grafo[vertice2 - 1].push_back(make_pair(vertice1 - 1, peso));
    }

    entrada.close();

    Solucao solucao;
    auto resultado = solucao.algoritmoPrim(numVertices, grafo, verticeInicial);

    // Escrevendo o resultado no arquivo, se necessário
    if (!arquivoSaida.empty()) {
        ofstream saida(arquivoSaida);
        if (!saida) {
            cerr << "Não foi possível abrir o arquivo de saída: " << arquivoSaida << endl;
            return 1;
        }
        for (auto &aresta : resultado.second) {
            saida << "(" << aresta.first + 1 << ", " << aresta.second + 1 << ") ";
        }
        saida << endl;
        saida.close();
    }

    // Mostrando o resultado no console
    if (opcaoSaida == "peso") {
        cout << resultado.first << endl;
    } else if (opcaoSaida == "arestas") {
        for (auto &aresta : resultado.second) {
            cout << "(" << aresta.first + 1 << ", " << aresta.second + 1 << ") ";
        }
        cout << endl;
    }

    return 0;
}
