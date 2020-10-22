#include "node.h"

#include <iostream>
#include <list>
#include <string>

void Node::seeName() { std::cout << name; }

std::list<Node*> Node::getNext() { return nextNodes; }

void Node::addNext(Node* newNext) { nextNodes.push_back(newNext); }

void Node::seeNextNodes() {
  this->seeName();
  for (Node* nodo : nextNodes) {
    std::cout << " -> ";
    nodo->seeName();
  }
  std::cout << std::endl;
}