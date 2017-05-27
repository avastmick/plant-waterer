/*
Refer to README for connection information
*/
// Variables
// If the sensor returns a higher value than this - water
int dryValue = 850;
// Sensor values
int sensorValue = 0;
// Connections
// Green light power connects to pin            D13
int greenLED = 13;
// Soil moisture sensor connects to Analog pin  A0
int soilSensor = 0;
// Connect the "IN" on the relay to pin         D3
int relay = 3;
/*
Setup
*/
void setup()
{
    // Start recording text at the Serial Monitor
    Serial.begin(9600);
    // Use a green led to some running state
    pinMode(greenLED, OUTPUT);
    // Setup relay to control pump
    pinMode(relay, OUTPUT);
    Serial.println("Monitoring - START");
}

/*
Loop @ ~1 sec
*/
void loop()
{
    // When the relay voltage is "low", pump is 'off'
    digitalWrite(relay, LOW);
    // Read from moisture sensor
    sensorValue = analogRead(soilSensor);
    Serial.println(sensorValue);
    if (sensorValue < dryValue)
        // Wet == low sensor values
    {
        Serial.println("No need to water");
        // TODO:0 Wait here 4 hours (no need for constant monitoring) id:3
        // Is this efficient?
        // delay(14400000);
    }
    else // Dry == high values
    {
        // Toggle green led to show running state
        digitalWrite(greenLED, HIGH);
        Serial.println("Watering now...");
        // Turn voltage to relay to high so power to pump is on
        digitalWrite(relay, HIGH);
    }
    // Wait a while to allow water absorption
    // TODO:0 there is some condition here that this is not working - need to turn off pump after n milliseconds, then re-test id:4
    delay(1000); // % seconds, then rechecking...
    digitalWrite(greenLED, LOW); // Toggle green led
    digitalWrite(relay, LOW); // Turn off the pump
}
