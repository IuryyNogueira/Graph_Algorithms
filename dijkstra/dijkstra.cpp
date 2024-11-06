#include <bits/stdc++.h>






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
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(in);
    
    if (!fin){
        cerr << "Could not open input file: " << in << endl;
        return 1;
    }

    // Leitura Numero de vertices e arestas do grafo
    int N, m;
    fin >> N >> m;
    fin.close();
}