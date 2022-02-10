// 5-2-2022  added serial print
// 27-01-2022 project 'autozem'
// servos controlled - e.g 'L50' (move left servo 50º) and/or 'R50' (move right servo 50º). Arduino will accept upper and lower case.
// servos move at the same speed. (this can be changed at the bottom of the sketch)
// servos move independent of eachother thanks to varspeedservo.h interrupt method
// servos dont move to default location after board reset thanks to saving last entered serial angle in EEPROM and loading before servo is attached.
// ** Arduino UNO R3 board has auto-reset disabled ** (need to add switch for easier sketch uploading)
// Varspeed library download http://www.glassier.biz/autozem/VarSpeedServo-master.zip
// use with HWiNFO

#include <EEPROM.h>
#include <VarSpeedServo.h>

int eeaddr1 = 0;  //sets EEPROM address to use for storing servo1 last angle 
int eeaddr2 = 10; //sets EEPROM address to use for storing servo2 last angle

char buffer[11];
VarSpeedServo servo1; //create a servo object
VarSpeedServo servo2; //create a second servo object

void setup()
{
  servo1.write(EEPROM.read(eeaddr1));  //sets servo1 last angle before attaching so no erratic movement
  servo2.write(EEPROM.read(eeaddr2));  //sets servo2 last angle before attaching so no erratic movement
  servo1.attach(9); //attaches servo1 on pin 9 to the servo1 object
  servo2.attach(10); //attaches servo2 on pin 10 to the servo2 object
  Serial.begin(115200);
  while (Serial.available())
    Serial.read();
}
void loop() {
  if (Serial.available() > 0) { // Check if data has been entered
    int index = 0;
    delay(100); //let the buffer fill up
    int numChar = Serial.available(); // Find the string length
    if (numChar > 10) {
      numChar = 10;
    }
    while (numChar--) {
      //fill the buffer with the string
      buffer[index++] = Serial.read();
    }
    buffer[index] = '\0';
    splitString(buffer); //run splitString function
  }
}
void splitString(char* data) {
  char* parameter;
  parameter = strtok (data, " ,"); //String to token
  while (parameter != NULL) { // If we haven't reached the end of the string...
    setServo(parameter); // ...run the setServo function
    parameter = strtok (NULL, " ,");
  }
  while (Serial.available())
    Serial.read();
}
void setServo(char* data) {
  int SPEED1 = 5; //servo1 speed.  lower is slower
  int SPEED2 = 5; //servo2 speed.  lower is slower

  if ((data[0] == 'L') || (data[0] == 'l')) {
    int firstVal = strtol(data + 1, NULL, 10); // String to long integer
    firstVal = constrain(firstVal, 1, 179); // Constrain values
    servo1.write(firstVal, SPEED1);
    EEPROM.update(0, firstVal); //save last entered serial angle for servo1 to EEPROM
    Serial.print("Rear Servo is set to: ");
    Serial.println(firstVal);
  }
  if ((data[0] == 'R') || (data[0] == 'r')) {
    int secondVal = strtol(data + 1, NULL, 10); // String to long integer
    secondVal = constrain(secondVal, 1, 179); // Constrain the values
    servo2.write(secondVal, SPEED2);
    EEPROM.update(10, secondVal); //save last entered serial angle for servo2 to EEPROM
    Serial.print("Front Servo is set to: ");
    Serial.println(secondVal);
  }
}
