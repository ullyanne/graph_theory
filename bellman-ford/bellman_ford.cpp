#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

typedef struct graph_edge {
    int u;
    int v;
    int w;
} graph_edge;

void bellman_ford(vector<graph_edge> &edges, vector<int> &dist, int n, int src) {
    dist[src] = 0;

    for (int i = 0; i < n; i++) {
        for (const auto &edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.w;

            if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (const auto &edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int w = edge.w;

        if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v]) {
            cerr << "Graph contains a negative weight cycle" << endl;
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    int opt;
    string output_filename;
    string input_filename;
    int src = 0;
    int output_stream = 0;

    string help_message =
        "Usage: " + string(argv[0]) + " [options] <file>\n"
        "This program computes the minimum path in a graph using Bellman-Ford algorithm\n\n"
        "Options:\n"
        "  -o <file>: specify the output file\n"
        "  -f <file>: specify the input file which contains the graph\n"
        "  -i <vertex>: specify the initial vertex to calculate the minimum path\n"
        "  -h: display this help\n";

    while ((opt = getopt(argc, argv, "ho:i:f:")) != -1) {
        switch (opt) {
            case 'h':
                cout << help_message;
                return 0;
            case 'o':
                output_filename = optarg;
                output_stream = 1;
                break;
            case 'f':
                input_filename = optarg;
                break;
            case 'i':
                src = stoi(optarg) - 1;
                break;
            default:
                cerr << "Unknown flag! Use -h for help instead." << endl;
                return 1;
        }
    }

    ifstream input_file(input_filename);

    if (!input_file.is_open()) {
        cerr << "Unable to open input file" << endl;
        return 1;
    }

    int n, m;
    bool digraph = false;

    input_file >> n >> m;

    if(m < 0){
        digraph = true;
        m = -1 * m;
    }

    vector<graph_edge> edges;
    int u, v, w;

    for (int i = 0; i < m; i++) {
        input_file >> u >> v >> w;

        if(digraph){
            edges.push_back({u - 1, v - 1, w});
        }
        else{
            edges.push_back({u - 1, v - 1, w});
            edges.push_back({v - 1, u - 1, w});
        }
    }

    vector<int> dist(n, numeric_limits<int>::max());

    bellman_ford(edges, dist, n, src);

    for (size_t i = 0; i < dist.size(); ++i) {
        cout << i + 1 << ":" << dist[i] << " ";
    }

    if (output_stream) {
        ofstream output_file(output_filename, ios::out);

        if (output_file.is_open()) {
            for (size_t i = 0; i < dist.size(); ++i) {
                output_file << i + 1 << ":" << dist[i] << " ";
            }
        } else {
            cerr << "Unable to open output file" << endl;
            return 1;
        }
    }

    input_file.close();
    return 0;
}
