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
}

void EBPF::hasCycle() {
  if (opGraph._isCyclic()) {
    std::cout << "Has a cycle" << std::endl;
  } else {
    std::cout << "Has no cycle" << std::endl;
  }
}

void EBPF::addInstructionToGraph(std::string line, int lineNumber) {
  if (line.size() == 0) return;
  Asmline instruction;
  parser.parseInstruction(line, instruction);
  opGraph.newNode(instruction.getOpcode(), lineNumber);
  if (lineNumber != 1) opGraph.connectLast(lineNumber);
  std::string label = instruction.getLabel();
  std::list<std::string> labelsToJump = instruction.getLabelsToJumpTo();
  if (label.size() != 0) {
    referenciasReconocidas[label] = lineNumber;
  }
  if (labelsToJump.size() != 0) {
    for (auto s : labelsToJump) {
      referenciasColgadas[s].push_back(lineNumber);
    }
  }
}

/*
eBPF:

dict 1 = Map<string:label, list<int>lineasEnQueSeLlamoALabelEnElAssembly>
dict 2 = Map<string:label, lineasEnQueDeclareLabel> // ANTES ESTABA EN EL GRAFO
                                                    // Y MAPEA LABEL A LINEA EN
                                                    // SE DEFINIO EN EL ASM

while tenga instrucciones:
  si la instruccion es ret corto
  si la instruccion es jump, en la linea i hacia las etiquetas A y B:
    Map[A].append(i)
    Map[B].append(i)
  else (es decir, no es jxx ni ret) reconecto al final del grafo la
  instruccion/nodo

una vez terminado...

while tenga referencias colgadas en dict1:
  recorriendo linealmente el dict1 tomo el label_i,
  y conecto los nodos asociados a las lineas guardadas en dict1[label_i]
  es decir, para todo nodo "v" en dict1[label_i]:
    grafo.añadirAristaEntre(nodes[v]---hacia---->nodes[dict2[label_i]])
*/