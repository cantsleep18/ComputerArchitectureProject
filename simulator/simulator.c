/* LC-2K Instruction-level simulator */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8 /* number of machine registers */
#define MAXLINELENGTH 1000
#define REGMASK 7
#define OFFMASK 0x0000FFFF

#define OP_ADD  0
#define OP_NOR  1
#define OP_LW   2
#define OP_SW   3
#define OP_BEQ  4
#define OP_JALR 5
#define OP_HALT 6
#define OP_NOOP 7


typedef struct stateStruct {
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);
int convertNum(int);

void addOp(int, int, int, stateType*);
void norOp(int, int, int, stateType*);
void lwOp(int, int, int, stateType*);
void swOp(int, int, int, stateType*);
void beqOp(int, int, int, stateType*);
void jalrOp(int, int, stateType*);
void haltOp(stateType*, int);

int main(int argc, char *argv[]){
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;
    
    if (argc != 2) {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    
    if (filePtr == NULL) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }
    
    /* read in the entire machine-code file into memory */
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; state.numMemory++) {
        if (sscanf(line, "%d", state.mem+state.numMemory) != 1) {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }
    
    memset(state.reg, 0, (sizeof(int) *NUMREGS));
    state.pc = 0;

    int regA, regB, regDest, offset, opHex;
    int executeNum = 0;

    
    while(1){
        printState(&state);

        int binaryInst = state.mem[state.pc];

        opHex = binaryInst >> 22;
        regA = binaryInst >> 19;
        regA &= REGMASK;

        regB = binaryInst >> 16;
        regB &= REGMASK;
        regDest = binaryInst & REGMASK;

        offset = binaryInst;
        offset &= OFFMASK;

        switch (opHex)
        {
        case OP_ADD:
            addOp(regA, regB, regDest, &state);
            break;
        case OP_NOR:
            norOp(regA, regB, regDest, &state);
            break;
        case OP_LW:
            lwOp(regA, regB, offset, &state);
            break;
        case OP_SW:
            swOp(regA, regB, offset, &state);
            break;
        case OP_BEQ:
            beqOp(regA, regB, offset, &state);
            break;
        case OP_JALR:
            jalrOp(regA, regB, &state);
            break;
        case OP_HALT:
            haltOp(&state, ++executeNum);
        case OP_NOOP:
            break;
        default:
            printf("ERROR: OPCODE INVALID\n");
            exit(1);
        }

        executeNum++;
        state.pc++;

    }
}

    void printState(stateType *statePtr){ 
        int i;
        
        printf("\n@@@\nstate:\n");
        printf("\tpc %d\n", statePtr->pc);
        printf("\tmemory:\n");
        
        for (i=0; i<statePtr->numMemory; i++) {
            printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
        }
        
        printf("\tregisters:\n");
        
        for (i=0; i<NUMREGS; i++) {
            printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
        }
        printf("end state\n");
    }
 
    int convertNum(int num){
    /* convert a 16-bit number into a 32-bit Linux integer */
        if (num & (1<<15) ) {
            num -= (1<<16);
        }
    return(num);
    }

    void addOp(int regA, int regB, int regDest, stateType * state){
        state->reg[regDest] = state->reg[regA] + state->reg[regB]; 
    }

    void norOp(int regA, int regB, int regDest, stateType* state){
        state->reg[regDest] = ~(state->reg[regA] | state->reg[regB]);
    }

    void lwOp(int regA, int regB, int offset, stateType* state){
        state->reg[regB] = state->mem[convertNum(state->reg[regA] + offset)];
    }

    void swOp(int regA, int regB, int offset, stateType* state){
        state->mem[convertNum(state->reg[regA] + offset)] = state->reg[regB];
    }

    void beqOp(int regA, int regB, int offset, stateType*state){
        if(state->reg[regA] == state->reg[regB])
            state->pc += convertNum(offset);
    }

    void jalrOp(int regA, int regB, stateType* state){
        state->reg[regB] = state->pc + 1;
        state->pc = state->reg[regA]-1;
    }

    void haltOp(stateType * state, int executeNum){
        printf("machine halted\n");
        printf("total of %d instructions executed\n", executeNum);
        printf("final state of machine:");
        printState(state);
        exit(1);
    }