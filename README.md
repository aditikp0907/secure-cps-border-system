# Secure Cyber-Physical Border Monitoring System

## Overview

This project is a simulated Cyber-Physical System (CPS) designed to detect physical intrusions and cyber threats such as sensor spoofing and data tampering.

## Features

* Dual ultrasonic sensor-based intrusion detection
* Cyber attack detection (sensor spoofing)
* Data integrity validation (tamper detection)
* High Alert Mode based on repeated threats
* LCD-based real-time monitoring
* Audio-visual alert system

## System Architecture

Physical Layer: Sensors (Ultrasonic)
Cyber Layer: Arduino-based logic and validation
Control Layer: LED, Buzzer, LCD

## Security Features

* Spoofing detection using sensor mismatch logic
* Simulated secure data validation using key-based verification
* Event counting and threat escalation

## Technologies Used

* Arduino (C++)
* Wokwi Simulation
* Embedded Systems
* Cyber-Physical Systems

## How to Run

1. Open project in Wokwi
2. Upload code
3. Simulate intrusion by adjusting sensor distance
4. Enable tampering by setting `simulateTamper = true`

## Future Improvements

* AI-based anomaly detection
* Integration with real-time alert systems
* Cloud-based logging
* Camera or drone integration

## Author

Aditi
