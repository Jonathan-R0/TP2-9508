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
  Asmline();

  // TEST ONLY
  void seeLabel();
  void seeOpCode();
  void seeLabelsToJump();
  void setLabel(std::string labelGiven);
  void setOpCode(std::string opCodeGiven);
  std::string getOpcode();
  std::string getLabel();
  std::list<std::string> getLabelsToJumpTo();
  void setLabelsToJump(std::list<std::string> labelsToJumpGiven);
  bool isJump();
  bool esCortante();
};

#endif  // ASMLINE_H_
