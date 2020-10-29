#include "fileFountain.h"

#include <algorithm>
#include <iostream>
#include <mutex>

/*
static int cmp(std::string a, std::string b) { return a > b; }

void FileFountain::sortFiles() {
  std::sort(files.begin(), files.end(), cmp);
  std::reverse(files.begin(), files.end());
}
*/
FileFountain::FileFountain(int argc, char* argv[]) : alreadyRead(0) {
  for (int i = argc - 1; i > 1; i--) {
    std::string file(argv[i]);
    files.push_back(file);
  }
  // this->sortFiles();
}

int FileFountain::getNumberOfFiles() { return files.size(); }

std::string FileFountain::getNext() {
  std::unique_lock<std::mutex> lock(m);
  if (files.size() == 0) return {};
  ++alreadyRead;
  std::string file = files.back();
  files.pop_back();
  return file;
}
