#include "eBPF.h"

#include <bits/stdc++.h>

#include <fstream>
#include <iostream>

#include "asmline.h"
#include "parser.h"
#include "results.h"

void EBPF::init() {
  std::ifstream reader;
  reader.open(filename, std::ifstream::in);
  int i = 1;
  while (reader.good()) {
    std::string myText;
    std::getline(reader, myText, '\n');
    if (myText.size() == 0) continue;
    this->addInstructionToGraph(myText, i);
    i++;
  }
  this->connectLostTags();
  reader.close();
}

EBPF::EBPF(std::string fname, Results& r) : filename(fname), results(r) {
  referenciasColgadas = {};
  referenciasReconocidas = {};
  this->init();
}

void EBPF::run() {
  bool hasCycles = this->hasCycle();
  if (hasCycles)
    results.addResult(filename, true, false);
  else
    results.addResult(filename, false, this->hasUnusedInstruction());
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
