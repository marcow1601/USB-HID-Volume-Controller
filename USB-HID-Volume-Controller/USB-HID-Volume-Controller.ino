// NicoHood's Arduino HID project library
#include <HID-Project.h>
#include <HID-Settings.h>

// Paul Stoffregen's Encoder library
#include <Encoder.h>

#define ROTARY_A 0
#define ROTARY_B 1
#define ROTARY_SW 7

volatile boolean rotary_sw_pressed = false;

long oldPosition  = -999;
// Instantiate rotary encoder
Encoder rotary(ROTARY_A, ROTARY_B);


// Interrupt service routine of rotary encoder switch
void isr_sw(){
  rotary_sw_pressed = true;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting USB-HID Volume Controller");
  
  // Attach external interrupt to switch of the rotary encoder
  attachInterrupt(digitalPinToInterrupt(ROTARY_SW), isr_sw, FALLING);
  
}

void loop() {
  if(rotary_sw_pressed){
    Serial.println("SW");
    rotary_sw_pressed = false;
  }

  long newPosition = rotary.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }

}
