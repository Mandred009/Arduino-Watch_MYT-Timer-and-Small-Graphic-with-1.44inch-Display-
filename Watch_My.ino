#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

const char mandred[7]="MANDRED";
//paramters define
#define MODEL ST7735S128
#define CS   A5
#define CD   A3
#define RST  A4
#define SDA  11
#define SCK  13
#define LED  A0   //if you don't need to control the LED pin,you should set it to -1 and set it to 3.3V

//the definiens of software spi mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_SPI mylcd(MODEL,CS,CD,-1,SDA,RST,SCK,LED); //model,cs,dc,sdo,sda,reset,sck,led

const int buzzer=2;
const int touch=8;
const int button=4;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int touchValue;
int buttonPress;
int c=0;
int state=0;
void setup() 
{
  pinMode(touch,INPUT);
  pinMode(button,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(1200);
  mylcd.Init_LCD();
  mylcd.Fill_Screen(WHITE);
  Mandredintro();
}

void loop() 
{
  touchValue=digitalRead(8);
  buttonPress=digitalRead(4);
  Serial.println(state);
  if(buttonPress==0)
  {
    state+=1;
  }
  if(state>=1 && state<=7)
  {
      
      //Serial.print("PRESSED");
      Timer();
    
  }
}
void Mandredintro()
{
  mylcd.Set_Text_Back_colour(WHITE);
  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Size(5);
  for(int i=0;i<strlen(mandred);i++)
  {
    mylcd.Print_String(String(mandred[i]), 52, 32);
    delay(500);
  }
  mylcd.Set_Text_Size(3);
  mylcd.Fill_Screen(WHITE);
  mylcd.Set_Draw_color(BLUE);
  for(int i=3;i<=100;i=i+2)
  {
    mylcd.Draw_Circle(65,65,i);
    delay(50);
  }
  mylcd.Print_String(mandred, 2, 45);
}
void buzz()
{
  tone(buzzer,2000);
  delay(1000);
  noTone(buzzer);
  delay(1000);
}

void Timer()
{
    if (touchValue==1)
  {
    c=c+1;
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(3);
    mylcd.Print_String(String(c), 55, 45);
    
  } 
  if (buttonPress==0)
  {
    mylcd.Fill_Screen(WHITE);
    while(c>0)
    {
      Serial.println("EACH");
      mylcd.Set_Text_Back_colour(WHITE);
      mylcd.Set_Text_Size(2);
      mylcd.Set_Text_colour(RED);
      mylcd.Print_String("Timer Start", 0, 0);
      mylcd.Set_Text_colour(GREEN);
      mylcd.Set_Text_Size(3);
      mylcd.Print_String(String(c)+" min", 32, 45);
      delay(60000);
      c=c-1;
      mylcd.Print_String(String(c)+" min", 32, 45);
    }
    buzz();
  }
}
