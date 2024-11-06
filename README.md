# **Graph Algorithms in C++**

Welcome to the **Graph Algorithms** repository, where i implement a set of graph algorithms in C++ as part of the **Graph Theory** course project. This project includes five key graph algorithms, each solving fundamental problems in graph theory.

---

## **Project Structure**

Each algorithm is placed in its own directory with a corresponding `Makefile` for easy compilation. 

### Compilation

To compile any of the algorithms, navigate to the corresponding folder and run the `Makefile` using the algorithm name:

```bash
make dijkstra
make prim
make kruskal
make carraghan-pardalos
make kosaraju
```

### Execution

Each algorithm has its own command-line interface with the following options:

- `-h`: Shows the help message.
- `-o <output_file>`: Redirects the output to the specified file.
- `-f <input_file>`: Specifies the input file containing the graph.
- `-s`: Shows the solution (for Prim and Kruskal algorithms).
- `-i <start_vertex>`: Specifies the starting vertex (used in Prim's and Dijkstra's algorithms).

#### **Example Execution**

- **Prim's Algorithm**:
    ```bash
    ./prim -f input_graph.dat -i 1 -s
    ```

- **Kosaraju's Algorithm**:
    ```bash
    ./kosaraju -f input_graph.dat
    ```

