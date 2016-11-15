#include <stdio.h>
 
void color_textBold(int color)
{
    if(color == -1)
    {
        printf("\x1B[0;39m");
        return;
    }
    printf("\x1B[1;%dm", color);
}
void color_text(int color)
{
    if(color == -1)
    {
        printf("\x1B[0;39m");
        return;
    }
    printf("\x1B[%dm", color);
}
void color_textTest(int color)
{
    if(color == -1)
    {
        printf("\x1B[0;39m");
        return;
    }
    printf("\x1B[2%dm", color);
}
int main()
{
    int i;
    for(i=0;i<40;i++){
        color_text(i);
        printf("%d=Test.\n",i);
        color_textBold(i);
        printf("%d=Test.\n",i);
        color_textTest(i);
        printf("%d=Test.\n",i);
    }
    printf("\x1B[0m normal\n");
    return 0;
}