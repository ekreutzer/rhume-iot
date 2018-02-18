//THIS CODE IS MEANT FOR THE DEVICE TO BE PLACE INSIDE OF THE ROOM WHERE PEOPLE NEED TO BE COUNTED

//Counter
int counter = 0;
int closeStandby = 0;
int farStandby = 0;

//Microwave Radar Sensor
int inputRadar = 4;                  // Pin for RADAR Sensor)
int radarState = LOW;                // default = no motion detected
int valRadar = 0;                    // variable for reading the pin status

//Obstacle avoidance sensor close to door
int inputClose = 2;                  // Pin for the Photoelectric sensor closer to the door
int closeState = LOW;                // default = no obstacle
int valClose = 0;                    // variable for reading the pin status

//Obstacle Avoidance sensor close to door
int inputFar = 7;                    // Pin for the Photoelectric sensor closer to the door
int farState = LOW;                  // default = no obstacle
int valFar = 0;                      // variable for reading the pin status

//Setup Code
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);               // declare Built in LED as output for the motion sensor
  pinMode(inputRadar, INPUT);                 // declare radar as input
  Serial.begin(9600);
  Serial.println(counter);
}

//Loop Code
void loop() {

//  Serial.println(counter);                   // print the counter to Serial
//
//  //Radar Sensor Code
//  valRadar = digitalRead(inputRadar);         // read input value
//  if (valRadar == HIGH) {                     // check if the input is HIGH
//    digitalWrite(LED_BUILTIN, HIGH);          // turn LED ON
//    if (radarState == LOW) {                  // if the state was previously LOW, motion was just detected
//      //Serial.println("True.");                // print "True." to Serial
//      radarState = HIGH;                      // change the radar state to HIGH
//    }
//  } else {                                        // valRadar != HIGH
//    digitalWrite(LED_BUILTIN, LOW);               // turn LED OFF
//    if (radarState == HIGH) {                     // if the state was previously HIGH, motion is no longer detected
//      //Serial.println("False.");                   // print "False." to Serial
//      radarState = LOW;                           // change the radar state to LOW
//    }
//  }

  //Obstacle Avoidance Sensor Code
  valClose = digitalRead(inputClose);         // read input value for close sensor
  valFar = digitalRead(inputFar);             // read input value for far sensor

  if (valClose == HIGH && farStandby == 0) {        // check if the input is HIGH and if the other sensor was active
    closeStandby = 1;                               // set the waiting variable for the close sensor to 1
    if (closeState == LOW) {                        // if the state was previously LOW, motion was just detected
      closeState = HIGH;                            // change the radar state to HIGH
    }
  } else if (valFar == HIGH && closeStandby == 0) { // check if the input is HIGH and if the other sensor was active
    farStandby = 1;                                 // set the waiting variable for the close sensor to 1
    if (farState == LOW) {                          // if the state was previously LOW, motion was just detected
      closeState = HIGH;                            // change the radar state to HIGH
    }
  } else if (valFar == HIGH && closeStandby == 1) {
    ++counter;                                      // add 1 to the counter
    closeStandby = 0;                               // turn closeStandby back to 0
  } else if (valFar == HIGH && closeStandby == 1) {
    if (counter > 0) {
      --counter;                                    // subtract 1 to the counter
    }
    farStandby = 0;                                 // turn farStandby back to 0
  } else {                                          // Reset the states to low if the sensors are no longer HIGH
    if (valClose == LOW) {                          // ***** NOTE: Standby values do not reset here ************
      if (closeState == HIGH) {
        closeState = LOW;
      }
    }
    if (valFar == LOW) {
      if (farState == HIGH) {
        farState = LOW;
      }
    }
  }
}
