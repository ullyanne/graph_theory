#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

int prim(vector<vector<pair<int, int>>> &adj_list, vector<int> &parent, int src, int n){
    int sum_weights = 0;
    vector<int> cost(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    
    cost[src] = 0;
    min_heap.push({cost[src], src});

    while(!min_heap.empty()){
        int edge_weight = min_heap.top().first;
        int u = min_heap.top().second;
        min_heap.pop();

        if(!visited[u]){
            visited[u] = true;
            sum_weights += edge_weight;

            for(const auto& neigh : adj_list[u]) { 
                int v = neigh.first;
                int w = neigh.second;

                if(cost[v] > w){
                    cost[v] = w;
                    parent[v] = u;
                    min_heap.push({cost[v], v});
                }
            }
        }
    }

    return sum_weights;
}

int main(int argc, char *argv[]) {
    int opt;
    string output_filename;
    string input_filename;
    int src = 0;
    int output_stream = 0;
    int show_solution = 0;

    string help_message =
        "Usage: " + string(argv[0]) + "[options] <file>\n"
        "This program computes the minimum path in a graph using Dijkstra's algorithm\n\n"
        "Options:\n"
        "  -o <file>: specify the output file\n"
        "  -f <file>: specify the input file which contains the graph\n"
        "  -i <vertex>: specify the initial vertex\n"
        "  -s: shows the solution\n"
        "  -h: display this help\n";

    while ((opt = getopt(argc, argv, "hso:i:f:")) != -1) {
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
            case 's':
                show_solution = 1;
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
    
    vector<int> parent(n, -1);
    int sum_weights;
    sum_weights = prim(adj_list, parent, src, n);
    
    if(show_solution){
        for(int i = 0; i < n; i++){
            if(i != src){
                cout << "(" << parent[i]+1 << "," << i+1 << ") ";
            }
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
            for(int i = 0; i < n; i++){
                if(i != src){
                    output_file << "(" << parent[i]+1 << "," << i+1 << ") ";
                }
            }
        }
        else{
            output_file << sum_weights << endl;
        }
    }

    input_file.close();

    return 0;
}