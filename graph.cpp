#include "graph.h"

#include <iostream>
#include <list>
#include <string>

#include "node.h"

void Graph::addVertex(Node* node) { nodes.push_back(node); }

int Graph::size() { return nodes.size(); }

bool Graph::isIn(Node* node) {
  int size = nodes.size();
  for (Node* i : nodes) {
    if (node == i) {
      return true;
    }
  }
  return false;
}

void Graph::addIfItsNotIn(Node* node) {
  if (!this->isIn(node)) {
    nodes.push_back(node);
  }
}

void Graph::addEdge(Node* from, Node* to) {
  this->addIfItsNotIn(from);
  this->addIfItsNotIn(to);
  from->addNext(to);
}

void Graph::printGraph() {
  for (Node* nodo : nodes) {
    nodo->seeNextNodes();
  }
}
