#include <iostream>
#include <vector>
using namespace std;

class Graph {
protected:
  bool isDirected;

public:
  virtual void addVertex() {}

  virtual void addEdge() {}

  virtual void removeVertex() {}

  virtual vector<int> getNeighbors() { return vector<int>(); }

  virtual void printGraph() {}
};
