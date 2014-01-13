/******************************************************************************/
// 7SEG FUNCTIONS
// Author: Kyle Ashley
// To be used with MC9S12 uP
/******************************************************************************/

void sev_setup(void);           // configures 7seg
void sev_write(char);           // writes any applicable char to the 7seg display
void sev_test(void);            // runs through all possible characters to test segments
