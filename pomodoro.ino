#define common1 12
#define common2 9
#define common3 8
#define common4 6

#define clearDelay 4

long pauseDuration = 5*60*1000L;
long workDuration = 25*60*1000L;

long currentTimer = workDuration;
bool isWorkTime = true;


bool isRunning = true;
unsigned long lastInput = 0;
unsigned long lastPass;

void setup() {
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(3), buttonPressed, FALLING);

  lastPass = millis();
}

// Map between common pin and digit
// Ex for 2 digit : digitMap[2] -> pin 9
int digitMap[5] = {0,common1,common2,common3,common4};


void selectDigit(int digit){
  digitalWrite(common1, HIGH);
  digitalWrite(common2, HIGH);
  digitalWrite(common3, HIGH);
  digitalWrite(common4, HIGH);

  digitalWrite(digitMap[digit], LOW);
}

void writeNumber(int number){
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(7, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  digitalWrite(1, LOW);
  switch (number)
  {
  case 1:
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    break;
  case 2:
    digitalWrite(11, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    break;
  case 3:
    digitalWrite(11, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    break;
  case 4:
    digitalWrite(10, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    break;
  case 5:
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    break;
  case 6:
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
    break;
  case 7:
    digitalWrite(11, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    break;
  case 8:
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
    break;
  case 9:
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    break;
  case 0:
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
    break;
  }
}

void writeNumberOnDigit(int number, int digit){
  selectDigit(digit);
  writeNumber(number);
  delay(clearDelay);
}


int quickPress = 0;
bool skip = false;

void buttonPressed(){
  unsigned long current = millis();
  long elapsed = current - lastInput;

  if (elapsed > 1000){
    quickPress = 0;
  }

  if ((elapsed) > 200){
    if (quickPress == 0){
      isRunning = !isRunning;
      lastPass = current;
      quickPress += 1;
    } else {
      quickPress += 1;
    }
    lastInput = current;
  }

  if (quickPress >= 2){
    skip = true;
    quickPress = 0;
  }
}

void writeSeconds(int seconds){
  int minutes = seconds / 60;
  writeNumberOnDigit(minutes / 10, 1);
  writeNumberOnDigit(minutes % 10, 2);
  int s = seconds % 60;
  writeNumberOnDigit(s / 10, 3);
  writeNumberOnDigit(s % 10, 4);
}

long decrementCurrentTime(long currentTime){
  currentTime -= (millis() - lastPass);
  lastPass = millis();
  if (currentTime <= 0){
    if (isWorkTime){
      currentTime = pauseDuration;
      isWorkTime = false;
    }
    else {
      currentTime = workDuration;
      isWorkTime = true;
    }
  }
  return currentTime;
}


void loop() {
  writeSeconds((int)(currentTimer/1000));
  
  if (isRunning){
     currentTimer = decrementCurrentTime(currentTimer);
  }
  if (isWorkTime){
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }

  if (skip){
    if (isWorkTime){
      currentTimer = pauseDuration;
      isWorkTime = false;
    } else {
      currentTimer = workDuration;
      isWorkTime = true;
    }
    isRunning = true;
    skip = false;
  }

}
