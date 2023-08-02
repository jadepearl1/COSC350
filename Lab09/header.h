#define NOT_READY -1
#define FILLED 0 
#define TAKEN 1 
#define GO 2
#define STOP 3

struct Memory {
    int status;
    int gostop;
    int n1, n2;
};
