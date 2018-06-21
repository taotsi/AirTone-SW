/*******************************************************************************
 * Brief:   Because the C libraries supported are not complete, so I have to
 *          write some of them on my own.
 * Author:	taotsi
 * Update:	2017.03.27
 *******************************************************************************/
#ifndef BasicOp_h
#define BasicOp_h


/* Functions ------------------------------------------------------------------*/
/* Math Calculation Functions **************************************************/
unsigned long power(int base, int exp);

/* String Processing Functions *************************************************/
void Num2Str(unsigned short x, char str[6]);
void NumX2Str(unsigned short x, char str[6]);

unsigned short Char2Num(char c);

#endif // BasicOp_h

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/