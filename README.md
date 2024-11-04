# AC_CURRENT_MEASUREMENT
## Project overview

Develop a system that measures AC current irrespective of the load and calculates the energy consumed in kilowatt-hours (kWh). The system will utilize an STM32F103C8T6 microcontroller and a ZMCT103 current sensor. The data will be saved in EEPROM and displayed on an LCD to show the current energy consumption. The project will leverage I2C, UART, and timer functionalities.

## Key Features

1. AC Current Measurement: Accurately measure AC current with the ZMCT103 sensor.
2. Energy Calculation: Calculate energy consumption in kWh based on measured current.
3. Data Storage: Save measurement data in EEPROM for later analysis.
3. User Interface: Display current energy consumption on an LCD.
4. Communication Interfaces: Utilize I2C for the EEPRom and timers for periodic updates.

## Components Needed

1. STM32F103C8T6 Microcontroller: Central processing unit for the project.
2. ZMCT103 Current Sensor: For measuring AC current.
3. LCD Display: To show the current energy consumed.
4. EEPROM: For storing measurement data.
5. Supporting Components: Breadboard, jumper wires, power supply, etc.

## Project Plan
### 1. Set Up Development Environment
(i) Install VS Code and necessary libraries for STM32 development.
### 2. Configure Hardware
(i)Microcontroller Setup: Connect the ZMCT103 sensor and LCD to the STM32.
### 3. Firmware Development
#### (i) Initialize Peripherals:
* Current Sensor Configuration: Set up the ZMCT103 for accurate current measurement.
* LCD Configuration: Configure the LCD for displaying information via I2C.
* Timer Setup: Set timers for periodic updates to the LCD.
### 4. Data Acquisition and Processing:
#### (i) Measure current and calculate energy consumed.
#### (ii) Store data in EEPROM.
### 5. User Interface:
#### (i) Implement functions to display current energy consumption on the LCD.
## Detailed Steps
### 1. Set Up Current Sensor
#### (i) Connect the ZMCT103 to the STM32 and calibrate for accurate readings.
### 2. Configure LCD via I2C
#### (i) Set up I2C communication and display relevant information on the LCD.
### 3. Implement Data Storage
#### (i) Define EEPROM structure for storing current measurements and energy calculations.
### 4. Create Timer Interrupts
#### (i) Set up a timer to update the LCD display with current energy consumption at regular intervals.
### 5. Final Validation
#### (i) Test the system by measuring known AC loads and verifying the energy calculations.
