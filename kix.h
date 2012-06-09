/*
 * KIX
 */
 
/* KIX Bar patterns */
static unsigned char kixBars[] = {
	0x00, // (dummy: space)
	0x00, // (dummy: !)
	0x00, // (dummy: ")
	0x00, // (dummy: #)
	0x00, // (dummy: $)
	0x00, // (dummy: %)
	0x00, // (dummy: &)
	0x00, // (dummy: ')
	0x00, // (dummy: ()
	0x00, // (dummy: ))
	0x00, // (dummy: *)
	0x00, // (dummy: +)
	0x00, // (dummy: ,)
	0x00, // (dummy: -)
	0x00, // (dummy: .)
	0x00, // (dummy: /)
	0x0f, // 0
	0x27, // 1
	0x2d, // 2
	0x87, // 3
	0x8d, // 4
	0xa5, // 5
	0x1b, // 6
	0x33, // 7 
	0x39, // 8
	0x93, // 9
	0x00, // (dummy: :)
	0x00, // (dummy: ;)
	0x00, // (dummy: <)
	0x00, // (dummy: =)
	0x00, // (dummy: >)
	0x00, // (dummy: ?)
	0x00, // (dummy: @)
	0x99, // A
	0xb1, // B
	0x1e, // C
	0x36, // D
	0x3c, // E
	0x96, // F
	0x9c, // G
	0xb4, // H
	0x4b, // I
	0x63, // J
	0x69, // K
	0xc3, // L
	0xc9, // M
	0xe1, // N
	0x4e, // O
	0x66, // P
	0x6c, // Q
	0xc6, // R
	0xcc, // S
	0xe4, // T
	0x5a, // U
	0x72, // V
	0x78, // W
	0xd2, // X
	0xd8, // Y
	0xf0	// Z   
};

/* prototypes */
void processKIX( char *str, char *text );
void drawKIXBar( XBM *barcode, char c, int x, int barStartY );
void drawSingleKIXBar( XBM *barcode, int type, int x, int barStartY );
