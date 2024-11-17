#include "stack-vm.h"
#include <iostream>
#include <vector>

// Constructor
stackVM::stackVM() : pc(-1), sp(-1), running(1), typ(0), dat(0) {
    memory.resize(1000000, 0);  // Resize memory to 1 million elements
}

// Extract instruction type
i32 stackVM::getType(i32 instruction) {
    return (instruction & 0xc0000000) >> 30;
}

// Extract instruction data
i32 stackVM::getData(i32 instruction) {
    return instruction & 0x3fffffff;
}

// Fetch the next instruction
void stackVM::fetch() {
    pc++;
    if (pc >= memory.size()) {
        std::cerr << "Error: Program counter out of bounds." << std::endl;
        running = 0;
    }
}

// Decode the current instruction
void stackVM::decode() {
    typ = getType(memory[pc]);
    dat = getData(memory[pc]);
}

// Execute the current instruction
void stackVM::execute() {
    if (typ == 0 || typ == 2) {
        sp++;
        if (sp >= memory.size()) {
            std::cerr << "Error: Stack pointer out of bounds." << std::endl;
            running = 0;
        } else {
            memory[sp] = dat;
        }
    } else {
        doPrimitive();
    }
}

// Perform primitive operations
void stackVM::doPrimitive() {
    switch (dat) {
        case 0:  // Halt
            std::cout << "Halt" << std::endl;
            running = 0;
            break;

        case 1:  // Add
            if (sp < 1) {
                std::cerr << "Error: Not enough elements on stack for addition." << std::endl;
                running = 0;
            } else {
                std::cout << "Add " << memory[sp - 1] << " " << memory[sp] << std::endl;
                memory[sp - 1] += memory[sp];
                sp--;
            }
            break;
        
        case 2: //Sub
            if (sp < 1) {
                std::cerr << "Error: Not enough elements on stack for addition." << std::endl;
                running = 0;
            } else {
                std::cout << "Sub " << memory[sp - 1] << " " << memory[sp] << std::endl;
                memory[sp - 1] -= memory[sp];
                sp--;
            }
            break;
        
        case 3: //Multiply
            if (sp < 1) {
                std::cerr << "Error: Not enough elements on stack for addition." << std::endl;
                running = 0;
            } else {
                std::cout << "Multiply " << memory[sp - 1] << " " << memory[sp] << std::endl;
                memory[sp - 1] *= memory[sp];
                sp--;
            }
            break;

        case 4: //Divide
            if (sp < 1) {
                std::cerr << "Error: Not enough elements on stack for addition." << std::endl;
                running = 0;
            } else {
                std::cout << "Divide " << memory[sp - 1] << " " << memory[sp] << std::endl;
                memory[sp - 1] /= memory[sp];
                sp--;
            }
            break;

        


        default:
            std::cerr << "Error: Unknown primitive operation " << dat << std::endl;
            running = 0;
            break;
    }
}

// Run the VM
void stackVM::run() {
    int iteration_count = 0;
    const int MAX_ITERATIONS = 100000;

    while (running == 1) {
        fetch();
        decode();
        execute();
        std::cout << "Top of Stack: " << memory[sp] << std::endl;

        if (++iteration_count > MAX_ITERATIONS) {
            std::cerr << "Error: Max iterations reached. Halting VM." << std::endl;
            break;
        }
    }
}

// Load a program into memory
void stackVM::loadProgram(std::vector<i32> prog) {
    pc = -1;  // Reset PC before loading
    for (i32 i = 0; i < prog.size(); ++i) {
        if (i >= memory.size()) {
            std::cerr << "Error: Program size exceeds memory capacity." << std::endl;
            break;
        }
        memory[i] = prog[i];
    }
}
