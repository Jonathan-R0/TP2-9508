#include "asmline.h"

#include <iostream>

Asmline::Asmline() {
  label = {};
  opCode = {};
  labelsToJump = {};
  jumpCodes = {"jmp", "ja",  "jeq", "jneq", "jne",
               "jlt", "jle", "jgt", "jge",  "jset"};
}

bool Asmline::isJump() {
  for (auto j : jumpCodes) {
    if (opCode.compare(j) == 0) return true;
  }
  return false;
}

// TEST ONLY
void Asmline::seeLabel() { std::cout << label << std::endl; }
void Asmline::seeOpCode() { std::cout << opCode << std::endl; }
void Asmline::seeLabelsToJump() {
  for (auto s : labelsToJump) std::cout << s << std::endl;
}

void Asmline::setLabel(std::string labelGiven) { label = labelGiven; }
void Asmline::setOpCode(std::string opCodeGiven) { opCode = opCodeGiven; }
void Asmline::setLabelsToJump(std::list<std::string> labelsToJumpGiven) {
  if (!this->isJump()) return;
  if (labelsToJumpGiven.size() == 0) {
    labelsToJump.push_back(labelsToJumpGiven.back());
  } else {
    labelsToJumpGiven.pop_front();
    labelsToJump = labelsToJumpGiven;
  }
}