#include "parser.h"

#include <iostream>
#include <string>

#define SUCCESS 0
#define FAILURE (SUCCESS - 1)

Parser::Parser() : delims({':', ',', ' ', '\n', '\t', '\0'}) {}

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

static void parseLabel(Asmline& instruction, bool hasLabel,
                       std::list<std::string>& parts) {
  if (parts.size() == 0) return;
  if (hasLabel) {
    instruction.setLabel(std::move(parts.front()));
    parts.pop_front();
  }
}

static int parseData(Parser* p, std::string asmLine, bool& hasLabel,
                     std::list<std::string>& parts, Asmline& instruction) {
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
  if (parts.size() == 0) return FAILURE;  // Empty line.
  parseLabel(instruction, hasLabel, parts);
  return SUCCESS;
}

void Parser::parseInstruction(std::string asmLine, Asmline& instruction) {
  bool hasLabel = false;
  std::list<std::string> parts;

  parseSpaces(&asmLine);

  if (parseData(this, std::move(asmLine), hasLabel, parts, instruction) ==
      SUCCESS) {
    instruction.setOpCode(std::move(parts.front()));
    parts.pop_front();
    instruction.setLabelsToJump(std::move(parts));
  }
}
