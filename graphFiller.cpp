#include "graphFiller.h"

#include "asmline.h"
#include "parser.h"

void Graphfiller::restart() {
  referenciasColgadas.clear();
  referenciasReconocidas.clear();
  aristaACortar.clear();
  opGraph.clear();
}

Graphfiller::Graphfiller() {
  referenciasColgadas = {};
  referenciasReconocidas = {};
  aristaACortar = {};
}

void Graphfiller::addInstructionToGraph(std::string line, int lineNumber) {
  if (line.size() == 0) return;
  Asmline instruction;
  parser.parseInstruction(line, instruction);
  opGraph.addVertex(lineNumber);
  if (lineNumber != 1) opGraph.connectLast(lineNumber);
  std::list<std::string> labelsToJump = instruction.getLabelsToJumpTo();
  if (instruction.esCortante()) aristaACortar.push_front(lineNumber);
  if (instruction.getLabel().size() != 0)
    referenciasReconocidas[instruction.getLabel()] = lineNumber;
  if (labelsToJump.size() != 0) {
    for (auto s : labelsToJump) {
      referenciasColgadas[s].push_back(lineNumber);
    }
  }
}

bool Graphfiller::hasCycle() { return opGraph.isCyclic(); }

bool Graphfiller::hasUnusedInstruction() {
  return opGraph.hasUnusedInstructions();
}

void Graphfiller::connectLostTags() {
  for (int i : aristaACortar) opGraph.disconnectNext(i);
  for (auto& it : referenciasColgadas) {
    for (int lineNumber : it.second) {
      opGraph.connect(lineNumber, referenciasReconocidas[it.first]);
    }
  }
}