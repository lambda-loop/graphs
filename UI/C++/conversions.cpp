
#include "adjacency_list.cpp"
#include "adjacency_matrix.cpp"

AdjacencyList fromAdjacencyMatrix(AdjacencyMatrix *m) {
  int numV  = m->getNumVerteces();
  int** mat = m->getMatrix();

  std::map<int, std::vector<int>> nbs;

  /* because were using maps instead of vectors,
  by doing this we have the garantee that every
  vertex, even the isoleted ones'll have a valid key.. */
  for (int i = 0; i < numV; i++) nbs[i] = {};

  for (int i = 0; i < numV; i++) {
    for (int j = 0; j < numV; j++) {
      if (mat[i][j]) {
        nbs[i].push_back(j);
      }
    }
  }

  return AdjacencyList(std::move(nbs), m->isDirected_());
}

