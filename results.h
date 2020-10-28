#ifndef RESULTS_H_
#define RESULTS_H_

#include <string>
#include <vector>

class Results {
 private:
  std::vector<std::string> good;
  std::vector<std::string> hasCycle;
  std::vector<std::string> hasUnusedInstructions;

 public:
  void addResult(std::string file, bool hasCycleB, bool hasUnusedOpB);
  void printResults();
};

#endif  // RESULTS_H_