#include <stdio.h>
#define MEET_ZNACK 1
#define MEET_RAVNO 1
#define MEET_NUMBER 1
#define DONT_MEET_NUMBER 0
#define MEET_FIRST_NUMBER 1
#define MEET_SECOND_NUMBER 1
#define MEET_THIRD_NUMBER 1
#define ERROR 1
#define DONT_HAVE_ERROR 0
#define DONT_MEET_ZNACK 0
#define DONT_MEET_RAVNO 0
#define MEET_SPACE 1
#define DONT_MEET_SPACE 0
int main(){
    char c;
    long a=0, b=0, r=0, ch1=0, ch2=0, ch3=0, z=0, eq=0, ad=0, er=0, ch=0, sp=0, an=0;
    c=getchar();
    if (c!='\n') {
        while ((c!='\n') && (er==DONT_HAVE_ERROR)){ 
                if (c>='0' && c<='9'&& er==DONT_HAVE_ERROR) {
                    if (sp==MEET_SPACE) {er=ERROR;} 
                    else {
                    if ((eq==DONT_HAVE_ERROR)&&(z==MEET_ZNACK)) {
                        b=b*10;
                        b=b+c-'0';
                        ch2=MEET_SECOND_NUMBER;
                    }
                    if (z==DONT_MEET_ZNACK){
                        a=a*10;
                        a=a+c-'0';
                        ch1=MEET_FIRST_NUMBER;
                    }
                    if (eq==MEET_RAVNO) {
                        r=r*10;
                        r=r+c-'0';
                        ch3=MEET_THIRD_NUMBER;
                    }
                    ch=MEET_NUMBER;
                    }
                }
                if (((c=='+') || (c=='*'))&&(er==DONT_HAVE_ERROR)) {
                    if ((ch1==MEET_FIRST_NUMBER)&&(z==DONT_MEET_ZNACK)){
                        if (c=='+') {ad=1;}
                    }
                    else {
                        er=ERROR;
                    }
                    ch=DONT_MEET_NUMBER;
                    z=MEET_ZNACK;
                    sp=DONT_MEET_SPACE;
                }
                if (c=='=' && er==DONT_HAVE_ERROR) {
                    if ((ch2==DONT_MEET_NUMBER) || (eq==MEET_RAVNO))  {er=ERROR;}
                    ch=DONT_MEET_NUMBER;
                    eq=MEET_RAVNO;
                    sp=DONT_MEET_SPACE;
                }
                if ((c==' ')||(c=='\t')) {
                    if (ch==MEET_FIRST_NUMBER) {
                        sp=MEET_SPACE;
                        }
                    ch=DONT_MEET_NUMBER;}
                if ((c<'0'|| c>'9') && (c!='*') && (c!='+') && (c!='=') && (c!=' ') && (c!='\t')) {er=ERROR;}
                    c=getchar();
        }
        if (ch3==DONT_MEET_NUMBER) {er=ERROR;}
        if (ad==1) {an=a+b;}
        else {an=(long long)a*b;}
        if (er==ERROR) {
                  if (ch2==MEET_SECOND_NUMBER && eq==DONT_MEET_RAVNO) {printf("NO EQUAL SIGN\n");}
                      else {
                            if (ch1==MEET_FIRST_NUMBER && z==DONT_MEET_ZNACK){printf("WRONG SIGN\n");}
                                 else {
                                        if (eq==MEET_RAVNO && ch3==DONT_MEET_NUMBER) {printf("NO ANSWER\n");}
                                             else {printf("INPUT ERROR\n");}
                                 }
                      }
        }
        else {
            if (an==r){printf("YES\n");}
            else {printf("NO\n");}
            }
     } else {printf("INPUT ERROR\n");}
    return 0;
}
