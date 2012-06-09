/*
 * Code39
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xbm.h"
#include "code39.h"

/**
 * processCode39
 *
 * We will use a 3:1 ratio for the difference between wide and narrow bars.
 * Wide bars will take up 3 pixels, narrow bars will take up 1 pixel.
 * Since every barcode will consist of 9 bars, of which 3 are wide, 6 bars will be small.
 * Every bar will take up 3*3+6*1=9+6=15 pixels
 */
void processCode39( char *str, char *text ) {

   XBM *barcode;
   unsigned int currChar;
   int barStartY;
         
   // The 60 is added because of the two '*' that are used as start and stop character, and 15 pixels wite space is used on each side
	
	if( strlen(text) != 0 ) {
	   barcode = newXBM( ( strlen( str ) * 16 ) + 62, 62 );
		xbmDrawString5x8( barcode, (barcode->width/2)-(strlen(text)*5)/2, 1, text );
		barStartY = 10;
	} else {
	   barcode = newXBM( ( strlen( str ) * 16 ) + 62, 54 );
		barStartY = 2;	
	}
	
	drawCode39Bar( barcode, '*', 16, barStartY, 1 );
	for( currChar = 0; currChar < strlen( str ); currChar++ ) {
		drawCode39Bar( barcode, str[currChar], 33+(currChar*16), barStartY, 0 );
		xbmDrawChar5x8( barcode, 33+(currChar*16)+5, barStartY + 42, str[currChar] );
	}
	drawCode39Bar( barcode, '*', (strlen(str)*16)+33, barStartY, 1 );
	
	xbmSaveXBM( barcode, "barcode", "degrunt.nl barcode; http://www.degrunt.nl/barcode/" );

	

	freeXBM( barcode );	
}

void drawCode39Bar( XBM *barcode, char c, int x, int barStartY, int sentry ) {

	int currBit, currX;
	unsigned int bars;
	unsigned int spaces;

	if( sentry == 1 ) {
		sentry = 10;
	}

	currX = x;

	bars = code39Bars[c-32];
	spaces = code39Spaces[c-32];
	
	for( currBit = 16; currBit >= 1; currBit /= 2 ) {
		
		if( bars & currBit ) {
			xbmVline( barcode, currX, barStartY, barStartY+40+sentry );
			xbmVline( barcode, currX+1, barStartY, barStartY+40+sentry );
			xbmVline( barcode, currX+2, barStartY, barStartY+40+sentry );
			currX += 3;
		} else {
			xbmVline( barcode, currX, barStartY, barStartY+40+sentry );
			currX++;
		}
		
		if( currBit > 1 ) {
			if( spaces & (currBit/2) ) {
				currX += 3;
			} else {
				currX++;
			}
		}

	}
	
}

