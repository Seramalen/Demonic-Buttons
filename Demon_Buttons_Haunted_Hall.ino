// Define all pins used in the program, these are buttons from top left to bottom right and their lights
int buttonOne = 22;
int lightOne = 23;

int buttonTwo = 24;
int lightTwo = 25;

int buttonThree = 26;
int lightThree = 27;

int buttonFour = 28;
int lightFour = 29;

int buttonFive = 30;
int lightFive = 31;

int buttonSix = 32;
int lightSix = 33;

int buttonSeven = 34;
int lightSeven = 35;

int buttonEight = 36;
int lightEight = 37;

int buttonNine = 38;
int lightNine = 39;

int doorButton = 40;



void setup() {
pinMode(buttonOne, INPUT_PULLUP);
pinMode(buttonTwo, INPUT_PULLUP);
pinMode(buttonThree, INPUT_PULLUP);
pinMode(buttonFour, INPUT_PULLUP);
pinMode(buttonFive, INPUT_PULLUP);
pinMode(buttonSix, INPUT_PULLUP);
pinMode(buttonSeven, INPUT_PULLUP);
pinMode(buttonEight, INPUT_PULLUP);
pinMode(buttonNine, INPUT_PULLUP);
pinMode(doorButton, INPUT_PULLUP);
pinMode(lightOne, OUTPUT);
pinMode(lightTwo, OUTPUT);
pinMode(lightThree, OUTPUT);
pinMode(lightFour, OUTPUT);
pinMode(lightFive, OUTPUT);
pinMode(lightSix, OUTPUT);
pinMode(lightSeven, OUTPUT);
pinMode(lightEight, OUTPUT);
pinMode(lightNine, OUTPUT);
Serial.begin(9600);
}

int checkKeyPress() {
  //Here we want to check the key that is being pressed
  if(digitalRead(buttonOne) == LOW) {
    digitalWrite(lightOne, LOW);
    return 1;    
    }
  else if(digitalRead(buttonTwo) == LOW) {
    digitalWrite(lightTwo, LOW);
    return 2;
    }
  else if(digitalRead(buttonThree) == LOW) {
    digitalWrite(lightThree, LOW);
    return 3;    
    } 
  else if(digitalRead(buttonFour) == LOW) {
    digitalWrite(lightFour, LOW);
    return 4;    
    }
  else if(digitalRead(buttonFive) == LOW) {
    digitalWrite(lightFive, LOW);
    return 5;    
    }
      else if(digitalRead(buttonSix) == LOW) {
        digitalWrite(lightSix, LOW);
    return 6;    
    } 
      else if(digitalRead(buttonSeven) == LOW) {
        digitalWrite(lightSeven, LOW);
    return 7;    
    } 
      else if(digitalRead(buttonEight) == LOW) {
        digitalWrite(lightEight, LOW);
    return 8;    
    } 
      else if(digitalRead(buttonNine) == LOW) {
        digitalWrite(lightNine, LOW);
    return 9;    
    } else {return 0;}
  }

  //this method is called to detect which key we want pressed and wait for that key to be unpressed before returning true
  static bool waitForKey(int wantedKey) {
    //weve added a delay here to account for some input issues
    delay(50);
    int key = checkKeyPress();
    //This pressedKey variable is in place since the arduino processes too fast, and will always read that no button was pressed upon return
    int pressedKey;
    while(key == 0) {
      //key has not been pressed
      //Check to see if the door is open. If it is, we immediately want to return
      if(digitalRead(doorButton) == LOW) 
    {
      return false;
      }
      key = checkKeyPress();     
      }
      //when key is pressed, we want to wait for it to be unpressed
      //Here we say what key has been pressed
      pressedKey = key;
      while(true){
      while(key == pressedKey){
        key = checkKeyPress();  
        //so again we do nothing
        }
        delay(50);
        key = checkKeyPress();
        if(key == pressedKey){
          //we do nothing here and let it loop again
        } else{
          break;
          }
      }
        //and finally we return to the main loop, but we tell it whether or not the button that was pressed was correct
        Serial.println(pressedKey);
        if(pressedKey == wantedKey){
          return true;
          }
        if(pressedKey != wantedKey){
          return false;
          }   
    }

//This method checks dor whether or not the closet door is open
static bool checkDoor()
{
  if(digitalRead(doorButton)==HIGH)
  {
    return true;
    } else
    {
    digitalWrite(lightOne, LOW);
    digitalWrite(lightTwo, LOW);
    digitalWrite(lightThree, LOW);
    digitalWrite(lightFour, LOW);
    digitalWrite(lightFive, LOW);
    digitalWrite(lightSix, LOW);
    digitalWrite(lightSeven, LOW);
    digitalWrite(lightEight, LOW);
    digitalWrite(lightNine, LOW);
    return false;      
      }
  }
  
void loop() {
  //So here we want to check for a "key press" or that key one has been connected, and we're basically going to ignore any other keys at this point
  //If the door is closed, we want the lights to stay on
  if(checkDoor){
  digitalWrite(lightOne, HIGH);
  digitalWrite(lightTwo, HIGH);
  digitalWrite(lightThree, HIGH);
  digitalWrite(lightFour, HIGH);
  digitalWrite(lightFive, HIGH);
  digitalWrite(lightSix, HIGH);
  digitalWrite(lightSeven, HIGH);
  digitalWrite(lightEight, HIGH);
  digitalWrite(lightNine, HIGH);
  }
  bool correct = true;
  bool failed = false;
  for (int i = 1; i<=9; i++) {
    if(!checkDoor())
    {
      failed = true;
      break;
      //we break from the loop so that it simply checks it as a fail
      }
    
    correct = waitForKey(i);
    //If this key is not correct, we still have to look for whether or not the door button was pressed
    if(!correct){
      failed = true;
      //If the door is open
      if(digitalRead(doorButton) == LOW)
      {
        //Then break and it should re-do the buttons
        break;
        }
      }
    }

  if(failed){
    //They failed at some point in the loop, so the maglock stays closed
    Serial.println("Incorrect");
    }
  if(!failed){
    //They succeeded! mag lock opens!
    Serial.println("Correct");
    }
    delay(1000);
}
