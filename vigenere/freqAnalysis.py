import matplotlib.pyplot as plt
import numpy as np

generalFreqs = [3,2,2,2,3,2,2,3,3,2,2,2,2,3,3,2,1,3,3,3,2,1,1,1,1,1]

def getIC(freqs, N):
    ic = 0
    for i in range(26):
        ic += freqs[i]*(freqs[i]-1)
    return ic * (1/(N*(N-1)))



def analyze():

    with open("cipher.txt") as fp:
        text = fp.readline()
    text = text.rstrip()


    keyLen = int(input("What key length would you like to try? "))

    alphabets = []
    for i in range(keyLen):
        a = ""
        for j in range((len(text)-1-i)//keyLen+1):
            a += text[i+j*keyLen]
        alphabets.append(a)
    print("Alphabets and IC: ")
    plt.plot(np.linspace(1, 26, 26), generalFreqs)
    
    for i, a in enumerate(alphabets):

        freqs = [0]*26
        for letter in a:
            freqs[ord(letter) - ord('A')] += 1
        print(a, "->", getIC(freqs, len(a)))
        plt.figure(figsize=(10, 6))
        plt.plot(np.linspace(1, 26, 26), generalFreqs, np.linspace(1, 26, 26), freqs)
        plt.title("GeneralFreqs vs Alphabet")
        plt.xlabel("Letters [1-26]")
        plt.ylabel("Letter Counts")
        plt.xticks(np.arange(1, 26, step=1))
        plt.legend(["General", "Alphabet"])
        
        plt.show()




    pass





