#ifndef MO2_HH
#define MO2_HH
#include <array>
#include <cstddef>
#include <ios>
#include <iostream>
#include <stdint.h>
#include <vector>

#define DEBUG

#define MO2DEBUG(name, ident)                                                  \
  std::cout << std::hex << " \033[33m" << #name << "\033[0m: " << #ident       \
            << " = \033[32m" << static_cast<size_t>(ident) << "\033[0m \n";

namespace MO2 {

static constexpr size_t MEMSIZE = 64 * 1024;
// clang-format off
// Thank you Mr.ChatGPT
enum isa: uint8_t {
    // Load and Store Instructions
    LDA_IMMEDIATE = 0xA9, LDA_ZERO_PAGE = 0xA5, LDA_ZERO_PAGE_X = 0xB5,
    LDA_ABSOLUTE = 0xAD, LDA_ABSOLUTE_X = 0xBD, LDA_ABSOLUTE_Y = 0xB9,
    LDA_INDIRECT_X = 0xA1, LDA_INDIRECT_Y = 0xB1,

    STA_ZERO_PAGE = 0x85, STA_ZERO_PAGE_X = 0x95, STA_ABSOLUTE = 0x8D,
    STA_ABSOLUTE_X = 0x9D, STA_ABSOLUTE_Y = 0x99, STA_INDIRECT_X = 0x81,
    STA_INDIRECT_Y = 0x91,

    LDX_IMMEDIATE = 0xA2, LDX_ZERO_PAGE = 0xA6, LDX_ZERO_PAGE_Y = 0xB6,
    LDX_ABSOLUTE = 0xAE, LDX_ABSOLUTE_Y = 0xBE,

    LDY_IMMEDIATE = 0xA0, LDY_ZERO_PAGE = 0xA4, LDY_ZERO_PAGE_X = 0xB4,
    LDY_ABSOLUTE = 0xAC, LDY_ABSOLUTE_X = 0xBC,

    STX_ZERO_PAGE = 0x86, STX_ZERO_PAGE_Y = 0x96, STX_ABSOLUTE = 0x8E,

    STY_ZERO_PAGE = 0x84, STY_ZERO_PAGE_X = 0x94, STY_ABSOLUTE = 0x8C,

    // Arithmetic Instructions
    ADC_IMMEDIATE = 0x69, ADC_ZERO_PAGE = 0x65, ADC_ZERO_PAGE_X = 0x75,
    ADC_ABSOLUTE = 0x6D, ADC_ABSOLUTE_X = 0x7D, ADC_ABSOLUTE_Y = 0x79,
    ADC_INDIRECT_X = 0x61, ADC_INDIRECT_Y = 0x71,

    SBC_IMMEDIATE = 0xE9, SBC_ZERO_PAGE = 0xE5, SBC_ZERO_PAGE_X = 0xF5,
    SBC_ABSOLUTE = 0xED, SBC_ABSOLUTE_X = 0xFD, SBC_ABSOLUTE_Y = 0xF9,
    SBC_INDIRECT_X = 0xE1, SBC_INDIRECT_Y = 0xF1,

    // Compare Instructions
    CMP_IMMEDIATE = 0xC9, CMP_ZERO_PAGE = 0xC5, CMP_ZERO_PAGE_X = 0xD5,
    CMP_ABSOLUTE = 0xCD, CMP_ABSOLUTE_X = 0xDD, CMP_ABSOLUTE_Y = 0xD9,
    CMP_INDIRECT_X = 0xC1, CMP_INDIRECT_Y = 0xD1,

    CPX_IMMEDIATE = 0xE0, CPX_ZERO_PAGE = 0xE4, CPX_ABSOLUTE = 0xEC,

    CPY_IMMEDIATE = 0xC0, CPY_ZERO_PAGE = 0xC4, CPY_ABSOLUTE = 0xCC,

    BIT_ZERO_PAGE = 0x24, BIT_ABSOLUTE = 0x2c,

    // Jump and Branch Instructions
    JMP_ABSOLUTE = 0x4C, JMP_INDIRECT = 0x6C, JSR_ABSOLUTE = 0x20,
    RTS = 0x60, BCC_RELATIVE = 0x90, BCS_RELATIVE = 0xB0, BEQ_RELATIVE = 0xF0,
    BMI_RELATIVE = 0x30, BNE_RELATIVE = 0xD0, BPL_RELATIVE = 0x10,
    BVC_RELATIVE = 0x50, BVS_RELATIVE = 0x70,

