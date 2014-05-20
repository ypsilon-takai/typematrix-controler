/*-*- mode:c++ -*-
  check keyboard matryx
*/

int colPins[] = {1, 2, 3};
int colPinCount = 3;

int rowPins[] = {10, 11, 12, 13};
int rowPinCount = 4;

// lastPinStatus holds pin status (0|1) for every cols
// rows are bitmaps
int lastPinStatus = {0, 0, 0};
int pinStatusCount = 3; 

// key matrix
char* keyMatrix[] = {"abcde",
		     "efgh",
		     "ijkl"};

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

  Keyboard.begin();
}

void loop() {
  
  for (int col = 0; col < colPinCount; col++) {

    digitalWrite(colPins[i], HIGH);

    int countInRow = 0;
    int pushedKeyIndex = 0;

    for (int row = 0; row < rowPinCount; row++) {
      int btnState = digitalRead(rowPins[row]);
      if ( btnState == HIGH ) {
	countInRow++;
	pushedKeyIndex = row;
      }
    }

    if ( countInRow == 1 ) {
      int prevColStat = lastPinStatus[col];
      for (int row = 0; row < rowPinCount; row++) {
	if (row = countInRow) {
	  Keyboard.press( keyMatrix[col][row] );
	}
	else if ( bitRead(prevColStat, row) == 1 ) {
	  Keyboard.release( keyMatrix[col][row] );
	}
      }
      lastPinStatus[col] = 0;
      betSet(lastPinStatus[col], pushedKeyIndex);
    }
    else if ( countInRow == 0 ) {
      for (int row = 0; row < rowPinCount; row++) {
	Keyboard.release( keyMatrix[col][row] );
      }
    }

    digitalWrite(colPins[i], LOW);
  }

  delay(300);
}
      
