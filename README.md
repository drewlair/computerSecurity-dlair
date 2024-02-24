# repo: computerSecurity-dlair

## Current Contents:
### Vigenere Cipher Decrypter
### DES Cipher Encrypt/Decrypter

#### Vigenere
- First, go into the 'vigenere' directory and add your cipher into 'cipher.txt'
- Run 'python3 vigenere.py'
- The program will output the most frequent factors in the cipher, choose one to analyze the cipher with
- Next, the program will show you a series of IC's and charts to help analyze the shift required at each character in the key
- Finally, input your guessed key and the program will decipher the ciphertext and output the resulting plaintext

### DES
- First, go into the 'des' directory and write the cipher and the key (in binary) in that order separeted by a newline and ending with a newline
- Run 'gcc des.c' and './a.out'
- The program will show the resulting decrytped cipher
