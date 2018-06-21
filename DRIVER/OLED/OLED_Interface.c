/*******************************************************************************
 * Brief:   UI interface library, based on OLED library, run on STM8L15x
 * Author:	taotsi
 * Update:	2017.03.27
 *******************************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "OLED_Interface.h"


/* Variavbles -----------------------------------------------------------------*/
/* Private Variables ***********************************************************/
extern int oPointer = 0;
extern int oPointer_slide = 0;

static char oBuffer[oBuffSize][21];

extern uint8_t oProgPointer = 0;
extern uint8_t oProgSW = oProgSW_UnStarted;


/* Functions ------------------------------------------------------------------*/

/**
  * Brief:  Initialize the oInterface program.
  */
void oInterface_Init()
{
    /* oBuffer initialization */
    int i, j;
    for(i=0; i<oBuffSize; i++)
        for(j=0; j<21; j++)
        {
            oBuffer[i][j] = ' ';
        }

    /* Set oPointer to zero, aka the start of the oBuffer. */
    oPointer = 0;

    /* oProgBar Initialization */
    oProgPointer = 0;
}


/**
  *
  */
void oProgBar_Start()
{
    // well, there's no static_assert() in the IAR library, pity.
    //static_assert(oProgSW == oProgSW_UnStarted, "You have to END the previous oProgBar by using oProgBar_End() before starting a new one!");
    oProgSW = oProgSW_Running;

    uint8_t i = 0;

    oProgPointer = 0;

    OLED_Set_Pos(0, 0);
    for(i = 0; i < 128; i++)
        OLED_WrDat(0x81);
}


/**
  * param:  prog:  can be 0~128
  */
void oProgBar_Dis(uint8_t prog)
{
    // well, there's no static_assert() in the IAR library, pity.
    //static_assert(oProgSW == oProgSW_Running, "You have to START oProgBar by using oProgBar_Start() first!");

    uint8_t i = 0;

    if(prog > 128)
    {
        prog = 128;
    }

    if(prog > oProgPointer)
    {
        i = oProgPointer;
        OLED_Set_Pos(0, oProgPointer);
        while(i <= prog)
        {
            OLED_WrDat(0xBD);
            i++;
        }

        oProgPointer = prog;
    }
    
}


/**
  *
  */
void oProgBar_End()
{
    // well, there's no static_assert() in the IAR library, pity.
    //static_assert(oProgSW == oProgSW_Running, "No oProgBar running, no need to END nothing!");

    oProgSW = oProgSW_UnStarted;

    if(oProgPointer < 128)
    {
        OLED_Set_Pos(0, oPointer);
        while(oProgPointer <= 128)
        {
            OLED_WrDat(0xBD);
            oProgPointer++;
        }
    }

    oProgPointer = 0;
}


/**
  * Brief:  Display a String on the screen. The screen will roll automaticly.
  * Param:  string[]: String you want to display.
  *                     You can display 168 chars at most at a time, aka a whole
  *                     screen of chars.
  */
void oPrint(char* string)
{
    uint8_t i = 0;

    if(oPointer >= oBuffSize)
    {
        oPointer=0;
    }

    /* Initialize a temporary buffer with spaces. */
    char tempbuff[8][21];
    /* This is necessary. Or else there'll be garbage values in the buffer. */
    for(i = 0; i<168; i++)
    {
        *(tempbuff[0]+i) = ' ';
    }


    for(i = 0; *(string+i) != '\0' && i<168; i++)
    {
      *(tempbuff[0]+i) = *(string+i);
    }

    int npage = (i-1)/21+1;

    uint8_t j = 0;
    for(i = 0; i<npage; i++)
    {
        for(j=0; j<21; j++)
        {
            oBuffer[oPointer][j] = tempbuff[i][j];
        }
        oDisplay();
        oPointer++;
    }

}


/**
  * Brief:  This works like the printf().
  * Param:  str:    No need to explain.
  *                 %d, %X, %c and %s can be used.
  * Param:  ...:    No need to explain.
  * 注意： 字符串缓冲区有溢出风险。因为要检测是否溢出需要额外付出计算量，所以忽略这一问题了。
  *        因此字符串不应该过长。
  * 注意： 转换符不要用错，不要对不准。没有检错机制，会导致内存错乱。
  */
