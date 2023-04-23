// The following code is an attachment of the report 'Santilli_ElectricMotorControl_rev00'. 
// Author: Luca Massimo Santilli

int sensorPin = 2;            // Define the digital pin used to read the encoder  
int TIP120pin = 9;            // Define the digital pin used to communicate with Base pin of TIP120
int motstate = 0;             // Initialize variable to control the motor speed
int PWM;                      // Declare variable to save the value read from the potentiometer
unsigned long start_time = 0; // Initialize variable to determine the starting time of each measurement
unsigned long end_time = 0;   // Initialize variable to determine the ending time off each measurement
int steps = 0;                // Initialize varible used to count the number of notches detected by the encoder
int steps_old = 0;          // Initialize varibale used to count the nubmer of notches detected during the previous measurement
int temp = 0;               // Initialize variable used to count the number of notches detected during each measurement
float rps = 0;                // Intialize varible used to count revolutions per second
float rpm = 0;                // Initialize variable used to count revolutions per minute


void setup() {
  Serial.begin(9600);         // Set communication speed between Arduino and PC
  pinMode(TIP120pin, OUTPUT); // Set pin to output to control TIP120 Base pin
  pinMode(sensorPin, INPUT);  // Set pin to input to read the encoder
}

void loop() {
  PWM = analogRead(0);                    // Write on the PWM variable the value read from the potentiometer
  motstate = map(PWM, 0, 1023, 0, 255);   // write on the motstate variable the vaule of the potentiomenter scaled through the map function
 
  if(motstate < 25){                      // If condition used to prevent the motor from receiving current if the potentiometer
    motstate = 0;                         // value is below 25
  }
  analogWrite(TIP120pin, motstate);       // Write on the TIP120 Base pin motstate value, controlling the speed of the motor

  start_time = millis();                  // Write on the start_time variable the starting time of a measurement
  end_time = start_time + 1000;           // Write on he end_time variable the ending time of a measurement

while(millis() < end_time){               // While condition used to check if the current time is less than the end measurement time
  if((digitalRead(sensorPin)) == 1){      // If conditiond used to increase the steps variable by 1 if the encoder detects a notch
    steps += 1;
    while(digitalRead(sensorPin) == 1);   // While condition used to "stop" the loop until the value of the encoder goes back to 0
  }
}
  temp = steps - steps_old;               // Write on temp variable the steps detected in the meausurement
  steps_old = steps;                      // Update the value of old_steps
  rps = (temp/20);                        // Determine the revolution per second
  rpm = (rps*60);                         // Determine the revolution per minute

 Serial.println(motstate);                // Print the scaled value of the potentiometer
 Serial.print("rps ="); Serial.print(rps); Serial.print(", rpm="); Serial.println(rpm); 
                                          // Print speed values
 delay(10);                                
}
