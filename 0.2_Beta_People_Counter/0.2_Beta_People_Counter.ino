//THIS CODE IS MEANT FOR THE DEVICE TO BE PLACE INSIDE OF THE ROOM WHERE PEOPLE NEED TO BE COUNTED
//Black is input
//Blue is Ground
//Brown is power
//
////Variables for sending Post request
//int CAPACITY = 20;
//int scale = 0;
//int tempScale = 0;

//Counter
int counter = 0;
int closeStandby = 0;
int farStandby = 0;

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
  pinMode(inputClose, INPUT);
  pinMode(inputFar, INPUT);
  Serial.begin(9600);
  Serial.println(counter);
}

//Loop Code
void loop() {

  //Obstacle Avoidance Sensor Code
  valClose = digitalRead(inputClose);         // read input value for close sensor
  valFar = digitalRead(inputFar);             // read input value for far sensor

  if (valClose == HIGH && valFar == HIGH) {
    closeStandby = 0;
    farStandby = 0;
  }

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
      valClose = digitalRead(inputClose);           // read input value for close sensor
      valFar = digitalRead(inputFar);               // read input value for far sensor
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
      valClose = digitalRead(inputClose);           // read input value for close sensor
      valFar = digitalRead(inputFar);               // read input value for far sensor
      //Wait until no detection
      delay(10);
    }
    
  } else {                                          // Reset the states to low if the sensors are no longer HIGH
    if (valClose == HIGH) {                         // ***** NOTE: Standby values do not reset here ************
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


//  client.println("Host: 10.0.0.138");
//  client.println("User-Agent: Arduino/1.0");
//  client.println("Connection: close");
//  client.print("Content-Length: ");

  char PostData[] = "{\"name\": \"Fred\", \"age\": 31}";

  //userID int
  //spaceID int
  //email string
  //rating int
  //hour int
  //date string 
//
//  IPAddress server(10,0,0,138);
//  client(server, 80);
//  
  client.println(PostData);




  
  delay(10);
}
