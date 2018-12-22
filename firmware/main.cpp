#include "Particle.h"
#include "oled-wing-adafruit/oled-wing-adafruit.h"

OledWingAdafruit display;

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void startupTasks()
{
  Serial.begin(115200);
}
STARTUP(startupTasks());


void setup() // Put setup code here to run once
{
  display.setup();

  	display.clearDisplay();
  	display.display();
}

void loop() // Put code here to loop forever
{
  display.loop();

  	if (display.pressedA()) {
  		display.clearDisplay();

  		display.setTextSize(1);
  		display.setTextColor(WHITE);
  		display.setCursor(0,0);
  		display.println("CHUNGUS");
  		display.display();
  	}

  	if (display.pressedB()) {
  	}

  	if (display.pressedC()) {
  	}
}
