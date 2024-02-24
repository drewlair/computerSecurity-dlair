from collections import defaultdict

from heapq import heappush, heappop
from freqAnalysis import analyze
from decipher import decipher
class Node:
    def __init__(self):
        
        self.branches = {}



def analyzeTrie(text):

    root = Node()

    prefix = defaultdict(list)
    
    for i in range(len(text)):
        curr = root
        
        
        for j in range(i, len(text)):
            letter = text[j]
            
            if letter not in curr.branches:
                curr.branches[letter] = Node()
                if (j-i) > 1:
                    
                    prefix[text[i:j]].append(i)
                
                
            
            curr = curr.branches[letter]
        
    return root, prefix



def getFactors(a):
    res = []
    for i in range(2, a//2+1):
        if a % i == 0:
            res.append(i)

    return res



    pass

def main():

    with open("cipher.txt", "r+") as fp:
        text = fp.readline()
    text = text.rstrip()

    trie, prefixes = analyzeTrie(text)
    for prefix in prefixes.copy():
        if len(prefixes[prefix]) == 1:
            del prefixes[prefix]

    factors = {}
    for prefix, indeces in prefixes.items():
        currFactors = set()

        for i in range(len(indeces)-1):

            for j in range(i+1, len(indeces)):
                f = getFactors(indeces[j] - indeces[i])

                for fact in f:
                    currFactors.add(fact)

                currFactors.add(indeces[j] - indeces[i])

        factors[prefix] = list(currFactors)
    
    for prefix, factorlist in factors.items():
        print(prefix, factorlist)
    

    counts = [0] * len(text)
    for factorlist in factors.values():

        for f in factorlist:
            counts[f-1] += 1

    heap = []
    for i, count in enumerate(counts):

        if count > 0 and (not heap or heap[0][0] < count):
            heappush(heap, (count, i+1))

            if len(heap) > 3:
                heappop(heap)

    print("Best factor frequencies (frequency, factor): ", heap)

    analyze()

    decipher()


    



    pass









if __name__ == "__main__":
    main()

