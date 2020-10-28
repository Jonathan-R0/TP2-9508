#include "results.h"

#include <algorithm>
#include <iostream>
#include <vector>

#define CORRECT " GOOD\n"
#define FAILHASCYCLES " FAIL: cycle detected\n"
#define FAILHASUNUSED " FAIL: unused instructions detected\n"

static int cmp(std::string a, std::string b) { return a > b; }

void static sort(std::vector<std::string>& v) {
  std::sort(v.begin(), v.end(), cmp);
}

void Results::addResult(std::string file, bool hasCycleB, bool hasUnusedOpB) {
  if (hasCycleB) {
    hasCycle.push_back(file);
  } else if (hasUnusedOpB) {
    hasUnusedInstructions.push_back(file);
  } else {
    good.push_back(file);
  }
}

void Results::printResults() {
  sort(hasCycle);
  sort(hasUnusedInstructions);
  sort(good);
  for (std::string s : good) std::cout << s << CORRECT;
  for (std::string s : hasCycle) std::cout << s << FAILHASCYCLES;
  for (std::string s : hasUnusedInstructions) std::cout << s << FAILHASUNUSED;
}