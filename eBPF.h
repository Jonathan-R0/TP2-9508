#ifndef EBPF_H_
#define EBPF_H_

#include <list>
#include <map>
#include <string>

#include "graph.h"
#include "parser.h"

class EBPF {
 private:
  std::map<std::string, std::list<int>> referenciasColgadas;
  std::map<std::string, int> referenciasReconocidas;
  std::list<int> aristaACortar;
  Graph opGraph;
  Parser parser;

 public:
  EBPF();
  void addInstructionToGraph(std::string line, int lineNumber);
  void connectLostTags();
  bool hasCycle();
  bool hasUnusedInstruction();
};

#endif  // EBPF_H_
