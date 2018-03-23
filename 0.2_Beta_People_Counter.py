#THIS CODE IS MEANT FOR THE DEVICE TO BE PLACED
#INSIDE OF THE ROOM WHERE PEOPLE NEED TO BE COUNTED

#Created by Shawn Kotch for Rhume

#Sensor Attachments to RPi 3
    #Far sensor (Farther from the door inside the room)
        #Black: Pin 16 - GPIO 23
        #Blue: Pin 6 - GND
        #Brown: Pin 2 - 5V
    #Close Sensor (Closer to the door inside the room)
        #Black: Pin 40 - GPIO 21
        #Blue: Pin 32 - GND
        #Brown: Pin 4 - 5V
#Imports
import RPi.GPIO as GPIO         # Import GPIO library
import time                     # Import 'time' library. Allows use of 'sleep'

#Constants
FAR = 16                        # Pin for the Photoelectric sensor closer to the door
CLOSE = 40                      # Pin for the Photoelectric sensor closer to the door
CAPACITY = 16.0                 # Capacity of the room where the sensor is located

#Counters
counter = 0.0                   # Counter for the # of people in the room
rating = 0                      # Rating: 0 = green, 1 = yellow, 2 = orange, 3 = red

#Obstacle avoidance sensor close to door
closeState = "HIGH"             # default = no obstacle
valClose = 0                    # variable for reading the pin status (close)
closeStandby = 0                # Standby variable for close sensor

#Obstacle Avoidance sensor far from door
farState = "HIGH"               # default = no obstacle
valFar = 0                      # variable for reading the pin status (close)
farStandby = 0                  # Standby variable for far sensor

# Begin Program ####################################################################
def setup():                    # variable for reading the pin status

    #Setup Code
    GPIO.setmode(GPIO.BOARD)    # Set pin layout to BOARD 
    GPIO.setup(FAR, GPIO.IN)    # Setup GPIO Pin 23 to IN
    GPIO.setup(CLOSE, GPIO.IN)  # Setup GPIO Pin 21 to IN

def loop():

    #Must declare the global variables that need to be changed 
    global counter, closeStandby, farStandby, closeState, valClose, farState, valFar, rating

    #Begin testing for change in rating
    #tempRating = counter/CAPACITY
    if (counter <= 4 and not(rating == 0)):
        print("Rating changed to Green (0)")
        rating = 0
    elif (counter > 4 and counter <= 8 and not(rating == 1)):
        print("Rating changed to Yellow (1)")
        rating = 1
    elif (counter > 8 and counter <= 12 and not(rating == 2)):
        print("Rating changed to Orange (2)")
        rating = 2
    elif (counter > 12 and not(rating == 3)):
        print("Rating changed to Red (3)")
        rating = 3
       
    #Obstacle Avoidance Sensor Code
    valClose = GPIO.input(CLOSE)                    # read input value for close sensor
    valFar = GPIO.input(FAR)                        # read input value for far sensor

    if (valClose == 1 and valFar == 1):             # if neither sensor detects obstacle, no longer standby
        closeStandby = 0
        farStandby = 0


    if (valClose == 0 and farStandby == 0):         # check if the input is HIGH and if the other sensor was active
        closeStandby = 1                            # set the standby variable for the close sensor to 1
        if (closeState == "HIGH"):                  # if the state was previously LOW, motion was just detected
            closeState = "LOW"                      # change the radar state to HIGH
        #print("if1")
    elif (valFar == 0 and closeStandby == 0):       # check if the input is HIGH and if the other sensor was active
        farStandby = 1                              # set the waiting variable for the close sensor to 1
        if (farState == "HIGH"):                    # if the state was previously LOW, motion was just detected
            closeState = "LOW"                      # change the radar state to HIGH
        #print("if2")
    elif (valFar == 0 and closeStandby == 1):       # check if the second sensor detects object and that the other is on standby
        counter+=1                                  # add 1 to the counter
        closeStandby = 0                            # turn closeStandby back to 0
        print(counter)
        print(rating)
        while(not(valFar == 1 and valClose == 1)):  # Wait until both sensors no longer detect an object
            valClose = GPIO.input(CLOSE)            # read input value for close sensor
            valFar = GPIO.input(FAR)                # read input value for far sensor
            time.sleep(0.001)                       # Wait to loop
        #print("if3")
    elif (valClose == 0 and farStandby == 1):       # check if the first sensor detects object and that the other is on standby
        if (counter > 0):                           # never make the counter go below 0
            counter-=1                              # subtract 1 to the counter
            print(counter)
            print(rating)
        else:
            print("Could not Subtract 1 from 0")
        farStandby = 0                              # turn farStandby back to 0
        while (not(valFar == 1 and valClose == 1)): # Wait until both sensors no longer detect an object
            valClose = GPIO.input(CLOSE)            # read input value for close sensor
            valFar = GPIO.input(FAR)                # read input value for far sensor
            time.sleep(0.001)                       # Wait to loop
        #print("if4")
    else:                                           # Reset the states to low if the sensors are no longer HIGH
        if (valClose == 1):                         # ***** NOTE: Standby values do not reset here ************
            if (closeState == "LOW"):
                closeState = "HIGH";
            #print("if5")        
        if (valFar == 1):
            if(farState == "LOW"):
                farState = "HIGH";
            #print("if6")

def main():
    setup()                                         # Run setup function
    while True:                                     # loop forever
        loop()                                      # call loop()
        time.sleep(0.001)                           # wait to loop
main()                                              # call main()
















    

