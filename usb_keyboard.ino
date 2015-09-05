#include <TimerOne.h>

#define led 10
#define zat 300
#define OFF 0
#define ON  1
#define msec 100000

int cnt = 0;
int batcnt = 0;
static boolean mon = OFF;
static boolean power = OFF;

void setup() 
{
  pinMode(A0, INPUT); //Bat voltage
  pinMode(A2, INPUT); //PC Power
  pinMode(10, OUTPUT); //led
  
  pinMode(6, OUTPUT); // keypad rows
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  pinMode(2, INPUT); // keypad columns
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
  digitalWrite(2, HIGH); // pull-up on
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  
  Keyboard.begin();
  Serial.begin(9600);
  
  Timer1.initialize(msec); // init on 100ms
  Timer1.attachInterrupt(monitor_on_off); // 
  
}

int rows[]={9,8,7,6}; //keypad rows
int cols[]={5,4,3,2}; //keypad columns

char simbols[][2]={  {0,'1'}, {1,'2'}, {2,'3'}, {3,'A'},
	             {4,'4'}, {5,'5'}, {6,'6'}, {7,'B'},
	             {8,'7'}, {9,'8'}, {10,'9'},{11,'C'},
	            {12,'*'}, {13,'0'},{14,'#'},{15,'D'}
	          };

void loop() 
{
 for(int i=0;i<4;i++) 
 {    
   digitalWrite(rows[i], LOW); 
    for(int j=0;j<4;j++) 
      {  if(digitalRead(cols[j])==LOW)
         { 
          int s = 4*i+j;
          if ((s>=0&&s<=2)||(s>=4&&s<=6)||(s>=8&&s<=10)||s==13)
          {
            Keyboard.print(simbols[4*i+j][1]);
            delay(zat);
          }
          if (s==3)
          {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press('1'); // when 'A' press 'Ctrl+1'          
            delay(zat);
            Keyboard.releaseAll();
          }  
          if (s==7)
          {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press('2'); // when 'B' press 'Ctrl+2'          
            delay(zat);
            Keyboard.releaseAll();
          }  
          if (s==11)
          {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press('3'); // when 'C' press 'Ctrl+3'          
            delay(zat);
            Keyboard.releaseAll();
          }  
          if (s==15)
          {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press('4'); // when 'D' press 'Ctrl+4'          
            delay(zat);
            Keyboard.releaseAll();
          }  

          if (s==14)  
          {
            Keyboard.write(0x20);       // when '#' press 'Space'
            delay(zat);
          }
          if (s==12) 
          {
            Keyboard.write(KEY_RETURN); // when '*' press 'Enter'
            delay(zat);
          }
         }
      }
 digitalWrite(rows[i], HIGH);  
 }
}

void monitor_on_off() 
{
  batcnt++;
  if(batcnt==10)
  {
    int BatVolt = analogRead(A0);
    Serial.println(BatVolt);
    batcnt=0;
  }
  if((digitalRead(A2)==HIGH)&&(!power))
  {
    power = ON;
    mon = ON;
  }
  if((digitalRead(A2)==LOW)&&(power))
  {
    power = OFF;
    mon = ON;
  }
  if (mon) cnt++;
  if (cnt == 10) digitalWrite(led, HIGH);
  if (cnt == 20)
  {
     cnt = 0;
     digitalWrite(led, LOW);
     mon = OFF;
  }
  
  
}

