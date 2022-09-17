union reg {
    struct bit {
          unsigned char b0:1;  
          unsigned char b1:1;    
          unsigned char b2:1; 
          unsigned char b3:1;
          unsigned char b4:1;
          unsigned char b5:1;
          unsigned char b6:1;
          unsigned char b7:1;
              }_BIT;
          unsigned char _BYTE;
};
union reg* _P2_DIR = (union reg*)0x2A ;
union reg* _P2_OUT = (union reg*)0x29 ;
union reg* _P2_IN  = (union reg*)0x28 ;
union reg* _P1_DIR = (union reg*)0x22 ;
union reg* _P1_OUT = (union reg*)0x21 ;
union reg* _P1_IN  = (union reg*)0x20 ;

/*  Three Wire LCD Interface using 74HC595*/

//Define 74HC595 Connections with msp430
#define Clock_dir (_P1_DIR->_BIT.b0) 
#define Data_dir (_P1_DIR->_BIT.b1)
#define Latch_dir (_P1_DIR->_BIT.b2)

#define Clock (_P1_OUT->_BIT.b0) 
#define Data (_P1_OUT->_BIT.b1)
#define Latch (_P1_OUT->_BIT.b2)

void LCDinit(void);
void LCDSendByte(char d,char RS);
void LCDgotoxy(unsigned char col, unsigned char row);
void LCDputs(const char* s);
void LCDclear(void);
void LCD2n(unsigned char x);
void ShiftData(char temp);
void LCD1n(unsigned char x);



//=============================================================
//             Send Data or Command to LCD
//=============================================================
void LCDSendByte(char d,char RS)
{
  char dH,dL,temp;
  //Keep Data on upper nybble
  dH = d & 0xF0;         //Get MSB
  dL = d & 0x0F;
  dL = d << 4;           //Get LSB
//Send MSB with E=clock  
  temp=0;
  temp=dH | RS | 0x02;  //MSB With RS+E bit
  ShiftData(temp);
//Send MSB with E=0
  temp=0;
  temp=dH | RS;  //MSB With RS bit
  ShiftData(temp);
//Send LSB with E=clock
  temp=0;
  temp=dL | RS | 0x02;  //MSB With RS+E bit
  ShiftData(temp);
//Send LSB with E=0
  temp=0;
  temp=dL | RS;  //MSB With RS bit
  ShiftData(temp);  
}
//=============================================
void ShiftData(char temp)
{
  int i;
  for(i=0;i<8;i++)      
  {
    if((temp & 0x80)==0x80)    //Send 1-bit to shift register
    {Data = 1;}
    else
    {Data = 0;}
          
    Clock = 0;
    Clock = 1;
    temp=temp<<1;
  }
  //Latch the data
  Latch = 0;
  __delay_cycles(1000);
  Latch = 1;        
}
//=================================================================
//           LCD Display Initialization Function
//=================================================================
void LCDinit()
{
  Clock_dir = 1;
  Data_dir = 1;
  Latch_dir = 1;
  int count;
  char t[]={0x43,0x03,0x03,0x02,0x28,0x01,0x0C,0x06,0x02,0x02};    
      for (count = 0; count <= 9; count++)
      {
        LCDSendByte(t[count],0);    //Command RS=0
      }
}
//=================================================================
//        Display Line on LCD at desired location Function
//=================================================================

void LCDgotoxy(unsigned char col, unsigned char row)
{
    unsigned char address;

    if(row!=0)
        address=0x40;
    else
        address=0;

    address += col;
    LCDSendByte(0x80|address,0);
    __delay_cycles(2000);    
}
void LCDputs(const char* s)
{
    while(( s!=0) &&(*s !=0))
  {
    LCDSendByte(*s,1);
    s++;
  }
}
void LCDputc(char c)
{
      LCDSendByte(c,1);
}
void LCDclear(void)
{
    LCDSendByte(0x01,0); 
    LCDSendByte(0x02,0);        // display off
    __delay_cycles(2000);   
}
void LCD2n(unsigned char x)
{
  LCDputc((x/10)+48);
  LCDputc((x%10)+48);
}
void LCD1n(unsigned char x)
{
  LCDputc((x%10)+48);
}
//=================================================================
