 /* LucidTronix LEO Keyboard
 * works as standard USB keyboard
 * Tutorial and details at:
 * http://www.lucidtronix.com/tutorials/51
 *  This code requires Arduino Leonardo
 */ 
 
int dataPin = 4;
int clockPin = 5;
int latchPin = 6;

unsigned long last_press = 0;
unsigned long last_key_press = 0;

char* letters[] ={"abcdefgh","ijklmnop","qrstuvwx","yz -@#.@" };

int leds[] = {7,8,9};

int num_chars = 43;
int num_registers = 4;
byte button_states[] = {0x00,0x00,0x00,0x00};  //01001000
int cursor_index = 0;
int char_index = 0;
char cur_char = 'X';

boolean shifting = false;

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, INPUT);
  for(int i = 0 ; i < 3; i++) pinMode(leds[i], OUTPUT);
  for(int i = 0 ; i < 3; i++) digitalWrite(leds[i], HIGH);
  delay(200);
  for(int i = 0 ; i < 3; i++) digitalWrite(leds[i], LOW);
  


}

void loop() {
  if (millis() - last_key_press > 450) read_keyboard();
  if ( shifting ) digitalWrite(leds[0], HIGH);
  else digitalWrite(leds[0], LOW);
  delay(350);
}


void read_keyboard(){
  //set it to 0 to transmit data serially  
  digitalWrite(latchPin,LOW);
  //while the shift register is in serial mode
  //collect each shift register into a byte
  //the register attached to the chip comes in first 
  for (int i = 0; i < num_registers; i++){
    button_states[i] = shiftIn(dataPin, clockPin);
  }
  boolean something_in = false;
  for (int i = 0; i < num_registers; i++){    
    something_in = translate_buttons_2_keys(button_states[i], letters[i]);
    if (something_in) last_key_press = millis(); 
  }
  digitalWrite(latchPin,HIGH);
}
boolean translate_buttons_2_keys(byte buttons, char* keys){
  for(int i = 0 ; i < 8; i++){
     if ( (1 << i) & buttons ){
       cur_char = keys[i];
       if (keys[i] == '-') Keyboard.write(KEY_RETURN);
       else if (keys[i] == '@') Keyboard.write(KEY_BACKSPACE);
       else if (keys[i] == '#' && shifting) Keyboard.release(KEY_LEFT_SHIFT); 
       else if (keys[i] == '#' && !shifting) Keyboard.press(KEY_LEFT_SHIFT);        
       else if (keys[i] == '|') Keyboard.write(21);
       else Keyboard.print(keys[i]);
       if (keys[i] == '#') shifting = !shifting;
       char_index++;
       return true;
     }     
  }
 return false; 
}
byte shiftIn(int myDataPin, int myClockPin) { 
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);

  for (i=7; i>=0; i--)
  {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(20);
    temp = digitalRead(myDataPin);
    if (temp) {
      pinState = 1;
      myDataIn = myDataIn | (1 << i);
    }
    else {
      pinState = 0;
    }
    digitalWrite(myClockPin, 1);
  }
  return myDataIn;
}
