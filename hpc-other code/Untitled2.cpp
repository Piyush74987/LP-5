#include<iostream>
#include<omp.h>
#include<vector>
#include<climits>
#include<stack>
#include<queue>
#include<ctime>  // For srand and time
#include<cstdlib> // For rand

using namespace std;

class Graph{
public:
    int vertices = 6;
    int edges = 5;
    vector<vector<int> > graph;
    vector<bool> visited;

    Graph(){
        graph.assign(vertices, vector<int>());
        // Add edges
        graph[0].push_back(1);
        graph[1].push_back(0);
        graph[1].push_back(2);
        graph[1].push_back(3);
        graph[2].push_back(1);
        graph[2].push_back(4);
        graph[2].push_back(5);
        graph[3].push_back(1);
        graph[3].push_back(4);
        graph[4].push_back(2);
        graph[4].push_back(3);
        graph[5].push_back(2);
    }

    void addEdge(int a, int b){
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    void printGraph(){
        for(int i = 0; i < vertices; i++){
            cout << i << " -> ";
            for(int j = 0; j < graph[i].size(); j++){
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    }

    void initialize_visited(){
        visited.assign(vertices, false);
    }

    void dfs(int i){
        stack<int> s;
        s.push(i);
        visited[i] = true;

        while(!s.empty()){
            int current = s.top();
            cout << current << " ";
            s.pop();
            for(int j = 0; j < graph[current].size(); j++){
                if(visited[graph[current][j]] == false){
                    s.push(graph[current][j]);
                    visited[graph[current][j]] = true;
                }
            }
        }
    }

    void parallel_dfs(int i){
        stack<int> s;
        s.push(i);
        visited[i] = true;

        while(!s.empty()){
            int current = s.top();
            cout << current << " ";
            #pragma omp critical
            s.pop();
            
            #pragma omp parallel for
            for(int j = 0; j < graph[current].size(); j++){
                if(visited[graph[current][j]] == false){
                    #pragma omp critical
                    {
                        s.push(graph[current][j]);
                        visited[graph[current][j]] = true;
                    }
                }
            }
        }
    }

    void bfs(int i){
        queue<int> q;
        q.push(i);
        visited[i] = true;

        while(!q.empty()){
            int current = q.front();
            q.pop();
            cout << current << " ";
            for(int j = 0; j < graph[current].size(); j++){
                if(visited[graph[current][j]] == false){
                    q.push(graph[current][j]);
                    visited[graph[current][j]] = true;
                }
            }
        }
    }

    void parallel_bfs(int i){
        queue<int> q;
        q.push(i);
        visited[i] = true;

        while(!q.empty()){
            int current = q.front();
            cout << current << " ";
            #pragma omp critical
            q.pop();

            #pragma omp parallel for
            for(int j = 0; j < graph[current].size(); j++){
                if(visited[graph[current][j]] == false){
                    #pragma omp critical
                    {
                        q.push(graph[current][j]);
                        visited[graph[current][j]] = true;
                    }
                }
            }
        }
    }
};

int main(){
    Graph g;
    cout << "Adjacency List:\n";
    g.printGraph();
    g.initialize_visited();

    cout << "Depth First Search: \n";
    clock_t start = clock();
    g.dfs(0);
    cout << endl;
    clock_t end = clock();
    cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC * 1000000 << " microseconds" << endl;

    cout << "Parallel Depth First Search: \n";
    g.initialize_visited();
    start = clock();
    g.parallel_dfs(0);
    cout << endl;
    end = clock();
    cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC * 1000000 << " microseconds" << endl;

    cout << "Breadth First Search: \n";
    g.initialize_visited();
    start = clock();
    g.bfs(0);
    cout << endl;
    end = clock();
    cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC * 1000000 << " microseconds" << endl;

    cout << "Parallel Breadth First Search: \n";
    g.initialize_visited();
    start = clock();
    g.parallel_bfs(0);
    cout << endl;
    end = clock();
    cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC * 1000000 << " microseconds" << endl;

    return 0;
}

