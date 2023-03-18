#include <stdio.h>
#include <stdlib.h>
#define FIRSTBIT 1<<7
#define SHIFTRIGHT >>1
#define STARTPACK (n+1)/2+1
#define OLD 2*i-2
#define YOUNG 2*i-1

void PrintElemBits ( unsigned char *elem ){
    unsigned char mask;
    int i;
    mask = FIRSTBIT;
    for (i=0;i<8;i++){
        if (mask&*elem){printf("1");}
        else {printf("0");}
        mask=mask SHIFTRIGHT;
    }
}

void PrintArrayBits ( unsigned char *array, unsigned char n ){
    int i;
    for (i=0;i<n;i++){
        PrintElemBits( &array[i] );
        if (i!=(n-1)) {printf(" ");}
    }
    printf("\n");
}

unsigned char CountBits ( unsigned char *elem ){
    unsigned char mask, ans;
    mask= FIRSTBIT;
    ans=8;
    if (*elem){
        while (!(mask&*elem)){
            mask=mask SHIFTRIGHT;
            ans=ans-1;
        }
    }
    else{ans=0;}
    return ans;
}

unsigned char *PackedArray ( unsigned char *array, unsigned char n, unsigned char *size ){
    unsigned char *packedarray;
    int i;
    unsigned char old, young, elem, mask, maskwrite, bit, j;
    packedarray = (unsigned char*)malloc( sizeof( unsigned char )*( n + n/2 + 2 ));
    if ( packedarray == NULL ){
        printf("NOT ENOUGH MEMORY\n");
        return 1;
    }
    packedarray[0]=n;
    for (i=1;i<=((n+1)/2);i++){
        elem = array[OLD];
        old = CountBits( &elem );
        old = old<<4;
        if (YOUNG>n-1){young=0;}
        else {
            elem = array[YOUNG];
            young = CountBits( &elem );
        }
        packedarray[i] = old | young;
    }

    maskwrite = FIRSTBIT;
    j=STARTPACK;
    for (i=0; i<=n-1; i++){
        if (array[i]){
            mask=FIRSTBIT;
            while (!(mask&array[i])){
                mask=mask SHIFTRIGHT;
            }
            while (mask) {
                bit=mask & array[i];
                if (!maskwrite){
                    j++;
                    maskwrite=FIRSTBIT;
                }
                if (bit) {packedarray[j]= packedarray[j] | maskwrite;}
                maskwrite=maskwrite SHIFTRIGHT;
                mask=mask SHIFTRIGHT;
            }
        }
    }
    if (!n) {j=0;}
    *size=j+1;
    return packedarray;
}

int main(){
    int i;
    unsigned char n, size;
    unsigned char *inarray, *outarray;
    scanf("%hhd",&n);
    inarray = (unsigned char*)malloc( sizeof(unsigned char)*n );
    if ( inarray == NULL ){
        printf("NOT ENOUGH MEMORY\n");
        return 1;
    }
    for (i=0; i<n; i++){
        scanf("%hhu", &inarray[i]);
    }
    outarray = PackedArray ( inarray, n, &size );
    if ( (n>=1) && (outarray[size-1]==0) ){
        size--;
    }
    PrintArrayBits ( outarray, size );
    free ( inarray );
    free ( outarray );
    return 0;
}
