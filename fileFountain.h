#ifndef FILEFOUNTAIN_H_
#define FILEFOUNTAIN_H_

#include <string>
#include <vector>

class FileFountain {
 private:
  std::vector<std::string> files;
  size_t alreadyRead;
  size_t toRead;

 public:
  FileFountain(int argc, char* argv[]);
  std::string getNext();
  void sortFiles();
};

#endif  // FILEFOUNTAIN_H_
