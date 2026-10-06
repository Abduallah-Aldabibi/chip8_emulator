#ifndef CHIP8_EMULATOR_CHIP8_H
#define CHIP8_EMULATOR_CHIP8_H



class chip8{
    //Current 16-bit instruction
    unsigned short opcode;
    // CHIP-8 has 4096 bytes of memory
    unsigned char memory[4096];
    // 16 general-purpose registers: V0 through VF
    unsigned char V[16];
    // Index register: used for memory addresses
    unsigned short I;
    // Program counter: Stores address of next instruction
    unsigned short pc;

    // CHIP-8 display: 64 x 32 pixels
    unsigned char gfx[64 * 32];

    //Timers that decrease at 60hz when greater than 0
    unsigned char delay_timer;
    unsigned char sound_timer;

    //Stack used to store return addresses for subroutine calls
    unsigned short stack[16];
    //Stack pointer keeps track of current stack position
    unsigned short sp;
    //State of the 16 CHIP-8 keys, 0 = not pressed , !0 = pressed
    unsigned char key[16];

    //Built-in CHIP-8 font sprites for hexadecimal characters 0-F
    unsigned char chip8_fontset[80] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
      };


public:
    //Reset the emulator to its initial state
    void initialize();
    //Fetch, decode, and execute one CHIP-8 instruction
    void emulateCycle();
    //Loads a CHIP-8 ROM into memory
    bool loadGame(const char* filename);
};

#endif