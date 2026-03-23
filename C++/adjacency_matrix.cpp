#include "graph.h"
#include <iostream>
#include <map>
#include <algorithm>
#include "graph.h"

using namespace std;

class AdjacencyMatrix : public Graph{
    private: 
        int** matrix;
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

  ~AdjacencyMatrix() {
    for (int i = 0; i < numVertices; i++)
      delete[] matrix[i];
    delete[] matrix;
  }
};
