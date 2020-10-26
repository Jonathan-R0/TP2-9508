#ifndef PARSER_H_
#define PARSER_H_
#include <list>
#include <string>

#include "asmline.h"

class Parser {
 private:
  std::list<char> delims;

 public:
  Parser();
  void parseInstruction(std::string asmLine, Asmline& instruction);
  bool isDelim(char c);
};

#endif  // PARSER_H_
