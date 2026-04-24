#pragma once

#include <iostream>
#include <vector>

class Graph {
protected:
  bool isDirected;

public:
  virtual void addVertex() {}

  virtual void addEdge() {}

  virtual void removeVertex() {}

  virtual std::vector<int> getNeighbors() { return std::vector<int>(); }

  virtual void printGraph() {}
};
