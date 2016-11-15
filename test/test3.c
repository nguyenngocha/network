#include <stdio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KBC   "\x1B[10m"

#define BKNRM  "\x1B[1;0m"
#define BKRED  "\x1B[1;31m"
#define BKGRN  "\x1B[1;32m"
#define BKYEL  "\x1B[1;33m"
#define BKBLU  "\x1B[1;34m"
#define BKMAG  "\x1B[1;35m"
#define BKCYN  "\x1B[1;36m"
#define BKWHT  "\x1B[1;37m"
int main()
{
    printf("%sred\n", KRED);
    printf("%sgreen\n", KGRN);
    printf("%syellow\n", KYEL);
    printf("%sblue\n", KBLU);
    printf("%smagenta\n", KMAG);
    printf("%scyan\n", KCYN);
    printf("%swhite\n", KWHT);
    printf("%snormal\n", KNRM);
    printf("%sRed%sNormal",KRED,KNRM);
    printf("%sRed%sNormal",KBC,KNRM);
    printf("%sbold green",BKGRN);
    return 0;
}