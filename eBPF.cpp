#include "eBPF.h"

#include <iostream>

#include "asmline.h"
#include "parser.h"

EBPF::EBPF() {
  referenciasColgadas = {};
  referenciasReconocidas = {};
}

void EBPF::connectLostTags() {
  for (auto it : referenciasColgadas) {
    for (int lineNumber : it.second) {
      opGraph.connect(lineNumber, referenciasReconocidas[it.first]);
    }
  }
  for (int i : aristaACortar) {
    opGraph.disconnectNext(i);
  }
}

void EBPF::hasCycle() {
  if (opGraph.isCyclic()) {
    std::cout << "Has a cycle" << std::endl;
  } else {
    std::cout << "Has no cycle" << std::endl;
  }
}

void EBPF::hasUnusedInstruction() {
  if (opGraph.hasUnusedInstructions()) {
    std::cout << "Has unused instructions" << std::endl;
  } else {
    std::cout << "Has no unused instructions" << std::endl;
  }
}

void EBPF::addInstructionToGraph(std::string line, int lineNumber) {
  if (line.size() == 0) return;
  Asmline instruction;
  parser.parseInstruction(line, instruction);
  opGraph.addVertex(lineNumber);
  if (lineNumber != 1) opGraph.connectLast(lineNumber);
  std::list<std::string> labelsToJump = instruction.getLabelsToJumpTo();
  if (instruction.esCortante()) {  // AÑADIR CASOS DE SALTOS INCONDICIONALES
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
