//circular shift: y = (x << shift) | (x >> (sizeof(x)*CHAR_BIT - shift));
#include <stdio.h>
#include <stdlib.h>

typedef struct subKey{
    unsigned long key : 48;
}subKey;

typedef struct Key{
    unsigned long shortKey : 56;
    unsigned int leftKey : 28;
    unsigned int rightKey : 28;
    subKey* subKeys;
}Key;



int permutation1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
int permutation2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
int messagePermute[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
int rightExpandPermute[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
int shiftTable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int funcTable1[4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7}, {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8}, {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0}, {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};
int funcTable2[4][16] = {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10}, {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5}, {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15}, {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}};
int funcTable3[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8}, {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1}, {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7}, {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};
int funcTable4[4][16] = {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15}, {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9}, {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4}, {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}};
int funcTable5[4][16] = {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9}, {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6}, {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14}, {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}};
int funcTable6[4][16] = {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11}, {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8}, {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6}, {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}};
int funcTable7[4][16] = {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1}, {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6}, {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2}, {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}};
int funcTable8[4][16] = {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7}, {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2}, {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8}, {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
int funcPermute[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
int finalPermute[64] =   {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};


int main(int argc, char* argv[]){
    puts("");

    FILE* fp = fopen("desCipherAndKey.txt", "r");
    char binCipher[66];
    char binKey[66];
    fgets(binCipher, 67, fp);
    binCipher[64] = '\0';
    binCipher[65] = '\0';
    fgets(binKey, 66, fp);
    binKey[64] = '\0';

    unsigned long cipher = 0;
    unsigned long mult = 1;
    for (int i = 63; i > -1; i--){
        if (binCipher[i] == '1'){
            cipher += mult;
        }
        mult *= 2;

    }
    unsigned long key = strtol(binKey, NULL, 2);
    printf("cipher: %lx\nkey: %lx\n\n", cipher, key);
    
    Key* k = (Key*)malloc(sizeof(Key));
    k->shortKey = 0;

    for (int i = 0; i < 56; i++){
        k->shortKey = k->shortKey | ( ( ( (key >> (64 - permutation1[i])) & 0x01 ) ) << (55 - i) );
    }
   

    k->leftKey = k->shortKey >> 28;
    k->rightKey = k->shortKey & 0xFFFFFFF;

    

    k->subKeys = (subKey*)malloc(sizeof(subKey) * 16);

    for (int i = 0; i < 16; i++){
        k->subKeys[i].key = 0;
    }


    for (int keyNum = 0; keyNum < 16; keyNum++){

        if (shiftTable[keyNum] == 1){
            k->leftKey = (k->leftKey << 1) | (k->leftKey >> 27);
            k->rightKey = (k->rightKey << 1) | (k->rightKey >> 27);
        }else{
            k->leftKey = (k->leftKey << 2) | (k->leftKey >> 26);
            k->rightKey = (k->rightKey << 2) | (k->rightKey >> 26);
        }
        
        k->shortKey = 0;
        k->shortKey = k->leftKey;
        k->shortKey = (k->shortKey<<28) | k->rightKey;
        
        for (int i = 0; i < 48; i++){
            k->subKeys[keyNum].key = k->subKeys[keyNum].key | ( ( ( (k->shortKey >> (56 - permutation2[i])) & 0x01 ) ) << (47 - i) );   
        }

    }
    


    unsigned long msg = 0;
    for (int i = 0; i < 64; i++){
        msg = msg | ( ( ( (cipher >> (64 - messagePermute[i])) & 0x01 ) ) << (63 - i) );
    }
    

    unsigned int msgLeft = msg >> 32;
    unsigned int msgRight = msg & 0xFFFFFFFF;

    for (int subKeyNum = 15; subKeyNum > -1; subKeyNum--){
        unsigned int oMsgRight = msgRight;

        
        
        subKey rightExpanded;
        rightExpanded.key = 0;
        for (int j = 0; j < 48; j++){
            long temp = 0;
            temp = (msgRight >> (32 - rightExpandPermute[j])) & 0x01;
            temp = temp << (47 - j);
            rightExpanded.key = rightExpanded.key | temp;
        }

        
        rightExpanded.key = rightExpanded.key ^ k->subKeys[subKeyNum].key;
        
        msgRight = 0;
        int r, c;
        for (int table = 0; table < 16; table++){
            r = ((rightExpanded.key >> (46 - table*6)) & 0x02) | ((rightExpanded.key >> (42 - table*6)) & 0x01);
        
            c = (rightExpanded.key >> (43 - table*6)) & 0x0f;
            switch(table){
                case 0:
        
                    msgRight = msgRight | funcTable1[r][c] << (28 - table*4);
                        
                    
                    break;

                case 1:
        
                    msgRight = msgRight | funcTable2[r][c] << (28 - table*4);
                    
                    
                    break;
                case 2:

                    msgRight = msgRight | funcTable3[r][c] << (28 - table*4);
                        
                    break;
                case 3:
        
                    msgRight = msgRight | funcTable4[r][c] << (28 - table*4);
                    break;
                case 4:

                    msgRight = msgRight | funcTable5[r][c] << (28 - table*4);
                        
                    break;
                case 5:

                    msgRight = msgRight | funcTable6[r][c] << (28 - table*4);
                        
                    break;
                case 6:

                    msgRight = msgRight | funcTable7[r][c] << (28 - table*4);
                        
                    break;
                case 7:

                    msgRight = msgRight | funcTable8[r][c] << (28 - table*4);
                        
                    break;
                default:
                    
                    break;
            }
            
        }
       
        unsigned int tempRight = 0;
        for(int i = 0; i < 32; i++){
            tempRight = tempRight | ( ( ( (msgRight >> (32 - funcPermute[i])) & 0x01 ) ) << (31 - i) );
        }
        msgRight = tempRight;
        printf("f output: %x\n", msgRight);
        

        msgRight = msgLeft ^ msgRight;
        msgLeft = oMsgRight;

        printf("Round %d: left: %x right: %x\n\n", (16-subKeyNum), msgLeft, msgRight);
        

    }
    

    unsigned long fullCipher = msgRight;
    fullCipher = (fullCipher << 32) | msgLeft;
    unsigned long encryptedMsg = 0;

    for (int i = 0; i < 64; i++){
        encryptedMsg = encryptedMsg | ( ( ( (fullCipher >> (64 - finalPermute[i])) & 0x01 ) ) << (63 - i) );
    }
    printf("Decrypted Message in hex: %lx\n", encryptedMsg);
    printf("In ascii: ");
    for (int i = 0; i < 8; i++){
        printf("%c", (char)(encryptedMsg >> (56 - 8*i)));
    }
    printf("\n\n");
    
   
    return 0;
}




