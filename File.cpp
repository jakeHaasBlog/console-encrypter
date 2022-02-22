#include "File.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "ConsistantRand.h"

const char FileHeader::correctIncryptionSignature[inscriptionSignatureLength] = "###@@@* This file is encrypted using <The Simple File Encryption Program> it can only be decrypted using the correct password *@@@###     e67yed67hcd667d8vct6t7ydc867yvd8ucx5r6y7vfct7y3dexctf66t7y8ui";
const char FileHeader::correctValidation[fileValidatorLength] = "vf6@y&jdcf6gy7,u!ed5f6g7$j9soj!!x.gy@e5fd 4g67h8j/5r4s5ud67vguidt56v$8egyhjcu567$93\\nxtd7djt5e/678d";


File::File(const std::string& filepath) {
    _isEncrypted = false;
    this->filepath = filepath;

    stream = std::fstream(filepath, std::ios::in | std::ios::out | std::ios::binary);
    validateFilepath();

    if (!_filepathIsValid) {
        stream.close();
        return;
    }

    readFileLength();
    readHeader();
    determineIsEncrypted(header);
}

File::~File() {
    stream.close();
}

void File::validateFilepath() {
    _filepathIsValid = stream.good();
}

void File::readFileLength() {
    std::streampos currentPos = stream.tellg();

    stream.seekg(0, std::ios::end);
    fileLength = stream.tellg();

    stream.seekg(currentPos);
}

void File::readHeader() {
    // if the file is not long enough to contain the header, than it can't be encripted
    if (fileLength <= fileValidatorLength + inscriptionSignatureLength) {
        _isEncrypted = false;
        return;
    }

    stream.seekg(fileLength - inscriptionSignatureLength - fileValidatorLength, std::ios::beg);
    stream.read(&header.fileValidator[0], fileValidatorLength);
    stream.read(&header.incryptionSignature[0], inscriptionSignatureLength);
    stream.seekg(0, std::ios::beg);

}

void File::determineIsEncrypted(const FileHeader& header) {

    for (int i = 0; i < inscriptionSignatureLength - 1; i++) {
        if (header.incryptionSignature[i] != FileHeader::correctIncryptionSignature[i]) {
            _isEncrypted = false;
            return;
        }
    }

    _isEncrypted = true;
}

bool File::isEncrypted() {
    return _isEncrypted;
}

bool File::filepathIsValid() {
    return _filepathIsValid;
}

std::string File::getFilepath() {
    return filepath;
}

bool File::encryptWithPassword(const std::string& password,  const std::function<void(long int currentBytesUpdated, long int totalFilesize)>& callback) {

    std::string scrambledPassword = scramblePassword(password);

    // --- add the header to the end of the file
    stream.seekp(fileLength, std::ios::beg);
    stream.write(&FileHeader::correctValidation[0], fileValidatorLength);
    stream.write(&FileHeader::correctIncryptionSignature[0], inscriptionSignatureLength);

    readFileLength();

    //--- roll each value in the body and validation forward
    int begin = 0;
    int end = 0;

    while (end != fileLength - inscriptionSignatureLength) {

        begin = end;
        end = end + bufferingSize;
        if (end > fileLength - inscriptionSignatureLength)
            end = fileLength - inscriptionSignatureLength;

        rollValuesInRange(begin, end, 0, true, scrambledPassword);
        callback(end, fileLength - inscriptionSignatureLength);
    }

    return true;

}

bool File::decrypt(const std::string& password, const std::function<void(long int currentBytesUpdated, long int totalFilesize)>& callback) {

    if (!_isEncrypted) {
        return false;
    }

    if (!checkPassword(password)) {
        return false;
    }

    std::string scrambledPassword = scramblePassword(password);
    

    // The file is valid, encrypted, and the correct password was given. Now decrypt.

    // --- roll each byte back using the correct password

    int begin = 0;
    int end = 0;

    while (end != fileLength) {

        begin = end;
        end = end + bufferingSize;
        if (end > fileLength)
            end = fileLength;

        rollValuesInRange(begin, end, 0, false, scrambledPassword);
        callback(end, fileLength);
    }

    // remove the header from the file
    truncateFile(inscriptionSignatureLength + fileValidatorLength);

    return true;
}

