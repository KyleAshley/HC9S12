/****************************************************************************/
// delays.h
// Author: Kyle Ashley
// Description: Delay functions used for HC9S12 uProccessor
/****************************************************************************/
#ifndef DELAYS_H_
#define DELAYS_H_

void delay_LCD_TH(unsigned int num);      // ACTUAL =41 ns per 'num + Overhead
void delay_LCD_PWEH(unsigned int num);    // ACTUAL = 458 ns per 'num' + Overhead
void delay_LCD_TAS(unsigned int num);     // ACTUAL = 167 ns per 'num' + Overhead
void delay_LCD_DATA(unsigned int num);    // ACTUAL = (40us per 'num' + Overhead) = 40 us
void delay_LCD_SCROLL(unsigned int num);  // 43 ms per 'num' + Overhead
void delay_us(unsigned int num);       // ACTUAL = (1.33 us per 'num' + Overhead) = 1.33 us
void delay_ms(unsigned int num);       // ACTUAL = 1.33 ms per 'num' + Overhead

#endif
