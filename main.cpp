#include <bits/stdc++.h>

#include <fstream>
#include <iostream>

#include "eBPF.h"
#include "fileFountain.h"
#include "results.h"

#define ERR_INSF_ARG "Error, argument not long enough.\n"

static void detectProblems(EBPF& ebpf, Results& results, std::string& file) {
  bool hasCycles = ebpf.hasCycle();
  if (hasCycles)
    results.addResult(file, true, false);
  else
    results.addResult(file, false, ebpf.hasUnusedInstruction());
}

static void callEBPF(EBPF& ebpf, Results& results, std::string& file) {
  std::ifstream reader;
  std::string filename(file);
  reader.open(filename, std::ifstream::in);
  int i = 1;
  while (reader.good()) {
    std::string myText;
    std::getline(reader, myText, '\n');
    if (myText.size() == 0) continue;
    ebpf.addInstructionToGraph(myText, i);
    i++;
  }
  ebpf.connectLostTags();
  reader.close();
}

static int work(int numberOfThreads, FileFountain& files) {
  std::string file;
  Results results;
  while (!(file = files.getNext()).empty()) {
    EBPF ebpf;
    callEBPF(ebpf, results, file);
    detectProblems(ebpf, results, file);
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
