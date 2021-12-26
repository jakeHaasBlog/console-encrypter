
#include "File.h"

#ifndef QUERY_FILE_STATE
#define QUERY_FILE_STATE

class QueryFileState {
public:
    static void run();

private:
    static void transitionToExitCase(bool exitSuccessfully);
    static void transitionToEncryptionCase(File& file);
    static void transitionToDecryptionCase(File& file);

};

#endif