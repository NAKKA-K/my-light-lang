#include<stdio.h>

// Prototype
static int eval();


static char *p;

int main(int argc, char **argv){
    p = argv[1];
    while(*p){
        printf("%d\n", eval());
    }

    return 0;
}

static int eval(){
    p++;
    return 0;
}
