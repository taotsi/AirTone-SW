/*******************************************************************************
 * Author:	LiYong
 * Update:	none
 *******************************************************************************/
#ifndef _MYTYPEDEF_H_
#define _MYTYPEDEF_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

/*Bit field operations*/
//#define SetBit( Byte, Bit )  ( Byte ) |= ( 1<<( Bit ) )
//#define ClrBit( Byte, Bit )  ( Byte ) &= ~( 1<<( Bit ) )
#define GetBit( Byte, Bit )  ( ( Byte ) & ( 1<<( Bit ) ) )
#define ComBit( Byte, Bit )  ( Bytes ) ^= ( 1<<( Bit ) )
#define SetBits( Byte, Bits ) ( Byte ) |= ( Bits )
#define ClrBits( Byte, Bits ) ( Byte ) &= ~( Bits )
#define GetBits( Byte, Bits ) ( ( Byte ) & ( Bits ) )
#define ComBits( Byte, Bits ) ( Byte ) ^= ( Bits )

/*Bit map for fast calculation*/
#define BitMap( x )   ( 1<<( x ) )
/*Get MAX or MIN value*/
#define GetMax( x1, x2 ) ( ( x1 ) > ( x2 ) ? ( x1 ) : ( x2 ) )
#define GetMin( x1, x2 ) ( ( x1 ) > ( x2 ) ? ( x2 ) : ( x1 ) )

#endif//_MYTYPEDEF_H_

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/