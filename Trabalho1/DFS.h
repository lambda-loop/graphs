

// Maldita obrigatoriedade de escrever em português 😡
// Btw, meu teclado tem unicode 🍿🙂

#include "ListaDeAdjacencia.h"
#include <memory>
#include <optional>
#include <set>
#include <stack>

class DFS {
public:
  int val;
  std::set<DFS*> sons;
  // std::set<std::shared_ptr<DFS>> return_edges;
  std::set<DFS*> return_edges;


  // versão empty
  DFS (int n) {
    this->val          = n;
    this->sons         = {};
    this->return_edges = {};
  }

  DFS (ListaDeAdjacencia<int> g, int P0) {
    // a fila do slide
    std::stack<int> stack;
    stack.push(P0); // fazendo uso da P0
    
    // o array dos visitados do slide
    std::set<int> visited;
    visited.insert(P0);

    // pq o grupo usou MAP, eu tenho q fazer assim. 
    // triste estou 😭 
    std::map<int, std::optional<int>> predecessor;

    // tambem pq o map leva pra um vector, resolvi fazer:
    std::map<int, std::vector<int>::iterator> iters;

    // muito importante pra não bugar..
    iters[P0] = g.adjacentes[P0].begin();

    std::map<int, int> PES;
    std::map<int, int> PSS;
    int PE_counter = 0;
    int PS_counter = 0;
    
    // A estrutura intermediária
    DFS dfs = DFS(P0);

    // LOUCURA:
    std::map<int, DFS*> refs;
    // std::map<int, std::shared_ptr<DFS>> refs; 
    // refs[P0]        = std::make_shared<DFS>(dfs);
    // this->val = P0;
    // refs[P0] = this;
    // predecessor[P0] = std::nullopt;

    // e vamos pro algoritmo.
    while(!stack.empty()) {
      int P0 = stack.top();
      
      // tem nós pra visitar?
      if (iters[P0] != g.adjacentes[P0].end()) {
        // visitando o..
        int P = *iters[P0];

        // se já foi visitado // TODO: devia ser o iters do P
        if (visited.find(P) != visited.end()) { 
          // aresta de retorno?
          if (predecessor[P0] != P) {
            // note que P já foi visitado..
            refs[P0]->return_edges.insert(refs[P]);
          }
            
          /* 
          theyre related? if yes, is a return edge.
          if not, just skip.
           * */
        }

        // se ainda não foi visitado
        else {
          stack.push(P);
          visited.insert(P);
          iters[P] = g.adjacentes[P].begin();

          // visitado a partir de .
          predecessor[P] = P0;

          // foi visitado na ordem blah (entrou na ordem blah)
          PES[P] = PE_counter;
          PE_counter++;

          DFS* new_guy = new DFS(P);
          refs[P] = new_guy; 
          refs[P0]->sons.insert(new_guy);
          // DFS* new_guy = new DFS(P);
          // refs[P0]->sons.insert(new_guy);
          // refs[P0]->sons.insert(new_guy);
        }

        iters[P0]++;
      }

      // caso ja foi visitado, desempilha!
      else {
        // current vira o pai dele após o pop
        stack.pop();
        PSS[P0] = PS_counter;
        PS_counter++;
      }
    }
  };





};
