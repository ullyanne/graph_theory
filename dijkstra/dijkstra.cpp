#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <utility>
#include <limits>
#include <queue>
using namespace std;

void dijkstra(int src, vector<int> &dist, vector<int> &visited, vector<vector<pair<int, int>>> &adj_list){
    for(size_t i = 0; i < dist.size(); i++){
        dist[i] = numeric_limits<int>::max();
        visited[i] = 0;
    }
    

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    dist[src] = 0;
    min_heap.push({dist[src], src});

    while(!min_heap.empty()){
        int u = min_heap.top().second;
        min_heap.pop();

        if(!visited[u]){
            visited[u] = 1;

            for(const auto& neigh : adj_list[u]) { 
                int v = neigh.first;
                int w = neigh.second;

                if(dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    min_heap.push({dist[v], v});
                }
            }
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
        "Usage: " + string(argv[0]) + "[options] <file>\n"
        "This program computes the minimum path in a graph using Dijkstra's algorithm\n\n"
        "Options:\n"
        "  -o <file>: specify the output file\n"
        "  -f <file>: specify the input file which contains the graph\n"
        "  -i <vertex>: specify the initial vertex to calculate the minimum path\n"
        "  -h: display this help\n";

    while ((opt = getopt(argc, argv, "ho:i:f:")) != -1) {
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
            case 'i':
                src = stoi(optarg) - 1;
                break;
            default:
                cerr << "Unknown flag! Use -h for help instead." << std::endl;
                return 1;
        }
    }

    ifstream input_file(input_filename);

    int n, m;

    input_file >> n >> m;

    vector<vector<pair<int, int>>> adj_list(n);
    int u, v, w;

    for(int i = 0; i < m; i++){
        input_file >> u >> v >> w;
        
        if(u > n || v > n){
            adj_list.resize(max(u, v));
        }
        
        adj_list[u-1].push_back({v-1, w});
        adj_list[v-1].push_back({u-1, w});
    }
    
    vector<int> dist(n);
    vector<int> visited(n);

    dijkstra(src, dist, visited, adj_list);

    for (size_t i = 0; i < dist.size(); i++) {
        if(dist[i] == numeric_limits<int>::max()){
            dist[i] = -1;
        }

        cout << i + 1 << ":" << dist[i] << " ";
    }

    if(output_stream){
        ofstream output_file(output_filename, ios::out);

        if(output_file.is_open()){
            for (size_t i = 0; i < dist.size(); i++) {
                output_file << i + 1 << ":" << dist[i] << " ";
            }
        }
    }
    
    cout << endl;

    input_file.close();

    return 0;
}