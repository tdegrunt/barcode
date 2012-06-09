/**
 * Bin2Hex
 *
 * v0.1
 *
 * @update 2002-08-03	Initial version
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define	BIN2HEX_VERSION	"0.1 beta"

void usage( void );


void main( int argc, char *argv[] ) {

	FILE *in;
	int currValue = 0;
	int currMultiplier = 128;
	char c;
	int col = 1;

	if( argc < 2 ) {
		usage();
	}

	in = fopen( argv[1], "r" );
	
	while( (c = fgetc(in)) != EOF ) {

		switch( c ) {
			case '\r':
				/* Eat the character */
				break;
			case '\n':
				printf( "0x%02x, ", currValue );
				col++;
				if( col == 9 ) {
					printf( "\n" );					
					col = 1;
				}
				currValue = 0;
				currMultiplier = 128;
				break;

			case '0':
			case '1':
				if( c == '1' ) {
					currValue += currMultiplier;	
				}
				currMultiplier /= 2;				
				break;
			default:
				/* Eat the character */
				break;
		}
	}
	
	fclose( in );

}

void usage( void ) {
	printf( "bin2hex v%s - by Tom de Grunt\n", BIN2HEX_VERSION );
	printf( "Converts 8bits binary numbers to heximal numbers.\n" );
	printf( "\n" );
	printf( "usage:\n" );
	printf( "bin2hex input-file\n" );
	printf( "   input-file - A ASCII-text file containing 8-bit binary numbers.\n");
	printf( "                Each binary number must be on a separate line.\n");	
	exit(1);
}