void oPrintf(char* str, ...)
{
    uint8_t i = 0;

    if(oPointer >= oBuffSize)
    {
        oPointer=0;
    }

    /* Initialize a temporary buffer with spaces. */
    char tempbuff[8][21];
    /* This is necessary. Or else there'll be garbage values in the buffer. */
    for(i = 0; i<168; i++)
    {
        *(tempbuff[0]+i) = ' ';
    }

    /* Pointer for variable argument list. */
    va_list parg;

    /* Initialize argument pointer. */
    va_start(parg, str);

    /* str pointer ahead */
    uint8_t str_ahd = 0;
    /* buff pointer ahead */
    uint8_t buff_ahd = 0;


    for(i = 0; *(str+i+str_ahd) != '\0' && (i+buff_ahd)<168; i++)
    {
        /* Trying to capture a conversion character. */
        if(*(str+i+str_ahd) == '%')
        {
            /* "%d" captured, means a 16-bit unsigned int in decimal form. */
            if(*(str+i+str_ahd+1) == 'd')
            {
                /* To store the current number */
                uint16_t tempNum = 0;
                /* To store the current number-converted string */
                char tempNumStr[6];

                /* str pointer jumps ahead. */
                str_ahd++;

                /* Get the current argument which should be a uint16_t type. */
                tempNum = va_arg(parg, uint16_t);

                /* Convert the current argument from a number to a string. */
                Num2Str(tempNum, tempNumStr);

                /* Copy the current number-converted string into the temporary buffer. */
                int k = 0;
                for(k = 0; (k<6) && (tempNumStr[k] != '\0'); k++)
                {
                    *(tempbuff[0]+i+buff_ahd + k) = tempNumStr[k];
                }

                /* buff pointer jumps ahead. */
                buff_ahd += (k-1);

            }

            /* "%X" captured, means a 16-bit unsigned int in hex form.*/
            else if(*(str+i+str_ahd+1) == 'X')
            {
                /* To store the current number */
                uint16_t tempNum = 0;
                /* To store the current number-converted string */
                char tempNumStr[6];

                /* str pointer jumps ahead. */
                str_ahd++;

                /* Get the current argument which should be a uint16_t type. */
                tempNum = va_arg(parg, uint16_t);

                /* Convert the current argument from a number to a string in Hex format. */
                NumX2Str(tempNum, tempNumStr);

                /* Copy the current number-converted string into the temporary buffer. */
                int k = 0;
                /* There are 4 digits at most for a 16-bit number, additionally with
                     an prefix of "0x", making it a 6-char string in total. */
                for(k = 0; (k<6) && (tempNumStr[k] != '\0'); k++)
                {
                    *(tempbuff[0]+i+buff_ahd + k) = tempNumStr[k];
                }

                /* buff pointer jumps ahead. */
                buff_ahd += (k-1);
            }

            /* %c captured, means a 8-bit char. */
            else if(*(str+i+str_ahd+1) == 'c')
            {
                /* To store the current char. */
                char tempChar = 'a';

                /* str pointer jumps ahead. */
                str_ahd++;

                /* Get the current argument which should be a char type. */
                /* It'll be fine even if the types are not the same.
                   But va_arg() does not accept uint8_t. */
                tempChar = va_arg(parg, uint16_t);

                /* Copy the current char into the temporary buffer. */
                *(tempbuff[0]+i+buff_ahd) = tempChar;
                // the codes below does not work.
                //*(tempbuff[0]+i+buff_ahd) = (uint8_t)va_arg(parg, uint16_t);

                /* buff pointer jumps ahead. */
                buff_ahd++;
            }

            /* %s captured, means a string. */
            else if(*(str+i+str_ahd+1) == 's')
            {
                /* To store the current string pointer. */
                char* tempStr;

                /* str pointer jumps ahead. */
                str_ahd++;

                /* Get the current argument which should be a char string poinger. */
                tempStr = va_arg(parg, char*);

                /* Copy the current string into the temporary buffer. */
                int k = 0;
                for(k = 0; k<42 && tempStr[k] != '\0'; k++)
                {
                    *(tempbuff[0]+i+buff_ahd + k) = *(tempStr+k);
                }

                /* buff pointer jumps ahead. */
                buff_ahd += (k-1);
            }

            /* Just a '%' captured without a conversion character behind it. */
            else
            {
                *(tempbuff[0]+i+buff_ahd) = '%';
            }
        }
        /* No "%d" captured. */
        else
        {
            *(tempbuff[0]+i+buff_ahd) = *(str+i+str_ahd);
        }
    }

    /* End variable argument process. */
    va_end(parg);


    /* Put all the stuff above on the screen.
       i+buff_ahd is the number of the chars in total*/
    int npage = (i + buff_ahd - 1)/21+1;

    uint8_t j = 0;
    for(i = 0; i<npage; i++)
    {
        for(j=0; j<21; j++)
        {
            oBuffer[oPointer][j] = tempbuff[i][j];
        }
        oDisplay();
        oPointer++;
    }
}


