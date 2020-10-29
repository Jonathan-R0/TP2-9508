#include <bits/stdc++.h>

#include <fstream>
#include <iostream>

#include "eBPF.h"
#include "fileFountain.h"
#include "results.h"

#define ERR_INSF_ARG "Error, argument not long enough.\n"

static int work(int numberOfThreads, FileFountain& files) {
  std::string file;
  Results results;
  while (!(file = files.getNext()).empty()) {
    EBPF ebpf(file, results);
    ebpf.run();
  }
  results.printResults();
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << ERR_INSF_ARG;
    return -1;
  }

  int numberOfThreads = strtol(argv[1], NULL, 10);
  FileFountain filefountain(argc, argv);
  return work(numberOfThreads, filefountain);
}
