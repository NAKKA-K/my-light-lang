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
static int evalFunction(char *code, int *args);
static int eval(int *args);
int getNameric();
int getCalcResult(int *args);


static char *p;
static char func[26][100];


int main(int argc, char **argv){
    p = argv[1];
    while(*p)
        printf("%d\n", eval(0));

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
        error("%c expected: %s", c, p);
    p++;
}

static void readUntil(char untilChar, char *buf){
    while(*p != untilChar)
        *buf++ = *p++;
    p++;
    *buf = '\0';
}

static int evalFunction(char *code, int *args){
    char *originPointer = p;
    p = code; // Replace code to method
    int val;
    while(*p)
        val = eval(args);
    p = originPointer; // Reassign pointer
    return val;
}

static int eval(int *args){
    spaceSkip();

    
    if (*p == 'P' && p[1] == 'O'){
        p += 2;
        expect('(');
        int val = eval(args);
        expect(')');
        printf("%d\n", val);
        return val;
    }


    if('a' <= *p && *p <= 'z')
        return args[*p++ - 'a'];

    if('A' <= *p && *p <= 'Z' && p[1] == '['){
        char name = *p;
        p += 2;
        readUntil(']', func[name - 'A']);
        return eval(args);
    }

    if('A' <= *p && *p <= 'Z' && p[1] == '('){
        int newArgs[26];
        char name = *p;
        p += 2;
        
        int i = 0;
        for(spaceSkip(); *p != ')'; spaceSkip())
            newArgs[i++] = eval(args);

        expect(')');
        return evalFunction(func[name - 'A'], newArgs);
    }


    // Nameric
    if(isdigit(*p))
        return getNameric();

    // Operate
    if(strchr("+-*/", *p))
        return getCalcResult(args);


    error("invalid character: %c", *p);
}


int getNameric(){
    int val = *p++ - '0';
    while(isdigit(*p))
        val = val * 10 + (*p++ - '0');
    return val;
}

int getCalcResult(int *args){
    // Confirm execution order in formula
    char op = *p++;
    int x = eval(args);
    int y = eval(args);

    switch(op){
    case '+': return x + y;
    case '-': return x - y;
    case '*': return x * y;
    case '/': return x / y;
    }
}
