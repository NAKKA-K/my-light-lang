#include<stdio.h>
#include<ctype.h>
#include<stdarg.h>
#include<stdlib.h>

// Prototype
static int eval();
static void spaceSkip();
static void error(char *fmt, ...);
int getNameric();


static char *p;


int main(int argc, char **argv){
    p = argv[1];
    while(*p){
        printf("%d\n", eval());
    }

    return 0;
}

static void spaceSkip(){
    while(isspace(*p))
        p++;
}

static void error(char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}


static int eval(){
    spaceSkip();

    // Nameric
    if(isdigit(*p)){
        return getNameric();
    }

    error("invalid character: %c", *p);
}

int getNameric(){
    int val = *p++ - '0';
    while(isdigit(*p))
        val = val * 10 + (*p++ - '0');
    return val;
}
