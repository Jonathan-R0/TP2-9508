#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "eBPF.h"
#include "fileFountain.h"
#include "results.h"
#include "thread.h"

#define ERR_INSF_ARG "Error, argument not long enough.\n"

static int work(int numberOfThreads, FileFountain& files) {
  std::vector<EBPF*> holders;
  Results results;

  numberOfThreads = numberOfThreads > files.getNumberOfFiles()
                        ? files.getNumberOfFiles()
                        : numberOfThreads;

  holders.reserve(numberOfThreads);

  for (int i = 0; i < numberOfThreads; i++) {
    holders.push_back(new EBPF(results, files));
  }

  for (auto& it : holders) it->start();
  for (auto& it : holders) {
    it->join();
    delete it;
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
  if (numberOfThreads < 1) return -1;
  FileFountain filefountain(argc, argv);
  return work(numberOfThreads, filefountain);
}
