#include "parser.h"

#include <iostream>
#include <string>

Parser::Parser() { delims = {':', ',', ' ', '\n', '\t', '\0'}; }

bool Parser::isDelim(char c) {
  for (auto i : delims) {
    if (i == c) return true;
  }
  return false;
}

static void parseSpaces(std::string* asmLine) {
  std::string noSpacesExtra = {};
  char anterior = 0;
  for (auto c : *asmLine) {
    if (!(c == ' ' && anterior == ' ')) noSpacesExtra.push_back(c);
    anterior = c;
  }
  *asmLine = noSpacesExtra;
}

static void parseData(Parser* p, std::string& asmLine, bool& hasLabel,
                      std::list<std::string>& parts) {
  std::string placeHolder;
  char lastChar = 0;
  for (auto c : asmLine) {
    lastChar = c;
    if (p->isDelim(c)) {
      if (c == ':') hasLabel = true;
      if (placeHolder.size() != 0) {
        parts.push_back(placeHolder);
      }
      if (c != '\n') placeHolder.erase();
    } else if (!p->isDelim(c)) {
      placeHolder.push_back(c);
    }
  }
  if (!p->isDelim(lastChar)) parts.push_back(placeHolder);
}

static void parseLabel(Asmline& instruction, bool hasLabel,
                       std::list<std::string>& parts) {
  if (parts.size() == 0) return;
  std::string s;
  if (hasLabel) {
    instruction.setLabel(parts.front());
    parts.pop_front();
  }
}

void Parser::parseInstruction(std::string asmLine, Asmline& instruction) {
  bool hasLabel = false;
  std::list<std::string> parts;

  parseSpaces(&asmLine);

  parseData(this, asmLine, hasLabel, parts);
  if (parts.size() == 0) return;  // Empty line.
  parseLabel(instruction, hasLabel, parts);

  instruction.setOpCode(parts.front());
  parts.pop_front();
  instruction.setLabelsToJump(parts);
}
