#include "graph.h"
#include <iostream>
#include <iterator>
#include <stack>
#include <unordered_map>
#include <unordered_set>

/* Alguns estados nações cometeram crime de guerra: antigo Império Persa
(Túrquia), Alemanha, França, EUA... pode-se dizer que este é um crime de guerra
Natalense: */
using namespace std;

class AdjacencyMatrix : public Graph {
private:
  int **matrix;
  int numVertices;
  bool isDirected;

public:
  AdjacencyMatrix(int numVertices, bool directed = false)
      : isDirected(directed) {
    this->numVertices = numVertices;
    matrix = new int *[numVertices];
    for (int i = 0; i < numVertices; i++) {
      matrix[i] = new int[numVertices];
      for (int j = 0; j < numVertices; j++) {
        matrix[i][j] = 0;
      }
    }
  }

  void addEdge(int from, int to) {
    matrix[from][to] = 1;

    if (!isDirected) {
      matrix[to][from] = 1;
    }
  }

  void removeEdge(int from, int to) {
    matrix[from][to] = 0;

    if (!isDirected) {
      matrix[to][from] = 0;
    }
  }

  void printMatrix() {
    for (int i = 0; i < numVertices; i++) {
      cout << i << " : ";
      for (int j = 0; j < numVertices; j++)
        cout << matrix[i][j] << " ";
      cout << "\n";
    }
  }

  vector<int> getNeighbors(int node) {
    vector<int> tempNeighbors;

    for (int i = 0; i < numVertices; i++) {
      if (matrix[node][i] == 1) {
        tempNeighbors.push_back(i);
      }
    }

    return tempNeighbors;
  }

  unordered_map<int, int> depthFSearch(AdjacencyMatrix &graph, int v_initial) {

    stack<int> v_stack;
    unordered_set<int> v_visited; // Set of visited vertices.
    unordered_map<int, int> dfs_graph;

    v_visited.insert(v_initial); // The initiial vertex is defined as visited.
    v_stack.push(v_initial);

    int v_current, v_predecessor;

    while (v_stack.size() > 0) {

      v_current = v_stack.top();

      vector<int> neighbors = graph.getNeighbors(v_current);

      if (!neighbors.empty()) {

        bool new_vertex = false;

        for (int neighbor : neighbors) {
          if (v_visited.find(neighbor) == v_visited.end()) {

            v_visited.insert(
                neighbor); // Add children of the current vertex to visited set.
            v_stack.push(neighbor); // Add clildren of current vertex stack.

            v_predecessor = v_current; // Current vertex becomes predecessor.
            dfs_graph.insert({neighbor, v_predecessor});

            new_vertex = true;

            break;
          }
        }
        if (!new_vertex) {
          v_stack.pop();
        }
      } else {
        v_stack.pop();
      }
    }

    return dfs_graph;
  }

  ~AdjacencyMatrix() {
    for (int i = 0; i < numVertices; i++)
      delete[] matrix[i];
    delete[] matrix;
  }

  int **getMatrix() { return this->matrix; }

  bool isDirected_() { return this->isDirected; }

  int getNumVerteces() { return this->numVertices; }
};
