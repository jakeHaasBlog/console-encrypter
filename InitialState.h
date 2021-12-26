#include <string>

#include "File.h"

#ifndef INITIAL_STATE
#define INITIAL_STATE

// The initial state deals with the program arguments. It either routes user input to the QueryFileState or directly sends the selected file into the Encryption or Decryption states.
class InitialState {
public:
    static void run(int argc, char* argv[]);

    static std::string helpCode;
    static std::string exitCode;

    static void printHelpMessage();

private:
    static void transitionToQueryFileState();
    static void transitionToEncryptionCase(File& file);
    static void transitionToDecryptionCase(File& file);
    static void transitionToExitState(File& file);

};


#endif