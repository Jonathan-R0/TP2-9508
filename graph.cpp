#include "graph.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string>

bool Graph::hasBeenFound(int node, std::list<int>& found) {
  return (find(found.begin(), found.end(), node) != found.end());
}

void Graph::addVertex(int node) { nodes[node] = {}; }

void Graph::addEdge(int from, int to) {
  this->addIfItsNotIn(from);
  this->addIfItsNotIn(to);
  nodes[from].push_front(to);
}

int Graph::size() { return nodes.size(); }

bool Graph::isIn(int node) {
  for (auto i : nodes) {
    if (node == i.first) return true;
  }
  return false;
}

void Graph::addIfItsNotIn(int node) {
  if (!this->isIn(node)) {
    this->addVertex(node);
  }
}

bool Graph::_isCyclic(int start, std::list<int>& found) {
  if (hasBeenFound(start, found)) return true;
  found.push_front(start);
  for (int i : nodes.at(start)) {
    if (Graph::_isCyclic(i, found)) return true;
  }
  found.remove(start);
  return false;
}

void Graph::clear() { nodes.clear(); }

bool Graph::isCyclic() {
  std::list<int> found;
  for (auto it : nodes) {
    if (this->_isCyclic(it.first, found)) {
      found.clear();
      return true;
    }
  }
  found.clear();
  return false;
}

void Graph::connectLast(int to) { this->addEdge(nodes.size() - 1, to); }

void Graph::dfs(int start, std::list<int>& found) {
  if (hasBeenFound(start, found)) return;
  found.push_front(start);
  for (int i : nodes[start]) {
    if (!(hasBeenFound(i, found))) {
      Graph::dfs(i, found);
    }
  }
}

bool Graph::hasUnusedInstructions() {
  std::list<int> found;
  if (nodes.size() == 0) return false;
  dfs(1, found);
  long unsigned int amountFound = found.size();
  found.clear();
  return (amountFound != nodes.size());
}

void Graph::disconnectNext(int nodo) {
  std::list<int> searching = nodes[nodo];
  for (int it : searching) {
    if (nodo + 1 == it) {
      nodes[nodo].remove(it);
      break;
    }
  }
}

void Graph::connect(int from, int to) { nodes[from].push_front(to); }
