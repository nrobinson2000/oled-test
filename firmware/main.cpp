#include "Particle.h"
#include "oled-wing-adafruit/oled-wing-adafruit.h"

OledWingAdafruit display;

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

void startupTasks()
{
        Serial.begin(115200);
        RGB.control(true);
        RGB.brightness(2);
        RGB.control(false);
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
        display.loop();

        static bool printStats = true;
        if (printStats) {
                static unsigned long msDelay = 0;
                if (millis() - msDelay >= 1000) {
                        msDelay = millis();
                        double voltage = analogRead(BATT) * 0.0011224;
                        int rssi = WiFi.RSSI().rssi;
                        double signalQuality = WiFi.RSSI().getQuality();
                        char message[100];
                        snprintf(message, sizeof(message), "u:%ld v:%.2f r:%d\ns:%.2f t:%ld", millis() / 1000, voltage, rssi, signalQuality, Time.now());
                        oledPrint(message);
                }
        }


        if (display.pressedA()) {
                display.clearDisplay();

                display.setTextSize(4);
                display.setTextColor(WHITE);
                display.setCursor(0,0);
                display.println("DERP!");
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
