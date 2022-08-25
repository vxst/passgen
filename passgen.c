#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<assert.h>

#define MAXL 64

static char charset[64] = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM__";

static unsigned char randbuf[MAXL];
static char passbuf[MAXL+1];
static FILE* rand_file;

static void writepass(int len){
    assert(len >= 0 && len < MAXL);
    srandomdev();
    fread(randbuf, sizeof(char), (size_t)len, rand_file);
    for(passbuf[len--] = 0; len >= 0; len--)
        passbuf[len] = charset[(randbuf[len] >> 2)^(len&1?0:arc4random()&63)];
    printf("%s\n", passbuf);
}


int main(int inn, const char** ins){
    int n, l = 0;
    double strength;
    const double rand_strength = 0.96; /* The randomness of generator, we trust it as percent of entropy of true random */
    rand_file = fopen("/dev/random", "rb");
    switch(inn){
        case 1:
            n = 1; l = 11; break;
        case 2:
            n = 1; sscanf(ins[1], "%d", &l); break;
        case 3:
            sscanf(ins[1], "%d", &n); sscanf(ins[2], "%d", &l); break;
        default:
            assert(0);
    }
    strength = log2(pow(63, l)) * rand_strength;
    printf("The strength of the password is about %.0f bits.\n", strength);
    if(strength < 40)
        printf("WARNING: The suggested minimal length of modern hardware protected password should have a strength at least 40 bits.\n");
    if(strength < 56)
        printf("WARNING: The suggested minimal length of unbreakable password for common people should have a strength at least 56 bits.\n");
    if(strength < 72)
        printf("WARNING: The suggested minimal length of unbreakable password for TOP 10 WANTED should have a strength at least 72 bits.\n");
    if(strength < 90)
        printf("WARNING: The suggested minimal length of no kdf password should have a strength at least 90 bits.\n");

    printf("\n");
    while(n--)
        writepass(l);
    fclose(rand_file);
    return 0;
}

