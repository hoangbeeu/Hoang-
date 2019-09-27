#include <Main.h>
#include <stdio.h>
#define SH_CP(x) output_bit(PIN_D0,x)
#define DS(x) output_bit(PIN_D1,x)
#define ST_CP(x) output_bit(PIN_D2,x)
#define CLK(x) output_bit(PIN_D3,x)
#define SH_LD(x) output_bit(PIN_D4,x)

#define XUNG_DICH { SH_CP(0);SH_CP(1);}
#define XUNG_CHOT { ST_CP(0);ST_CP(1);}
unsigned char  outBuffer595[3] = {0};
unsigned int8 arrayInput[2]={0};
int t=0;
typedef enum
{
   OUT_Led_Light1 = 0x00,
   OUT_IRTransmitter1,
   OutLock1,
   OutLight2,
   OUT_IRTransmitter2,
   OutLock2,
   OutLight3,
   OUT_IRTransmitter3,
   OutLock3,
   OutLight4,
   OUT_IRTransmitter4,
   OutLock4,
   OutLight5,
   OUT_IRTransmitter5,
   OutLock5,
   OutLight6,
   OUT_IRTransmitter6,
   OutLock6,
   OutLight7,
   OUT_IRTransmitter7,
   OutLock7,
   OutLight8,
   OUT_IRTransmitter8,
   OutLock8,
   
}outputnam_t;

void HC595_Outbit(outputnam_t index, int status)
{
   /* Thay doi trang thai byte */
   if(status == 0x00)
   {
      outBuffer595[index / 8] = outBuffer595[index / 8] & ~(0x01 << (index % 8));
   }
   else if(status == 0x01)
   {
      outBuffer595[index / 8] = outBuffer595[index / 8] |(0x01 << (index % 8));
   }
   else if(status == 0x02)
   {
      outBuffer595[index / 8] = outBuffer595[index / 8] ^=(0x01 << (index % 8));
   }
   for(int j = 0; j < 3; j++)
   {
      int a = outBuffer595[2-j];
      for(int i=0; i<8; i++)
      {
         DS(a&(0b10000000>>i));
         SH_CP(0);
         SH_CP(1);
      }
   
   }
   ST_CP(0); 
   ST_CP(1);

}
// Chuyen cac gia tri chua co di
void setUp()
{  SH_LD(0);
   SH_LD(1);

   for(int j=0;j<8;j++)
   {
      CLK(0);
      CLK(1);
   }
}
// Doc gia tri dau vao
void readInput()
{  SH_LD(0);
   SH_LD(1);
   for(int i=0;i<16;i++)
      {
         if(input(PIN_D5)==1)
         { 
            arrayInput[i/8] |= (0x01 << (i % 8));
            
         }
         else 
         { 
            arrayInput[i / 8] &=  ~(0x01 << (i % 8));
            
         }
      CLK(0);
      CLK(1);
      }
   for(int j=0;j<2;j++)
   {
      char str[80];
      sprintf(str, "Gia tri la = %x", arrayInput[j]);
      puts(str);
   }
   
   SH_LD(0);
   SH_LD(1);
}
void testButton()
{  
  if(input(PIN_B4)==0) 
  {
     delay_ms(1);
     if(input(PIN_B4)==0)
            {
               t++;
            }
     else{ t=0;}
    if(t=10)
    {
      t=0;
      puts("Da on dinh");
      while(input(PIN_B4)==0);
    }
  }
}    
   
void Keypad_Process()
{

}
#INT_RDA
void  RDA_isr(void) 
{
char c;
c=getc();
putc(c);


}


void main()
{  
   

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

    
    //setUp();
    HC595_Outbit(4, 1);
    HC595_Outbit(5, 1);
    HC595_Outbit(6, 1);
    HC595_Outbit(7, 1);
    HC595_Outbit(8, 1);
   while(TRUE)
   {
    readInput();
    testButton();
   }
}





