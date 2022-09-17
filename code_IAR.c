
#include "io430.h"
#include "lcd_74595_IAR.h"
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  LCDinit();
  LCDgotoxy(0,0);
  LCDputs("    WELCOME     ");
  LCDgotoxy(4,1);
  LCD2n(22);
  
}
