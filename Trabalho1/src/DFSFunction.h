#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <functional>
#include <stack>
#include <vector>
#include <map>

using namespace std;

// Graph Agnostic DFS
inline void DFS(int startNode, function<vector<int>(int)> getNeighbors){
    map<int, bool> visited;
    stack<int> p;

    visited[startNode] = true;
    cout << "Visiting: " << startNode << endl;
    p.push(startNode);

    while(!p.empty()){
        bool nonVisitedFound = false;

        vector<int> neighbors = getNeighbors(p.top());

        for (int n : neighbors){
            if(!visited[n]){
                visited[n] = true;
                cout << "Visiting: " << n << endl;
                p.push(n);
                nonVisitedFound = true;
                break;
            }
        }

        if(!nonVisitedFound){
            p.pop();
        }
    }
}

#endif