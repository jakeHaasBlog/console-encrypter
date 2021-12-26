Welcome to the simple file encryptor!

This encryptor can be used to lock single files of any type behind a password. While the file is locked, it will be completely unaccessible until this program is used to unlock it. unlike previous itterations of this program, entering an invalid password is no big deal. You will be able to simply try again with no loss of data and no limit to the number of attempts allowed. Note that there is absolutely no way to recover a lost/forgotten password.


User manual:

This program can be used through the command line. When application is executed, it can be given one argument for the filepath of the file you wish to encrypt or decrypt or no arguments to be prompted through selecting a file manually.

If the file that was chosen has already been encrypted: 
    You will be prompted to enter the password for the file. If an incorrect password is given, the program will prompt you that the password was incorrect and ask you to enter another password. Once the correct password is given, you will be prompted. The program will then present a loading bar. The program must not be closed until the file is fully decrypted, this should only take a few seconds at most. If you have forgotten the password for the given file, then theoretically it will be gone forever and should be deleted. There is no password recovery system provided.

If the file that was chosen has not been encrypted: 
    You will be prompted to enter a password to lock the chosen file behind. Once you have chosen and entered a password, you will be prompted to re-enter it to reduce the possibility of entering a typo. The program will then present a loading bar. The program must not be closed until the file is fully encrypted, this should only take a few seconds at most. Make sure not to lose the password, there is no password recovery system.

Note that the name of the file does not matter at all to this program. If the filename changes after the file is encrypted, it will still be able to be un-encrypted. It is reccomended to change the name of a file after it is encrypted to make it less obvious what is contained inside of it. 

Known bugs:
- A file that is encrypted on Windows cannot be decrypted on Unix
- A file that is encrypted on Unix cannot be decrypted on Windows

Features that may be added in the future!
- Write a message to yourself when locking a file, then be able to read it before unlocking the file.
- Ability to encrypt an entire folder recursively
- Compressing the encrypted file to save storage space
- Option to open the file explorer to select a file
- Ability to lock multiple files inside of one big file and extract them with the password
- Use a real encryption standard of some kind. Not just my own invention.