#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAXL 1024

const char* charset = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM__";

unsigned char randbuf[MAXL];
char passbuf[MAXL+1];
FILE* rand_file;

void writepass(int len){
    assert(len >= 0 && len < MAXL);
    srandomdev();
    fread(randbuf, sizeof(char), (size_t)len, rand_file);
    for(passbuf[len--] = 0; len >= 0; len--)
        passbuf[len] = charset[(randbuf[len] >> 2)^(len&1?0:arc4random()&63)];
    printf("%s\n", passbuf);
}

int main(int inn, const char** ins){
    int n, l;
    rand_file = fopen("/dev/random", "rb");
    switch(inn){
        case 1:
            n = 1, l = 10; break;
        case 2:
            n = 1; sscanf(ins[1], "%d", &l); break;
        case 3:
            sscanf(ins[1], "%d", &n); sscanf(ins[2], "%d", &l); break;
    }
    while(n--)
        writepass(l);
    fclose(rand_file);
    return 0;
}
