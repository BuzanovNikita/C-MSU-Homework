#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 10
int my_strlen ( char* str ){
    int len=0;
    if ( str == NULL ) return -1;
    else {
        while ( *str != '\0' ){
            len++;
            str++;
        }
        return len;
    }
}

char* my_strstr ( char* str, char* substr ){
    char* substrcopy, *result;
    if ( (str==NULL) || (substr==NULL) ) return NULL;
    else {
        substrcopy = substr;
        while ( (*substr != '\0') && (*str != '\0') ){
            while ( (*str != '\0') && (*str != *substr) ){
                str++;
                substr = substrcopy;
            }
            if ( substrcopy == substr ){
                result = str;
            }
            str++;
            substr++;
        }
        if ( *substr != '\0' ){
            result = NULL;
        }
        return result;
    }
}

int my_strcmp ( char* str1, char* str2 ){
    if ( (str1==NULL) || (str2==NULL) ) return INT_MAX;
    else {
        while ( (*str1 != '\0') && (*str2 != '\0') ){
            if ( *str1 == *str2 ){
                str1++;
                str2++;
            }
            else {
                return *str1 - *str2;
                break;
            }
        }
        if ( *str1 == *str2 ){
            return 0;
        }
    }

}

void search_arr ( char** text, char* substr, int n ){
    int i=0, count=0;
    char* tmp;
    while ( text[i] != NULL ){
        count = 0;
        tmp = my_strstr( text[i], substr );
        while ( tmp!=NULL ){
            tmp++;
            tmp = my_strstr( tmp, substr );
            count++;
        }
        if ( count == n ){
            printf("%d:", i+1);
            printf("%s", text[i] );
        }
        i++;
    }
}

void print_str_arr ( char** text ){
    int i=0;
    while ( text[i] != NULL ){
        printf("%s", text[i] );
        i++;
    }
}
int main(int argc, char** argv){
    int j=0, i=0, textin=1, stringin=1, n;
    char **text, **tmp1;
    char *tmp;
    char c;
    c = getchar();
    text = malloc ( sizeof( char* ) * textin * N );
    if (!text) {
        printf( "NOT ENOUGH MEMORY\n" );
        return 1;
    }
    while ( 1 ){
        if ( i + 1 > textin * N ){
            textin++;
            tmp1 = text;
            text = realloc ( text, sizeof( char* ) * N * textin );
        }
        if (!text){
            printf( "NOT ENOUGH MEMORY\n" );
            text = tmp1;
            break;
        }
        text[i] = malloc ( sizeof( char ) * N * stringin );
        if (!text[i]){
            printf( "NOT ENOUGH MEMORY\n" );
            break;
        }
        j = 0;
        while ( (c!='\n') && (c!=EOF) ){
            if ( j+2 > N * stringin ){
                stringin++;
                tmp = text[i];
                text[i] = realloc ( text[i] , sizeof( char ) * N * stringin );
            }
            if (!text[i]){
                printf( "NOT ENOUGH MEMORY\n" );
                text[i] = tmp;
            }
            text[i][j] = c;
            c = getchar();
            j++;
        }
        text[i][j] = '\n';
        j++;
        text[i][j] = '\0';
        i++;
        if ( c == EOF ){
            break;
        }
        c = getchar();
    }
    text[i-1] = NULL;
    n = atoi( argv[2] );
    if ( (argv[1]!=NULL) && (argv[2]!=NULL) && (n>0) ) search_arr( text, argv[1], n );
    i = 0;
    while ( text[i]!=NULL ){
        free( text[i] );
        i++;
    }
    return 0;
}
