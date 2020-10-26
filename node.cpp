#include "node.h"

#include <iostream>
#include <list>
#include <string>

void Node::seeName() { std::cout << name << " " << this->line; }

std::list<Node*> Node::getNext() { return nextNodes; }

void Node::addNext(Node* newNext) { nextNodes.push_back(newNext); }

void Node::seeNextNodes() {
  for (Node* nodo : nextNodes) {
    this->seeName();
    std::cout << " -> ";
    nodo->seeName();
    std::cout << "\n";
  }
  std::cout << std::endl;
}