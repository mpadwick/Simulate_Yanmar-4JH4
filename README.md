# Yanmar Engine Simulator Sketch

This Arduino sketch simulates engine data for a Yanmar engine using an ESP32 microcontroller and sends the data over the onboard CAN controller using the J1939 protocol. The sketch simulates various engine parameters such as engine speed, coolant temperature, oil temperature, engine run hours, alternator voltage, and alternator current.

## Description

The sketch uses the CAN library to send J1939 messages over the CAN bus. It includes functions to simulate engine operation and to send different types of engine data at specified intervals. The simulation is based on random values within realistic ranges for each parameter.

## Engine Parameters

- **Engine Speed**: Simulates the RPM (revolutions per minute) of the engine.
- **Coolant Temperature**: Simulates the temperature of the engine coolant in Celsius.
- **Oil Temperature**: Simulates the temperature of the engine oil in Celsius.
- **Engine Run Hours**: Simulates the total run time of the engine in hours.
- **Alternator Voltage**: Simulates the voltage output of the alternator in volts.
- **Alternator Current**: Simulates the current output of the alternator in amperes.

## Timing of Data Transmission

- **Engine Speed**: Sent every second.
- **Coolant Temperature** and **Oil Temperature**: Sent every 5 seconds.
- **Engine Run Hours**: Sent every 10 seconds.
- **Alternator Voltage** and **Alternator Current**: Sent every 10 seconds.

## How It Works

1. The sketch initializes the CAN bus at a baud rate of 500 kbps.
2. In the `loop()` function, the engine operation is simulated using the `simulateEngine()` function.
3. Engine data is sent periodically based on the specified intervals using separate functions for each type of data (`sendEngineSpeed()`, `sendCoolantTemperature()`, `sendOilTemperature()`, `sendEngineRunHours()`, `sendAlternatorData()`).
4. Timing of data transmission is managed using `millis()` to track elapsed time since the last transmission of each type of data.
5. Random values within realistic ranges are generated to simulate engine parameters.
6. The CAN messages are constructed with the appropriate PGNs and data bytes and then sent over the CAN bus.

This sketch can be modified and extended to include additional engine parameters or to interface with other systems in a vehicle or marine application.
