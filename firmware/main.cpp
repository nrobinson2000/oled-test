#include "Particle.h"
#include "oled-wing-adafruit/oled-wing-adafruit.h"

OledWingAdafruit display;

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

void startupTasks()
{
        Serial.begin(115200);
}
STARTUP(startupTasks());

int cloudOledPrint(const char *message)
{
        display.clearDisplay();

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println(message);
        display.display();

        return 0;
}

void setup() // Put setup code here to run once
{
        pinMode(BATT, INPUT);

        display.setup();
        display.clearDisplay();
        display.display();

        Particle.connect();
        Particle.function("oled", cloudOledPrint);
}

void oledPrint(const char *message)
{
        display.clearDisplay();

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println(message);
        display.display();
}

void loop() // Put code here to loop forever
{
        static uint32_t msDelay = 0;
        static bool printStats = false;

        display.loop();

        if (printStats) {
                if (millis() - msDelay > 1000) {
                        msDelay = millis();
                        double voltage = analogRead(BATT) * 0.0011224;
                        char message[40];
                        snprintf(message, sizeof(message), "%ld seconds %.2f volts", millis() / 1000, voltage);
                        oledPrint(message);
                }
        }


        if (display.pressedA()) {
                display.clearDisplay();

                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(0,0);
                display.println("BIG CHUNGUS");
                display.display();
        }

        if (display.pressedB()) {

        }

        if (display.pressedC()) {
                display.clearDisplay();
                display.display();
                printStats=!printStats;
        }
}
