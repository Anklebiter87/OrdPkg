#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

Password password = Password( "1234" );

const byte ROWS = 4; 
const byte COLS = 3; 
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 8, 7, 6 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 13, 12, 11 };


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){

  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  keypad.getKey();
}

//Key was pressed event
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	switch (eKey){
	  case '*': checkPassword(); break;
	  case '#': clearPassword(); break;
	  default: Defaultkeyhandler(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("\nSuccess");
    password.reset();
  }else{
    Serial.println("\nWrong");
    password.reset();
  }
}
//clears the password that had been entered
void clearPassword(){
    Serial.println("\nPasword Cleared");
    password.reset();
}
//Default keypressed handle function
void Defaultkeyhandler(KeypadEvent eKey){
  password.append(eKey);
  Serial.print(eKey);
}
