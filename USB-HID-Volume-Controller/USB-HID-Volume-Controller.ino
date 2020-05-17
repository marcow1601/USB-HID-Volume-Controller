// NicoHood's Arduino HID project library
#include <HID-Project.h>
#include <HID-Settings.h>

// Paul Stoffregen's Encoder library
#include <Encoder.h>

#define ROTARY_A 0
#define ROTARY_B 1
#define ROTARY_SW 7

// USB HID device configuration
static boolean ROTARY_INVERTED = true; // Rotary motion direction inverted
static int ROTARY_SPEED = 2; // Encoder clicks per step



volatile boolean rotary_sw_pressed = false;

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

  // Sends a clean report to the host
  Consumer.begin();
  
}

void loop() {
  if(rotary_sw_pressed){
    Serial.println("SW");
    Consumer.write(MEDIA_PLAY_PAUSE);
    rotary_sw_pressed = false;
  }

  if(abs(rotary.read()) >= 4*ROTARY_SPEED){
    if(rotary.read() < 0) {
      if(!ROTARY_INVERTED) Consumer.write(MEDIA_VOLUME_DOWN);
      else Consumer.write(MEDIA_VOLUME_UP);
      
    }
    else {
      if(!ROTARY_INVERTED) Consumer.write(MEDIA_VOLUME_UP);
      else Consumer.write(MEDIA_VOLUME_DOWN);
    }

    rotary.write(0);
  }
 
}
