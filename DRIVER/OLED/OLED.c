/*******************************************************************************
 * Brief:   OLED library based on SSD1306, run on STM8L152x
 * Author:  Taotsi
 * Origin:  Internet
 * Update:	2017.04.05
 * Note:    This driver is not complete. For more commands, see SSD1306 datasheet.
 *******************************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "OLED.h"
#include "SPIsim.h"
#include "OLED_font.h"
#include "BSP.h"
//note: H files above must be included in OLED.c. 
//      It won't work if they are included in BSP.h.


/* Functions ------------------------------------------------------------------*/

/* High layer functions ********************************************************/

/**
  * Brief:  Initialize the OLED. Refer to SSD1306 datasheet. 
  */
void OLED_Init(void)
{
    SPI_OLED_RST_L();    // Reset the OLED
    Delay_ms(100);       // waiting for reset
    SPI_OLED_RST_H();
    
    OLED_WrCmd(0xae);    // Turn off the OLED
    OLED_WrCmd(0x00);    // Set low column address
    OLED_WrCmd(0x10);    // Set high column address
    OLED_WrCmd(0x40);    // Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd(0x81);    // Set contrast control register
    OLED_WrCmd(0xff);    // Set SEG Output Current Brightness
    OLED_WrCmd(0xa1);    // Set SEG/Column Mapping       0xa0左右反置 0xa1正常
    OLED_WrCmd(0xc8);    // Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WrCmd(0xa6);    // Set normal display
    OLED_WrCmd(0xa8);    // Set multiplex ratio(1 to 64)
    OLED_WrCmd(0x3f);    // 1/64 duty
    OLED_WrCmd(0xd3);    // Set display offset Shift Mapping RAM Counter
    OLED_WrCmd(0x00);    // Not offset
    OLED_WrCmd(0xd5);    // Set display clock divide ratio/oscillator frequency
    OLED_WrCmd(0x80);    // Set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrCmd(0xd9);    // Set pre-charge period
    OLED_WrCmd(0xf1);    // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrCmd(0xda);    // Set com pins hardware configuration
    OLED_WrCmd(0x12);
    OLED_WrCmd(0xdb);    // Set vcomh
    OLED_WrCmd(0x40);    // Set VCOM Deselect Level
    OLED_WrCmd(0x20);    // Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd(0x02);    //
    OLED_WrCmd(0x8d);    // Set Charge Pump enable/disable
    OLED_WrCmd(0x14);    // Set(0x10) disable
    OLED_WrCmd(0xa4);    // Disable Entire Display On (0xa4/0xa5)
    OLED_WrCmd(0xa6);    // Disable Inverse Display On (0xa6/a7)
    OLED_WrCmd(0xaf);    // Turn on oled panel
    
    OLED_Clear();        // Clear the screen
}


/**
  * Brief:  Display a 6px*8px char from a font library.
  * Param:  page:   Indicates the row position where you want to put the char.
  *                   It can be from 0 to 7. 
  * Param:  colomn: Indicates the column position where you want to put the char.
  *                   It can be from 0 to 127.
  * Param:  ch:     The char you want to display.
  */
void OLED_Dis_Char(uint8_t page, uint8_t column, char ch)
{
    uint8_t j = 0;
    uint16_t pos = 0;
    
    if (ch < ' ')
        return;

    pos = 6 * (ch-' ');
    OLED_Set_Pos(page, column);
    for (j=0; j<6; j++)     
    {
        OLED_WrDat(Font6x8[pos++]);
    }
}


/**
  * Brief:  Display a 6px*8px char from a font library, in REVERSE type.
  * Param:  page:   Indicates the row position where you want to put the char.
  *                   It can be from 0 to 7. 
  * Param:  colomn: Indicates the column position where you want to put the char.
  *                   It can be from 0 to 127.
  * Param:  ch:     The char you want to display.
  */
void OLED_Dis_Char_Rev(uint8_t page, uint8_t column, char ch)
{
    uint8_t j = 0;
    uint16_t pos = 0;
    
    if (ch < ' ')
        return;

    pos = 6 * (ch-' ');
    OLED_Set_Pos(page, column);
    for (j=0; j<6; j++)     
    {
        /* All the font data are reversed. */
        OLED_WrDat(~(Font6x8[pos++]));
    }
}


/**
  * Brief:  Display a string using 6px*8px chars.
  * param:  page:   Indicates the row position where you want to put the string.
  *                   It can be from 0 to 7.
  * Param:  comume: Indicates the column position where you want to put the string.
  *                   It can be from 0 to 127.
  *                 Note that the chars beyond the screen row of the string 
  *                   will be cut off.
  * Param:  *str:   Pointer of the string you want to display.
  * 注意，这个函数仅适合起始位置为0的字符串显示！需要改进
  */
