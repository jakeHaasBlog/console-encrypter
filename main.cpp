
#include "InitialState.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main(int argc, char* argv[]) {

    #ifdef _WIN32
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif

    InitialState::run(argc, argv);
    return 0;
}