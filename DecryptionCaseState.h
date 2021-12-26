#include "File.h"

#ifndef DECRYPTION_CASE_STATE
#define DECRYPTION_CASE_STATE

class DecryptionCaseState {
public:
    static void run(File& file);

private:
    static void transitionToExitState(bool exitSuccessfully);

    static void progressBarUpdateCallback(long int currentBytesUpdated, long int totalFilesize);

};

#endif