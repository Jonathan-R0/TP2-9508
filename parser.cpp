#include "parser.h"

#include <iostream>
#include <string>

static void parseSpaces(std::string* asmLine) {
  std::string noSpacesExtra = {};
  char anterior = 0;
  for (auto c : *asmLine) {
    if (!(c == ' ' && anterior == ' ')) noSpacesExtra.push_back(c);
    anterior = c;
  }
  if (noSpacesExtra.front() == ' ') noSpacesExtra.erase(0, 1);
  *asmLine = noSpacesExtra;
}

void Parser::parseInstruction(std::string asmLine, Asmline& instruction) {
  parseSpaces(&asmLine);

  int firstDots = asmLine.find_first_of(":");
  if (firstDots != -1) {
    instruction.setLabel(asmLine.substr(0, firstDots));
    asmLine.erase(0, firstDots + 1);
    int firstNonSpace = asmLine.find_first_not_of(" ");
    asmLine.erase(0, firstNonSpace);
  }

  int firstSpace = asmLine.find_first_of(" ");
  if (firstSpace != -1) {
    instruction.setOpCode(asmLine.substr(0, firstSpace));
    asmLine.erase(0, firstSpace + 1);
  }

  if (instruction.isJump()) {
    int firstComma = asmLine.find_first_of(",");
    std::string secondArg;
    if (firstComma != -1) {
      asmLine.erase(0, firstComma + 2);
      int secondComma = asmLine.find_first_of(",");
      if (secondComma != -1) {
        secondArg = asmLine.substr(0, secondComma);
        asmLine.erase(0, secondComma + 2);
        instruction.setLabelToJump(secondArg);
        instruction.setLabelToJump(asmLine);
      } else {
        instruction.setLabelToJump(asmLine);
      }
    } else {
      instruction.setLabelToJump(asmLine);
    }
  }
}
