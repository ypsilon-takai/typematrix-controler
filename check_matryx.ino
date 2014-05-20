/*
  check keyboard matryx
*/

int colPins[] = {1, 2, 3};
int colPinCount = 3;

int rowPins[] = {10, 11, 12, 13};
int rowPinCount = 4;

void setup() {
  // setup colPins as OUTPUT
  for (int i = 0; i < colPinCount; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }

  // setup rowPins as INPUT
  for (int i = 0; i < rowPinCount; i++) {
    pinMode(rowPins[i], INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    for (int col = 0; col < colPinCount; col++) {
      digitalWrite(colPins[i], HIGH);
      for (int row = 0; row < rowPinCount; row++) {
	int btnState = digitalRead(rowPins[row]);
	if ( btnState == HIGH ) {
	  Serial.print(col);
	  Serial.print(" - ");
	  Serial.println(row);
	}
      }
      digitalWrite(colPins[i], LOW);
    }
  }
  delay(300);
}
      
