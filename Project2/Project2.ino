#define BUTTON_1 A2
#define BUTTON_2 A3
#define LED_1 A1
#define LED_2 A4
#define PIEZO A5

#define GAME_OVER_DELAY 1000

#define MAX_LENGTH 100

#define TIMEOUT 3000

/**
 * @brief Generates a random pattern of given length.
 * 
 * @param pattern Array to store the generated pattern.
 * @param length Length of the pattern to generate.
 */
void generatePattern(int pattern[], int length);

/**
 * @brief Displays the generated pattern using LEDs.
 * 
 * @param pattern Array containing the pattern to display.
 * @param length Length of the pattern to display.
 */
void displayPattern(int pattern[], int length);

/**
 * @brief Gets and validates the player's input against the pattern.
 * 
 * @param pattern Array containing the correct pattern.
 * @param length Length of the pattern to validate.
 * @return true if the input matches the pattern.
 * @return false if the input does not match or times out.
 */
bool getPlayerInput(int pattern[], int length);

/**
 * @brief Handles individual button presses and validates against the pattern.
 * 
 * @param pattern Array containing the correct pattern.
 * @param button The button number pressed.
 * @param led The corresponding LED to light up.
 * @param index The current index in the pattern.
 * @return true if the button press matches the pattern.
 * @return false if the button press does not match the pattern.
 */
bool handlePlayerInput(int pattern[], int button, int led, int index);

/**
 * @brief Handles game over scenario.
 */
void gameOver();


void playStartupTune();

void playWinTune();

void playFailureTone();

void playGameOverTune();

/**
 * @brief Plays a series of notes with specified durations.
 * 
 * @param notes Array of note frequencies.
 * @param durations Array of note durations.
 * @param size Number of notes in the arrays.
 */
void playTune(int *notes, int *durations, int size);

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  randomSeed(analogRead(A0)); // Initialize the random seed with a noise value
  Serial.begin(9600);
  Serial.println("Welcome to Simon Says!");
  playStartupTune(); // Play a tune at the start of the game
}

void loop() {
  static int pattern[MAX_LENGTH];
  static int patternLength = 0;
  static int level = 0;

  patternLength = 1; // Start with a single pattern length
  level = 1; // Initial game level

  while (true) {
    Serial.print("Level ");
    Serial.println(level);
    generatePattern(pattern, patternLength); // Generate a new pattern
    displayPattern(pattern, patternLength); // Display the generated pattern
    if (!getPlayerInput(pattern, patternLength)) { // Get and validate player's input
      gameOver(); // End the game if input is incorrect
      return;
    }
    playWinTune(); // Play a tune indicating success
    Serial.print("Correct! Pattern length: ");
    Serial.println(patternLength);
    ++patternLength; // Increment pattern length for next round
    ++level; // Increment game level
    if (patternLength > MAX_LENGTH) { // Check if maximum length is reached
      Serial.println("You win! You've completed the pattern!");
      playWinTune(); // Play a tune indicating overall win
      delay(GAME_OVER_DELAY);
      return;
    }
    delay(1000); // Delay before starting the next round
  }
}

void generatePattern(int pattern[], int length) {
  pattern[length - 1] = random(1, 3); // Generate a random pattern element (1 or 2)
  // Serial.println(pattern[length - 1]);
}

void displayPattern(int pattern[], int length) {
  Serial.println("Watch the pattern!");
  for (int i = 0; i < length; ++i) {
    digitalWrite(LED_1, pattern[i] == 1); // Light up LED_1 if pattern element is 1
    digitalWrite(LED_2, pattern[i] == 2); // Light up LED_2 if pattern element is 2
    delay(1000); // Keep LED on for 1 second
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    delay(250); // Short delay before next element
  }
}

bool getPlayerInput(int pattern[], int length) {
  int playerTurn = 0;
  unsigned long startTime = millis(); // Record the start time for timeout handling
  while (playerTurn < length) {
    if (millis() - startTime > TIMEOUT) { // Check if player has timed out
      Serial.println("Time's up!");
      return false;
    }
    if (digitalRead(BUTTON_1) == HIGH) {
      if (!handlePlayerInput(pattern, 1, LED_1, playerTurn++)) return false; // Handle input for BUTTON_1
    }
    if (digitalRead(BUTTON_2) == HIGH) {
      if (!handlePlayerInput(pattern, 2, LED_2, playerTurn++)) return false; // Handle input for BUTTON_2
    }
  }
  return true;
}

bool handlePlayerInput(int pattern[], int button, int led, int index) {
  Serial.print("Button ");
  Serial.print(button);
  Serial.println(" pressed!");
  digitalWrite(led, HIGH); // Light up the corresponding LED
  delay(200);
  digitalWrite(led, LOW);
  if (pattern[index] != button) { // Check if player input matches the pattern
    Serial.println("Wrong input!");
    return false;
  }
  return true;
}

void gameOver() {
  playFailureTone(); // Play a tone indicating failure
  Serial.println("Game over.");
  //playGameOverTune();
  delay(GAME_OVER_DELAY); // Delay before game reset
}

void playStartupTune() {
  int notes[] = { 262, 330, 392, 523 };
  int durations[] = { 200, 200, 200, 400 };
  playTune(notes, durations, 4); // Play a sequence of notes
}

void playWinTune() {
  int winNotes[] = { 523, 587, 659, 698 };
  int durations[] = { 150, 150, 150, 300 };
  playTune(winNotes, durations, 4); // Play a sequence of notes indicating success
}

void playFailureTone() {
  tone(PIEZO, 300, 500); // Play a single failure tone
  delay(500);
  noTone(PIEZO);
}

void playGameOverTune() {
  int notes[] = { 400, 300 };
  int durations[] = { 300, 300 };
  playTune(notes, durations, 2); // Play a sequence of notes indicating game over
}

void playTune(int *notes, int *durations, int size) {
  for (int i = 0; i < size; ++i) {
    tone(PIEZO, notes[i], durations[i]); // Play a single note
    delay(durations[i] + 50); // Delay between notes
    noTone(PIEZO);
  }
}
