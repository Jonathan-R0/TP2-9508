#include "fileFountain.h"

#include <algorithm>
#include <iostream>
#include <mutex>

FileFountain::FileFountain(int argc, char* argv[]) {
  for (int i = argc - 1; i > 1; i--) {
    std::string file(argv[i]);
    files.push_back(file);
  }
}

int FileFountain::getNumberOfFiles() { return files.size(); }

std::string FileFountain::getNext() {
  std::unique_lock<std::mutex> lock(m);
  if (files.size() == 0) return "";
  std::string file = files.back();
  files.pop_back();
  return file;
}
