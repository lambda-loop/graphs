#include <functional>
#include <iostream>
#include <map>

using namespace std;

// Graph Agnostic Recursive DFS
void RecursiveDFS(int currentNode, map<int, bool> &visited,
                  function<vector<int>(int)> getNeighbors,
                  // no neighbors on first iteration!
                  vector<int> neighbors = {}, int neighborIndex = 0) {

  cout << "Visiting: " << currentNode << endl;

  // if current node has already been visited, exits (prevents infinite loop)
  if (neighborIndex == 0) {
    if (visited[currentNode])
      return;
    visited[currentNode] = true;
    neighbors = getNeighbors(currentNode);
  }

  // if the neighbor index is bigger that the number of neighbors, then theres
  // no more neighbors to visit
  if (neighborIndex >= neighbors.size()) {
    return;
  }

  // visits the current neighbor if not visited
  int nextNode = neighbors[neighborIndex];
  if (!visited[nextNode]) {
    RecursiveDFS(nextNode, visited, getNeighbors);
  }

  // go to next neighbor
  RecursiveDFS(currentNode, visited, getNeighbors, neighbors,
               neighborIndex + 1);
}
