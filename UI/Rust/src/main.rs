
// Crie um programa para criação e manipulação de
// um grafo simples, incluindo as funções de inserir
// vértice, excluir vértice e imprimir grafo. Execute a
// instância do primeiro exemplo desta aula.

mod simple_graph;
use simple_graph::*;

use std::io;

fn main() {
    let g: Graph<i32> = Graph::new();
    

    dbg!(g);



    println!("Hello, world!");
}

enum Action {
    Insert, 
    Remove,
    Print,
}

fn interact() -> Action {

    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("🤡");

    match input {
        "insert" => {}



    }
}
