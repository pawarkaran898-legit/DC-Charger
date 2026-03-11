## DC Charger Selector (Arduino)

This project controls a DC charger output using an Arduino, two push buttons, a MOSFET, and a 16x2 I2C LCD.  
The user can select either **6 V** or **9 V** output via dedicated buttons, and the LCD displays the selected voltage.

### Features

- **Two voltage options**: 6 V and 9 V (selectable via push buttons)
- **LCD feedback**: 16x2 I2C LCD displays prompts and the active voltage
- **MOSFET control**: Arduino drives a MOSFET gate to enable the charger output
- **Debounced input**: Simple software debounce on button presses

### Hardware

- **Microcontroller**: Arduino (e.g., Uno/Nano)
- **Display**: 16x2 LCD with I2C backpack  
  - Default I2C address: `0x27` (change in code if needed)
- **Inputs**:
  - `button6V` on digital pin `2` (wired to GND when pressed, with internal pull-up)
  - `button9V` on digital pin `3` (wired to GND when pressed, with internal pull-up)
- **Output**:
  - `mosfetPin` on digital pin `6` drives MOSFET gate

> Make sure to add appropriate gate resistor, pull-down, and protection circuitry in your actual hardware design.

### Wiring overview

- **Buttons**
  - One side of each button → Arduino pin (`2` or `3`)
  - Other side of each button → GND  
  - Internal pull-ups are enabled in code (`INPUT_PULLUP`), so the pin reads:
    - `HIGH` when not pressed  
    - `LOW` when pressed

- **LCD**
  - Connect `VCC`, `GND`, `SDA`, `SCL` to Arduino according to your board:
    - On Uno/Nano: `A4` = SDA, `A5` = SCL (or the labeled SDA/SCL pins)
  - If your LCD uses a different I2C address, update this line in `src/DC_charger.ino`:
    - `LiquidCrystal_I2C lcd(0x27, 16, 2);`

- **MOSFET**
  - Arduino pin `6` → gate (through a small resistor, e.g., 100–220 Ω)
  - Source → GND
  - Drain → negative side of load (charger output path)
  - Positive side of load → supply (+6/9 V as per your design)

### Code structure

The main sketch is in `src/DC_charger.ino` and has three core parts:

- **`setup()`**
  - Configures button pins as `INPUT_PULLUP`
  - Sets the MOSFET control pin as `OUTPUT` and turns it OFF initially
  - Initializes the I2C LCD and shows the welcome message

- **`loop()`**
  - Monitors both buttons
  - On a new button press, updates `selectedVoltage` and calls `applyVoltage()`
  - Includes a basic delay for debouncing

- **Helper functions**
  - `applyVoltage()`: enables the MOSFET and updates the LCD to show the selected voltage
  - `showWelcomeMessage()`: clears the display and prompts the user to choose 6 V or 9 V

### Dependencies

Install these libraries in the Arduino IDE:

- **LiquidCrystal I2C**
  - Library manager: search for `LiquidCrystal_I2C` (e.g., by Frank de Brabander or similar)
- **Wire** (I2C) – comes with the Arduino core

### How to build and upload

1. **Open the project**
   - Open `src/DC_charger.ino` in the Arduino IDE.
2. **Select your board and port**
   - `Tools → Board` → choose your Arduino model.
   - `Tools → Port` → select the correct COM port.
3. **Install libraries (if not already installed)**
   - `Sketch → Include Library → Manage Libraries…`
   - Search for and install `LiquidCrystal_I2C`.
4. **Compile & upload**
   - Click **Verify** to compile.
   - Click **Upload** to flash to the board.

### Future improvements

- **More voltage options** (multi-button or encoder)
- **Timeout / auto-off** for safety
- **Current/voltage sensing** with ADC and on-screen readouts
- **Configurable parameters** stored in EEPROM

### License

This project is currently unlicensed.  
If you plan to share, reuse, or accept contributions, consider adding a license file (e.g., MIT or Apache-2.0).

