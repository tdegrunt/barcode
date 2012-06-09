/*
 * KIX
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xbm.h"
#include "kix.h"

/**
 * processKIX
 *
 * With KIX every barcode character uses 4 bars and 3 spaces. 
 * Bars will be 1 pixel wide, spaces will be 4 pixels wide.
 * So every barcode character will take up 4*1+3*4=4+12=16 pixels
 */
void processKIX( char *str, char *text ) {

   XBM *barcode;
   unsigned int currChar;
   int barStartY;
         
	if( strlen(text) != 0 ) {
	   barcode = newXBM( ( strlen( str ) * 17 ) + 20, 29 );
		xbmDrawString5x8( barcode, (barcode->width/2)-(strlen(text)*5)/2, 1, text );
		barStartY = 11;
	} else {
	   barcode = newXBM( ( strlen( str ) * 17 ) + 20, 20 );
		barStartY = 2;	
	}
	
	for( currChar = 0; currChar < strlen( str ); currChar++ ) {
		drawKIXBar( barcode, str[currChar], 10+(currChar*17), barStartY );
	}
	
	xbmSaveXBM( barcode, "barcode", "degrunt.nl barcode; http://www.degrunt.nl/barcode/" );

	freeXBM( barcode );	
}

void drawKIXBar( XBM *barcode, char c, int x, int barStartY ) {

	unsigned int bars;

	bars = kixBars[c-32];
	
	drawSingleKIXBar( barcode, ( bars & 0xc0 )>>6, x, barStartY );
	drawSingleKIXBar( barcode, ( bars & 0x30 )>>4, x+4, barStartY );
	drawSingleKIXBar( barcode, ( bars & 0x0c )>>2, x+8, barStartY );
	drawSingleKIXBar( barcode, ( bars & 0x03 ), x+12, barStartY );
		
}

void drawSingleKIXBar( XBM *barcode, int type, int x, int barStartY ) {

	switch( type ) {
		case 3:
			xbmVline( barcode, x, barStartY, barStartY+15 );
			break;
		case 2:
			xbmVline( barcode, x, barStartY+5, barStartY+15 );
			break;		
		case 1:
			xbmVline( barcode, x, barStartY, barStartY+10 );
			break;
		case 0:
			xbmVline( barcode, x, barStartY+5, barStartY+10 );
			break;
	}
}