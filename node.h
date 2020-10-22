#ifndef NODE_H_
#define NODE_H_

#include <list>
#include <string>

class Node {
 private:
  const std::string name;
  std::list<Node*> nextNodes;

 public:
  int line;
  void seeName();
  Node(std::string nameGiven, int lineGiven)
      : name(nameGiven), line(lineGiven) {}
  std::list<Node*> getNext();
  void addNext(Node* newNext);
  void seeNextNodes();
};

#endif  // NODE_H_