    // Increment and Decrement Instructions
    INC_ZERO_PAGE = 0xE6, INC_ZERO_PAGE_X = 0xF6, INC_ABSOLUTE = 0xEE,
    INC_ABSOLUTE_X = 0xFE, DEC_ZERO_PAGE = 0xC6, DEC_ZERO_PAGE_X = 0xD6,
    DEC_ABSOLUTE = 0xCE, DEC_ABSOLUTE_X = 0xDE,

    // Logical Instructions
    AND_IMMEDIATE = 0x29, AND_ZERO_PAGE = 0x25, AND_ZERO_PAGE_X = 0x35,
    AND_ABSOLUTE = 0x2D, AND_ABSOLUTE_X = 0x3D, AND_ABSOLUTE_Y = 0x39,
    AND_INDIRECT_X = 0x21, AND_INDIRECT_Y = 0x31,

    ORA_IMMEDIATE = 0x09, ORA_ZERO_PAGE = 0x05, ORA_ZERO_PAGE_X = 0x15,
    ORA_ABSOLUTE = 0x0D, ORA_ABSOLUTE_X = 0x1D, ORA_ABSOLUTE_Y = 0x19,
    ORA_INDIRECT_X = 0x01, ORA_INDIRECT_Y = 0x11,

    EOR_IMMEDIATE = 0x49, EOR_ZERO_PAGE = 0x45, EOR_ZERO_PAGE_X = 0x55,
    EOR_ABSOLUTE = 0x4D, EOR_ABSOLUTE_X = 0x5D, EOR_ABSOLUTE_Y = 0x59,
    EOR_INDIRECT_X = 0x41, EOR_INDIRECT_Y = 0x51,

    // Shift and Rotate Instructions
    ASL_ACCUMULATOR = 0x0A, ASL_ZERO_PAGE = 0x06, ASL_ZERO_PAGE_X = 0x16,
    ASL_ABSOLUTE = 0x0E, ASL_ABSOLUTE_X = 0x1E, LSR_ACCUMULATOR = 0x4A,
    LSR_ZERO_PAGE = 0x46, LSR_ZERO_PAGE_X = 0x56, LSR_ABSOLUTE = 0x4E,
    LSR_ABSOLUTE_X = 0x5E, ROL_ACCUMULATOR = 0x2A, ROL_ZERO_PAGE = 0x26,
    ROL_ZERO_PAGE_X = 0x36, ROL_ABSOLUTE = 0x2E, ROL_ABSOLUTE_X = 0x3E,
    ROR_ACCUMULATOR = 0x6A, ROR_ZERO_PAGE = 0x66, ROR_ZERO_PAGE_X = 0x76,
    ROR_ABSOLUTE = 0x6E, ROR_ABSOLUTE_X = 0x7E,

    // Miscellaneous Instructions
    NOP = 0xEA, BRK = 0x00, RTI = 0x40, CLC = 0x18, SEC = 0x38, CLI = 0x58,
    SEI = 0x78, CLV = 0xB8, CLD = 0xD8, SED = 0xF8,
        // Transfer Instructions
    TAX = 0xAA, TXA = 0x8A, DEX = 0xCA, INX = 0xE8, TAY = 0xA8, TYA = 0x98,
    DEY = 0x88, INY = 0xC8,

    // Stack Instructions
    TSX = 0xBA, TXS = 0x9A, PHA = 0x48, PLA = 0x68, PHP = 0x08, PLP = 0x28
};
// clang-format on

using inst_type = std::vector<uint8_t>;
struct MO2 {
  MO2() {
    memory = std::array<uint8_t, MEMSIZE>{0};
    accumulator = 0;
    X = 0;
    Y = 0;
    programCounter = 0;
  }

  MO2(const std::array<uint8_t, MEMSIZE> &mem)
      : memory(mem), programCounter(0) {}

  void reset() {
    memory = std::array<uint8_t, MEMSIZE>{0};
    programCounter = 0;
    instructionCounter = 0;
    flags.Break = 0;
    flags.Zero = 0;
    flags.Negative = 0;
    accumulator = 0;
    X = 0;
    Y = 0;
  }

