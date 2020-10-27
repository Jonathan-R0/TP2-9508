#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <map>
#include <string>

class Graph {
 private:
  std::map<int, std::list<int>> nodes;
  std::list<int> found;

 public:
  Graph() {}
  void addVertex(int node);
  bool hasBeenFound(int node);
  int size();
  bool isIn(int node);
  void addIfItsNotIn(int node);
  void addEdge(int from, int to);
  bool _isCyclic(int start);
  bool isCyclic();
  void dfs(int start, std::list<int>& found);
  void connect(int from, int to);
  void connectLast(int to);
  bool hasUnusedInstructions();
  void disconnectNext(int nodo);
};

#endif  // GRAPH_H_
