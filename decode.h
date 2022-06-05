
union IR {
    unsigned int B;

    struct RFormat {
        unsigned int funct : 6;
        unsigned int shamt : 5;
        unsigned int rd : 5;
        unsigned int rt : 5;
        unsigned int rs : 5;
        unsigned int opcode : 6;
    } RI;

    struct IFormat {
        int operand : 16;
        unsigned int rt : 5;
        unsigned int rs : 5;
        unsigned int op : 6;
    } II;

    struct JFormat {
        unsigned int address : 26;
        unsigned int op : 6;
    } JI;
};

// OPCODE
enum OPCODE {
    R_FORMAT = 0,
    BLTZ = 1,
    J = 2,
    JAL = 3,
    BEQ = 4,
    BNE = 5,
    ADDI = 8,
    ADDIU = 9,
    SLTI = 10,
    SLTIU = 11,
    ANDI = 12,
    ORI = 13,
    XORI = 14,
    LUI = 15,
    LB = 32,
    LW = 35,
    LBU = 36,
    SB = 40,
    SW = 43
};

// FUNCT
enum FUNCT {
    SLL = 0,
    SRL = 2,
    SRA = 3,
    JR = 8,
    SYSCALL = 12,
    MFHI = 16,
    MFLO = 18,
    MUL = 24,
    DIV = 26,
    ADD = 32,
    SUB = 34,
    AND = 36,
    OR = 37,
    XOR = 38,
    NOR = 39,
    SLT = 42
};


static char OPCODE_STR[48][10] = {
  "R-format", "bltz", "j", "jal", "beq", "bne", "", "", "addi", "", "slti", "", "andi", "ori", "xori", "lui", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "lb", "", "", "lw", "lbu", "", "", "", "sb", "", "", "sw", "", "", "", ""
};

static char FUNCT_STR[48][10] = {
  "sll", "", "srl", "sra", "", "", "", "", "jr", "", "", "", "syscall", "", "", "", "", "mfhi", "", "mflo", "", "", "", "", "", "mul", "", "", "", "", "", "", "add", "", "sub", "", "and", "or", "xor", "nor", "", "", "slt", "", "", "", "", ""
};

void instructionToString(unsigned int word, char** str);
void printInstruction(unsigned int word);
