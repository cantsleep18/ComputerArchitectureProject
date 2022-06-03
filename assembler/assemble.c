/* Assembler code fragment for LC-2K */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000
#define OP_ADD  0x00000000
#define OP_NOR  0x00400000
#define OP_LW   0x00800000
#define OP_SW   0x00C00000
#define OP_BEQ  0x01000000
#define OP_JALR 0x01400000
#define OP_HALT 0x01800000
#define OP_NOOP 0x01C00000

char labelList [65536][7];
int lineNum = 0;

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);
int labelCompare(char *, int);
void labelCalculation(FILE *, FILE *);
void machineCalculation(FILE *, FILE *);

int main(int argc, char *argv[]){
     char *inFileString, *outFileString;
     FILE *inFilePtr, *outFilePtr;
     
    if (argc != 3) {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",argv[0]);
        exit(1);
    }

    inFileString = argv[1];
    outFileString = argv[2];
    inFilePtr = fopen(inFileString, "r");
    
    if (inFilePtr == NULL) {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }

    outFilePtr = fopen(outFileString, "w");
    
    if (outFilePtr == NULL) {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }

    labelCalculation(inFilePtr, outFilePtr);

    rewind(inFilePtr);


    // label test
    // for(int i =0;i<lineNum; i++){
    //     printf("%s %d\n", labelList[i], i);
    // }

    machineCalculation(inFilePtr, outFilePtr);
    
    return(0);
}

    /*
    * Read and parse a line of the assembly-language file. Fields are returned
    * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
    * allocated to them).
    *
    * Return values:
    * 0 if reached end of file
    * 1 if all went well
    *
    * exit(1) if line is too long.
    */
    int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0, char *arg1, char *arg2){ 
        char line[MAXLINELENGTH];
        char *ptr = line;
        /* delete prior values */
        label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';
        /* read the line from the assembly-language file */
        
        if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
            /* reached end of file */
            return(0);
        }

        /* check for line too long (by looking for a \n) */
        if (strchr(line, '\n') == NULL) {
            /* line too long  */
            printf("error: line too long\n");
            exit(1);
        }
        /* is there a label? */
        ptr = line;
        if (sscanf(ptr, "%[^\t\n\r ]", label)) {
            /* successfully read label; advance pointer over the label */
            ptr += strlen(label);
        }
        /*
        * Parse the rest of the line. Would be nice to have real regular
        * expressions, but scanf will suffice.
        */
        sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",opcode, arg0, arg1, arg2);
        return(1);
    }
    
    int isNumber(char *string){
        /* return 1 if string is a number */
        int i;
        
        return( (sscanf(string, "%d", &i)) == 1);
    }
    
    int labelCompare(char *label, int lineNum){
        for(int i = 0 ;i < lineNum;i++){
            if(!strcmp(labelList[i], label)){
                return i;
            }
        }
        return -1;
    }

    // Check the location of label and save it to array
    void labelCalculation(FILE * inFilePtr, FILE * outFilePtr){
        char trash[MAXLINELENGTH];
        char label[MAXLINELENGTH];
        
        while (1)
        {   
            // Don't need other values as parmeter. 
            if(!readAndParse(inFilePtr, label, trash, trash, trash, trash))
                break;

            // If no label -> line Count +1
            if(!strcmp(label, "")){
                lineNum++;
                continue;
            }
            
            // Check LABEL LENGTH
            if(strlen(label) > 6){
                printf("ERROR: LABEL LENGTH more than 6\n");
                exit(1);
            }

            // Check First Letter is Number
            if ((label[0] >= 'a' && label[0] <= 'z') || (label[0] >= 'A' && label[0] <= 'Z')){
            }else{
                printf("ERROR: First Letter is Number\n");
                exit(1);
            }

            // Check Same Label
            if(labelCompare(label, lineNum) != -1){
                    printf("ERROR: Same Label Exists\n");
                    exit(1);
            }
            strcpy(labelList[lineNum],label);
            lineNum++;
        }
    }
    
    // assembly to machine code
    void machineCalculation(FILE * inFilePtr, FILE * outFilePtr){
        char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
        int lineCount = 0;

        while (1)
        {      
            if(!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)){                
                break;
            }
                

            int register1 = 0;
            int register2 = 0;
            int offset = 0;
            int opHex = 0;
            int result = 0;
            
            // R-Type Instruction
            if(!strcmp(opcode, "add") || !strcmp(opcode,"nor")){
                if(strlen(arg0)==0 || strlen(arg1) == 0 || strlen(arg2) == 0){
                    printf("ERROR: NEED MORE ARG\n");
                    exit(1);
                }

                if(!(isNumber(arg0) && isNumber(arg1) && isNumber(arg2))){
                    printf("ERROR: ARG IS NOT NUM\n");
                    exit(1);
                }
                
                if(!strcmp(opcode, "add"))
                    opHex = OP_ADD;
                else
                    opHex = OP_NOR;

                register1 = atoi(arg0);
                register1 <<= 19;

                register2 = atoi(arg1);
                register2 <<= 16;

                offset = atoi(arg2);

                result = register1 | register2 | offset;
            }

            else if(!strcmp(opcode, "lw") || !strcmp(opcode, "sw") || !strcmp(opcode, "beq")){
                if(strlen(arg0)==0 || strlen(arg1) == 0 || strlen(arg2) == 0){
                    printf("ERROR: NEED MORE ARG\n");
                    exit(1);
                }
                if(!(isNumber(arg0) && isNumber(arg1))){
                    printf("ERROR: ARG IS NOT NUM\n");
                    exit(1);
                }
                
                if(!strcmp(opcode, "lw"))
                    opHex = OP_LW;
                else if(!strcmp(opcode, "sw"))
                    opHex = OP_SW;
                else if(!strcmp(opcode, "beq")){
                    opHex = OP_BEQ;
                }

                // To check whether offset is num
                if(isNumber(arg2)){
                    offset = atoi(arg2);
                }else{
                    offset = labelCompare(arg2, lineNum);
                    if(offset==-1){
                        printf("ERROR: UNAVAILABLE LABEL\n");
                        exit(1);
                    }  
                    if(opHex == OP_BEQ){
                        offset -= (lineCount+1);
                    }
                }

                // offset range
                if(offset < -32768 || offset > 32767){
                    printf("ERROR: OFFSET OUT OF RANGE\n");
                    exit(1);
                }
                
                // masking offset to get last 16bits
                if(opHex == OP_BEQ){
                    offset &= 0x0000FFFF;
                }

                register1 = atoi(arg0);
                register1 <<= 19;
                
                register2 = atoi(arg1);
                register2 <<= 16;

                result = register1 | register2 | offset;
            }

            // J-Type Instruction
            else if(!strcmp(opcode , "jalr")){
                if(strlen(arg0)==0 || strlen(arg1) == 0){
                    printf("ERROR: NEED MORE ARG\n");
                    exit(1);
                }

                if(!(isNumber(arg0) && isNumber(arg1))){
                    printf("ERROR: ARG IS NOT NUM\n");
                    exit(1);
                }


                register1 = atoi(arg0);
                register1 <<= 19;

                register2 = atoi(arg1);
                register2 <<= 16;
                
                opHex = OP_JALR;

                result = register1 | register2;   
            }

            // O-Type Instruction
            else if(!strcmp(opcode , "halt"))
                opHex = OP_HALT;
            else if(!strcmp(opcode, "noop")){
                opHex = OP_NOOP;
            }

            //.Fill
            else if(!strcmp(opcode, ".fill")){
                if(strlen(arg0) == 0){
                    printf("ERROR: NEED MORE ARG\n");
                    exit(1);
                }

                if(isNumber(arg0))
                    result = atoi(arg0);
                else{
                    result = labelCompare(arg0, lineNum);
                    if(result == -1){
                        printf("ERROR: UNAVAILABLE LABEL\n");
                        exit(1);
                    }
                }
            }
            
            else{
                printf("ERROR: NO SUCH OPCODE\n");
                exit(1);
            }

            result = result | opHex;
            fprintf(outFilePtr, "%d\n", result);
            lineCount++;
        }

        exit(0);
    }
