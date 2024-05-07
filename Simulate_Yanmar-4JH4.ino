#include <CAN.h>

// Define J1939 PGNs (Parameter Group Numbers) for engine data
#define ENGINE_SPEED_PGN 61444
#define COOLANT_TEMPERATURE_PGN 65260
#define OIL_TEMPERATURE_PGN 65261
#define ENGINE_RUN_HOURS_PGN 65253
#define ALTERNATOR_VOLTAGE_PGN 65262
#define ALTERNATOR_CURRENT_PGN 65263
// Define more PGNs for other engine parameters as needed

// Define engine parameters
float engineSpeed = 0.0; // RPM
float coolantTemperature = 0.0; // Celsius
float oilTemperature = 0.0; // Celsius
float engineRunHours = 0.0; // Hours
float alternatorVoltage = 0.0; // Volts
float alternatorCurrent = 0.0; // Amperes
// Define more parameters as needed

// Variables to track the last transmission time for each type of data
unsigned long lastEngineSpeedTransmission = 0;
unsigned long lastTemperatureTransmission = 0;
unsigned long lastEngineRunHoursTransmission = 0;
unsigned long lastAlternatorTransmission = 0;

void setup() {
  // Initialize CAN bus at 500 kbps
  CAN.begin(500E3);
}

void loop() {
  // Simulate engine operation
  simulateEngine();

  unsigned long currentTime = millis();

  // Send engine speed every second
  if (currentTime - lastEngineSpeedTransmission >= 1000) {
    sendEngineSpeed();
    lastEngineSpeedTransmission = currentTime;
  }

  // Send temperatures every 5 seconds
  if (currentTime - lastTemperatureTransmission >= 5000) {
    sendCoolantTemperature();
    sendOilTemperature();
    lastTemperatureTransmission = currentTime;
  }

  // Send engine run hours every 10 seconds
  if (currentTime - lastEngineRunHoursTransmission >= 10000) {
    sendEngineRunHours();
    lastEngineRunHoursTransmission = currentTime;
  }

  // Send alternator data every 10 seconds
  if (currentTime - lastAlternatorTransmission >= 10000) {
    sendAlternatorData();
    lastAlternatorTransmission = currentTime;
  }
}

void simulateEngine() {
  // Simulate engine speed, coolant, and oil temperature changes
  engineSpeed = random(1000, 3000); // Random RPM between 1000 and 3000
  coolantTemperature = random(50, 100); // Random coolant temperature between 50 and 100 Celsius
  oilTemperature = random(50, 120); // Random oil temperature between 50 and 120 Celsius
  // Simulate engine run hours incrementing by 0.001 hour each iteration
  engineRunHours += 0.001;
  // Simulate alternator voltage and current
  alternatorVoltage = random(11, 15); // Random voltage between 11 and 15 volts
  alternatorCurrent = random(20, 50); // Random current between 20 and 50 amperes
  // Simulate more engine parameters
}

void sendEngineSpeed() {
  // Create CAN message for engine speed
  CANMessage speedMessage;
  speedMessage.id = ENGINE_SPEED_PGN;
  speedMessage.len = 8;
  speedMessage.buf[0] = (int)engineSpeed & 0xFF;
  speedMessage.buf[1] = ((int)engineSpeed >> 8) & 0xFF;
  // Add more bytes for extended data
  
  // Send engine speed message
  CAN.send(speedMessage);
}

void sendCoolantTemperature() {
  // Create CAN message for coolant temperature
  CANMessage coolantTempMessage;
  coolantTempMessage.id = COOLANT_TEMPERATURE_PGN;
  coolantTempMessage.len = 8;
  coolantTempMessage.buf[0] = (int)coolantTemperature & 0xFF;
  coolantTempMessage.buf[1] = ((int)coolantTemperature >> 8) & 0xFF;
  // Add more bytes for extended data
  
  // Send coolant temperature message
  CAN.send(coolantTempMessage);
}

void sendOilTemperature() {
  // Create CAN message for oil temperature
  CANMessage oilTempMessage;
  oilTempMessage.id = OIL_TEMPERATURE_PGN;
  oilTempMessage.len = 8;
  oilTempMessage.buf[0] = (int)oilTemperature & 0xFF;
  oilTempMessage.buf[1] = ((int)oilTemperature >> 8) & 0xFF;
  // Add more bytes for extended data
  
  // Send oil temperature message
  CAN.send(oilTempMessage);
}

void sendEngineRunHours() {
  // Create CAN message for engine run hours
  CANMessage runHoursMessage;
  runHoursMessage.id = ENGINE_RUN_HOURS_PGN;
  runHoursMessage.len = 8;
  int runHoursInt = (int)(engineRunHours * 3600); // Convert hours to seconds
  runHoursMessage.buf[0] = runHoursInt & 0xFF;
  runHoursMessage.buf[1] = (runHoursInt >> 8) & 0xFF;
  runHoursMessage.buf[2] = (runHoursInt >> 16) & 0xFF;
  runHoursMessage.buf[3] = (runHoursInt >> 24) & 0xFF;
  // Add more bytes for extended data if needed
  
  // Send engine run hours message
  CAN.send(runHoursMessage);
}

void sendAlternatorData() {
  // Create CAN message for alternator voltage
  CANMessage voltageMessage;
  voltageMessage.id = ALTERNATOR_VOLTAGE_PGN;
  voltageMessage.len = 8;
  voltageMessage.buf[0] = (int)alternatorVoltage & 0xFF;
  voltageMessage.buf[1] = ((int)alternatorVoltage >> 8) & 0xFF;
  // Add more bytes for extended data if needed
  
  // Send alternator voltage message
  CAN.send(voltageMessage);

  // Create CAN message for alternator current
  CANMessage currentMessage;
  currentMessage.id = ALTERNATOR_CURRENT_PGN;
  currentMessage.len = 8;
  currentMessage.buf[0] = (int)alternatorCurrent & 0xFF;
  currentMessage.buf[1] = ((int)alternatorCurrent >> 8) & 0xFF;
  // Add more bytes for extended data if needed
  
  // Send alternator current message
  CAN.send(currentMessage);
}
