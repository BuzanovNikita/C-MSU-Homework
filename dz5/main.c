#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZEBUF 15
#define CONSISTSPACE ((*tmp==' ')||(*tmp==',')||(*tmp=='.')||(*tmp=='\n'))

void bufcpy( char* buf1, char* buf2, int size ){
    for( ; size>0; size-- ) buf2[size-1] = buf1[size-1];
}

void expandfile( int fd, int n, int m, int len ){
    //char buf[SIZEBUF+1];
    //int rd_ch;
    shiftfile( fd, n );
    lseek( fd, n + len - m, SEEK_CUR );
    shiftfile( fd, m );
    lseek( fd, 2*m, SEEK_CUR );
    //rd_ch = read( fd, buf, SIZEBUF );
    //write( 1, buf, rd_ch );
}


void shiftfile( int fd, int n ){

    char bufr[SIZEBUF+1], bufw[SIZEBUF+1];
	int rd_ch, cnt=0, tmp=0;

    rd_ch = read( fd, bufw, n );
    lseek( fd, -rd_ch, SEEK_CUR );

    rd_ch = (int)read( fd, bufr, n );
    while( rd_ch ){

        lseek( fd, -rd_ch, SEEK_CUR );
        write( fd, bufw, n );
        //write( 1, bufw, n );
        //printf("\n");
        bufcpy( bufr, bufw, SIZEBUF );
        tmp = rd_ch;
        rd_ch = (int)read( fd, bufr, n );
        cnt++;

    }
    write( fd, bufw, tmp );
    //write( 1, bufw, tmp );
    //printf("\n");
    lseek( fd, -cnt*n - tmp , SEEK_CUR );
    //read( fd, bufr, n );
    //write( 1, bufr, n );

}

int lenword( int fd ){

    int len=0, cnt=0, rd_ch;
    char buf[SIZEBUF+1], *tmp;

    rd_ch = read( fd, buf, SIZEBUF );

    while ( rd_ch ){
        tmp = buf;
        while (tmp-buf<rd_ch){
            if ( CONSISTSPACE ) break;
            tmp++;
        }
        tmp--;
        if ( !((tmp-buf==SIZEBUF-1) && (!CONSISTSPACE)) ) break;
        cnt++;
        rd_ch = read( fd, buf, SIZEBUF );
    }
    len = cnt * SIZEBUF + tmp - buf + 1;
    lseek( fd, -cnt*SIZEBUF - rd_ch , SEEK_CUR );
    //rd_ch = read( fd, buf, SIZEBUF );
    //write( 1, buf, rd_ch );
    return len;

}

void repends( int fd, int n, int m ){
    char buf[SIZEBUF+1], *tmp;
    int rd_ch, len;

    rd_ch = read( fd, buf, SIZEBUF );
    while( rd_ch ){
        tmp = buf;
        while( (CONSISTSPACE) && (rd_ch>tmp-buf) ) tmp++;
        if ( rd_ch!=tmp-buf ){
            lseek( fd, - rd_ch + (tmp-buf), SEEK_CUR );
            /*rd_ch = read( fd, buf, SIZEBUF);
            write( 1, buf, rd_ch );
            printf( "\n" );*/
            len = lenword( fd );
            if ( len >= n+m ) expandfile( fd, n, m, len );
            else lseek( fd, len, SEEK_CUR );
            /*rd_ch = read( fd, buf, SIZEBUF);
            write( 1, buf, rd_ch );
            printf( "\n" );
            break;*/
        }
        rd_ch = read( fd, buf, SIZEBUF );
    }



}

int main( int argc, char** argv ) {
    char *r = "rep";
    char *tmp = argv[2];
    int  fd, n=0, m=0;

    if ( (argc<5) || (argc>6) ) return 1;

    fd = open( argv[1], O_RDWR );

    if ( fd==-1 ) return 1;

    while ( (*tmp==*r) && (*tmp!='\0')  && (*r!='\0') ){
        tmp++;
        r++;
    }
    if ( !((*tmp==*r) && (*tmp=='\0')) ){
        return 1;
    }

    if ( *argv[3] == 't' ) m = atoi( argv[4] );
    if ( *argv[3] == 'h' ) n = atoi( argv[4] );
    if ( *argv[3] == 'e' ) {
        n = atoi( argv[4] );
        m = atoi( argv[5] );
    }

    repends( fd, n, m );

    close( fd );

    return 0;
}
