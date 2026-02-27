#include "SPI.h" 
#include "Adafruit_GFX.h" 
#include "Adafruit_GC9A01A.h" 
 
// Pin Definitionen 
#define TFT_CS 10 
#define TFT_DC 7 
#define TFT_RST 8 
 
Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST); 
 
#define COLOR_YELLOW 0xFFE0  
#define COLOR_RED    0xF800 
#define COLOR_BLACK  0x0000 
 
void setup() { 
  tft.begin(); 
  tft.setRotation(0); 
  tft.fillScreen(COLOR_BLACK); 
} 
 
// Hilfsfunktion für die Sektoren (Blätter) 
// Anmerkung Max: offset hinzugefügt, um Rotation zu ermöglichen
void drawSectors(int16_t x, int16_t y, int16_t r, float offset) { 
  // ISO-Winkel: Drei 60° Sektoren bei 90°, 210° und 330° 
  float angles[] = {90.0, 210.0, 330.0}; 
   
  for (int a = 0; a < 3; a++) { 
    for (float i = 0; i < 60; i += 2.0) { 
      float rad1 = (angles[a] + i + offset) * 0.017453; 
      float rad2 = (angles[a] + i + 2.1 + offset) * 0.017453; 
       
      tft.fillTriangle(x, y,  
                       x + cos(rad1) * r, y + sin(rad1) * r,  
                       x + cos(rad2) * r, cy + sin(rad2) * r, // Anmerkung Max: cy korrigiert zu y 
                       COLOR_BLACK); 
    } 
  } 
} 
 
// Anmerkung Max: Parameter offset ergänzt
void drawRadioactive(uint16_t symbolColor, float offset) { 
  int16_t cx = 120; 
  int16_t cy = 120; 
  int16_t r = 110; 
 
  // 1. Hintergrund-Kreis (Gelb oder Rot) 
  tft.fillCircle(cx, cy, r, symbolColor); 
 
  // 2. Schwarze Flügel zeichnen 
  drawSectors(cx, cy, r - 2, offset); 
 
  // 3. Innerer Ring (Abstandshalter) 
  tft.fillCircle(cx, cy, r * 0.25, symbolColor); 
 
  // 4. Zentraler Kern 
  tft.fillCircle(cx, cy, r * 0.2, COLOR_BLACK); 
} 
 
void loop() { 
  // Anmerkung Max: Gelbe Rotation (einmal 360 Grad)
  for (int angle = 0; angle < 360; angle += 15) {
    drawRadioactive(COLOR_YELLOW, angle); 
  }
 
  // Anmerkung Max: 3x Rotes Blinken
  for (int i = 0; i < 3; i++) {
    drawRadioactive(COLOR_RED, 0); 
    delay(300);
    tft.fillScreen(COLOR_BLACK);
    delay(200);
  }
} 

/*
Anmerkung Max: 
* drawSectors/drawRadioactive um "offset" erweitert, damit der Winkel variabel ist.
* In setup/loop die feste Abfolge durch zwei for-Schleifen ersetzt.
* Schrittweite in der Rotation auf 15 Grad gesetzt für flüssiges Zeichnen.
* Kleinen Tippfehler im originalen fillTriangle (cy statt y) korrigiert.
*/