  uint8_t fetchByte() { return memory[++programCounter]; }

  uint16_t fetchWord() {
    uint8_t first = memory[++programCounter];
    uint8_t second = memory[++programCounter];
    return (second << 8) | first;
  }

  // utility
  void setZeroNegative(uint8_t _byte) {
    flags.Zero = _byte == 0;
    flags.Negative = (_byte & 0b1000000) > 0;
  }

  // Load instructions
  void perLdaImm() {
    accumulator = fetchByte();
    MO2DEBUG(LDA IMM, accumulator)
  }

  // load instructions
  void perLdaZeroPage() { accumulator = memory[fetchByte()]; }
  void perLdaZeroPageX() { accumulator = memory[fetchByte() + X]; }
  void perLdaAbs() { accumulator = memory[fetchWord()]; }
  void perLdaAbsX() { accumulator = memory[fetchWord() + X]; }
  void perLdaAbsY() { accumulator = memory[fetchWord() + Y]; }
  void perLdaIndiX() { accumulator = memory[memory[fetchWord() + X]]; }
  void perLdaIndiY() { accumulator = memory[memory[fetchWord()] + Y]; }

  void perLdxImm() { X = fetchByte(); }
  void perLdxZeroPage() { X = memory[fetchByte()]; }
  void perLdxZeroPageY() { X = memory[fetchByte() + Y]; }
  void perLdxAbs() { X = memory[fetchWord()]; }
  void perLdxAbsY() { X = memory[fetchWord() + Y]; }

  void perLdyImm() { X = fetchByte(); }
  void perLdyZeroPage() { X = memory[fetchByte()]; }
  void perLdyZeroPageY() { X = memory[fetchByte() + Y]; }
  void perLdyAbs() { X = memory[fetchWord()]; }
  void perLdyAbsY() { X = memory[fetchWord() + Y]; }

  // Store instructions
  void perStaZeroPage() { memory[fetchByte()] = accumulator; }
  void perStaZeroPageX() { memory[fetchByte() + X] = accumulator; }
  void perStaAbs() { memory[fetchWord()] = accumulator; }
  void perStaAbsX() { memory[fetchWord() + X] = accumulator; }
  void perStaAbsY() { memory[fetchWord() + Y] = accumulator; }
  void perStaIndi() { memory[memory[fetchWord()]] = accumulator; }
  void perStaIndiX() { memory[memory[fetchWord() + X]] = accumulator; }
  void perStaIndiY() { memory[memory[fetchWord()] + Y] = accumulator; }

  void perStxZeroPage() { memory[fetchByte()] = X; }
  void perStxZeroPageY() { memory[fetchByte() + Y] = X; }
  void perStxAbs() { memory[fetchWord()] = X; }

  void perStyZeroPage() { memory[fetchByte()] = Y; }
  void perStyZeroPageX() { memory[fetchByte() + X] = Y; }
  void perStyAbs() { memory[fetchWord()] = Y; }

// compare instructions
#define _HandleCpFunc(fun, reg, exp)                                           \
  void per##fun() {                                                            \
    uint8_t operand = exp;                                                     \
    uint8_t value = reg;                                                       \
    uint8_t p = value - operand;                                               \
    flags.Zero = p == 0;                                                       \
    flags.Carry = value >= p;                                                  \
  }

  // clang-format off

  _HandleCpFunc(CmpImm, accumulator, fetchByte()) _HandleCpFunc(CmpZeroPage, accumulator, memory[fetchByte()])
  _HandleCpFunc(CmpZeroPageX, accumulator, memory[fetchByte() + X]) _HandleCpFunc(CmpAbs, accumulator, memory[fetchWord()])
  _HandleCpFunc(CmpAbsX, accumulator, memory[fetchWord() + X])
  _HandleCpFunc(CmpAbsY, accumulator, memory[fetchWord() + Y])
  _HandleCpFunc(CmpIndiX, accumulator, memory[memory[fetchWord() + X]])
  _HandleCpFunc(CmpIndiY, accumulator, memory[memory[fetchWord()] + Y])

  _HandleCpFunc(CpxImm, X, fetchByte())
  _HandleCpFunc(CpxZeroPage, X, memory[fetchByte()])
  _HandleCpFunc(CpxAbs, X, memory[fetchWord()])

