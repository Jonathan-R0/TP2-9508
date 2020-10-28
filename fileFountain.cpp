#include "fileFountain.h"

#include <algorithm>
#include <iostream>
/*
static int cmp(std::string a, std::string b) { return a > b; }

void FileFountain::sortFiles() {
  std::sort(files.begin(), files.end(), cmp);
  std::reverse(files.begin(), files.end());
}
*/
FileFountain::FileFountain(int argc, char* argv[])
    : alreadyRead(0), toRead(files.size() - 1) {
  for (int i = argc - 1; i > 1; i--) {
    std::string file(argv[i]);
    files.push_back(file);
  }
  // this->sortFiles();
}

std::string FileFountain::getNext() {
  if (files.size() == 0) return {};
  ++alreadyRead;
  std::string file = files.back();
  files.pop_back();
  return file;
}
