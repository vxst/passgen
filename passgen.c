#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<assert.h>
#include<stdint.h>
#include<ctype.h>
#include<string.h>
#include<openssl/rand.h>

#define MAXL 64

#define RANDOMPASS 1
#define RANDOMWORD 2

static const char charset[65] = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_7";

static unsigned char randbuf[MAXL];
static char passbuf[MAXL+1];
static char wordbuf[MAXL*9+1];
static int mode = RANDOMPASS;

static void writepass(int len){
    uint64_t u_pos;
    int i;

    RAND_bytes(randbuf, len);
    RAND_bytes((unsigned char*)(&u_pos), 8);

    u_pos %= len;

    for(i = 0; i < len; i++)
        passbuf[i] = charset[randbuf[i] & 63];
    passbuf[u_pos] = '_';
    passbuf[len]=0;

    printf("%s\n", passbuf);
}

extern char const _binary_words_txt_start[];
extern char const _binary_words_txt_end[];

static char wordlist[2048][16];

static void init_wordlist(){
    char *i, *begin = (char*)_binary_words_txt_start, *end = (char*)_binary_words_txt_end;
    int iw, jw;
    for(iw = jw = 0, i = begin; i != end; i++){
        if(islower(*i))
            wordlist[iw][jw++] = *i;
        else
            jw = wordlist[iw++][jw] = 0;
    }
}

static void writeword(int len){
    int i;
    *wordbuf = 0;
    uint32_t wp;
    for(i = 0; i < len; i++){
        RAND_bytes((unsigned char*)(&wp), 4);
        strcat(wordbuf, (i==0?"":"_"));
        strcat(wordbuf, wordlist[wp&2047]);
    }
    printf("%s\n", wordbuf);
}

static void writeline(int len){
    if(mode == RANDOMPASS)
        writepass(len);
    if(mode == RANDOMWORD)
        writeword(len);
}
    

int main(int argn, const char** args){
    int n, l = 0;
    double strength;
    if(argn > 1 && strcmp(args[1], "-w")==0){
        args++;
        argn--;
        mode = RANDOMWORD;
        init_wordlist();
    }
    switch(argn){
        case 1:
            n = 12;
            l = mode == RANDOMPASS? 10: 6;
            break;
        case 2:
            n = 12;
            sscanf(args[1], "%d", &l);
            break;
        case 3:
            sscanf(args[1], "%d", &n);
            sscanf(args[2], "%d", &l);
            break;
        default:
            printf("Invaild input\n");
            return 1;
    }
    if(l < 1 || l >= MAXL || n < 1 || n >= 1024){
        printf("Invaild input\n");
        return 1;
    }
    if(mode == RANDOMPASS)
        strength = log2(pow(63, l-1)) + log2(l);
    else
        strength = 11 * l;
    printf("The strength of the password is about %.0f bits.\n\n", strength);

    while(n--)
        writeline(l);

    return 0;
}
