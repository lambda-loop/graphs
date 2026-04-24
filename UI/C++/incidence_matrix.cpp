#include "graph.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class IncidenceMatrix : public Graph {
private:
  int **matrix;
  int numEdges;
  int numVertices;
  bool isDirected;

public:
  IncidenceMatrix(int numEdges, int numVertices, bool directed = false)
      : isDirected(directed) {
    this->numEdges = numEdges;
    this->numVertices = numVertices;
    matrix = new int *[numEdges];
    for (int i = 0; i < numEdges; i++) {
      matrix[i] = new int[numVertices];
      for (int j = 0; j < numVertices; j++) {
        matrix[i][j] = 0;
      }
    }
  }

  void addEdge(int edgeLabel, pair<int, int> verticesLabels) {
    if (!isDirected) {
      matrix[edgeLabel][verticesLabels.first] = 1;
      matrix[edgeLabel][verticesLabels.second] = 1;
    } else {
      matrix[edgeLabel][verticesLabels.first] = 1;
      matrix[edgeLabel][verticesLabels.second] = -1;
    }
  }

  void removeEdge(int edgeLabel, pair<int, int> verticesLabels) {
    matrix[edgeLabel][verticesLabels.first] = 0;
    matrix[edgeLabel][verticesLabels.second] = 0;
  }

  void printMatrix() {
    for (int i = 0; i < numEdges; i++) {
      cout << i << " : ";
      for (int j = 0; j < numVertices; j++)
        cout << matrix[i][j] << " ";
      cout << "\n";
    }
  }

  vector<int> getNeighbors(int node) {
    vector<int> tempNeighbors;

    for (int i = 0; i < numEdges; i++) {
      if (matrix[i][node] != 0) {
        for (int j = 0; j < numVertices; j++) {
          if (j != node && matrix[i][j] != 0) {
            tempNeighbors.push_back(j);
          }
        }
      }
    }

    return tempNeighbors;
  }
  ~IncidenceMatrix() {
    for (int i = 0; i < numEdges; i++)
      delete[] matrix[i];
    delete[] matrix;
  }
};
