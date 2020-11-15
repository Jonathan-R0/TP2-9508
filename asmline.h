#ifndef ASMLINE_H_
#define ASMLINE_H_

#include <list>
#include <string>

class Asmline {
 private:
  std::string opCode;
  std::string label;
  std::list<std::string> labelsToJump;
  std::list<std::string> jumpCodes;

 public:
  Asmline(std::string label_, std::string opCode);
  void setLabelToJump(std::string labelToJumpGiven);
  std::string getOpcode();
  std::string getLabel();
  std::list<std::string> getLabelsToJumpTo();
  void setLabelsToJump(std::list<std::string> labelsToJumpGiven);
  bool isJump();
  bool esCortante();
  Asmline(Asmline&& other);
};

#endif  // ASMLINE_H_
