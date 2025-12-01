#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <limits>

using namespace std;


class Graph {
private:
        int edgesList;
        int edgesMat;
        int nodes;
        vector<int> *adjList;
        int *adjMatrix;

public:
        Graph(int);
        Graph();
        void addEdgeAdjList(int, int);
        void addEdgeAdjMatrix(int, int);
        string printAdjList();
        string printAdjMat();
        string printAdjMat_clean();

        string DFS(int, int);
        string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int> >&, int);
        string BFS(int, int);
        string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int> >&);
 
        string print_visited(list<int>);
        string print_path(vector<vector<int> >&,int ,int);
        bool contains(list<int>, int);
        void sortAdjList();

        void loadGraphList(string, int);
        void loadGraphMat(string, int, int);
};

Graph::Graph() {
    edgesList = edgesMat = 0;
    nodes = 0;
    adjList = 0;
    adjMatrix = 0;
}

Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int>[nodes];
    adjMatrix = new int [nodes*nodes];
    for (int i = 0; i < nodes*nodes; i++)
        adjMatrix[i] = 0;
    edgesList = edgesMat = 0;
}

void Graph::loadGraphList(string input, int n){
    if (adjList != 0) delete[] adjList;

    adjList = new vector<int>[n];
    nodes = n;
    edgesList = 0;

    stringstream ss(input);
    char discard;
    int u, v;

    while (ss >> discard >> u >> discard >> v >> discard) {
    addEdgeAdjList(u, v);
    }

    sortAdjList();
}


void Graph::loadGraphMat(string input, int n, int m){
    if (adjMatrix != 0) delete[] adjMatrix;

    adjMatrix = new int [n*m];
    nodes = n;
    edgesMat = 0;

    for (int i = 0; i < n*m; i++)
        adjMatrix[i] = 0;

    stringstream ss(input);
    char discard;
    int u, v;

    while (ss >> discard >> u >> discard >> v >> discard) {
        addEdgeAdjMatrix(u, v);
    }
}

void Graph::addEdgeAdjList(int u, int v){
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
    adjMatrix[u*nodes+v] = 1;
    adjMatrix[v*nodes+u] = 1;
    edgesMat++;
}

void Graph::sortAdjList(){
    for (int i = 0; i < nodes; i++)
        sort(adjList[i].begin(),adjList[i].end());
}


string Graph::printAdjList(){
    stringstream aux;
    for (int i = 0; i < nodes; i++){
        aux << "vertex " << i << " :";
        for (int j = 0; j < adjList[i].size(); j ++){
            aux << " " << adjList[i][j];
        }
        aux << " ";
    }
    return aux.str();
}

string Graph::printAdjMat(){
    stringstream aux;
    for (int i = 0; i < nodes; i++){
        for (int j = 0; j < nodes; j++){
            aux << adjMatrix[i*nodes+j] << " ";
        }
    }
    return aux.str();
}

string Graph::printAdjMat_clean(){
    stringstream aux;
    aux << "\n nodes \t|";
    for (int i = 0; i < nodes; i++){
        aux << "\t" << i ;
    }
    aux << "\n";
    for (int i = 0; i < nodes; i++){
        aux << "__________";
    }
    aux << "\n";
    for (int i = 0; i < nodes; i++){
        aux << i << "\t|";
        for (int j = 0; j < nodes; j++){
            aux << "\t" << adjMatrix[i*nodes+j];
        }
        aux << "\n";
    }
    return aux.str();
}


string Graph::DFS(int start, int goal){
    stack<int> st;
    list<int> visited;
    vector<vector<int> > paths(nodes, vector<int>(1, -1)); 
    paths[start][0] = start;
    st.push(start);
    return depthHelper(start, goal, st, visited, paths, start);
}

string Graph::depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int> > &paths, int original_start){
    visited.push_back(current);
    if (current == goal) {
        return print_visited(visited) + print_path(paths, original_start, goal);
    }

    for (size_t i = 0; i < adjList[current].size(); i++) {
        int neighbor = adjList[current][i];
        if (!contains(visited, neighbor)) {
            paths[neighbor][0] = current; 
            st.push(neighbor);
            string result = depthHelper(neighbor, goal, st, visited, paths, original_start);
            if (result.find("path:") != string::npos) {
                return result;
            }
            st.pop();
        }
    }
    return " node not found";
}

string Graph::BFS(int start, int goal){
    queue<int> qu;
    list<int> visited;
    vector<vector<int> > paths(nodes, vector<int>(1, -1)); 

    qu.push(start);
    paths[start][0] = start; 

    return breadthHelper(start, goal, qu, visited, paths);
}

string Graph::breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int> > &paths){
    while (!qu.empty()){
        current = qu.front();
        qu.pop();
        if (!contains(visited, current)) {
            visited.push_back(current);
        } else {
            continue;
        }

        if (current == goal) {
    
            int start_node = -1;
            for(int i=0; i<nodes; ++i) {
                if(paths[i][0] == i) { start_node = i; break; }
            }
            return print_visited(visited) + print_path(paths, start_node, goal);
        }

        for (size_t i = 0; i < adjList[current].size(); i++) {
            int neighbor = adjList[current][i];
            if (!contains(visited, neighbor)) {

                if (paths[neighbor][0] == -1) { 
                    paths[neighbor][0] = current;
                    qu.push(neighbor);
                }
            }
        }
    }
    return " node not found";
}


bool Graph::contains(list<int> ls, int node){
    list<int>::iterator it;
    it = find(ls.begin(), ls.end(), node);
    if(it != ls.end())
        return true;
    else
        return false;
}


string Graph::print_visited(list<int> q){
    stringstream aux;
    aux << "visited:";
    
    list<int>::iterator it; 
    for (it = q.begin(); it != q.end(); ++it) {
        aux << " " << *it;
    }
    
    aux << " ";
    return aux.str();
}

string Graph::print_path(vector<vector <int> > &path, int start, int goal){
    int node = goal;
    stack<int> reverse;
    reverse.push(goal);
    stringstream aux;
    aux << "path:";

    while (node != start) {
        if (path[node][0] == -1) {
            return " path: no path found"; 
        }
        node = path[node][0];
        reverse.push(node);
    }

    while (!reverse.empty()) {
        aux << " " << reverse.top() ;
        reverse.pop();
    }
    return aux.str();
}

#endif /* Graph_H_ */