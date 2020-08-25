/**********************************************************************************
 *  TITLE: Ultrasonic sensor HCSR04 and Arduino distance measurement (0.96" I2C OLED)
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/ajQh_uQ7nNI
 *  Related BLOG : https://easyelectronicsproject.com/arduino/ultrasonic-sensor-arduino-01
 *  by Tech StudyCell
 **********************************************************************************/


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// define pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int greenLedPin = 13;
const int buzzerPin = 12;

// define Trigger Distance in CM
const int trigDistance = 15; //change this value from 2 to 400

// define variables
long duration;
int distance;
uint32_t delayMS;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT); // Sets the greenLedPin as an Output
  pinMode(greenLedPin, OUTPUT); // Sets the redLedPin as an Output
  Serial.begin(9600); // Starts the serial communication
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay(); // Clear display buffer
  delayMS = 1000;
}

void ledOnOff(int distance){
  if(distance < trigDistance){
    digitalWrite(greenLedPin, LOW);   // turn the GREEN LED off
    digitalWrite(buzzerPin, HIGH);   // turn the RED LED on
    delay(100);
    digitalWrite(buzzerPin, LOW);   // turn the RED LED off
    delay(100);
    digitalWrite(buzzerPin, HIGH);   // turn the RED LED on
  }
  else{
    digitalWrite(greenLedPin, HIGH);   // turn the GREEN LED on
    digitalWrite(buzzerPin, LOW);   // turn the RED LED off
  }
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < trigDistance){
      ledOnOff(distance);
      display.setTextSize(1);
      display.setCursor(1,1);
      display.print("STAY BACK!"); 
      display.println();
      display.setTextSize(2);
      display.setCursor(15,15);  
      display.print(distance);     
      display.display();
      delay(delayMS);
      display.clearDisplay();
  }
  else{
      ledOnOff(distance);
      display.setTextSize(1);
      display.setCursor(1,1);
      display.print("Distance:"); 
      display.println();
      display.setTextSize(2);
      display.setCursor(15,15);  
      display.print(distance);     
      display.display();
      delay(delayMS);
      display.clearDisplay();
  }
}
