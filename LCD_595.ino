#include "lcd_74595_Energia.h"
void setup() {
  // put your setup code here, to run once:
  LCDinit();
  LCDgotoxy(0,0);
  LCDputs("    WELCOME     ");
  LCDgotoxy(0,1);
  LCDputs("    EVERYONE");
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
