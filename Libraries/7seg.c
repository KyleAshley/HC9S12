/******************************************************************************/
// 7SEG FUNCTIONS
// Author: Kyle Ashley
// To be used with MC9S12 uP
/******************************************************************************/
#include "7seg.h"
#include <hidef.h>          /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
/******************************************************************************/
// PRE: NONE
// POST: seven-segment display is configured to be written to
// (Common Anode)
/******************************************************************************/
void sev_setup(void)
{
    DDRH = 0xFF;        // Configure PTH for Output
}

/******************************************************************************/
// PRE: NONE
// POST: Character is written to the seven-segment display (if applicable)
// (Common Anode)
/******************************************************************************/
void sev_write(char symbol)
{
    // NUMERIC?
    if(symbol >= 48 && symbol <= 57)
        switch (symbol)
        {
            case '0':
                PTH = 0x40;
                break;
            case '1':
                PTH = 0x79;
                break;
            case '2':
                PTH = 0x24;
                break;
            case '3':
                PTH = 0x30;
                break;
            case '4':
                PTH = 0x19;
                break;
            case '5':
                PTH = 0x12;
                break;
            case '6':
                PTH = 0x02;
                break;
            case '7':
                PTH = 0x78;
                break;
            case '8':
                PTH = 0x00;
                break;
            case '9':
                PTH = 0x10;
                break;
        }
        // ALPHABETICAL
        else
        {
            if(symbol == 'a' || symbol == 'A')
                PTH = 0x08;
            else if(symbol == 'b' || symbol == 'B')
                PTH = 0x03;
            else if(symbol == 'c')
                PTH = 0x27;
            else if(symbol == 'C')
                PTH = 0x46;
            else if(symbol == 'd' || symbol == 'D')
                PTH = 0x21;
            else if(symbol == 'e' || symbol == 'E')
                PTH = 0x06;
            else if(symbol == 'f' || symbol == 'F')
                PTH = 0x0E;
            else if(symbol == 'h')
                PTH = 0x0B;
            else if(symbol == 'H')
                PTH = 0x09;
            else if(symbol == 'l')
                PTH = 0x4F;
            else if(symbol == 'L')
                PTH = 0x47;
            else if(symbol == 'n' || symbol == 'N')
                PTH = 0x2B;
            else if(symbol == 'o' || symbol == 'O')
                PTH = 0x23;
            else if(symbol == 'p' || symbol == 'P')
                PTH = 0x0E;
            else if(symbol == 'q' || symbol == 'Q')
                PTH = 0x18;
            else if(symbol == 'r' || symbol == 'R')
                PTH = 0x2F;
            else if(symbol == 'u')
                PTH = 0x63;
            else if(symbol == 'U')
                PTH = 0x41;
            else if(symbol == 'y' || symbol == 'Y')
                PTH = 0x11;

            // Default NOT A LETTER, write blank
            else
            PTH = 0x7F;
        }
        delay_LCD_SCROLL(1);
}

/******************************************************************************/
// PRE: NONE
// POST: Tests Segments by displaying all characters
// (Common Anode)
/******************************************************************************/
void sev_test()
{
   sev_setup();
   sev_write('0');
   delay_LCD_SCROLL(5);
   sev_write('1');
   delay_LCD_SCROLL(5);
   sev_write('2');
   delay_LCD_SCROLL(5);
   sev_write('3');
   delay_LCD_SCROLL(5);
   sev_write('4');
   delay_LCD_SCROLL(5);
   sev_write('5');
   delay_LCD_SCROLL(5);
   sev_write('6');
   delay_LCD_SCROLL(5);
   sev_write('7');
   delay_LCD_SCROLL(5);
   sev_write('8');
   delay_LCD_SCROLL(5);
   sev_write('9');
   delay_LCD_SCROLL(5);

   sev_write('a');
   delay_LCD_SCROLL(5);
   sev_write('b');
   delay_LCD_SCROLL(5);
   sev_write('c');
   delay_LCD_SCROLL(5);
   sev_write('d');
   delay_LCD_SCROLL(5);
   sev_write('e');
   delay_LCD_SCROLL(5);
   sev_write('f');
   delay_LCD_SCROLL(5);
   sev_write('h');
   delay_LCD_SCROLL(5);
   sev_write('L');
   delay_LCD_SCROLL(5);
   sev_write('n');
   delay_LCD_SCROLL(5);
   sev_write('o');
   delay_LCD_SCROLL(5);
   sev_write('p');
   delay_LCD_SCROLL(5);
   sev_write('q');
   delay_LCD_SCROLL(5);
   sev_write('r');
   delay_LCD_SCROLL(5);
   sev_write('u');
   delay_LCD_SCROLL(5);
   sev_write('y');
   delay_LCD_SCROLL(5);
}


