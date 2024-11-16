#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string.h>
using namespace std;

class ConjuntoDisjunto {
    vector<int> rank, pai, tamanho;
public:
    ConjuntoDisjunto(int numVertices) {
        rank.resize(numVertices + 1, 0);
        pai.resize(numVertices + 1);
        tamanho.resize(numVertices + 1);
        for (int i = 0; i <= numVertices; i++) {
            pai[i] = i;
            tamanho[i] = 1;
        }
    }

    int encontrarPai(int vertice) {
        if (vertice == pai[vertice]) return vertice;
        return pai[vertice] = encontrarPai(pai[vertice]);
    }

    void unirPorRank(int vertice1, int vertice2) {
        int pai1 = encontrarPai(vertice1);
        int pai2 = encontrarPai(vertice2);
        if (pai1 == pai2) return;
        if (rank[pai1] < rank[pai2]) {
            pai[pai1] = pai2;
        } else if (rank[pai1] > rank[pai2]) {
            pai[pai2] = pai1;
        } else {
            pai[pai2] = pai1;
            rank[pai1]++;
        }
    }

    void unirPorTamanho(int vertice1, int vertice2) {
        int pai1 = encontrarPai(vertice1);
        int pai2 = encontrarPai(vertice2);
        if (pai1 == pai2) return;
        if (tamanho[pai1] < tamanho[pai2]) {
            pai[pai1] = pai2;
            tamanho[pai2] += tamanho[pai1];
        } else {
            pai[pai2] = pai1;
            tamanho[pai1] += tamanho[pai2];
        }
    }
};

class Solucao {
public:
    pair<int, vector<pair<int, int>>> executarKruskal(int numVertices, vector<vector<pair<int, int>>> &adjacencias) {
        vector<pair<int, pair<int, int>>> todasArestas;
        for (int vertice = 0; vertice < numVertices; vertice++) {
            for (auto aresta : adjacencias[vertice]) {
                int destino = aresta.first;
                int peso = aresta.second;
                todasArestas.push_back(make_pair(peso, make_pair(vertice, destino)));
            }
        }

        ConjuntoDisjunto conjunto(numVertices);
        sort(todasArestas.begin(), todasArestas.end());

        int pesoTotalMST = 0;
        vector<pair<int, int>> arestasMST;

        for (auto aresta : todasArestas) {
            int origem = aresta.second.first;
            int destino = aresta.second.second;

            if (conjunto.encontrarPai(origem) != conjunto.encontrarPai(destino)) {
                pesoTotalMST += aresta.first;
                arestasMST.push_back(make_pair(origem, destino));
                conjunto.unirPorRank(origem, destino);
            }
        }

        return make_pair(pesoTotalMST, arestasMST);
    }
};

int main(int argc, char *argv[]) {
    string arquivoEntrada = "";
    string arquivoSaida = "";
    string tipoSaida = "resultado";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Ajuda:" << endl;
            cout << "-h: mostra esta mensagem" << endl;
            cout << "-o <arquivo>: redireciona a saída para um arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo de um arquivo" << endl;
            cout << "-s: mostra os vértices na solução" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            arquivoSaida = argv[i + 1];
            tipoSaida = "nenhum";
        } else if (strcmp(argv[i], "-f") == 0) {
            arquivoEntrada = argv[i + 1];
        } else if (strcmp(argv[i], "-s") == 0) {
            tipoSaida = "vertices";
        }
    }

    if (arquivoEntrada == "") {
        cout << "Nenhum arquivo de entrada especificado. Use o parâmetro -f." << endl;
        return 1;
    }

    ifstream entrada(arquivoEntrada);
    if (!entrada) {
        cerr << "Não foi possível abrir o arquivo de entrada: " << arquivoEntrada << endl;
        return 1;
    }

    int numVertices, numArestas;
    entrada >> numVertices >> numArestas;
    vector<vector<pair<int, int>>> listaAdjacencias(numVertices + 1);

    for (int i = 0; i < numArestas; i++) {
        int origem, destino, peso;
        entrada >> origem >> destino >> peso;
        listaAdjacencias[origem].push_back(make_pair(destino, peso));
        listaAdjacencias[destino].push_back(make_pair(origem, peso));
    }

    entrada.close();

    Solucao algoritmo;
    auto resultado = algoritmo.executarKruskal(numVertices, listaAdjacencias);

    if (!arquivoSaida.empty()) {
        ofstream saida(arquivoSaida);
        if (!saida) {
            cerr << "Não foi possível abrir o arquivo de saída: " << arquivoSaida << endl;
            return 1;
        }
        for (auto &aresta : resultado.second) {
            saida << "(" << aresta.first << ", " << aresta.second << ") ";
        }
        saida << endl;
        saida.close();
    }

    if (tipoSaida == "resultado") {
        cout << resultado.first << endl;
    }

    if (tipoSaida == "vertices") {
        for (auto &aresta : resultado.second) {
            cout << "(" << aresta.first << ", " << aresta.second << ") ";
        }
        cout << endl;
    }

    return 0;
}
