//THIS CODE IS MEANT FOR THE DEVICE TO BE PLACE INSIDE OF THE ROOM WHERE PEOPLE NEED TO BE COUNTED
//Black is input
//Blue is Ground
//Brown is power


//Counter
int counter = 0;
int closeStandby = 0;
int farStandby = 0;

//Microwave Radar Sensor
int inputRadar = 7;                  // Pin for RADAR Sensor)
int radarState = HIGH;                // default = no motion detected
int valRadar = 0;                    // variable for reading the pin status

//Obstacle avoidance sensor close to door
int inputClose = 2;                  // Pin for the Photoelectric sensor closer to the door
int closeState = HIGH;                // default = no obstacle
int valClose = 0;                    // variable for reading the pin status

//Obstacle Avoidance sensor close to door
int inputFar = 4;                    // Pin for the Photoelectric sensor closer to the door
int farState = HIGH;                  // default = no obstacle
int valFar = 0;                      // variable for reading the pin status

//Setup Code
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);               // declare Built in LED as output for the motion sensor
  pinMode(inputRadar, INPUT);                 // declare radar as input
  pinMode(inputClose, INPUT);
  pinMode(inputFar, INPUT);
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


  //
  //  if (valClose == HIGH && valFar == HIGH) {
  //    //do nothing
  //  } else
  if (valClose == LOW && farStandby == 0) {        // check if the input is HIGH and if the other sensor was active
    closeStandby = 1;                               // set the waiting variable for the close sensor to 1
    //Serial.println("Close Standby");
    if (closeState == HIGH) {                        // if the state was previously LOW, motion was just detected
      closeState = LOW;                            // change the radar state to HIGH
    }
  } else if (valFar == LOW && closeStandby == 0) { // check if the input is HIGH and if the other sensor was active
    farStandby = 1;                                 // set the waiting variable for the close sensor to 1
    //Serial.println("Far Standby");
    if (farState == HIGH) {                          // if the state was previously LOW, motion was just detected
      closeState = LOW;                            // change the radar state to HIGH
    }
  } else if (valFar == LOW && closeStandby == 1) {
    ++counter;                                      // add 1 to the counter
    closeStandby = 0;                               // turn closeStandby back to 0
    Serial.println("Add to counter");
    Serial.println(counter);
    while (!(valFar == HIGH && valClose == HIGH)) {
      valClose = digitalRead(inputClose);         // read input value for close sensor
      valFar = digitalRead(inputFar);             // read input value for far sensor
      //Wait until no detection
      delay(10);
    }

  } else if (valClose == LOW && farStandby == 1) {
    if (counter > 0) {
      --counter;                                    // subtract 1 to the counter
      Serial.println("Subtract counter");
      Serial.println(counter);
    } else {
      Serial.println("Counter already at 0");
    }
    farStandby = 0;                                 // turn farStandby back to 0
    while (!(valFar == HIGH && valClose == HIGH)) {
      valClose = digitalRead(inputClose);         // read input value for close sensor
      valFar = digitalRead(inputFar);             // read input value for far sensor
      //Wait until no detection
      delay(10);
    }
  } else {                                          // Reset the states to low if the sensors are no longer HIGH
    if (valClose == HIGH) {                          // ***** NOTE: Standby values do not reset here ************
      if (closeState == LOW) {
        closeState = HIGH;
      }
    }
    if (valFar == HIGH) {
      if (farState == LOW) {
        farState = HIGH;
      }
    }
  }
  delay(10);
}
