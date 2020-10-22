#include "graph.h"

#include <iostream>
#include <list>
#include <map>
#include <string>

#include "node.h"

static bool isContained(Node* node, std::list<Node*> list) {
  for (Node* i : list) {
    if (node == i) return true;
  }
  return false;
}

void Graph::addVertex(Node* node) { nodes.insert({node->line, node}); }

void Graph::addEdge(Node* from, Node* to) {
  this->addIfItsNotIn(from);
  this->addIfItsNotIn(to);
  from->addNext(to);
}

int Graph::size() { return nodes.size(); }

bool Graph::isIn(Node* node) {
  if (node == nullptr) return false;
  int size = nodes.size();
  for (iterator_t it = nodes.begin(); it != nodes.end(); ++it) {
    if (node == it->second) {
      return true;
    }
  }
  return false;
}

void Graph::addIfItsNotIn(Node* node) {
  if (!this->isIn(node)) {
    this->addVertex(node);
  }
}

void Graph::printGraph() {
  int size = nodes.size();
  for (iterator_t it = nodes.begin(); it != nodes.end(); ++it) {
    it->second->seeNextNodes();
  }
}

void Graph::dfs(Node* start, std::list<Node*>* found) {
  if (!this->isIn(start) || found == nullptr) return;
  found->push_front(start);
  std::list<Node*> adyacentes = start->getNext();
  for (Node* i : adyacentes) {
    if (!isContained(i, *found)) {
      Graph::dfs(i, found);
    }
  }
}

Node* Graph::newNode(std::string name, int line) {
  if (line < this->size()) return nullptr;
  Node* nodo = new Node(name, line);
  this->addVertex(nodo);
  return (nodo);
}
