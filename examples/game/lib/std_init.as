/******************************************************************************
 * NES High Level Assembler Library
 * (c) 2003,2004,2005 Brian Provinciano
 * http://www.bripro.com
 ******************************************************************************
 * STD_INIT.AS
 ******************************************************************************
 * Functions for system initialization
 ******************************************************************************/
	
// function	clear_ram()
	
/******************************************************************************/


/******************************************************************************
 * clears the 2K ram ($800 bytes)
 *
 * Registers changed:	A, X
 */
function clear_ram()
{
	lda #0 	// the value
	ldx #0 	// the loop (256 reps)
	
	do {
		sta  0x00,x
		// no $100 because it's the stack!
		sta 0x200,x
		sta 0x300,x
		sta 0x400,x
		sta 0x500,x
		sta 0x600,x
		sta 0x700,x
		dex
	} while(nonzero)
}
/******************************************************************************/
