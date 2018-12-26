
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h> 


#define Password_Length 8 

int signalPin = 12;

char Data[Password_Length]; 
char Master[Password_Length] = "1234567"; 
int data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo myservo;          
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int pos = 0;            
String pass = "";
int a ;

void setup()
{
  Serial.begin(9600);
  myservo.attach(10); 
  myservo.write(pos);
    
  lcd.init(); 
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
}


void loop()
{   

  lcd.setCursor(0,0);
  lcd.print("Enter Password:");

  customKey = customKeypad.getKey();
  if (customKey){
    lcd.clear();
    Data[data_count] = customKey; 
    lcd.setCursor(0,1); 
    lcd.print(String(Data)); 
    data_count++; 
    }

  if(data_count == Password_Length-1){
  
    lcd.clear();
    Serial.println(Data);
    Serial.println("Sama");
    Serial.println(Master);

    if(!strcmp(Data, Master)){
      lcd.print("Correct");
        while(pos < 180)
        {
          myservo.write(pos);
          delay(15);  
          pos = pos + 1;  
          //Serial.println(pos);
        } 
        delay(6000);
        data_count = 0;
        while(!(pos == 0))
        {
          myservo.write(pos);
          delay(15);  
          pos = pos - 1;  
          //Serial.println(pos);
        } 
      }
    else{
      lcd.print("Incorrect");
      delay(1000);
     }
  }
    
}