  _HandleCpFunc(CpyImm, Y, fetchByte())
  _HandleCpFunc(CpyZeroPage, Y, memory[fetchByte()])
  _HandleCpFunc(CpyAbs, Y, memory[fetchWord()])

  void perBitZeroPage() {
    uint8_t temp = accumulator & memory[fetchByte()];
    setZeroNegative(temp);
  }
  void perBitAbs() {
    uint8_t temp = accumulator & memory[fetchWord()];
    setZeroNegative(temp);
  }
  // clang-format on

  // flags instructions
  void perClc() { flags.Carry = 0b0; }
  void perSec() { flags.Carry = 0b1; }
  void perClv() { flags.Overflow = 0b0; }
  void perCli() { flags.Mask = 0b0; }
  void perSei() { flags.Mask = 0b1; }
  void perCld() { flags.Decimal = 0b0; }
  void perSed() { flags.Decimal = 0b1; }
  void perBrk() {
    flags.Break = 0b1;
    instructionCounter = 0;
  }

  // register instructions
  void perTax() { X = accumulator; }
  void perTay() { Y = accumulator; }
  void perTxa() { accumulator = X; }
  void perTya() { accumulator = Y; }
  void perDex() {
    X -= 1;
    MO2DEBUG(DEX, X)
  } // no points in dex
  void perDey() { Y = Y - 1; }
  void perInx() {
    X = X + 1;
    MO2DEBUG(INX, X)
  }
  void perIny() { Y = Y + 1; }

  void perIncZeroPage() { ++memory[fetchByte()]; }
  void perIncZeroPageX() { ++memory[fetchByte() + X]; }
  void perIncAbs() { ++memory[fetchWord()]; }
  void perIncAbsX() { ++memory[fetchWord() + X]; }

  void perDecZeroPage() { ++memory[fetchByte()]; }
  void perDecZeroPageX() { ++memory[fetchByte() + X]; }
  void perDecAbs() { ++memory[fetchWord()]; }
  void perDecAbsX() { ++memory[fetchWord() + X]; }

  void perAdc() {
    uint8_t addr = fetchByte();
    uint16_t temp = memory[addr] + accumulator + flags.Carry;
    flags.Carry = temp > 0xff;
    flags.Overflow = (memory[addr] & 0x80) != (temp & 0x80);
    setZeroNegative(temp);
    accumulator = temp & 0xff; // ensure the value fits 8 bits
  }
  void perSbc() {
    uint8_t addr = fetchByte();
    uint16_t temp = memory[addr] - accumulator - flags.Carry;
    flags.Carry = temp > 0xff;
    flags.Overflow = (memory[addr] & 0x80) != (temp & 0x80);
    accumulator = temp & 0xff;
  }

  // bitwise
  void perAndImm() {
    accumulator &= fetchByte();
    setZeroNegative(accumulator);
  }
  void perAndZeroPage() {
    accumulator &= memory[fetchByte()];
    setZeroNegative(accumulator);
  }
  void perAndZeroPageX() {
    accumulator &= memory[fetchByte() + fetchByte()];
    setZeroNegative(accumulator);
  }
  void perAndAbs() {
    accumulator &= memory[fetchWord()];
    setZeroNegative(accumulator);
  }
  void perAndAbsX() {
    accumulator &= memory[fetchWord() + fetchByte()];
    setZeroNegative(accumulator);
  }
  void perAslacc() {
    accumulator <<= 1;
    flags.Carry = ((accumulator >> 7) & 1);
    setZeroNegative(accumulator);
    MO2DEBUG(ASL, accumulator) MO2DEBUG(ASL, flags.Carry)
  }
  void perAslZeroPage() {
    accumulator <<= memory[fetchByte()];
    flags.Carry = ((accumulator >> 7) & 1);
    setZeroNegative(accumulator);
  }
  void perAslZeroPageX() {
    accumulator <<= memory[fetchByte() + X];
    setZeroNegative(accumulator);
  }
  void perAslAbs() {
    accumulator <<= memory[fetchWord()];
    setZeroNegative(accumulator);
  }
  void perAslAbsX() {
    accumulator <<= memory[fetchWord() + X];
    setZeroNegative(accumulator);
  }

