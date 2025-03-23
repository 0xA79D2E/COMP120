// Define component pins according to STM32 F-401RE pinout
#define LED_R A0
#define BUTTON_R D7

// #define LED_L A1
// #define BUTTON_L D6


/**
 * @brief button structure to handle debounce logic 
 */
typedef struct Button {
  int buttonState;
  int lastButtonState = LOW;
  unsigned long lastDebounceTime = 0;
} Button;

unsigned long debounceDelay = 10;

Button buttonR = { LOW, LOW, 0 };
// Button buttonL = { LOW, LOW, 0 };

int debounceButton(Button &btn, int pin);

void setup() {
  Serial.begin(9600);  // Start serial communication

  pinMode(LED_R, OUTPUT);
  // pinMode(LED_L, OUTPUT);

  pinMode(BUTTON_R, INPUT);
  // pinMode(BUTTON_L, INPUT);
}

void loop() {
  // Get debounced button states
  int stateR = Debounce(buttonR, BUTTON_R);
  // int stateL = Debounce(buttonL, BUTTON_L);

  // Set LED states based on button states
  digitalWrite(LED_R, stateR);
  // digitalWrite(LED_L, stateL);

  // Print button states for debugging
  Serial.print("Button R: ");
  Serial.print(stateR);
  // Serial.print(" | Button L: ");
  // Serial.println(stateL);
}


/**
 * @brief Debounces a button press.
 * 
 * @param btn Reference to a Button struct.
 * @param pin The digital pin the button is connected to.
 * @return int The debounced button state (HIGH/LOW).
 */
int Debounce(Button &btn, int pin) {
  int reading = digitalRead(pin);  // Read the button state

  // If the button state changed, reset the debounce timer
  if (reading != btn.lastButtonState) {
    btn.lastDebounceTime = millis();
  }

  // If enough time has passed, update the button state
  if ((millis() - btn.lastDebounceTime) > debounceDelay) {
    if (reading != btn.buttonState) {
      btn.buttonState = reading;  // Update state if it's stable
    }
  }

  btn.lastButtonState = reading;  // Update lastButtonState for next loop
  return btn.buttonState;
}
