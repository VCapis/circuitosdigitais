#include <Wire.h>
#include <MCP23017.h>


#define END_12 6
#define END_0 0
#define END_1 1
#define END_2 2
#define END_3 3
#define END_4 4
#define END_5 5
#define END_6 6
#define END_7 7
#define END_8 8
#define END_9 9
#define END_10 10
#define END_11 11

#define D0 12
#define D1 13
#define D2 14
#define D3 15
#define D4 2
#define D5 3
#define D6 4
#define D7 5


#define int8 char


// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)

// Input #0 is on pin 21 so connect a button or switch from there to ground

MCP23017 mcp;
 
 
void  habilita_leitura ()
{
     digitalWrite(END_12, HIGH);

}
void  desabilita_leitura ()
{
     digitalWrite(END_12, LOW);
}

unsigned char le_dados ()
{ 
    unsigned char dados=0;
    
    dados = (digitalRead(D7)<<7)| (digitalRead(D6)<<6) | (digitalRead(D5)<<5) |  (digitalRead(D4)<<4) | (mcp.digitalRead(D3)<<3) | (mcp.digitalRead(D2)<<2) | (mcp.digitalRead(D1)<<1) | mcp.digitalRead(D0) ;
    return dados;
}
  
void setup() {  
  
  Serial.begin(115200);
  mcp.begin();      // use default address 0

  mcp.pinMode(END_0, OUTPUT);
  mcp.pinMode(END_1, OUTPUT);
  mcp.pinMode(END_2, OUTPUT);
  mcp.pinMode(END_3, OUTPUT);
  mcp.pinMode(END_4, OUTPUT);
  mcp.pinMode(END_5, OUTPUT);
  mcp.pinMode(END_6, OUTPUT);
  mcp.pinMode(END_7, OUTPUT);
  
  mcp.pinMode(END_8,  OUTPUT);
  mcp.pinMode(END_9,  OUTPUT);
  mcp.pinMode(END_10, OUTPUT);
  mcp.pinMode(END_11, OUTPUT);
  
  mcp.pinMode(D0, INPUT);
  mcp.pinMode(D1, INPUT);
  mcp.pinMode(D2, INPUT);
  mcp.pinMode(D3, INPUT);
  
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(END_12, OUTPUT);
  

  
 // mcp.pullUp(0, HIGH);  // turn on a 100K pullup internally

 
}



void endereco(int v)
{
     mcp.digitalWrite(END_0,v & 1);
     mcp.digitalWrite(END_1,(v >> 1) & 1);
     mcp.digitalWrite(END_2,(v >> 2) & 1);
     mcp.digitalWrite(END_3,(v >> 3) & 1);
     mcp.digitalWrite(END_4,(v >> 4) & 1);
     mcp.digitalWrite(END_5,(v >> 5) & 1);
     mcp.digitalWrite(END_6,(v >> 6) & 1);
     mcp.digitalWrite(END_7,(v >> 7) & 1);
     
     mcp.digitalWrite(END_8,(v >> 8) & 1);
     mcp.digitalWrite(END_9,(v >> 9) & 1);
     mcp.digitalWrite(END_10,(v >> 10) & 1);
     mcp.digitalWrite(END_11,(v >> 11) & 1);

}
int dados;
int x;
unsigned char c;

void loop()
{
   unsigned char a='x';
   

   while (a!= 'A')
   {
      if (Serial.available()>0)   a = Serial.read();
   }
   for (x=0;x<4095;x++)
   {
      desabilita_leitura();
      endereco(x);
      habilita_leitura();
      c=le_dados();
      desabilita_leitura();
      Serial.write(c);
    
   }
   for (;;);
}