/**
  * Brief:  Display a Number on the screen. The screen will roll automaticly.
  * Param:  x: Number you want to display. It must be less than 65536.
  */
void oPrintNum(uint16_t x)
{
    char TempStr[6];
    Num2Str(x, TempStr);

    oPrint(TempStr);
}


/**
  * Brief:  Display the oBuffer according to the oPointer.
  */
void oDisplay(void)
{
    oDisplayPointer(oPointer);

    /* Every time the screen rolls because of new data input,
         oPointer_slide is reset equal to oPionter. */
    oPointer_slide = oPointer;
}


/**
  * Brief:  Display the oBuffer according to the oPointer_slide.
  * Note:   The current oPointer is actually bigger by 1 than the
  *           "real" pointer. That's because oPointer is incremented
  *           by one everytime oPrint90 has run. And program below
  *           uses the "real" pointer, which equals oPointer-1.
  * Note:   This function can work with an up key and a down key.
  *           Each time you press a key, the screen will scroll one row
  *           of chars. If you want to scroll more than one row each time,
  *           you have to set some logic switches to judge whether the up
  *           key or the down key is pressed.
  */
void oDisplay_slide(void)
{
    /* If oPointer_slide has been incremented bigger than oPointer,
         it must be reset equal to oPointer.                        */
    if(oPointer_slide == oPointer)
        oPointer_slide--;

    /* If oPointer_slide has been substracted to ("real"pointer+7-oBuffsize),
             is has reach the oldest record and mustn't be less any more. */
    if(oPointer > (oBuffSize-8))
    {
        /*
        if(oPointer_slide == -1)
          oPointer_slide = oBuffSize-1;
        */

        if(oPointer_slide == oPointer+6-oBuffSize)
            oPointer_slide++;
    }
    else
    {
        if(oPointer_slide == -1)
            oPointer_slide = oBuffSize-1;

        if(oPointer_slide == oPointer+6)
            oPointer_slide++;

        if(oPointer_slide == oBuffSize)
            oPointer_slide = 0;
    }


    oDisplayPointer(oPointer_slide);

}


/**
  * Brief:  Display the oBuffer according to the specified pointer.
  * Param:  pointer:  Pointer of the oBuffer. Can be from 0 to oBuffSize.
  */
void oDisplayPointer(int pointer)
{
    int i=0;
    if(pointer >= 8)
    {
        for(i=0;i<8;i++)
        {
          OLED_Dis_Str(i,0,oBuffer[pointer-7+i]);
        }
    }

    /* If pointer < Page, the function will display some of bottom strings
         in the oBuffer to make a circle. */
    else if(pointer < 8)
    {
        int n = 8-pointer;
        for(i=0;i<=n;i++)
        {
            OLED_Dis_Str(i,0,oBuffer[oBuffSize-n+i]);
        }
        for(i=0;i<=pointer;i++)
        {
            //OLED_Dis_Str(i+n,0,oBuffer[i]);
            OLED_Dis_Str(i+n-1,0,oBuffer[i]);
        }
    }
}


/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
