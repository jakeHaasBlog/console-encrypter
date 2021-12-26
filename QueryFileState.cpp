#include "QueryFileState.h"

#include <iostream>
#include <string>

#include "AnsiCodes.h"
#include "File.h"

#include "EncryptionCaseState.h"
#include "DecryptionCaseState.h"
#include "ExitState.h"
#include "InitialState.h"

void QueryFileState::run() {

    std::string input;
    while (true) {
        std::cout << "Enter the filepath for the desired file to encrypt or decrypt: " << AnsiCodes::cyan;
        std::cin >> input;
        std::cout << AnsiCodes::reset;

        if (input == InitialState::exitCode) {
            std::cout << AnsiCodes::green << "Exiting program" << AnsiCodes::reset << std::endl;
            transitionToExitCase(true);
            return;
        }

        if (input == InitialState::helpCode) {
            InitialState::printHelpMessage();
            run();
            return;
        }

        File file(input);

        if (file.filepathIsValid()) {
            
            if (file.isEncrypted()) {
                transitionToDecryptionCase(file);
                return;
            }
            else {
                transitionToEncryptionCase(file);
                return;
            }

        }

        else {
            std::cout << AnsiCodes::red << "The entered filepath is invalid" << AnsiCodes::reset << std::endl;
        }

    }

    std::cout << AnsiCodes::red << "APPLICATION ERROR: File was not querried from user before return (InitialState.cpp : void run() )" << AnsiCodes::reset << std::endl;
    transitionToExitCase(false);
}


void QueryFileState::transitionToExitCase(bool exitSuccessfully) {
    ExitState::run(exitSuccessfully);
}

void QueryFileState::transitionToEncryptionCase(File& file) {
    EncryptionCaseState::run(file);
}

void QueryFileState::transitionToDecryptionCase(File& file) {
    DecryptionCaseState::run(file);
}