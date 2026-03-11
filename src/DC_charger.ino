#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD object setup
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 if your I2C scanner shows a different address

// Pin Definitions
const int button6V = 2;
const int button9V = 3;
const int mosfetPin = 6;

// Track selected voltage
int selectedVoltage = 0;  // 0 = none, 6 = 6V, 9 = 9V

void setup() {
  // Button pins
  pinMode(button6V, INPUT_PULLUP);
  pinMode(button9V, INPUT_PULLUP);

  // MOSFET control
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW); // OFF initially

  // LCD setup
  lcd.init();
  lcd.backlight();

  // Default message
  showWelcomeMessage();
}

void loop() {
  // 6V button pressed
  if (digitalRead(button6V) == LOW) {
    if (selectedVoltage != 6) {       // Only update if new
      selectedVoltage = 6;
      applyVoltage();
    }
    delay(200); // debounce
  }

  // 9V button pressed
  if (digitalRead(button9V) == LOW) {
    if (selectedVoltage != 9) {       // Only update if new
      selectedVoltage = 9;
      applyVoltage();
    }
    delay(200); // debounce
  }
}

// ---------- FUNCTIONS ----------
void applyVoltage() {
  digitalWrite(mosfetPin, HIGH); // Enable output
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage Selected:");
  lcd.setCursor(0, 1);
  lcd.print(String(selectedVoltage) + "V Output");
}

void showWelcomeMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please select");
  lcd.setCursor(0, 1);
  lcd.print("voltage: 6V/9V");
}
