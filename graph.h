#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <map>
#include <string>

#include "node.h"

typedef std::map<int, Node*>::iterator iterator_t;

class Graph {
 private:
  std::map<std::string, int> labels;
  std::map<int, Node*> nodes;

 public:
  Graph() {}
  void addVertex(Node* node);
  int size();
  bool isIn(Node* node);
  void addIfItsNotIn(Node* node);
  void addEdge(Node* from, Node* to);
  void printGraph();
  void dfs(Node* start, std::list<Node*>* found);
  Node* newNode(std::string name, int line);

  ~Graph() {
    for (iterator_t it = nodes.begin(); it != nodes.end(); ++it) {
      delete (it->second);
    }
  }
};

#endif  // GRAPH_H_