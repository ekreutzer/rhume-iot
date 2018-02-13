/*
 * PIR sensor tester
 */

 
int inputPin = 4;               // choose the input pin (for PIR sensor) (4)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
//  delay(50);
  Serial.println(analogRead(inputPin));


  
  val = digitalRead(inputPin);  // read input value
//  if (val == HIGH) {            // check if the input is HIGH
  if(analogRead(inputPin)<=300.0){
    double radar = analogRead(inputPin);
    digitalWrite(LED_BUILTIN, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      Serial.println(digitalRead(inputPin));
      Serial.println(radar);
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW); // turn LED OFF
    if (pirState == HIGH){
      Serial.println(digitalRead(inputPin));
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

}


