
#include "File.h"

#ifndef ENCRYPTION_CASE_STATE
#define ENCRYPTION_CASE_STATE

class EncryptionCaseState {
public:
    static void run(File& file);

private:
    static void transitionToExitState(bool exitSuccessfully);


    static const int passwordMinLength = 5;
    static void progressBarUpdateCallback(long int currentBytesUpdated, long int totalFilesize);
};

#endif