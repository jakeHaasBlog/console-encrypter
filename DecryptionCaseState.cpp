#include "DecryptionCaseState.h"

#include <iostream>
#include <string>
#include <iomanip>

#include "AnsiCodes.h"
#include "File.h"

#include "ExitState.h"
#include "InitialState.h"

void DecryptionCaseState::run(File& file) {

    std::cout << "The selected file is encrypted. Please enter the password to decrypt it: " << AnsiCodes::cyan;
    std::string input;

    while (true) {

        std::cin >> input;
        std::cout << AnsiCodes::reset;

        if (input == InitialState::exitCode) {
            std::cout << AnsiCodes::green << "Exiting program" << AnsiCodes::reset << std::endl;
            transitionToExitState(true);
            return;
        }

        if (input == InitialState::helpCode) {
            InitialState::printHelpMessage();
            run(file);
            return;
        }

        if (file.checkPassword(input)) {
            break;
        } else {
            std::cout << "The password that you entered was incorrect, please try again: " << AnsiCodes::cyan;
        }

    }

    std::cout << AnsiCodes::green << "The correct password was entered. Please do not close this program." << AnsiCodes::reset << std::endl;

    std::cout << std::endl;
    file.decrypt(input, progressBarUpdateCallback);

    std::cout << AnsiCodes::green << "\nYour file has been decrypted successfully!" << AnsiCodes::reset << std::endl;
    transitionToExitState(true);
    return;

}


void DecryptionCaseState::transitionToExitState(bool exitSuccessfully) {
    ExitState::run(exitSuccessfully);
}


void DecryptionCaseState::progressBarUpdateCallback(long int currentBytesUpdated, long int totalFilesize) {

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
    std::cout << "Decrypting: " << spacer << std::fixed;
    std::cout << std::setprecision(2) << progress << "% - " << progressBar << std::flush;

}