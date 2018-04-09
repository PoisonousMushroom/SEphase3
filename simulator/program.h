#ifndef PROGRAM_H
#define PROGRAM_H

#include "bug.h"
#include "instruction.h"
#include  <vector>

class Program{
private:
  int id;
  vector<Instruction> inst;
public:
  Program(std::string filename);
  void step(Bug b);

};


#endif