  // branching
  void perBne() {
#ifdef DEBUG
    MO2DEBUG(BNE, flags.Zero)
#endif
    if (!flags.Zero) {
      programCounter = static_cast<size_t>(fetchByte());
      MO2DEBUG(BNE, programCounter)
    }
  }
  void perBeq() {
#ifdef DEBUG
    MO2DEBUG(BEQ, flags.Zero)
#endif
    if (flags.Zero) {
      programCounter = static_cast<size_t>(fetchByte());
    }
  }
  void perBcc() {
#ifdef DEBUG
    MO2DEBUG(BCC, flags.Carry)
#endif
    if (!flags.Carry)
      programCounter = static_cast<size_t>(fetchByte());
  }
  void perBcs() {
#ifdef DEBUG
    MO2DEBUG(BCS, flags.Carry)
#endif
    if (flags.Carry) {
      programCounter = static_cast<size_t>(fetchByte());
      MO2DEBUG(BCS, programCounter) MO2DEBUG(BCS, memory[programCounter])
    }
  }
  void perBvc() {
#ifdef DEBUG
    MO2DEBUG(BVC, flags.Overflow)
#endif
    if (!flags.Overflow)
      programCounter = static_cast<size_t>(fetchByte());
  }
  void perBvs() {
#ifdef DEBUG
    MO2DEBUG(BVS, flags.Overflow)
#endif
    if (flags.Overflow)
      programCounter = static_cast<size_t>(fetchByte());
  }
  void perBpl() {
#ifdef DEBUG
    MO2DEBUG(BPL, flags.Negative)
#endif
    if (!flags.Negative)
      programCounter = static_cast<size_t>(fetchByte());
  }
  void perBmi() {
#ifdef DEBUG
    MO2DEBUG(BMI, flags.Negative)
#endif
    if (flags.Negative)
      programCounter = static_cast<size_t>(fetchByte());
  }

  void perJmpAbs() {
    programCounter = fetchWord();
#ifdef DEBUG
    MO2DEBUG(JMP, programCounter)
#endif
  }

  void perJsrAbs() {
    memory[--stackPtr] = programCounter - 1;
    programCounter = fetchWord();
  }

  void perRts() {
    uint8_t first = memory[--stackPtr];
    uint8_t second = memory[--stackPtr];  
    programCounter = (first << 8) | second;
  }

  // stack operations
  void perPha() {
    memory[--stackPtr] = accumulator;
    programCounter++;
    MO2DEBUG(PHA, programCounter)
  }
  void perPla() {
    stackPtr += 1;
    accumulator = memory[stackPtr];
    programCounter++;
  }
  void perPhp() {
    memory[--stackPtr] = P;
    programCounter++;
  }

