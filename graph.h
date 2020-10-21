#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <list>
#include <string>

#include "node.h"

class Graph {
 private:
  std::list<Node*> nodes;

 public:
  Graph() {}
  void addVertex(Node* node);
  int size();
  bool isIn(Node* node);
  void addIfItsNotIn(Node* node);
  void addEdge(Node* from, Node* to);
  void printGraph();
};

#endif  // GRAPH_H_