#include <bits/stdc++.h>

#include <fstream>
#include <iostream>

#include "eBPF.h"
#include "fileFountain.h"

#define ERR_INSF_ARG "Error, argument not long enough.\n"

static void callEBPF(std::string file) {
  std::cout << "A PROCESAR: " << file << std::endl;
  EBPF ebpf;
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
  ebpf.hasCycle();
  ebpf.hasUnusedInstruction();
  reader.close();
  std::cout << std::endl;
}

static int work(int numberOfThreads, FileFountain& files) {
  std::string file;
  while (!(file = files.getNext()).empty()) {
    callEBPF(file);
  }
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
