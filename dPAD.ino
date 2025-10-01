/*
* dPAD
* Simple Resistor Ladder D-Pad
*
* Based on the great work by Brian Park (bxparks).
* https://github.com/bxparks/AceButton/blob/develop/docs/resistor_ladder/README.md
*
* In particular, the PCB for dPAD the Parallel Resistor
* Ladder schematic described by Brian. You rock Brian!
*
* This code written by 2025 Bryn Mosher (BPM)
* Public Domain
*/

// Pin to connect to sense ("SEN") on the circuit board.
int senPin = A1;
// Some time between allowed presses to debounce our buttons.
unsigned long debounceWait = 300;
// The last time we detected a "bounce" on our button.
unsigned long lastBounce = 0;

void setup() {
  // Wait for Serial or 2500 msec, whichever comes first.
  while(Serial.available() == 0 && millis() < 2500);
  // Degin that Serial we waited for - ready or not!
  Serial.begin(9600);
  // Set the pin for the dPAD up.
  pinMode(senPin, INPUT);
  // Announce ourselves with a line between old and new Serial output.
  Serial.println("\ndPAD setup() finished.");
}

void loop() {
  // During loop(), just call millis() once and re-use the timestamp.
  unsigned long loopStamp = millis();
  // Check if debounceWait time has passed since our last "bounce".
  // This approach not block other processing like using delay()
  // for debouncing will do.
  if (loopStamp - lastBounce > debounceWait) {
    // Read our sense pin value.
    int senValue = analogRead(senPin);
    // Check for an initial drop below the max of 1023 with a little
    // wiggle room for electrical interference.
    if (senValue < 950) {
      // We've detected some button being pushed, but we can't assume
      // it's the one with the highest value. Let's check them from
      // low to high.
      if (senValue < 75) {
        // This is the 220Ω resistor and button combo, thus
        // it will have the lowest value for the sense pin.
        // Use experimentation to derive your own values for these
        // pins. They will be dependent on factors like voltage,
        // wire length, and other sources of interference. Just
        // because B1 for me reads 20 for my use doesn't mean yours
        // will.
        Serial.print("B1 pressed. Value: ");
        Serial.println(senValue);
      } else if (senValue < 425) {
        // This is the 4.7kΩ resistor and button.
        Serial.print("B2 pressed. Value: ");
        Serial.println(senValue);
      } else if (senValue < 750) {
        // This is the 10kΩ resistor and button.
        Serial.print("B3 pressed. Value: ");
        Serial.println(senValue);
      } else {
        // This is the 47kΩ resistor and button.
        Serial.print("B4 pressed. Value: ");
        Serial.println(senValue);
      }
    }
    // We "bounced", so let's set our record of it.
    lastBounce = loopStamp;
  }
}
