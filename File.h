#include <string>
#include <fstream>
#include <array>

#include <functional>

#define inscriptionSignatureLength 200
#define fileValidatorLength 100
#define saltLength 30

#define bufferingSize 3000000

#ifndef FILE_HEADER
#define FILE_HEADER

struct FileHeader {

    static const char correctIncryptionSignature[inscriptionSignatureLength];
    static const char correctValidation[fileValidatorLength];

    char incryptionSignature[inscriptionSignatureLength]; // this should always be the first 200 bytes of the file, just shows that this is indeed an encrypted file
    char salt[saltLength]; // this will be randomized when encrypting and used to roll the password before encryption and decryption
    char fileValidator[fileValidatorLength]; // this will be rolled forward during encryption and backward to show the correct key was used

};


class File {
public:
    File(const std::string& filepath);
    ~File();

    bool isEncrypted();
    bool filepathIsValid();
    std::string getFilepath();

    bool encryptWithPassword(const std::string& password, const std::function<void(long int currentBytesUpdated, long int totalFilesize)>& callback);
    bool decrypt(const std::string& password, const std::function<void(long int currentBytesUpdated, long int totalFilesize)>& callback);

    bool checkPassword(const std::string& password);

private:
    void validateFilepath();
    void readFileLength();
    void readHeader();
    void determineIsEncrypted(const FileHeader& header);
    void truncateFile(int bytes);

    std::string scramblePassword(const std::string& password); // turns the password into a fixed length so that repeating patterns don't reveal the password length
    void subScramble(int a, int b, char* scramble, const std::string& password);

    char rollValue(char original, bool forward, long int itteration, const std::string& password);
    void rollValuesInRange(long int begin, long int end, int itterationOffset, bool forward, const std::string& password);

    void generateSalt();
    void applySalt(std::string& target, const std::string& salt);

private:
    std::fstream stream;
    std::string filepath;
    bool _filepathIsValid;
    bool _isEncrypted;
    FileHeader header;

    long int fileLength;
};


#endif