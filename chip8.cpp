#include "chip8.h"
#include <fstream>

void chip8::initialize()
{
    // Initialize registers and memory once
    pc     = 0x200;  // Program counter starts at 0x200
    opcode = 0;      // Reset current opcode
    I      = 0;      // Reset index register
    sp     = 0;      // Reset stack pointer

    //Clear display
    std::fill(std::begin(gfx), std::end(gfx), 0);

    // Clear stack
    std::fill(std::begin(stack), std::end(stack), 0);

    // Clear registers V0-VF
    std::fill(std::begin(V),std::end(V),0);

    // Clear memory
    std::fill(std::begin(memory),std::end(memory),0);

    //Clear keys
    std::fill(std::begin(key),std::end(key),0);

    // Load fontset
    for(int i = 0; i<80;++i){
        memory[i] = chip8_fontset[i];
    }

}

