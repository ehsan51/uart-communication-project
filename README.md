# UART Communication Project (PC ↔ STM32)

## Overview
This project implements a basic UART communication interface between a PC application (Windows) and an embedded system based on STM32.

The goal is to design and progressively improve a reliable, structured communication protocol between a host machine and a microcontroller.

---

## Current Features (PC Side)
- Open and configure a serial port using WinAPI
- Configure UART parameters (115200, 8N1)
- Handle communication timeouts to avoid blocking behavior
- Send raw binary packets over UART

---

## Work in Progress
This project is being actively developed and will be extended with:

- STM32 firmware for UART reception
- Packet parsing using a state machine
- Bidirectional communication (request/response)
- Custom protocol with:
  - Header
  - Length
  - Payload
  - CRC/checksum

---

## Project Structure
- pc/ → Windows UART communication code
- stm32/ → Embedded firmware (coming soon)
- protocol/ → Shared packet definitions 

---

## Example Packet
Current test packet:
FF 03 03 04 05 02


Future versions will include structured packets with validation.

---

## How to Build & Run (PC)
1. Open the project in a C compiler (e.g. MSVC or MinGW)
2. Update the COM port if needed:
   "\\\\.\\COM14"
3. Compile and run:
   gcc *.c -o *.exe  
   *.exe

---

## Goals
- Develop a reusable UART communication layer
- Implement a robust embedded communication protocol
- Gain hands-on experience with low-level I/O and microcontroller interfacing

---

## Future Improvements
- Cross-platform support (Linux using termios)
- Error handling and retries
- Logging and debugging tools
- Integration with real hardware peripherals (sensors, actuators)

---

## Author
Ehsan Fatemi









