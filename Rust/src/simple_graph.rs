
use std::{collections::{HashMap, HashSet}, hash::Hash};


#[derive(Debug)]
pub struct Graph<T: Sized + Eq + Hash + Clone> {
    content: HashMap<T, HashSet<T>>,
}

// TODO: error msgs with Result
impl<T> Graph<T> where 
    T: Sized + Eq + Hash + Clone {
    pub fn new() -> Graph<T> {
        Graph { content: HashMap::new() }
    }

    pub fn insert_node(&mut self, node: T) {
        let new_hash = HashSet::new();
        self.content.insert(node, new_hash);
    }

    pub fn remove_node(&mut self, node: T) {
        let connections = self.content.get(&node).unwrap().clone();
        for k in connections.iter() {
            let s = self.content.get_mut(k).unwrap();
            s.remove(&node);
        }

        self.content.remove(&node);
    }

    pub fn insert_edge(&mut self, from: T, to: T) {
        self.content.get_mut(&from).unwrap().insert(to.clone());
        self.content.get_mut(&to).unwrap().insert(from);
    }

    pub fn remove_edge(&mut self, from: T, to: T) {
        self.content.get_mut(&from).unwrap().remove(&to);
        self.content.get_mut(&to).unwrap().remove(&from);
    }
}


