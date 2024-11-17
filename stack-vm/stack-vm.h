#ifndef STACK_VM_H
#define STACK_VM_H

#include <iostream>
#include <vector>

typedef int32_t i32;

class stackVM{

    i32 pc = 0;
    i32 sp = 0;
    std::vector<i32> memory;
    i32 typ = 0;
    i32 dat = 0;
    i32 running  = 1;


    //private functions
    i32 getType(i32 instruction);
    i32 getData(i32 instruction);

    void fetch();
    void decode();
    void execute();
    void doPrimitive();

    public:

    stackVM();
    void run();
    void loadProgram(std::vector<i32> prog);


};

#endif