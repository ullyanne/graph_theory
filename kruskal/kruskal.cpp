#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct graph_edge{
    int u;
    int v;
    int w;
} graph_edge;

void make_set(int n, vector<int> &parent, vector<int> &rank){
    for(int i = 1; i < n; i++){
        parent[i] = i;
        rank[i] = i;
    }
}

int find(int u, vector<int> &parent){
    if(parent[u] != u){
        parent[u] = find(parent[u], parent);
    }
    return parent[u];
}

void unite(int u, int v, vector<int> &parent, vector<int> &rank){
    int u_parent = find(u, parent);
    int v_parent = find(v, parent);

    if(u_parent != v_parent){
        if(rank[u_parent] < rank[v_parent]){
            parent[u_parent] = v_parent;
        }
        else if(rank[u_parent] > rank[v_parent]){
            parent[v_parent] = u_parent;
        }
        else{
            parent[v_parent] = u_parent;
            rank[u_parent]++;
        }
    }

}

bool compare_edge_weights(graph_edge e1, graph_edge e2){
    return e1.w < e2.w;
}

int kruskal(vector<graph_edge> &edges, int n, vector<graph_edge> &solution){
    sort(edges.begin(), edges.end(), compare_edge_weights);
    
    vector<int> parent(n+1);
    vector<int> rank(n+1);
    int sum_weights = 0;
    make_set(n+1, parent, rank);

    for(const auto& edge : edges){
        int u = edge.u;
        int v = edge.v;
        int w = edge.w;

        if(find(u, parent) != find(v, parent)){
            unite(u, v, parent, rank);
            sum_weights += w;
            solution.push_back({u, v, w});
        }
    }

    return sum_weights;
}

int main(int argc, char *argv[]) {
    int opt;
    string output_filename;
    string input_filename;
    int output_stream = 0;
    int show_solution = 0;

    string help_message =
        "Usage: " + string(argv[0]) + "[options] <file>\n"
        "This program computes the minimum path in a graph using Dijkstra's algorithm\n\n"
        "Options:\n"
        "  -o <file>: specify the output file\n"
        "  -f <file>: specify the input file which contains the graph\n"
        "  -s: shows the solution\n"
        "  -h: display this help\n";

    while ((opt = getopt(argc, argv, "ho:sf:")) != -1) {
        switch (opt) {
            case 'h':
                cout << help_message;
                break;
            case 'o':
                output_filename = optarg;
                output_stream = 1;
                break;
            case 'f':
                input_filename = optarg;
                break;
            case 's':
                show_solution = 1;
                break;
            default:
                cerr << "Unknown flag! Use -h for help instead." << endl;
                return 1;
        }
    }

    ifstream input_file(input_filename);

    int n, m;

    input_file >> n >> m;

    vector<graph_edge> edges(m);
    int u, v, w;

    for(int i = 0; i < m; i++){
        input_file >> u >> v >> w;
        
        edges[i] = {u, v, w};
    }

    vector<graph_edge> solution;
    int sum_weights;

    sum_weights = kruskal(edges, n, solution);

    if(show_solution){
        for(const auto& edge : solution){
            cout << "(" << edge.u << "," << edge.v << ") ";
        }
    }
    else{
        cout << sum_weights << endl;
    }

    if(output_stream){
        ofstream output_file(output_filename, ios::out);
        if(!output_file.is_open()){
            return 1;
        }
        
        if(show_solution){
            for(const auto& edge : solution){
                output_file << "(" << edge.u << "," << edge.v << ") ";
            }
        }
        else{
            output_file << sum_weights << endl;
        }
    }

    input_file.close();

    return 0;
}