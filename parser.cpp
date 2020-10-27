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

static void parseData(Parser* p, std::string& asmLine,
                      std::list<char>& delimsSeen,
                      std::list<std::string>& parts) {
  std::string placeHolder;
  char lastChar = 0;
  for (auto c : asmLine) {
    lastChar = c;
    if (p->isDelim(c)) {
      delimsSeen.push_back(c);
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

static void parseLabel(Asmline& instruction, std::list<char>& delimsSeen,
                       std::list<std::string>& parts) {
  if (parts.size() == 0) return;
  std::string s;
  if (delimsSeen.front() == ':') {
    delimsSeen.pop_front();
    instruction.setLabel(parts.front());
    parts.pop_front();
  }
}

void Parser::parseInstruction(std::string asmLine, Asmline& instruction) {
  std::list<char> delimsSeen;
  std::list<std::string> parts;

  parseSpaces(&asmLine);

  parseData(this, asmLine, delimsSeen, parts);
  if (parts.size() == 0) return;  // Empty line.
  parseLabel(instruction, delimsSeen, parts);

  if (delimsSeen.front() == ' ') delimsSeen.pop_front();
  instruction.setOpCode(parts.front());
  parts.pop_front();
  instruction.setLabelsToJump(parts);
}
