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
  void buildInstruction(std::list<char>* delimsSeen,
                        std::list<std::string>* parts);
};

#endif  // PARSER_H_
