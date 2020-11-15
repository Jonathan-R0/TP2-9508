#ifndef PARSER_H_
#define PARSER_H_
#include <list>
#include <string>

#include "asmline.h"

class Parser {
 public:
  void parseInstruction(std::string asmLine, Asmline& instruction);
};

#endif  // PARSER_H_
