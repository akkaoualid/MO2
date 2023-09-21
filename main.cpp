#include "include/i02.hpp"
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

void run(const std::string &name, i02::i02 &i, const i02::inst_type &ins) {
  i.loadProgramToMem(ins);
  std::cout << "==============[START]==============\n"
            << "program name: " << name << "\n\n";
  i.execute();
  std::cout << "===============[END]===============\n";
}

int main() {
  i02::i02 instance{};
  // i02::inst_type addNStore{
  //     {0xA9, 0x0A}, // LDA #10
  //     {0x85, 0x00}, // STA $00
  //     {0xA9, 0x14}, // LDA #20
  //     {0x85, 0x01}, // STA $01
  //     {0x18},       // CLC
  //     {0xA5, 0x00}, // LDA $00
  //     {0x65, 0x01}, // ADC $01
  //     {0x85, 0x02}, // STA $02
  //     {0x00}        // BRK
  // };
  // i02::inst_type ff{
  //     {i02::LDX_IMMEDIATE, 0},          // LDX #00
  //     {i02::INX},             // INX
  //     {i02::CPX_IMMEDIATE, 10},         // CPX #10
  //     {i02::BEQ_RELATIVE, 0x05},       // BEQ Done
  //     {i02::JMP_ABSOLUTE, 0x01, 0x00}, // JMP Loop
  //     {i02::BRK}              // BRK
  // };
  // i02::inst_type _asl{
  //   {i02::LDA_IMMEDIATE, 0xff},
  //   {i02::ASL_ACCUMULATOR},
  //   {i02::BCS_RELATIVE, 0x05},
  //   {i02::LDX_IMMEDIATE, 0xab},
  //   {i02::BRK},
  //   {i02::BRK}
  // };
  i02::inst_type t{
      i02::LDX_IMMEDIATE, 0x08, i02::DEX, i02::CPX_IMMEDIATE, 0x03,
      i02::BNE_RELATIVE,  0x01, i02::BRK,
  };
  i02::inst_type a{
      i02::LDA_IMMEDIATE, 0x01, i02::STA_ABSOLUTE, 0x02, 0x00,
      i02::LDA_IMMEDIATE, 0x05, i02::STA_ABSOLUTE, 0x02, 0x01,
      i02::LDA_IMMEDIATE, 0x08, i02::STA_ABSOLUTE, 0x02, 0x02,
  };
  // run("add 10 using routines", instance, ff);
  run("shift A", instance, a);
}