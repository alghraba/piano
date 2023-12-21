#include "rgb_lcd.h"
#include <Wire.h>

rgb_lcd lcd;
int buttonPin = 5;
int buzzer = 6;
int buttonState = 0;
int lastButtonState = 0;
int note = 0;

const char* noteNames[] = {"DO", "RE", "MI", "FA"};

void setup()
{
 lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
 lcd.setRGB(255,215,0);  // Set the LCD backlight color (green)
 pinMode(buzzer, OUTPUT);
 pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      // Bouton enfoncé
      note++;
      if (note >= 4) {
        note = 0;
      }
      playNote(note);
      displayNoteName(note-1);
    }
    lastButtonState = buttonState;
  }
}
void playNote(int note) {
  int frequencies[] = {262, 294, 330, 349}; // Fréquences des notes (Do, Ré, Mi, Fa)

  tone(buzzer, frequencies[note]);  // Jouer la note sur le buzzer
  delay(500);  // Jouer la note pendant 0.5 seconde
  noTone(buzzer);  // Arrêter le son
}
void displayNoteName(int note) {
  lcd.setCursor(0, 0);
  lcd.print("Note:       ");
  lcd.setCursor(0, 1);
  lcd.print(noteNames[note]);
  delay(1000);  // Display the note name for 2 seconds
  lcd.clear();
}