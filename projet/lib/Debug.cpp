#include "Debug.h"

void debugPrint(char* x){
    Rs232 rs232;
    rs232.initialise();
    rs232.readData(x);
}