#include "include/MO2.hpp"
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

void run(const std::string &name, MO2::MO2 &i, const MO2::inst_type &ins) {
  i.loadProgramToMem(ins);
  std::cout << "==============[START]==============\n"
            << "program name: " << name << "\n\n";
  i.execute();
  std::cout << "===============[END]===============\n";
}

int main() {
  MO2::MO2 instance{};
  MO2::inst_type t{
      MO2::LDX_IMMEDIATE, 0x08, MO2::DEX, MO2::CPX_IMMEDIATE, 0x03,
      MO2::BNE_RELATIVE,  0x01, MO2::BRK,
  };
  MO2::inst_type a{
      MO2::LDA_IMMEDIATE, 0x01, MO2::STA_ABSOLUTE, 0x02, 0x00,
      MO2::LDA_IMMEDIATE, 0x05, MO2::STA_ABSOLUTE, 0x02, 0x01,
      MO2::LDA_IMMEDIATE, 0x08, MO2::STA_ABSOLUTE, 0x02, 0x02,
  };
  MO2::inst_type stck{
    MO2::PHA,
    MO2::TXA,             
    MO2::PHA,            
    MO2::TYA,            
    MO2::PHA,
    MO2::JSR_ABSOLUTE, 0x00, 0xC1,
    MO2::PLA, 
    MO2::TAY, 
    MO2::PLA,
    MO2::TAX, 
    MO2::PLA, 
    MO2::RTS

   };
  // run("add 10 using routines", instance, ff);
  run("stack", instance, stck);
}