#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>

struct LabelHolder {
    char *labelName;
    int address;
    int lineNum;
} LabelHolder;


int main(int argc, char const *argv[])
{
    // parse input into categories (code, data, comments)
    // read line by line (getline)
    // separate each line using switch case to determine what kind of line
    // direct line to handler once you decide what line
    // subsequent lines will be part of data for .code/.data
    // ignore comments, jump to next
    // interpret assembler into byte code

    // offset pointer to find filename
    if (argc < 2)
    {
        printf("Invalid tinker filepath\n");
        exit(1);
    }

    char *filename = argv[1]; // star before to dereference pointer
    // printf("%s\n",filename);

    FILE *input = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (input == NULL)
    {
        printf("Invalid tinker filepath\n");
        exit(1);
    }


    char *pattern[41];

    // for : label
    pattern[40] = "\tld r([0-9]|1[0-9]|2[0-9]|3[0]), :([a-zA-Z0-9_]){0,256}$\n";

    // for : label
    pattern[39] = "^:([a-zA-Z0-9_]){0,256}";

    //for .code
    pattern[38] = "^.code\0";

    // for .data
    pattern[37] = "^.data\0";

    // for ;
    pattern[36] = "^;\0";

    // ARITHMETIC INSTRUCTIONS
    // for add
    pattern[0] = "^\tadd r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";
    

    // for addi
    pattern[1] = "^\taddi r([0-9]|1[0-9]|2[0-9]|3[0]), ([0-9]$|[0-9][0-9]$|[0-9][0-9][0-9]$|[0-3][0-9][0-9][0-9]$|[4][0][0-9][0-5]$)\n";

    // for sub
    pattern[2] = "^\tsub r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for subi
    pattern[3] = "^\tsubi r([0-9]|1[0-9]|2[0-9]|3[0]), ([0-9]$|[0-9][0-9]$|[0-9][0-9][0-9]$|[0-3][0-9][0-9][0-9]$|[4][0][0-9][0-5]$)\n";

    // for mul
    pattern[4] = "^\tmul r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    //for div
    pattern[5] = "^\tdiv r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    
    // LOGIC INSTRUCTIONS
    // for and
    pattern[6] = "^\tand r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for or
    pattern[7] = "^\tor r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for xor
    pattern[8] = "^\txor r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for not
    pattern[9] = "^\tnot r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]\n)";

    // for shftr
    pattern[10] = "^\tshftr r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    //for shftri
    pattern[11] = "^\tshftri r([0-9]|1[0-9]|2[0-9]|3[0]), ([0-9]$|[0-9][0-9]$|[0-9][0-9][0-9]$|[0-3][0-9][0-9][0-9]$|[4][0][0-9][0-5]$)\n";

    // for shftl
    pattern[12] = "^\tshftl r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for shiftli
    pattern[13] = "^\tshftli r([0-9]|1[0-9]|2[0-9]|3[0]), ([0-9]$|[0-9][0-9]$|[0-9][0-9][0-9]$|[0-3][0-9][0-9][0-9]$|[4][0][0-9][0-5]$)\n";

    //CONTROL INSTRUCTIONS
    // for br
    pattern[14] = "^\tbr r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for brr
    pattern[15] = "^\tbrr r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // brr L
    pattern[16] = "^\tbrr ([0-9]$|[0-9][0-9]$|[0-9][0-9][0-9]$|[0-3][0-9][0-9][0-9]$|[4][0][0-9][0-5]$)\n";

    // for brnz
    pattern[17] = "^\tbrnz r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for call
    pattern[18] = "^\tcall r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for return
    pattern[19] = "^\treturn\n";

    // for brgt
    pattern[20] = "^\tbrgt r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    //DATA MOVEMENT INSTRUCTIONS
    // for mov rd, (rs)(L)
    pattern[21] = "^\tmov r([0-9|1[0-9]|2[0-9]|3[0]), \\(r([0-9|1[0-9]|2[0-9]|3[0])\\)\\(([0-9_-]+)\\)\n";
     //"^\tmov r([0-9|1[0-9]|2[0-9]|3[0]), \(r([0-9|1[0-9]|2[0-9]|3[0])\)\(([0-9_-]+)\)\n";

    // for mov rd, rs
    pattern[22] = "^\tmov r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for mov rd L
    pattern[23] = "^\tmov r([0-9]|1[0-9]|2[0-9]|3[0]), ([0-9_-]+)\n";

    // for mov (rd)(l), rs
    pattern[24] = "^\tmov \\(r([0-9]|1[0-9]|2[0-9]|3[0])\\)\\(([0-9_-]+)\\), r([0-9]|1[0-9]|2[0-9]|3[0])$\n";
    //FIX: THIS DOESNT WORK FOR L BC IT EXCEEDS 4095

    //FLOATING POINT INSTRUCTIONS
    // for addf
    pattern[25] = "^\taddf r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for subf
    pattern[26] = "^\tsubf r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for mulf
    pattern[27] = "^\tmulf r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for divf
    pattern[28] = "^\tdivf r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    //IO INSTRUCTIONS
    // for in
    pattern[29] =  "^\tin r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for out
    pattern[30] = "^\tout r([0-9]|1[0-9]|2[0-9]|3[0]), r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // HALT: for halt
    pattern[31] = "^\thalt\n";

    //USEFUL MACROS
    // for clr
    pattern[32] = "^\tclr r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for ld
    pattern[33] = "^\tld r([0-9]|1[0-9]|2[0-9]|3[0]), ([0-9]$|[0-9][0-9]$|[0-9][0-9][0-9]$|[0-3][0-9][0-9][0-9]$|[4][0][0-9][0-5]$)\n";

    // for push
    pattern[34] = "^\tpush r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    // for pop
    pattern[35] = "^\tpop r([0-9]|1[0-9]|2[0-9]|3[0])\n";

    regex_t r[41];

    for (size_t i = 0; i < 41; i++)
    {
        if (regcomp(&r[i], pattern[i], REG_EXTENDED | REG_NOSUB) != 0) {
            return 0;
        }
    }

    int lineCounter = 1;

    while ((read = getline(&line, &len, input)) != -1)
    {
        int i;
        char matched = 0;
        for (i = 0; i < 41; i++) {       
            int status;
            status = regexec(&r[i], line, (size_t)0, NULL, 0);
            if (status == 0) {
                matched = 1;
                break;
            }
        }

        //printf("%d\n", i);

        uint32_t instr = 0;
        uint32_t opcode = 0;
        uint32_t r_0 = 0;
        uint32_t r_1 = 0;
        uint32_t r_2 = 0;
        uint32_t L = 0;

        int firstn = 6;
        int secondn = 10;
        int thirdn = 14;

        int firstL = 7;
        int secondL = 10;

        //printf("%d\n", i);
        if (i < 36) {
            // this is opcode
            instr |= i << 27;
            
            switch (i)
            {
            case 0:
            // add (r_0 = r_1 + r_2)
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: add\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 1:
            // addi (r_0 = r_0 + L)
                if (line[firstL+1] != ',') {
                    r_0 = (line[firstL] - '0') * 10;
                    r_0 += (line[firstL+1] - '0');
                    secondL++;
                }
                else {
                    r_0 = line[firstL] - '0';
                }

                if (line[secondL+1] == '\n')
                {
                    // one digit
                    L = (line[secondL] - '0');
                } else if (line[secondL+2] == '\n') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                } else if (line[secondL+3] == '\n') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');
                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                }
                printf("opcode: addi\n");  
                printf("%d\n%d\n", r_0, L);            
                break;
            case 2:
            // sub r_0 = r_1 - r_2
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: sub\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);    
                break;
            case 3:
            // subi (r_0 = r_0 - L)
                if (line[firstL+1] != ',') {
                    r_0 = (line[firstL] - '0') * 10;
                    r_0 += (line[firstL+1] - '0');
                    secondL++;
                    printf("two r ");
                }
                else {
                    r_0 = line[firstL] - '0';
                    printf("one r ");
                }

                if (line[secondL+1] == '\n')
                {
                    // one digit
                    L = (line[secondL] - '0');
                    printf("one l ");
                } else if (line[secondL+2] == '\n') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                    printf("two l ");
                } else if (line[secondL+3] == '\n') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');
                    printf("three l ");
                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                    printf("four l ");
                }
                printf("opcode: subi\n");
                printf("%d\n%d\n", r_0, L);          
                break;
            case 4:
            // mul (r_0 = r_1 * r_2)
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: mul\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);   
                break;
            case 5:
            // div (r_0 = r_1 / r_2)
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: div\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 6:
            // and (r_0 = r_1 & r_2)
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: and\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 7:
            // or (r_0 = r_1 | r_2)
            firstn--;
            secondn--;
            thirdn--;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: or\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 8:
            // xor (r_0 = r_1 ^ r_2)
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: xor\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 9:
            // not (r_0 = !r_2)
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                printf("%c\n", line[secondn]);
                if (line[secondn+1] != '\n') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                }
                else {
                    r_1 = (line[secondn] - '0');
                }
                printf("opcode: not\n");
                printf("%d\n%d\n", r_0, r_1);
                break;
            case 10:
            // shftr (r_0 = r_1 >> r_)
                firstn += 2;
                secondn += 2;
                thirdn += 2;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: shftr\n");
                printf("%d\n%d\n", r_0, r_1);
                break;
            case 11:
            // shftri (r_0 = r_0 >> L)
                firstL+=2;
                secondL+=2;
                if (line[firstL+1] != ',') {
                    r_0 = (line[firstL] - '0') * 10;
                    r_0 += (line[firstL+1] - '0');
                    secondL++;
                }
                else {
                    r_0 = line[firstL] - '0';
                }

                if (line[secondL+1] == '\n')
                {
                    // one digit
                    L = (line[secondL] - '0');
                } else if (line[secondL+2] == '\n') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                } else if (line[secondL+3] == '\n') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');
                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                }
                printf("opcode: shftri\n");
                printf("%d\n%d\n", r_0, L);
                break;
            case 12:
            // shftl
                firstn+=2;
                secondn+=2;
                thirdn+=2;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: shftl\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);   
                break;
            case 13:
                // shftli
                firstL +=2;
                secondL +=2;
                if (line[firstL+1] != ',') {
                    r_0 = (line[firstL] - '0') * 10;
                    r_0 += (line[firstL+1] - '0');
                    secondL++;
                }
                else {
                    r_0 = line[firstL] - '0';
                }

                if (line[secondL+1] == '\n')
                {
                    // one digit
                    L = (line[secondL] - '0');
                } else if (line[secondL+2] == '\n') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                } else if (line[secondL+3] == '\n') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');
                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                }
                printf("opcode: shftli\n");
                printf("%d\n%d\n", r_0, L);   
                break;
            case 14:
                // br
                firstn--;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                printf("opcode: br\n");
                printf("%d\n", r_0);  
                break;
            case 15:
                // brr rd
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                printf("opcode: brr rd\n");
                printf("%d\n", r_0);  
                break;
            case 16:
            // brr L
                secondL = 5;
                if (line[secondL+1] == '\n')
                {
                    // one digit
                    L = (line[secondL] - '0');
                } else if (line[secondL+2] == '\n') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                } else if (line[secondL+3] == '\n') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');
                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                }
                printf("opcode: brr L\n");
                printf("%d\n", L); 
                break;
            case 17:
            // brnz
                firstn++;
                secondn++;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                if (line[secondn+1] != '\n') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                }
                else {
                    r_1 = (line[secondn] - '0');
                }
                printf("opcode: brnz\n");
                printf("0: %d\n 1: %d\n", r_0, r_1); 
                break;
            case 18:
            // call
                firstn++;
                secondn++;
                thirdn++;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: call\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 19:
            // return
                printf("opcode: return\n");
                break;
            case 20:
            // brgt
                firstn++;
                secondn++;
                thirdn++;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: brgt\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 21:
            // mov rd, (rs)(L)
                secondn++;
                secondL+=4;

                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ')') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[secondL+1] == ')')
                {
                    // one digit
                    L = (line[secondL] - '0');
                } else if (line[secondL+2] == ')') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                } else if (line[secondL+3] == ')') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');

                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                }
                printf("opcode: mov rd, (rs)(L)\n"); //regex matches
                printf("%d\n%d\n%d\n", r_0, r_1, L);
                break;
            case 22:
            // mov rd rs
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                if (line[secondn+1] != '\n') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                }
                else {
                    r_1 = (line[secondn] - '0');
                }
                printf("opcode: mov r r\n");
                printf("0: %d\n 1: %d\n", r_0, r_1); 
                break;
            case 23:
            // mov rd L
                printf("%s\n", line);
                firstL--;
                secondL--;
                if (line[firstL+1] != ',') {
                    r_0 = (line[firstL] - '0') * 10;
                    r_0 += (line[firstL+1] - '0');
                    secondL++;
                }
                else {
                    r_0 = line[firstL] - '0';
                }

                if (line[secondL+1] == '\n')
                {
                    // one digit
                    L = (line[secondL] - '0');
                } else if (line[secondL+2] == '\n') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                } else if (line[secondL+3] == '\n') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');
                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                }
                printf("opcode: mov rd L\n");  
                printf("%d\n%d\n", r_0, L);            
                break;
            case 24:
            // mov (rd)(L), rs
            // DO LATER
                firstn++;
                firstL+=3;
                secondn+=5;
                if (line[firstn+1] != ')') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    firstL++;
                    secondn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondL+1] == ')')
                {
                    // one digit
                    L = (line[secondL] - '0');
                } else if (line[secondL+2] == ')') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                    secondn++;
                } else if (line[secondL+3] == ')') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');
                    secondn+=2;
                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                    secondn+=3;
                }

                if (line[secondn+1] != '\n') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                }
                else {
                    r_1 = (line[secondn] - '0');
                }
                printf("opcode: mov (rd)(L), rs\n"); //regex matches
                printf("%d\n%d\n%d\n", r_0, L, r_1); 
                break;
            case 25:
            // addf
                firstn++;
                secondn++;
                thirdn++;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: addf\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 26:
            // subf
                firstn++;
                secondn++;
                thirdn++;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: subf\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 27:
            // mulf
                firstn++;
                secondn++;
                thirdn++;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: mulf\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 28:
            // divf
                firstn++;
                secondn++;
                thirdn++;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                    thirdn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }

                if (line[secondn+1] != ',') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                    thirdn++;
                }
                else {
                    r_1 = (line[secondn] - '0');
                }

                if (line[thirdn+1] != '\n') {
                    r_2 = (line[thirdn] - '0') * 10;
                    r_2 += (line[thirdn+1] - '0');
                }

                else {
                    r_2 = (line[thirdn] - '0');
                }
                printf("opcode: divf\n");
                printf("%d\n%d\n%d\n", r_0, r_1, r_2);
                break;
            case 29:
            // in
                firstn--;
                secondn--;
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                if (line[secondn+1] != '\n') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                }
                else {
                    r_1 = (line[secondn] - '0');
                }
                printf("opcode: in\n");
                printf("%d\n%d\n", r_0, r_1);
                break;
            case 30:
            // out
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                    secondn++;
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                if (line[secondn+1] != '\n') {
                    r_1 = (line[secondn] - '0') * 10;
                    r_1 += (line[secondn+1] - '0');
                }
                else {
                    r_1 = (line[secondn] - '0');
                }
                printf("opcode: out\n");
                printf("%d\n%d\n", r_0, r_1);
                break;
            case 31:
            // halt
                break;
            case 32:
            // clr
                if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                printf("opcode: clr rd\n");
                printf("%d\n", r_0);
                break;
            case 33:
            // ld
                firstL-=2;
                secondL-=2;
                if (line[firstL+1] != ',') {
                    r_0 = (line[firstL] - '0') * 10;
                    r_0 += (line[firstL+1] - '0');
                    secondL++;
                }
                else {
                    r_0 = line[firstL] - '0';
                }

                if (line[secondL+1] == '\n')
                {
                    // one digit
                    L = (line[secondL] - '0');
                } else if (line[secondL+2] == '\n') {
                    // two digits
                    L = (line[secondL] - '0') * 10;
                    L += (line[secondL+1] - '0');
                } else if (line[secondL+3] == '\n') {
                    // three digits
                    L = (line[secondL] - '0') * 100;
                    L += (line[secondL+1] - '0') * 10;
                    L += (line[secondL+2] - '0');
                } else {
                    // four digits
                    L = (line[secondL] - '0') * 1000;
                    L += (line[secondL+1] - '0') * 100;
                    L += (line[secondL+2] - '0') * 10;
                    L += (line[secondL+3] - '0');
                }
                printf("opcode: ld\n");  
                printf("%d\n%d\n", r_0, L);            
                break;
            case 34:
                //push
                firstn++;
                 if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                printf("opcode: push\n");
                printf("%d\n", r_0);
                break;
                break;
            case 35:
                //pop
                 if (line[firstn+1] != ',') {
                    r_0 = (line[firstn] - '0') * 10;
                    r_0 += (line[firstn+1] - '0');
                }
                else {
                    r_0 = line[firstn] - '0';
                }
                printf("opcode: pop\n");
                printf("%d\n", r_0);
                break;
            default:
                break;
            }            
        }
        else if (i == 36) {
            // ; comment
            printf("i: %d\n", i);
        }
        else if (i == 37) {
            // .data
            printf("i: %d\n", i);
        }
        else if (i == 38) {
            // .code
            printf("i: %d\n", i);
        }
        else if (i == 39) {
            // labels on their own
            printf("i: %d\n", i);
        }
        else if (i == 40 && matched) {
            // ld with label
            // find index of label and store that info in array
            // compare array indices as necessary to each other
        }
        else {
            printf("Error on line %d\n", lineCounter);
            exit(1);
        }
        //uint32_t instr = 0;

        instr |= L;
        instr |= r_0 << 12;
        instr |= r_1 << 17;
        instr |= r_2 << 22;
        instr |= opcode << 27;

        char *output = strdup(filename);
        char *dot = strrchr(output, '.');
        if (dot) {
            *dot = '\0';
        }
        strcat(output, ".tko");
        FILE *outputFile = fopen(output, "wb");

        if (output == NULL) {
            printf("Error: Unable to open output file\n");
            fclose(input);
            return EXIT_FAILURE;
        }

        fwrite((const void *) &instr, sizeof(instr), 1, outputFile);
        fclose(outputFile);
        //printf("Line read: %s on line number %d\n", line, lineCounter);
        lineCounter++;
    }

    return 0;
}
