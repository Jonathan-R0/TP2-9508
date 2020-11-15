#include "asmline.h"

#include <algorithm>
#include <iostream>
#include <utility>

Asmline::Asmline()
    : jumpCodes({"jmp", "ja", "jeq", "jneq", "jne", "jlt", "jle", "jgt", "jge",
                 "jset"}) {}

bool Asmline::isJump() {
  return (find(jumpCodes.begin(), jumpCodes.end(), opCode) != jumpCodes.end());
}

bool Asmline::esCortante() {
  if (opCode == "ret" || opCode == "jmp" ||
      (this->isJump() && labelsToJump.size() == 2))
    return true;
  return false;
}

std::string Asmline::getLabel() { return this->label; }
std::list<std::string> Asmline::getLabelsToJumpTo() {
  return this->labelsToJump;
}
void Asmline::setOpCode(std::string opCodeGiven) { opCode = opCodeGiven; }
void Asmline::setLabelToJump(std::string labelToJumpGiven) {
  labelsToJump.push_back(labelToJumpGiven);
}
void Asmline::setLabel(std::string labelGiven) { label = labelGiven; }
