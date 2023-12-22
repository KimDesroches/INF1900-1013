#include "debug.h"

void debugPrint(char* x){
    RS232 rs232;
    rs232.initialise();
    rs232.readData(x);
}