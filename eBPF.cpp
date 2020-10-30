#include "eBPF.h"

#include <bits/stdc++.h>

#include <fstream>
#include <iostream>

#include "asmline.h"
#include "fileFountain.h"
#include "parser.h"
#include "results.h"

void EBPF::init(std::ifstream& reader) {
  int i = 1;
  while (reader.good()) {
    std::string myText;
    std::getline(reader, myText, '\n');
    if (myText.size() == 0) continue;
    this->addInstructionToGraph(myText, i);
    i++;
  }
  this->connectLostTags();
}

EBPF::EBPF(Results& r, FileFountain& f) : results(r), fileFountain(f) {
  referenciasColgadas = {};
  referenciasReconocidas = {};
}

void EBPF::run() {
  std::string filename;
  while (!(filename = fileFountain.getNext()).empty()) {
    std::ifstream reader;
    Graph opGraph;
    reader.open(filename, std::ifstream::in);
    this->init(reader);
    reader.close();
    bool cycle = this->hasCycle();
    bool unused = this->hasUnusedInstruction();
    this->restart();
    results.addResult(filename, cycle, unused);
  }
}

void EBPF::restart() {
  referenciasColgadas.clear();
  referenciasReconocidas.clear();
  aristaACortar.clear();
  opGraph.clear();
}

void EBPF::connectLostTags() {
  for (int i : aristaACortar) {
    opGraph.disconnectNext(i);
  }
  for (auto it : referenciasColgadas) {
    for (int lineNumber : it.second) {
      opGraph.connect(lineNumber, referenciasReconocidas[it.first]);
    }
  }
}

bool EBPF::hasCycle() { return opGraph.isCyclic(); }

bool EBPF::hasUnusedInstruction() { return opGraph.hasUnusedInstructions(); }

void EBPF::addInstructionToGraph(std::string line, int lineNumber) {
  if (line.size() == 0) return;
  Asmline instruction;
  parser.parseInstruction(line, instruction);
  opGraph.addVertex(lineNumber);
  if (lineNumber != 1) opGraph.connectLast(lineNumber);
  std::list<std::string> labelsToJump = instruction.getLabelsToJumpTo();
  if (instruction.esCortante()) {
    aristaACortar.push_front(lineNumber);
  }
  if (instruction.getLabel().size() != 0) {
    referenciasReconocidas[instruction.getLabel()] = lineNumber;
  }
  if (labelsToJump.size() != 0) {
    for (auto s : labelsToJump) {
      referenciasColgadas[s].push_back(lineNumber);
    }
  }
}
