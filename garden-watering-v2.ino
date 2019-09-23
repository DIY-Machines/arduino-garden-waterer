// Garden watering porject by Lewis for DIY Machines   www.youtube.com/c/diymachines     www.diymachines.co.uk
// Full details of the project inlcuding instructional video and 3D printable components available on the projects pgae at https://diymachines.co.uk/projects/automatic-arduino-based-garden-waterer.html

// This project uses the handy DS3231 Simple library:- https://github.com/sleemanj/DS3231_Simple   Please follow the instruction on installing this provided on the libraries page

// Before you install this code you need to set the time on your DS3231. Once you have connected it as shown in this project and have installed the DS£@£!_Simple library (see above) you
// to go to  'File' >> 'Examples' >> 'DS3231_Simple' >> 'Z1_TimeAndDate' >> 'SetDateTime' and follow the instructions in the example to set the date and time on your RTC

#include <DS3231_Simple.h>
#include <Servo.h>
#include <Wire.h>

DS3231_Simple Clock;

Servo myservo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int posClosed = 0;
int posOpen = 90;
DateTime MyDateAndTime;  // Create a variable to hold the time data for reading the time
float MyFloatTemperature;

void setup() {
  
Serial.begin(9600);  

    //code to help reduce power requirments as suggested here: https://www.youtube.com/watch?v=urLSDi7SD8M 
  for(int i=0; i<20; i++){
    pinMode(i, OUTPUT);
  } 

   myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
   Wire.begin();
   Clock.begin();
   closeValve();

  // Get an initialized timestamp
  DateTime MyTimestamp = Clock.read();        
}

void loop() 
{ 

  readTheTime();
  readTheTemp();

    Serial.print("The minute is: ");              //print what time the Arduino beleives it is to the serial monitor to help with debugging
    Serial.println(MyDateAndTime.Minute);
    Serial.print("The hour is: ");
    Serial.println(MyDateAndTime.Hour);

    if ((MyDateAndTime.Hour == 6) && (MyDateAndTime.Minute == 30)){  // set the hour (24hr clock) and minute you want the watering to begin
    openValve();
    delay(180000); //time in millisecnods (thousandths of a second) for the valve to remain open
    closeValve();
    delay(50000);   //this 50 second delay is desinged to stop the same watering 'window' from repeating if it water for less than 10 seconds.
    }

    if ((MyDateAndTime.Hour == 14) && (MyDateAndTime.Minute == 30)){  // set the hour (24hr clock) and minute you want the watering to begin
    openValve();
    delay(120000); //time in millisecnods (thousandths of a second) for the valve to remain open
    closeValve();
    delay(50000);   //this 50 second delay is desinged to stop the same watering 'window' from repeating if it water for less than 10 seconds.
    }
    

    
}

void openValve() {
        for (pos = posClosed; pos <= posOpen; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(20);                       // waits 15ms for the servo to reach the position
      }
    }


void closeValve() {
    for (pos = posOpen; pos >= posClosed; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
}

void readTheTime(){
  // Ask the clock for the data.
  MyDateAndTime = Clock.read();
  
  // And use it
  Serial.println("");
  Serial.print("Time is: ");   Serial.print(MyDateAndTime.Hour);
  Serial.print(":"); Serial.print(MyDateAndTime.Minute);
  Serial.print(":"); Serial.println(MyDateAndTime.Second);
  Serial.print("Date is: 20");   Serial.print(MyDateAndTime.Year);
  Serial.print(":");  Serial.print(MyDateAndTime.Month);
  Serial.print(":");    Serial.println(MyDateAndTime.Day);
}

void readTheTemp(){
    MyFloatTemperature   = Clock.getTemperatureFloat();
  Serial.println("Note that temperature is updated every 64 seconds by the DS3231.");
  Serial.print("Float Temperature:   "); Serial.println(MyFloatTemperature);
}
