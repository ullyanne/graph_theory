#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

void dfs_fill_stack(vector<vector<int>> &adj_list, vector<bool> &visited, int u, stack<int> &stack){
    visited[u] = true;

    for(const auto& v : adj_list[u]){ 
        if(!visited[v]){
            dfs_fill_stack(adj_list, visited, v, stack);
        }
    }

    stack.push(u);
}

void dfs(vector<vector<int>> &adj_list, vector<bool> &visited, int u, vector<int> &scc_group){
    visited[u] = true;
    scc_group.push_back(u);

    for(const auto& v : adj_list[u]){ 
        if(!visited[v]){
            dfs(adj_list, visited, v, scc_group);
        }
    }
}

void kosaraju(vector<vector<int>> &adj_list, vector<vector<int>> &adj_list_r, vector<vector<int>> &scc, int n){
    vector<bool> visited(n, false);
    stack<int> stack;

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            dfs_fill_stack(adj_list_r, visited, i, stack);
        }
    }

    for(int i = 0; i < n; i++){
        visited[i] = false;
    }

    while(!stack.empty()){
        int u = stack.top();
        stack.pop();

        if(!visited[u]){
            vector<int> scc_group;
            dfs(adj_list, visited, u, scc_group);
            scc.push_back(scc_group);
        }
    }
}

int main(int argc, char *argv[]) {
    int opt;
    string output_filename;
    string input_filename;
    int output_stream = 0;
    int src = 0;

    string help_message =
        "Usage: " + string(argv[0]) + "[options] <file>\n"
        "This program computes the minimum path in a graph using Dijkstra's algorithm\n\n"
        "Options:\n"
        "  -o <file>: specify the output file\n"
        "  -f <file>: specify the input file which contains the graph\n"
        "  -h: display this help\n";

    while ((opt = getopt(argc, argv, "hi:o:f:")) != -1) {
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

    vector<vector<int>> adj_list(n);
    vector<vector<int>> adj_list_r(n);
    int u, v;

    for(int i = 0; i < m; i++){
        input_file >> u >> v;
        
        if(u > n || v > n){
            adj_list.resize(max(u, v));
            adj_list_r.resize(max(u, v));
        }
        
        adj_list[u-1].push_back(v-1);
        adj_list_r[v-1].push_back(u-1);
    }

    vector<vector<int>> scc;

    kosaraju(adj_list, adj_list_r, scc, n);

    for (size_t i = 0; i < scc.size(); ++i) {
        for (size_t j = 0; j < scc[i].size(); ++j) {
            cout << scc[i][j]+1 << " ";
        }
        cout << endl;
    }

    input_file.close();

    return 0;
}