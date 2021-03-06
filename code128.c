/*
 * Code128
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xbm.h"
#include "code128.h"

/**
 * processCode128
 *
 */
void processCode128( char *str, char *text ) {

   /*XBM *barcode;
   */
   unsigned int currChar;
   /*
   int barStartY;
   */
         
	for( currChar = 0; currChar < strlen(str); currChar++ ) {
		printf( "%c: %d\n", str[currChar], getCode128BarWidth( str[currChar] ) );			
	}

   // The 60 is added because of the two '*' that are used as start and stop character, and 15 pixels wite space is used on each side
	/*
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
	*/
}

unsigned int getCode128BarWidth( char c ) {

	int currBar;

	unsigned int bars;
	unsigned int spaces;
	
	int width = 0;
	int bitShift = 6;
	
	/*** FIXME: This will only work with Code A types */
	bars = code128Bars[c-32];
	spaces = code128Spaces[c-32];

	/* We will add the bars and the spaces separately */
	for( currBar = 0; currBar < 3; currBar++ ) {
		width += (((bars & code128Masks[currBar])>>bitShift) + 1);
		bitShift -= 2;
	}	

	bitShift = 6;
	for( currBar = 0; currBar < 3; currBar++ ) {
		width += (((spaces & code128Masks[currBar])>>bitShift) + 1);
		bitShift -= 2;
	}	

	return width;	
}

void drawCode128Bar( XBM *barcode, char c, int x, int barStartY, int sentry ) {

	/*

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
	
	*/
	
}

