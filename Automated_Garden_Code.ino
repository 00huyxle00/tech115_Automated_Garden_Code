// Majority of the code is written by Huy Le
// YL-69 and LM393 Moisture Sensor
int water_Sensor_Pin = A0; // Soil Sensor input at Analog PIN A0
int output_value;

// Pump Input
const int water_Pump_Pin = 4;

//Setup for the Thermistor
const int ThermistorPin = 1;
int Vo;
float R1 = 100000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//All of LED Setup
const int Yellow_LED = 7;
const int Red_LED = 8;
const int Green_LED = 12;

//StartButton Setup
int buttonState = 0;
int buttonTemp = 0; 
const int startButtonPin = 13; 

//DHT Temperature Hudmidity Sensor Setup
#include "DHT.h"
#define Type DHT11 //Version type of DHT using
int sensePin = 2;
DHT HT(sensePin, Type);
float humidity;
float tempC;
float tempF;

void setup() {

  //Hudmidity and Temperature Sensor Setup
  Serial.begin(9600);//open serial and set the baudrate
  delay(1000);//Wait before accessing Sensor
  HT.begin(); //Begins reading the Humidity 

  //Button Setup
  buttonState = digitalRead(startButtonPin); //Boolean the button State to False
  pinMode(startButtonPin, OUTPUT); //Make Button an Output

  //Pump Setup
  pinMode(water_Pump_Pin,OUTPUT);
  
  //LED Setup
  pinMode(Yellow_LED,OUTPUT);
  pinMode(Green_LED,OUTPUT);
  pinMode(Red_LED,OUTPUT);
}

void loop() {

//Temperature and Humidity Code
   humidity = HT.readHumidity(); 
   tempF = HT.readTemperature(true); // True means it will read F 
   tempC = HT.readTemperature(); // False means it will read C
   buttonState = digitalRead(startButtonPin);
   buttonTemp = LOW;

  //Green LED Which is heat lamp turns on if TemperatureF is not set to the ideal temperature
  if (tempF >= 70 && tempF <= 80){
    digitalWrite(Green_LED, HIGH);
  }
  else{
    digitalWrite(Green_LED, LOW);
  }
   
   // When the Start Button is Pressed
   if (buttonState == HIGH ){
    buttonState == HIGH;
    while (buttonState == HIGH){
        //Display Hudmidity and Temperature
   
     if (buttonState == HIGH){
     Serial.print("Current humidity = ");
     Serial.print(humidity);
     Serial.print("%  ");
     Serial.println();
     Serial.print("Temp F= ");
     Serial.print(tempF);
     Serial.print("%  ");
     Serial.println();
     Serial.print("Temp C= ");
     Serial.print(tempC);
     Serial.print("%  ");
     Serial.println();
     digitalWrite(Yellow_LED, HIGH);
      
      
     //Pump the water if the moisture is too low
     output_value = analogRead(water_Sensor_Pin);
     output_value = map(output_value,550,10,0,100);
     Serial.print("Mositure : ");
     Serial.print(output_value);
     Serial.println("%");
     if(output_value < 0){
          digitalWrite(water_Pump_Pin,HIGH);
          digitalWrite(Red_LED, HIGH);
     }
     else{
          digitalWrite(water_Pump_Pin,LOW);
          digitalWrite(Red_LED, LOW);
     }
     delay (3000);
     buttonTemp = digitalRead(startButtonPin);
     if (buttonTemp == HIGH){
        buttonState == LOW;
        break;
        
     }

     }
     
   }
    digitalWrite(Red_LED, LOW);
    digitalWrite(Yellow_LED, LOW);
    digitalWrite(Red_LED, LOW);

   }
  delay(500);
  
    //Thermistor Sensor Code
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
 int Tc = T - 273.15;
 int Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  Serial.print("Thermistor Temperature in F: "); 
  Serial.print(Tf);
  Serial.print(" F; "); 
  Serial.print("Thermistor Temperature in C: "); 
  Serial.print(Tc);
  Serial.println(" c"); 
  delay(2000);
}
