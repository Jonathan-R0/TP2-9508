#include "asmline.h"

#include <algorithm>
#include <iostream>

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

std::string Asmline::getOpcode() { return this->opCode; }
std::string Asmline::getLabel() { return this->label; }
std::list<std::string> Asmline::getLabelsToJumpTo() {
  return this->labelsToJump;
}
void Asmline::setLabel(std::string labelGiven) { label = labelGiven; }
void Asmline::setOpCode(std::string opCodeGiven) { opCode = opCodeGiven; }
void Asmline::setLabelToJump(std::string labelToJumpGiven) {
  labelsToJump.push_back(labelToJumpGiven);
}

void Asmline::setLabelsToJump(std::list<std::string> labelsToJumpGiven) {
  if (!this->isJump()) return;
  if (labelsToJumpGiven.size() == 1) {
    labelsToJump.push_back(labelsToJumpGiven.back());
  } else {
    labelsToJumpGiven.pop_front();
    labelsToJump = std::move(labelsToJumpGiven);
  }
}
