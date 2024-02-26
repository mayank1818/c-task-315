// Defining Led Pins
#define RED_LED 7
#define GREEN_LED 6

// Defining Sensors Pins
#define FIRST_MOTION_SENSOR 2
#define SOIL_MOISTURE_SENSOR 3  // Replace with the appropriate pin for your soil moisture sensor

volatile bool firstMotionDetected = false;
volatile bool soilMoistureDetected = false;
volatile int firstSensorValue = 0;
volatile int soilMoistureValue = 0;

void setup()
{
  Serial.begin(9600);

  // Setting pin Mode of Actuators (LEDS) and Sensors
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(FIRST_MOTION_SENSOR, INPUT);
  pinMode(SOIL_MOISTURE_SENSOR, INPUT);

  // Attaching the interrupts
  attachInterrupt(digitalPinToInterrupt(FIRST_MOTION_SENSOR), firstMotionISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SOIL_MOISTURE_SENSOR), soilMoistureISR, CHANGE);
}

void loop()
{
  // Your main loop code can go here if needed
}

void firstMotionISR()
{
  static bool value = LOW;
  value = !value;
  digitalWrite(RED_LED, value);
  firstMotionDetected = value;

  if (firstMotionDetected)
  {
    firstSensorValue = analogRead(FIRST_MOTION_SENSOR);
    // Printing the Analog Value of First Motion Sensor when motion detected
    Serial.print("Motion Detected AND VALUE OF PIR 1: ");
    Serial.println(firstSensorValue);
  }
}

void soilMoistureISR()
{
  static bool value = LOW;
  value = !value;
  digitalWrite(GREEN_LED, value);
  soilMoistureDetected = value;

  if (soilMoistureDetected)
  {
    soilMoistureValue = analogRead(SOIL_MOISTURE_SENSOR);
    // Printing the Analog Value of Soil Moisture Sensor when moisture detected
    Serial.print("Soil Moisture Detected AND VALUE OF SOIL MOISTURE SENSOR: ");
    Serial.println(soilMoistureValue);
  }
}
