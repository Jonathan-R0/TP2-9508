#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <list>
#include <string>

class Node {
 private:
  const std::string name;
  std::list<Node*> next;

 public:
  Node(std::string nameGiven) : name(nameGiven) {}
  void seeName();
  std::list<Node*> getNext();
  void addNext(Node* newNext);
  void seeNextNodes();
};

#endif  // NODE_H_