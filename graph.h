#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <map>
#include <string>

#include "node.h"

class Graph {
 private:
  // std::map<std::string, int> labels; // <- debería estar en el eBPF
  std::map<int, Node*> nodes;

 public:
  Graph() {}
  void addVertex(Node* node);
  int size();
  bool isIn(Node* node);
  void addIfItsNotIn(Node* node);
  void addEdge(Node* from, Node* to);
  void printGraph();
  bool isCyclic(Node* start, std::list<Node*>* found);
  bool _isCyclic();
  Node* newNode(std::string name, int line);
  void dfs(Node* start, std::list<Node*>* found);
  void connect(int from, int to);
  void connectLast(int to);
  ~Graph();
};

#endif  // GRAPH_H_