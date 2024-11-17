#include "stack-vm.h"


int main() {
    //std::cout<<"Initialising vm"<<std::endl;
    stackVM vm;

    std::vector<i32> prog{3, 4, 0x40000001, 12, 0x40000003, 4, 0x40000002, 5, 0x40000004, 0x40000000};
    //std::cout<<"loading program"<<std::endl;
    vm.loadProgram(prog);
    //std::cout<<"Running program"<<std::endl;
    vm.run();
    //std::cout<<"Thank you!"<<std::endl;
    return 0;
}