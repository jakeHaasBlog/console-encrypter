#include "ExitState.h"

#include <iostream>
#include "AnsiCodes.h"

void ExitState::run(bool exitSuccessfully) {
    if (exitSuccessfully)
        std::cout << AnsiCodes::green << "Exited successfully!" << AnsiCodes::reset << std::endl;
    else
        std::cout << AnsiCodes::red << "Exited with errors" << AnsiCodes::reset << std::endl;
}