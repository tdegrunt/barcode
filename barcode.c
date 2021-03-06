/**
 * Barcode
 *
 * v0.5
 *
 * @update 2002-08-31	Support for KIX barcodes
 * @update 2002-08-30	Support for Code39 barcodes
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xbm.h"
#include "code39.h"
#include "code128.h"
#include "kix.h"

#define	BARCODE_VERSION	"0.5 beta"

void usage( void );

void main( int argc, char *argv[] ) {

	char *type;
	char *value;
	char *text;
	
	if( argc < 3 ) {
		usage();
	}
	
	type = strdup( argv[1] );
	value = strdup( argv[2] );
	
	if( argc == 4 ) {
		text = strdup( argv[3] );	
	} else {
		strcpy( text, "" );
	}

	if( strcmp( type, "code39" ) == 0 ) {
		processCode39( value, text );		
	} else if( strcmp( type, "kix" ) == 0 ) {
		processKIX( value, text );		
	} else if( strcmp( type, "code128" ) == 0 ) {
		processCode128( value, text );		
	} else {
		usage();
	}

   exit( 0 );
}

void usage( void ) {
	printf( "barcode v%s\n", BARCODE_VERSION );
	printf( "\n" );
	printf( "usage:\n" );
	printf( "barcode type value [text]\n" );
	printf( "   type  - the barcode type (code39,kix)\n");
	printf( "   value - the value of the barcode\n");	
	printf( "   text  - optional text\n");	
	exit(1);
}