void OLED_Dis_Str(uint8_t page, uint8_t column, char *str)
{
    int i = 0;
    
    while (*str != '\0')
    {
        /* Chars beyond the screen row of the string will be cut off. */
        if(i<21)
        {
            OLED_Dis_Char(page, column+1, *str++);
            column += 6;
            i++;
        }
        else
            break;
    }
    
    /* Fill the same page where there are no chars written with blank. */
    if(i<21)
    {
        for(int j=i; j<21; j++)
        {
            OLED_Dis_Char(page, column+1, ' ');
            column += 6;
        }
    }
    
    /* Within 128px in each row 21 chars can be put at most. And the rest
         two pixels aka the first and the last will be filled with blank. */
    OLED_Set_Pos(page, 127);
    OLED_WrDat(0x00);
    OLED_Set_Pos(page, 0);
    OLED_WrDat(0x00);
}


/**
  * Brief:  Display a string using 6px*8px chars, in REVERSE type.
  * param:  page:   Indicates the row position where you want to put the string.
  *                   It can be from 0 to 7.
  * Param:  comume: Indicates the column position where you want to put the string.
  *                   It can be from 0 to 127.
  *                 Note that the chars beyond the screen row of the string 
  *                   will be cut off.
  * Param:  *str:   Pointer of the string you want to display.
  * 注意，这个函数仅适合起始位置为0的字符串显示！需要改进
  */
void OLED_Dis_Str_Rev(uint8_t page, uint8_t column, char *str)
{
    int i = 0;
    int col = 0;
    
    /* Within 128px in each row 21 chars can be put at most. 
       Fill the first column which will never be used if the tring
         does not start to display on the first column, with blank. */
    OLED_Set_Pos(page, 0);
    OLED_WrDat(0x00);
    
    /* Add an extra 8px column white to the start of the string. */
    //OLED_Set_Pos(page, column);
    //OLED_WrDat(0xFF);
    
    while (*str)
    {
        /* Chars beyond the screen row of the string will be cut off. */
        if(i<21)
        {
            /* All the chars are reversed. */
            OLED_Dis_Char_Rev(page, column+1, *str++);
            column += 6;
            i++;
        }
        else
            break;
        /* Used to add an extra 8px column white to the end of the string. */
        col = column+1;
    }
    
    /* Fill the same page where there are no chars written with blank. */
    if(i<21)
    {
        for(int j=i; j<21; j++)
        {
            OLED_Dis_Char(page, column+1, ' ');
            column += 6;
        }
        /* Within 128px in each row 21 chars can be put at most. 
           Fill the 127th column which will never be used if the number
             of the chars is less than 21, with blank.                  */
        OLED_Set_Pos(page, 127);
        OLED_WrDat(0x00);
    }
    
    /* Add an extra 8px column white to the end of the string. */
    //OLED_Set_Pos(page, col);
    //OLED_WrDat(0xFF);
}


/**
  * Brief:  Display a 128*64 picture with data written in a one-dimension
  *           array with 8192 chars in it.
  * Param:  *data:  Where the picture data is stored.
  */
void OLED_Dis_Pic(uint8_t* data)
{
    int i=0;
    for(int page=0; page<8; page++)
    {
        OLED_Set_Pos(page, 0);
        for(int col=0; col<128; col++)
        {
            OLED_WrDat(data[i++]);
        }
    }
}


/* Low layer functions *********************************************************/

/**
  * Brief:  Set the start position for page addressing mode.
  * Param:  page:   Set the start page position.
  *                   It can be from 0 to 7.
  * Param:  column: Set the start column position.
  *                   It can be from 0 to 127.
  */
void OLED_Set_Pos(uint8_t page, uint8_t column)
{
    OLED_WrCmd(0xb0 | (page&0x07));
    OLED_WrCmd(0x10 | ((column>>4)&0x0F)); // higher nibble of the column start address
    OLED_WrCmd(column & 0x0F);             // lower nibble of the column start address
}


/**
  * Brief:  Write command to OLED.
  * Param:  data: command to write.
  */
void OLED_WrCmd(uint8_t cmd)
{
    SPI_OLED_DC_CMD();
    
    SPI_OLED_CSN_L();
    SPI_ExchangeByte(cmd);
    SPI_OLED_CSN_H();
}


/**
  * Brief:  Write data to OLED.
  * Param:  data: data to write.
  */
void OLED_WrDat(uint8_t data)
{
    SPI_OLED_DC_DATA();
    
    SPI_OLED_CSN_L();
    SPI_ExchangeByte(data);
    SPI_OLED_CSN_H();
}


/**
  * Brief:  Clear the screen up.
  */
void OLED_Clear(void)
{
    for(int page=0; page<8; page++)
    {
        OLED_Set_Pos(page, 0);
        for(int col=0; col<128; col++)
        {
            OLED_WrDat(0x00);
        }
    }
    
    /*
    uint8_t y, x;
    for(y=0; y<8; y++)
    {
        OLED_WrCmd(0xb0 + y);
        OLED_WrCmd(0x01);
        OLED_WrCmd(0x10);
        for (x=0; x<128; x++)
        OLED_WrDat(0x00);
    }
    */
}


/**
  * Brief:  Display a snow screen for fun and for test purpose.
  */
void OLED_Dis_snow(void)
{
    for(int page=0; page<8; page++)
    {
        OLED_Set_Pos(page, 0);
        for(int col=0; col<126; col++)
        {
            OLED_WrDat(rand());
        }
    }
}

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/