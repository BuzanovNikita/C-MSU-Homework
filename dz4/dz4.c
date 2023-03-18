#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct s_file{
	int data;
	FILE *name_file;
} FileStruct;

FileStruct* create_elem( char* input ){
	FileStruct *elem = NULL;
	FILE *f = fopen( input, "r" );
	if ( f != NULL ){
		elem = ( FileStruct* )malloc( sizeof( FileStruct ) );
		elem -> name_file = f;
	}
	return elem;
}


void read_new_elem( FileStruct **p_s_file ){
	int c, set_data;
	c = fscanf( (*p_s_file) -> name_file, "%d", &set_data );
	if ( c == 1 ){
		(*p_s_file) -> data = set_data;
	}
	else { 
		fclose ( (*p_s_file) -> name_file );
		free( *p_s_file );
		*p_s_file = NULL;
	}
}

void print_sort( FileStruct **m, int size, int flag ){
	FileStruct **p_min=NULL, **end = m + size, **beg = m;
	int min = INT_MAX;
	
	for( ; beg < end; beg++ ){
		if ( *beg != NULL ){
			if ( (*beg) -> data <= min ){
				min = (*beg) -> data;
				p_min = beg;
			}
		}
	}

	if ( p_min != NULL ){
		if (flag) printf( "%d", min );
		else printf( " %d", min );
		read_new_elem( p_min );
		print_sort( m, size, 0 );
	}
}

int main( int argc, char** argv ){
	int i, size=argc-1;
	FileStruct **m = (FileStruct**) malloc( size * sizeof( FileStruct* ) );

	if ( m == NULL ){
		printf("NOT ENOUGH MEMORY\n");
		return 1;
	}

	if ( argc>1 ){
		for( i=0; i<size; i++ ){
			m[i] = create_elem( argv[i+1] );
			if ( m[i] != NULL ) read_new_elem( &m[i] );
		}

		print_sort( m, size, 1 );
		printf( "\n" );

		free( m );
	}
	
	return 0;
}
