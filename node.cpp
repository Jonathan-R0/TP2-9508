#include "node.h"

#include <iostream>
#include <list>
#include <string>

void Node::seeName() { std::cout << name; }

std::list<Node*> Node::getNext() { return next; }

void Node::addNext(Node* newNext) { next.push_back(newNext); }

void Node::seeNextNodes() {
  this->seeName();
  std::cout << " -> ";
  for (Node* nodo : next) {
    nodo->seeName();
    std::cout << " -> ";
  }
  std::cout << std::endl;
}