  void executeInstructions() {
    auto insts = memory[programCounter];

    // clang-format off
    MO2DEBUG(EXEC, insts)
    MO2DEBUG(EXEC, programCounter)
       

    switch (insts) {

      #define _HandleCase(e, fun)                                                    \
        case e:                                                                      \
          per##fun();                                                                \
          break;

      // transfer
      _HandleCase(TAX, Tax) _HandleCase(TAY, Tay) _HandleCase(TXA, Txa) _HandleCase(TYA, Tya)
      _HandleCase(DEX, Dex) _HandleCase(DEY, Dey) _HandleCase(INX, Inx) _HandleCase(INY, Iny)

      // memory 
      _HandleCase(LDY_IMMEDIATE, LdyImm) _HandleCase(LDY_ZERO_PAGE, LdyZeroPage) _HandleCase(LDX_IMMEDIATE, LdxImm)
      _HandleCase(LDA_ZERO_PAGE, LdaZeroPage) _HandleCase(LDX_ZERO_PAGE, LdxZeroPage) _HandleCase(LDA_IMMEDIATE, LdaImm)
      _HandleCase(STY_ZERO_PAGE, StyZeroPage) _HandleCase(STX_ZERO_PAGE, StxZeroPage) _HandleCase(STA_ZERO_PAGE, StaZeroPage)

      _HandleCase(STA_ZERO_PAGE_X, StaZeroPageX) _HandleCase(STA_ABSOLUTE, StaAbs) _HandleCase(STA_ABSOLUTE_X, StaAbsX)
      _HandleCase(STA_ABSOLUTE_Y, StaAbsY) _HandleCase(STA_INDIRECT_Y, StaIndiY) _HandleCase(STA_INDIRECT_X, StaIndiX)

      _HandleCase(INC_ZERO_PAGE, IncZeroPage) _HandleCase(INC_ZERO_PAGE_X, IncZeroPageX) _HandleCase(INC_ABSOLUTE, IncAbs)
      _HandleCase(INC_ABSOLUTE_X, IncAbsX)
      
      _HandleCase(DEC_ZERO_PAGE, DecZeroPage) _HandleCase(DEC_ZERO_PAGE_X, DecZeroPageX) _HandleCase(DEC_ABSOLUTE, DecAbs)
      _HandleCase(DEC_ABSOLUTE_X, DecAbsX)
      
      _HandleCase(BRK, Brk) _HandleCase(CLC, Clc) _HandleCase(CLI, Cli) _HandleCase(CLV, Clv)
      
      // bitwise
      _HandleCase(ADC_IMMEDIATE, Adc) _HandleCase(ASL_ACCUMULATOR, Aslacc)
      

      // compare
      _HandleCase(CMP_IMMEDIATE, CmpImm) _HandleCase(CMP_ZERO_PAGE, CmpZeroPage) _HandleCase(CMP_ZERO_PAGE_X, CmpZeroPageX)
      _HandleCase(CMP_ABSOLUTE, CmpAbs) _HandleCase(CMP_ABSOLUTE_X, CmpAbsX) _HandleCase(CMP_ABSOLUTE_Y, CmpAbsY)
      _HandleCase(CMP_INDIRECT_X, CmpIndiX) _HandleCase(CMP_INDIRECT_Y, CmpIndiY)
      
      _HandleCase(CPX_IMMEDIATE, CpxImm) _HandleCase(CPX_ZERO_PAGE, CpxZeroPage)
      
      _HandleCase(CPY_IMMEDIATE, CpyImm) _HandleCase(CPY_ZERO_PAGE, CpyZeroPage)
      
      _HandleCase(BIT_ZERO_PAGE, BitZeroPage) _HandleCase(BIT_ABSOLUTE, BitAbs)
      

      // branching
      _HandleCase(BNE_RELATIVE, Bne) _HandleCase(BEQ_RELATIVE, Beq) _HandleCase(BPL_RELATIVE, Bpl)
      _HandleCase(BMI_RELATIVE, Bmi) _HandleCase(JMP_ABSOLUTE, JmpAbs) _HandleCase(BCS_RELATIVE, Bcs)

      _HandleCase(PLA, Pla) _HandleCase(PHA, Pha) _HandleCase(PHP, Php) _HandleCase(JSR_ABSOLUTE, JsrAbs)

    default:
      break;
    }
    // 
  }

  void execute() {
    while (!flags.Break) {
      executeInstructions();
      ++programCounter;
    }
#ifdef DEBUG
    std::cout << "First 255 Bytes: " << '\n';
    for (size_t i = 0; i < 255; ++i) {
      std::cout << std::hex << static_cast<size_t>(memory[i]) << ' ';
    }
    std::cout << '\n';
    MO2DEBUG(execute, X) MO2DEBUG(execute, Y) MO2DEBUG(execute, accumulator) MO2DEBUG(execute, stackPtr) MO2DEBUG(execute, programCounter)
#endif
  }

  void loadProgramToMem(const inst_type &instructions) {
    for (size_t i = 0; i < instructions.size(); ++i) {
      memory[i] = instructions[i];
    }
  }

  std::array<uint8_t, MEMSIZE> memory;
  uint8_t accumulator;
  uint8_t X;
  uint8_t Y;
  size_t programCounter = 0;
  size_t instructionCounter = 0;
  size_t stackPtr = 0x1ff;

  // flags
  struct Flags {
  uint8_t Zero : 1 = 0;
  uint8_t Carry : 1 = 0;
  uint8_t Mask : 1 = 0;
  uint8_t Decimal : 1 = 0;
  uint8_t Break : 1 = 0;
  uint8_t Unused : 1 = 0;
  uint8_t Overflow : 1 = 0;
  uint8_t Negative : 1 = 0;
  };
  union {
    uint8_t P;
    Flags flags;
  };
};
} // namespace MO2
#endif