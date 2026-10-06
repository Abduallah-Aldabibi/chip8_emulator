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

bool chip8::loadGame(const char* filename){
    std::ifstream file(filename, std::ios::binary | std::ios::ate);// Open ROM in read only (binary) and start at the end of the file

    if(!file){
        return false; //Return false if unable to open file
    }

    std::streamsize size = file.tellg(); //Get the size of the file by using the position of the pointer at the end.

    file.seekg(0, std::ios::beg); //Move file read position back to the start

    unsigned char* buffer = new unsigned char[size]; //Allocate enough memory to temp store the ROM

    if (!file.read(reinterpret_cast<char*>(buffer), size)) { // Read ROM bytes into temp buffer
        delete [] buffer;
        return false;
    }

    for (int i = 0 ; i < size; ++i) {
        memory[i + 0x200] = buffer[i]; //Copy ROM byte to chip-8 memory starting at position 0x200
    }

    delete [] buffer; //Free temporary buffer
    return true;
}

