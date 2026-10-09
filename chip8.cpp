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

void chip8::emulateCycle()
{
    // Fetch Opcode
    opcode = memory[pc] << 8 | memory[pc + 1];
    // Decode Opcode
    switch(opcode & 0xF000) {
        case 0xA000: // ANNN: Sets I to the address NNN
            // Execute opcode
            I = opcode & 0x0FFF;
            pc += 2;
            break;

        case 0xB000:
            pc = V[0] + (opcode & 0x0FFF);
            break;

        case 0xC000:
            V[(opcode & 0x0F00) >> 8] = rand() + opcode & 0x00FF;
            pc += 2;
            break;
        case 0xD000:
            break;
        case 0xE000:
            switch(opcode & 0x00FF) {
                case 0x009E:
                    if(key[V[(opcode & 0x0F00) >> 8]] != 0) {
                        pc += 2;
                    }
                    pc += 2;
                    break;
                case 0x00A1:
                    if(key[V[(opcode & 0x0F00) >> 8]] == 0) {
                        pc += 2;
                    }
                    pc += 2;
                    break;
            }
        case 0xF000:
            switch(opcode & 0x00FF) {
                case 0x0007:
                    V[(opcode & 0x0F00) >> 8] = delay_timer;
                    pc += 2;
                    break;
                case 0x000A:
                    for (int i = 0; i < 16; ++i) {
                        if (key[i]!=0) {
                            V[(opcode & 0x0F00) >> 8] = i;
                            pc += 2;
                            break;
                        }
                    }
                    break;
                case 0x0015:
                    delay_timer = V[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;
                case 0x0018:
                    sound_timer = V[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;
                case 0x001E:
                    I += V[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;

            }

        default:
            printf("Unknown opcode: 0x%X\n", opcode);
    }
    // Update timers
    if(delay_timer > 0)
        --delay_timer;
    if(sound_timer > 0)
    {
        if(sound_timer == 1)
            printf("BEEP!\n");
        --sound_timer;
    }
}