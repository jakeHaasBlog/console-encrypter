#include "EncryptionCaseState.h"

#include <iostream>
#include <string>
#include <iomanip>

#include "AnsiCodes.h"
#include "File.h"

#include "ExitState.h"
#include "InitialState.h"

void EncryptionCaseState::run(File& file) {


    std::cout << "The selected file is not encrypted." << std::endl;

    std::string input1;
    std::string input2;
    
    while (true) {
        std::cout << "Enter a new password to encrypt your file: " << AnsiCodes::cyan;
        std::cin >> input1;
        std::cout << AnsiCodes::reset;

        if (input1 == InitialState::exitCode) {
            std::cout << AnsiCodes::green << "Exiting program" << AnsiCodes::reset << std::endl;
            transitionToExitState(true);
            return;
        }

        if (input1 == InitialState::helpCode) {
            InitialState::printHelpMessage();
            run(file);
            return;
        }

        if (input1.size() < passwordMinLength) {
            std::cout << AnsiCodes::red << "The password that was entered is too short. Passwords must be at least " << passwordMinLength << " characters in length." << AnsiCodes::reset << std::endl;
            continue;
        }

        std::cout << "Confirm your password by re-entering it: " << AnsiCodes::cyan;
        std::cin >> input2;
        std::cout << AnsiCodes::reset;

        if (input2 == InitialState::exitCode) {
            std::cout << AnsiCodes::green << "Exiting program" << AnsiCodes::reset << std::endl;
            transitionToExitState(true);
            return;
        }

        if (input2 == InitialState::helpCode) {
            InitialState::printHelpMessage();
            run(file);
            return;
        }

        if (input1.compare(input2) != 0) {
            std::cout << AnsiCodes::red << "The confirmation password does not match the original. Aborting." << AnsiCodes::reset << std::endl;
            continue;
        }

        break;

    }

    std::cout << AnsiCodes::green << "Encrypting your file. " << AnsiCodes::magenta << "Please do not close this program." << AnsiCodes::reset << std::endl;

    std::cout << std::endl;
    file.encryptWithPassword(input1, progressBarUpdateCallback);

    std::cout << "\nYour file has been encrypted successfully!" << std::endl;
    transitionToExitState(true);   

}

void EncryptionCaseState::transitionToExitState(bool exitSuccessfully) {
    ExitState::run(exitSuccessfully);
}



void EncryptionCaseState::progressBarUpdateCallback(long int currentBytesUpdated, long int totalFilesize) {

    float progress = (float)((double)currentBytesUpdated / totalFilesize); 
    progress *= 100.0f;

    std::string spacer = "";
    if (progress < 10.0f) spacer.append("  ");
    else if (progress < 100.0f) spacer.append(" ");

    int progressGreens = (int)((progress / 100.0f) * 30.0f);
    std::string progressBar = "";
    progressBar.append(AnsiCodes::green);
    for (int i = 0; i < progressGreens; i++) {
        progressBar.append("#");
    }

    progressBar.append(AnsiCodes::red);
    for (int i = 0; i < 30 - progressGreens; i++) {
        progressBar.append("-");
    }

    progressBar.append(AnsiCodes::reset);
    
    
    std::cout << '\r' << std::flush;
    std::cout << "Encrypting: " << spacer << std::fixed;
    std::cout << std::setprecision(2) << progress << "% - " << progressBar << std::flush;

}