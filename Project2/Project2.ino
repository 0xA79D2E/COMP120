/**
 * Simon Says
 *
 * Author: Shygaan Khalili
 * Date: Apr-02-2025
 * Course: COMP 120
 *
 *
 * Description:
 * Arduino-based implementation of "Simon Says". Generates random pattern of LED flashes that player must
 * memorize and replicate by pressing corresponding buttons. Each round, pattern increases in length.
 * Game continues until the player makes an error or reaches the maximum
 * pattern length.
 * 
 * 
 * Hardware Requirements:
 * - 2 LEDs
 * - 2 Buttons
 * - 1 buzzer
 * - Arduino-compatible MCU (I used STM32)
 */

#define LED_1 A1
#define BUTTON_1 A2
#define BUTTON_2 A3
#define LED_2 A4
#define PIEZO A5

#define GAME_OVER_DELAY 1000
#define MAX_LENGTH 100
#define TIMEOUT 3000
#define LED_ON_TIME 1000
#define LED_OFF_TIME 250
#define DEBOUNCE_DELAY 50

/**
 * @brief Generates a random pattern for the game.
 *
 * @param pattern Array to store the generated pattern.
 * @param length Length of the pattern to generate.
 */
void generatePattern(int* pattern, int length);

/**
 * @brief Displays the generated pattern using LEDs.
 *
 * @param pattern Array containing the pattern to display.
 * @param length Length of the pattern to display.
 */
void displayPattern(int* pattern, int length);

/**
 * @brief Processes the player's input sequence and validates it.
 *
 * @param pattern Array containing the correct pattern.
 * @param length Length of the pattern to validate.
 * @return true if the player's input matches the pattern.
 * @return false if the input does not match or times out.
 */
bool processPlayerSequence(int* pattern, int length);

/**
 * @brief Validates if a player's button press matches the pattern.
 *
 * @param pattern Array containing the correct pattern.
 * @param button The button number pressed.
 * @param index The current index in the pattern.
 * @return true if the button press matches the pattern.
 * @return false if the button press does not match.
 */
bool validatePlayerInput(int* pattern, int button, int index);

/**
 * @brief Checks if a button is pressed, applying debouncing and LED feedback.
 *
 * @param buttonPin The pin of the button being checked.
 * @param ledPin The LED pin to provide immediate feedback.
 * @return true if the button press is confirmed.
 * @return false otherwise.
 */
bool isButtonPressed(int buttonPin, int ledPin);

/**
 * @brief Handles game over scenario.
 */
void gameOver();

/**
 * @brief Various sound functions
 */
void playStartupTune();
void playWinTune();
void playGameOverTune();

/**
 * @brief Plays a series of notes with specified durations.
 *
 * @param notes Array of note frequencies.
 * @param durations Array of note durations.
 * @param size Number of notes in the arrays.
 */
void playTune(int* notes, int* durations, int size);

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);

  randomSeed(analogRead(A0));  // Initialize random number generator with noise

  Serial.begin(9600);
  Serial.println("Welcome to Simon Says!");
  playStartupTune();
}

void loop() {
  static int pattern[MAX_LENGTH];
  static int patternLength = 1;  // Keep track of progress across loops

  Serial.print("Level ");
  Serial.println(patternLength);

  generatePattern(pattern, patternLength);
  displayPattern(pattern, patternLength);

  if (!processPlayerSequence(pattern, patternLength)) {
    gameOver();
    patternLength = 1;  // Reset game
    return;             // Break loop
  }

  playWinTune();
  Serial.println("Correct! Pattern length: " + String(patternLength));

  patternLength++;

  if (patternLength > MAX_LENGTH) {
    Serial.println("Impossibly, you have completed the game. Congratulations.");
    playWinTune();
    delay(GAME_OVER_DELAY);
    patternLength = 1;
  }
  delay(GAME_OVER_DELAY);
}


void generatePattern(int* pattern, int length) {
  pattern[length - 1] = random(1, 3);
}

void displayPattern(int* pattern, int length) {
  Serial.println("Watch the pattern!");
  for (int i = 0; i < length; i++) {
    int ledPin = (pattern[i] == 1) ? LED_1 : LED_2;
    digitalWrite(ledPin, HIGH);
    delay(LED_ON_TIME);
    digitalWrite(ledPin, LOW);
    delay(LED_OFF_TIME);
  }
}

bool processPlayerSequence(int* pattern, int length) {
  int playerTurn = 0;
  unsigned long startTime = millis();

  while (playerTurn < length) {
    if (millis() - startTime > TIMEOUT) {
      Serial.println("Time's up!");
      return false;
    }
    if (digitalRead(BUTTON_1) == HIGH && isButtonPressed(BUTTON_1, LED_1)) {
      if (!validatePlayerInput(pattern, 1, playerTurn++)) return false;
      startTime = millis();
    }
    if (digitalRead(BUTTON_2) == HIGH && isButtonPressed(BUTTON_2, LED_2)) {
      if (!validatePlayerInput(pattern, 2, playerTurn++)) return false;
      startTime = millis();
    }
  }
  return true;
}

bool validatePlayerInput(int* pattern, int button, int index) {
  if (pattern[index] != button) {
    Serial.println("Wrong input!");
    return false;
  }
  return true;
}

bool isButtonPressed(int buttonPin, int ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(DEBOUNCE_DELAY);
  if (digitalRead(buttonPin) == HIGH) {
    while (digitalRead(buttonPin) == HIGH)
      ;
    digitalWrite(ledPin, LOW);
    return true;
  }
  digitalWrite(ledPin, LOW);
  return false;
}

void gameOver() {
  playGameOverTune();
  Serial.println("Game over.");
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

void playGameOverTune() {
  int notes[] = { 400, 300 };
  int durations[] = { 300, 300 };
  playTune(notes, durations, 2);
}

void playTune(int* notes, int* durations, int size) {
  for (int i = 0; i < size; ++i) {
    tone(PIEZO, notes[i], durations[i]);  // Play a single note
    delay(durations[i] + 50);             // Delay between notes
    noTone(PIEZO);
  }
}