void File::truncateFile(int bytes) {

    stream.close();
    std::filesystem::resize_file(filepath, fileLength - bytes);
    stream = std::fstream(filepath, std::ios::in | std::ios::out | std::ios::binary);

}


bool File::checkPassword(const std::string& password) {

    std::string scrambledPassword = scramblePassword(password);

    for (int i = 0; i < fileValidatorLength - 1; i++) {
        if (rollValue(header.fileValidator[i], false, fileLength - fileValidatorLength - inscriptionSignatureLength + i, scrambledPassword) != FileHeader::correctValidation[i]) {
            return false;
        }
    }

    return true;
}


char File::rollValue(char original, bool forward, long int itteration, const std::string& password) {

    //c_srand(itteration);
    long int delta = password[itteration % (password.size())] * 9342;

    delta += itteration;

    delta += itteration * delta;
    delta += itteration % 4700;
    delta += itteration % 640;
    //delta += password[(itteration + c_rand()) % (password.size())]; // would be nice, but is pretty expensive

    delta += itteration / 2;
    delta += itteration / 3;
    delta += itteration / 5;
    delta += itteration / 7;
    delta += itteration / 11;
    delta += itteration / 20;
    delta += itteration / 34;
    delta += itteration / 50;
    delta += itteration / 145;
    delta += itteration / 1110;
    delta += itteration / 2301;
    delta += itteration / 5024;
    delta += itteration / 45024;
    delta += itteration / 1204324;


    if (!forward) delta *= -1;
    return original + (char)delta;
}


void File::rollValuesInRange(long int begin, long int end, int itterationOffset, bool forward, const std::string& password) {

    static char buffer[bufferingSize];
    stream.seekg(begin, std::ios::beg);
    stream.read(buffer, end - begin);

    for (int i = 0; i < end - begin; i++) {
        buffer[i] = rollValue(buffer[i], forward, i + begin + itterationOffset, password);        
    }

    stream.seekp(begin, std::ios::beg);
    stream.write(buffer, end - begin);

}


std::string File::scramblePassword(const std::string& password) {

    c_srand(password[0]);
    char scramble[1000];
    for (int i = 0; i < 1000; i++) {
        scramble[i] = password[i % password.size()];
        scramble[i] += c_rand();
    }

    c_srand((password[0] + password[1]) * 3);
    char x;
    int swapI;
    int swapJ;
    for (int i = 0; i < 10000; i++) {
        swapI = c_rand() % 1000;
        swapJ = c_rand() % 1000;

        x = scramble[swapI];
        scramble[swapI] = scramble[swapJ];
        scramble[swapJ] = x;

        scramble[i % 1000] += (i % 1000000);
    }

    {
        int i = 0;
        while (i < 300)
        {
            scramble[i] += i % 10;
            scramble[i] -= 10;

            i++;
        }

        while (i < 350)
        {
            scramble[i] += i % 87;
            scramble[i] += password.size() * 7;

            i++;
        }

        while (i < 600)
        {
            scramble[i] += (char)(scramble[i] % 100);

            i++;
        }

    }

    for (int i = 0; i < 1000; i += 7) {
        scramble[i] = scramble[(i * 5) % 1000];
    }

    for (int i = 0; i < 10000; i++) {
        subScramble(c_rand() % 1000, c_rand() % 1000, scramble, password);
    }

    for (int i = 0; i < 1000; i++) {
        if (scramble[i] == '\0')
            scramble[i] = '?';
    }
    
    scramble[999] = '\0';
    return scramble;
}


void File::subScramble(int a, int b, char* scramble, const std::string& password) {

    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }

    for (int i = 0; i < password.size(); i++) {

        c_srand(password[i]);

        for (int j = a; j < b; j++) {
            scramble[j] += c_rand() * i;
        }
    }

}

