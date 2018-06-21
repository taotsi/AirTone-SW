/*******************************************************************************
 * Brief:   Because the C libraries supported are not complete, so I have to
 *          write some of them on my own.
 * Author:	taotsi
 * Update:	2017.03.27
 *******************************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "BasicOp.h"


/* Functions ------------------------------------------------------------------*/

/* Math Calculation Functions **************************************************/

/**
  * Brief:  Calculate  the n-th power of b.
  * Param:  b: the base.
  * Param:  n: the exponent.
  * RetVal: the power.
  */
unsigned long power(int b, int n)
{
    unsigned long pow = 1;
    for(int i=0; i<n; i++)
    {
        pow *= b;
    }
    return pow;
}


/**
  * Brief:  Convert a decimal number into a string.
  * Param:  x:      Number to convert, can be from 0 to 65536.
  * Param:  str[6]: String converted with 6 digits at most.
  */
void Num2Str(unsigned short x, char str[6])
{
    unsigned char Num[6];
    unsigned short temp = 1;
    int d = 0;
    
    /* Get the digit of the Number. */
    while(x/power(10, d))
    {
        d++;
    }
    
    /* The digit being zero means the Number is zero. */
    if(d == 0)
    {
        str[0] = '0';
        str[1] = '\0';
    }
    
    /* Convert the number into the relative string. */
    else
    {
        for(int i=0; i<d; i++)
        {
            temp = x % power(10, d-i);
            temp /= power(10,d-i-1);
            Num[i] = temp;
            str[i] = Num[i] + '0';
        }
        str[d] = '\0';
    }
}


/**
  * Brief:  Convert a Hexadecimal number into a string.
  */
void NumX2Str(unsigned short x, char str[6])
{
    unsigned char Num[6];
    unsigned short temp = 1;
    int d = 0;
    
    /* Get the digit of the Number. */
    while(x/power(16, d))
    {
        d++;
    }
    
    /* To make the hex always be 2-digit or 4-digit */
    if((d == 1) || (d == 3))
        d++;
    
    /* The digit being zero means the Number is zero. */
    if(d == 0)
    {
        str[0] = '0';
        str[1] = 'x';
        str[2] = '0';
        str[3] = '0';
        str[4] = '\0';
    }
    
    /* Convert the number into the relative string. */
    else
    {
        str[0] = '0';
        str[1] = 'x';
        
        for(int i=0; i<d; i++)
        {
            temp = x % power(16, d-i);
            temp /= power(16,d-i-1);
            Num[i] = temp;
            if(Num[i] < 10)
                str[i+2] = Num[i] + '0';
            else
                str[i+2] = Num[i] - 10  + 'A'; 
        }
        
        /* 无论是超出长度，还是遇到\0，都会使字符串终结。这样做有一个缺点，
             就是长度在最长的时候，会没有\0，没法判断终止。
             以后再改进。                                                   */
        if(d < 4)
            str[d+2] = '\0';
    }
}


/**
  * Brief: Convert char '0'~'9' and 'A'~'F' to the associated number.       
  */
unsigned short Char2Num(char c)
{
    unsigned short x;

    if(c >= '0' && c <= '9')
    {
        x = c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        x= c + 10 - 'A';
    }
    /* 这里应该有一个检错的机制，暂时不写了 */
    else
    {
        oPrint(">Error: This is not a char!");
    }
    
    return x;
}
/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/