#define BUTTON_1 A2
#define BUTTON_2 A3
#define LED_1 A1
#define LED_2 A4
#define PIEZO A5

#define GAME_OVER_DELAY 1000

#define MAX_LENGTH 100

#define TIMEOUT 3000



void generatePattern(int pattern[], int length);
void displayPattern(int pattern[], int length);
bool getPlayerInput(int length);
bool handlePlayerInput(int pattern[], int button, int led, int index);
void gameOver();
void playStartupTune();
void playWinTune();
void playFailureTone();
void playGameOverTune();
void playTune(int *notes, int *durations, int size);

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  Serial.println("Welcome to Simon Says!");
  playStartupTune();
}

void loop() {

  static int pattern[MAX_LENGTH];
  static int patternLength = 0;
  static int level = 0;

  patternLength = 1;
  level = 1;


  while (true) {
    Serial.print("Level ");
    Serial.println(level);
    generatePattern(pattern, patternLength);
    displayPattern(pattern, patternLength);
    if (!getPlayerInput(pattern, patternLength)) {
      gameOver();
      return;
    }
    playWinTune();
    Serial.print("Correct! Pattern length: ");
    Serial.println(patternLength);
    ++patternLength;
    ++level;
    if (patternLength > MAX_LENGTH) {
      Serial.println("You win! You've completed the pattern!");
      playWinTune();
      delay(GAME_OVER_DELAY);
      return;
    }
    delay(1000);
  }
}

void generatePattern(int pattern[], int length) {
  pattern[length - 1] = random(1, 3);
  // Serial.println(pattern[length - 1]);
}

void displayPattern(int pattern[], int length) {
  Serial.println("Watch the pattern!");
  for (int i = 0; i < length; ++i) {
    digitalWrite(LED_1, pattern[i] == 1);
    digitalWrite(LED_2, pattern[i] == 2);
    delay(1000);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    delay(250);
  }
}

bool getPlayerInput(int pattern[], int length) {
  int playerTurn = 0;
  unsigned long startTime = millis();
  while (playerTurn < length) {
    if (millis() - startTime > TIMEOUT) {
      Serial.println("Time's up!");
      return false;
    }
    if (digitalRead(BUTTON_1) == HIGH) {
      if (!handlePlayerInput(pattern, 1, LED_1, playerTurn++)) return false;
    }
    if (digitalRead(BUTTON_2) == HIGH) {
      if (!handlePlayerInput(pattern, 2, LED_2, playerTurn++)) return false;
    }
  }
  return true;
}

bool handlePlayerInput(int pattern[], int button, int led, int index) {
  Serial.print("Button ");
  Serial.print(button);
  Serial.println(" pressed!");
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  if (pattern[index] != button) {
    Serial.println("Wrong input!");
    return false;
  }
  return true;
}

void gameOver() {
  playFailureTone();
  Serial.println("Game over.");
  //playGameOverTune();
  delay(GAME_OVER_DELAY);
}

void playStartupTune() {
  int notes[] = { 262, 330, 392, 523 };
  int durations[] = { 200, 200, 200, 400 };
  playTune(notes, durations, 4);
}

void playWinTune() {
  int winNotes[] = { 523, 587, 659, 698 };
  int durations[] = { 150, 150, 150, 300 };
  playTune(winNotes, durations, 4);
}

void playFailureTone() {
  tone(PIEZO, 300, 500);
  delay(500);
  noTone(PIEZO);
}

void playGameOverTune() {
  int notes[] = { 400, 300 };
  int durations[] = { 300, 300 };
  playTune(notes, durations, 2);
}

void playTune(int *notes, int *durations, int size) {
  for (int i = 0; i < size; ++i) {
    tone(PIEZO, notes[i], durations[i]);
    delay(durations[i] + 50);
    noTone(PIEZO);
  }
}
