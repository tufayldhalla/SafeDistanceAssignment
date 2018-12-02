//By: Tufayl Dhalla
//Final Summitive Assignment
//Jan 20th, 2015

#include <LiquidCrystal.h>

//Declecration of all the LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Variables
int pingPin = 7; //output 10us pulse to this pin
int inPin = 6; //measure return pulse width from this pin
long duration, cm; //Variables of converting the duration to cm
int cmdec; //covertion to decimal variable
int cmconv = 59; // ratio between pulse width and cm
String s2; //String for the cm to display

// initialise LCD library and pins
void setup() {
  lcd.begin(16, 2);
  pinMode(pingPin, OUTPUT);
  pinMode(inPin, INPUT);
  pinMode(10, OUTPUT); //Pin of the red light
  pinMode(9, OUTPUT); //Pin of the green light
}

void loop()
{
  // Send a short LOW followed by HIGH pulse to Trigger input:
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  // read the length of the return pulse on Echo output
  duration = pulseIn(inPin, HIGH);

  // convert the time into a distance (non-floating point with decimals
  cm = microsecondsToCentimeters(duration);
  cmdec = (duration - cm * cmconv) * 10 / cmconv;
  s2 = String(cm) + "." + String(cmdec) + "cm" + "     ";
  lcd.setCursor(0,1); // print cm on second line of LCD
  lcd.print(s2);

  //If statements to determine the frequency of the buzzer, which light colour turns on, and what to display on the lCD
  if (cm <= 5)
  {
    lcd.setCursor(0, 0); // print text on top line of LCD
    lcd.print("DANGER ZONE!!!!");
    tone(13, 800); //The frequency of the buzzer
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
  }
  else if(cm > 5 && cm <= 12)
  {
    lcd.setCursor(0, 0); // print text on top line of LCD
    lcd.print("THREAT DETECTED!!");
    tone(13, 460); //The frequency of the buzzer
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
  }
  else if(cm > 12 && cm <= 22)
  {
    lcd.setCursor(0, 0); // print text on top line of LCD
    lcd.print("Safe Distance!  ");
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    tone(13, 240); //The frequency of the buzzer
  }
  else if (cm > 22)
  {
    lcd.setCursor(0, 0); // print text on top line of LCD
    lcd.print("  ALL Clear    ");
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    noTone(13);
  }
  delay(100);

}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / cmconv;
}

