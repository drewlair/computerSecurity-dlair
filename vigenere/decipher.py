

def decipher():

    key = input("Enter the key: ")

    with open("cipher.txt", "r+") as fp:
        text = fp.readline()
    text = text.rstrip()
    keylen = len(key)
    plaintext = ""
    print(chr(ord('A') + ord('M')))
    for i in range(len(text)):
        offset = ord(text[i]) - ord(key[i % keylen])
        if offset < 0:
            plaintext += chr( ord('Z') + (offset+1) )
        else:
            plaintext += chr( ord('A') + offset )
    print("Decrypted Message: ", plaintext)

