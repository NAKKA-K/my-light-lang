#include<stdio.h>
#include<ctype.h>
#include<stdarg.h>
#include<stdlib.h>
#include<string.h> // silent warning from 'strchr' ...

// Prototype
static void spaceSkip();
static void error(char *fmt, ...);
static void expect(char c);
static void readUntil(char untilChar, char *buf);
static int evalFunction(char *code, int arg);
static int eval(int arg);
int getNameric();
int getCalcResult(int arg);


static char *p;
static char func[26][100];


int main(int argc, char **argv){
    p = argv[1];
    while(*p){
        printf("%d\n", eval(0));
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

static void expect(char c){
    if(*p != c)
        error("%c expected: %s", p);
    p++;
}

static void readUntil(char untilChar, char *buf){
    while(*p != untilChar)
        *buf++ = *p++;
    p++;
    *buf = '\n';
}

static int evalFunction(char *code, int arg){
    char *originPointer = p;
    p = code; // Replace code to method
    int val = eval(arg);
    p = originPointer; // Reassign pointer
    return val;
}

static int eval(int arg){
    spaceSkip();

    // Nameric
    if(isdigit(*p)){
        return getNameric();
    }

    // Operate
    if(strchr("+-*/", *p)){
        return getCalcResult(arg);
    }

    
    if(*p == '.'){
        p++;
        return arg;
    }

    if(*p >= 'A' && *p <= 'Z' && *(p + 1) == '['){
        char name = *p;
        p += 2;
        readUntil(']', func[name - 'A']);
        return eval(arg);
    }

    if(*p >= 'A' && *p <= 'Z' && *(p + 1) == '('){
        char name = *p;
        p += 2;
        int newArg = eval(arg);
        expect(')');
        return evalFunction(func[name - 'A'], newArg);
    }

    error("invalid character: %c", *p);
}


int getNameric(){
    int val = *p++ - '0';
    while(isdigit(*p))
        val = val * 10 + (*p++ - '0');
    return val;
}

int getCalcResult(int arg){
    // Confirm execution order in formula
    char op = *p++;
    int x = eval(arg);
    int y = eval(arg);

    switch(op){
    case '+': return x + y;
    case '-': return x - y;
    case '*': return x * y;
    case '/': return x / y;
    }
}
