#include "InitialState.h"

#include <iostream>

#include "AnsiCodes.h"
#include "File.h"

#include "QueryFileState.h"
#include "EncryptionCaseState.h"
#include "DecryptionCaseState.h"
#include "ExitState.h"

std::string InitialState::helpCode = "help";
std::string InitialState::exitCode = "exit";


void InitialState::run(int argc, char* argv[]) {
    std::cout << AnsiCodes::cyan << "Beginning the execution of " << argv[0] << "." << AnsiCodes::reset << std::endl;
    std::cout << "Enter the value " << AnsiCodes::magenta << exitCode << AnsiCodes::reset << " to exit this program at any point" << std::endl;
    std::cout << "Enter the value " << AnsiCodes::magenta << helpCode << AnsiCodes::reset << " at any point to print this program's manual" << std::endl;

    std::string targetFile = "";
    if (argc > 1) {
        
        targetFile = argv[1];
        for (int i = 2; i < argc; i++){
            // for filepaths containing spaces. All args need to be appended with spaces between.
            targetFile.append(" ");
            targetFile.append(argv[i]);
        }

        File file(targetFile);
        if (!file.filepathIsValid()) {
            transitionToExitState(file);
            return;
        }

        if (file.isEncrypted()) {
            transitionToDecryptionCase(file);
            return;
        } else {
            transitionToEncryptionCase(file);
            return;
        }

    }

    transitionToQueryFileState();
    return;

}


void InitialState::printHelpMessage() {
    std::cout << AnsiCodes::blue << "=== User Manual ==" << AnsiCodes::reset << std::endl;
    std::cout << AnsiCodes::blue << "Description:" << AnsiCodes::reset << std::endl;
    std::cout << AnsiCodes::blue << "- This program can be used to encrypt and decrypt files. Only one file can be encrypted or decrypted at a time either by passing the file as a parameter or by following along the user interface. This program will automatically detect if a given file is encrypted or decrypted and will prompt the user through the encrypting/decrypting proceess." << AnsiCodes::reset << std::endl;
    std::cout << std::endl;
    std::cout << AnsiCodes::blue << "Limitations:" << AnsiCodes::reset << std::endl;
    std::cout << AnsiCodes::magenta << "- PASSWORDS CANNOT BE RECOVERED " << AnsiCodes::blue << "and a file that has been encrypted to a forgotten password will be unsalvageable." << AnsiCodes::reset << std::endl;    
    std::cout << AnsiCodes::blue << "This program cannot decrypt files that have been encrypted using other programs." << AnsiCodes::reset << std::endl;
    std::cout << std::endl;
    std::cout << AnsiCodes::blue << "Arguments:" << AnsiCodes::reset << std::endl;
    std::cout << AnsiCodes::blue << "- 0 arguments given: When there are no parameters supplied, the user will be guided through the program" << AnsiCodes::reset << std::endl;
    std::cout << AnsiCodes::blue << "- 1 argument given: When one argument is supplied, it will be used as a filepath. If the filepath is invalid, the program will exit." << AnsiCodes::reset << std::endl;
    std::cout << AnsiCodes::blue << "- more than one argument given: Only the first argument will be used and a warning message will be printed." << AnsiCodes::reset << std::endl;
    std::cout << std::endl;
    std::cout << AnsiCodes::blue << "For a more detailed overview of the system, please refer to the readme.md file located in this program's root directory" << AnsiCodes::reset << std::endl;
}


void InitialState::transitionToQueryFileState() {
    QueryFileState::run();
}

void InitialState::transitionToEncryptionCase(File& file) {
    EncryptionCaseState::run(file);
}

void InitialState::transitionToDecryptionCase(File& file) {
    DecryptionCaseState::run(file);
}

void InitialState::transitionToExitState(File& file) {

    std::cout << AnsiCodes::red << "ERROR: The target file: " << file.getFilepath() << " is invalid" << AnsiCodes::reset << std::endl;

    ExitState::run(false);
}