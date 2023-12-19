# Building-access-control-and-fire-alarm-system
This repository contains the implementation of a building access control and fire alarm system, comprising multiple software components programmed in C to manage various security and safety aspects within a building environment.

Components Overview
1. Card Reader Controller
Manages access via card scanning.
Implements secure entry and exit protocols.
2. Fire Alarm Call-Point Controller
Monitors fire alarm call points for rapid emergency response.
Coordinates with other systems during fire incidents.
3. Temperature Sensor Controller
Provides real-time temperature data for fire hazard detection.
Ensures environmental monitoring within the building.
4. Fire Alarm Unit
Central unit for fire alarm management.
Activates alarms and coordinates evacuation procedures.
5. Door Controller
Manages building door operations, excluding specific functionalities.
Ensures controlled access and security measures.
6. Overseer
Supervises the integrated system, ensuring optimal functionality.
Excludes functionalities unrelated to security and fire alarm systems.
7. Simulator
Facilitates system testing with simulated events.
Focuses on crucial events like CARD_SCAN and CALLPOINT_TRIGGER.
Implementation Details
Programming Language: C
Communication Protocols: TCP, UDP over IPv4
File Structure:
Each component has its directory with detailed code and documentation.
Usage Instructions:
Detailed instructions for building, configuring, and running each component.
Getting Started
Clone this repository:
bash
Copy code
git clone https://github.com/olukoyeVin/building-access-control-fire-alarm.git
Refer to individual component directories for specific setup and usage instructions.
Contribution Guidelines
Contributions are welcome! If you wish to contribute, follow these steps:

Fork the repository.
Make your changes.
Create a pull request with a detailed description of your modifications.
License
This project is licensed under MIT. See the LICENSE file for details.

Acknowledgements
@rocelli
