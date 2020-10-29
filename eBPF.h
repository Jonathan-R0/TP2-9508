#ifndef EBPF_H_
#define EBPF_H_

#include <list>
#include <map>
#include <string>

#include "graph.h"
#include "parser.h"
#include "results.h"
#include "thread.h"

class EBPF : public Thread {
 private:
  std::map<std::string, std::list<int>> referenciasColgadas;
  std::map<std::string, int> referenciasReconocidas;
  std::list<int> aristaACortar;
  std::string filename;
  Results& results;
  Graph opGraph;
  Parser parser;
  void init();

 public:
  EBPF(std::string fname, Results& r);
  void run();
  void addInstructionToGraph(std::string line, int lineNumber);
  void connectLostTags();
  bool hasCycle();
  ~EBPF() {}
  bool hasUnusedInstruction();
};

#endif  // EBPF_H_
