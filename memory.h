
#define PROG_START 0x00400000
#define PROG_END 0x00500000
#define DATA_START 0x10000000
#define DATA_END 0x10100000
#define STAK_START 0x7FF00000
#define STAK_END 0x80000000


int MEM(unsigned int A, int V, int nRW, int S);
void resetMem();
void viewMemory(unsigned int start, unsigned int end);
int setMemory(unsigned int A, int V);
