# Neuro Optix Project Documentation

## Introduction
Neuro Optix is an innovative project that revolutionizes robotic surveillance and safety systems through advanced automation and artificial intelligence. Built with durable 3D-printed parts and acrylic sheets, the robotic car features DC motor-powered wheels for seamless movement across various terrains. At its core is the OAK-D AI camera, mounted atop the car to monitor distances between personnel and machinery, enhancing safety in environments like construction sites.

## Problem Statement
Managing worker safety on construction sites presents several logistical and financial challenges:
- Handling transportation costs.
- Ensuring timely payment of monthly salaries.
- Addressing persistent issues related to corruption and negligence that undermine safety enforcement.

These challenges necessitate a robust and efficient monitoring system to ensure the safety and well-being of workers.

## Proposed Solutions
To address these challenges, we propose a multi-faceted approach:
- **Stationary Cameras:** Installed around the site for continuous surveillance and monitoring worker activities.
- **Safety Helmet Cameras:** Provide a first-person perspective to ensure real-time monitoring of individual workers' safety and compliance with safety protocols.
- **Robots:** Equipped with advanced computer vision technology to autonomously navigate the site, detect potential hazards, and provide dynamic surveillance.

## Objectives
- **Enhance Workplace Safety:** Advanced surveillance to reduce risks.
- **Improve Operational Efficiency:** Streamline safety monitoring processes.
- **Global Remote Control:** Enable remote operation from anywhere in the world.
- **Versatile Deployment:** Adapt the system for various industrial environments.

## Why Neuro Optix?
![Main Overview](https://github.com/EngrAwab/Robo_rumble/blob/main/img/Copy%20of%20EME.png)
Neuro Optix offers several advantages over traditional safety measures:
- **Mobility:** Unlike stationary cameras, Neuro Optix can navigate diverse terrains, providing dynamic, real-time surveillance.
- **AI Technology:** Continuously monitors and analyzes surroundings to prevent collisions and enhance safety.
- **Advanced Coverage:** Combines computer vision and remote connectivity for more reliable and efficient monitoring.

## Unveiling Neuro Optix
### Designing
The initial design of Neuro Optix involves crafting the robotic car's body using AutoCAD software, focusing on durability and functionality.
![Designing](https://github.com/EngrAwab/NeuroOptix/blob/main/img/Design.jpg)

### 3D Printing & Laser Cutting
Components are designed using CAD software, 3D-printed for precision, and acrylic sheets are laser-cut to enhance structural support and durability.

![3D Printing & Laser Cutting](https://github.com/EngrAwab/NeuroOptix/blob/main/img/cut.jpg)
### Soldering
Wires of DC motors are soldered to ensure reliable electrical connections crucial for the car's operational integrity.
![Soldering](https://github.com/EngrAwab/NeuroOptix/blob/main/img/robot%20.jpg)

### Components to Assemble
Components are assembled methodically to ensure compatibility and functionality, resulting in a robust framework ready for hardware integration.
![Assembly](https://github.com/EngrAwab/NeuroOptix/blob/main/img/All%20components.jpg)
## Hardware Components
### Kria KR260
The Kria KR260 is a high-performance FPGA kit from Xilinx (now AMD), providing powerful processing capabilities for AI and machine learning tasks.
![Kria](https://github.com/EngrAwab/NeuroOptix/blob/main/img/KRIA.jpg)

### OAK-D Camera
The OAK-D Lite is a compact AI vision system built on the Myriad X VPU from Intel. It provides real-time depth sensing, object detection, and AI processing capabilities.

### DC Motors
Drive the robotic car's movement, controlled by motor drivers for smooth and precise operation.

### Servo Motors
Control the pan-tilt movements of the OAK-D AI camera, enhancing surveillance capabilities.

### Motor Drivers (L298N)
Regulate the speed, torque, and direction of the DC motors, interfacing between the Raspberry Pi and motors.

### Arduino
Manages motor drivers and servo motors, facilitates Bluetooth communication, and enables remote control.

## Software Setup
### Vitis AI
Vitis AI simplifies the deployment of deep learning models on FPGAs. It converts models into xModel format for efficient deployment on FPGA DPUs.

### OpenCV
A widely-used library for image processing, enabling functionalities like object detection and depth perception.

### DepthAI API
Interfaces with the OAK-D Lite to perform advanced computer vision tasks, leveraging its AI processing capabilities.

### Luxonis Hub
A central tool for managing multiple OAK-D Lite devices, handling video feeds, deploying AI models, and managing network interactions.

## Block Diagram
![Block Diagram](https://github.com/EngrAwab/NeuroOptix/blob/main/img/Block%20Diagram%20.jpg)

The block diagram illustrates the data flow from the OAK-D camera through KRIA processing to motor control and visualization.

## KRIA Setup
### Step 1: Access the Official Documentation
Visit the Kria KR260 official documentation to familiarize yourself with the setup process and requirements.

### Step 2: Update the Firmware
Run the following commands to update the firmware:
```
wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=1wACTcpbwLPOH9UUuURk5qcnIYeEverSB' -O k26_update3.BIN
sudo xmutil bootfw_update -i <path-to-FW.BIN file>
sudo xmutil bootfw_status
sudo shutdown -r now
sudo xmutil bootfw_update -v
```
Replace `<path-to-FW.BIN file>` with the actual path.

### Step 3: Set Up Wi-Fi
Install Wi-Fi drivers using the following commands:
```
sudo apt-get install build-essential git dkms linux-headers-$(uname -r)
git clone https://github.com/McMCCRU/rtl8188gu.git
cd rtl8188gu
make
sudo make install
sudo apt install --reinstall linux-firmware
sudo reboot
```
Update DNS settings if necessary:
```
sudo nano /etc/resolv.conf
```
Add:
```
nameserver 8.8.8.8
```
Save and close the file.

### PYNQ Installation
Clone the repository and convert scripts to Unix format:
```
git clone https://github.com/amd/Kria-RoboticsAI.git
sudo apt install dos2unix
cd /home/ubuntu/Kria-RoboticsAI/files/scripts
for file in $(find . -name "*.sh"); do
    echo ${file}
    dos2unix ${file}
done
```
Install PYNQ and reboot:
```
sudo su
cd /home/ubuntu/Kria-RoboticsAI
cp files/scripts/install_update_kr260_to_vitisai35.sh /home/ubuntu
cd /home/ubuntu
source ./install_update_kr260_to_vitisai35.sh
reboot
```
Set up the PYNQ environment:
```
sudo su
source /etc/profile.d/pynq_venv.sh
cd $PYNQ_JUPYTER_NOTEBOOKS
pynq get-notebooks pynq-dpu -p
```

## Code Configuration and Setup
### Clone the Repository
```
git clone https://github.com/EngrAwab/NeuroOptix.git
```
### Install Dependencies
```
cd NeuroOptix
pip install -r requirements.txt
cd Code
```
### Run the Code
```
python3 dpu.py
```

## Features
### Fire Detection
Using OpenCV's image processing algorithms, Neuro Optix detects flames in real-time, ensuring swift identification of fire outbreaks and enabling immediate preventive measures. We made a fire by ourself to test our model and here are the results. 
![Fire](https://github.com/EngrAwab/NeuroOptix/blob/main/img/Fire%20detection%20.jpg)
### Helmet Detection
The system accurately detects whether workers are wearing helmets in real-time, ensuring compliance with safety regulations. Unfortunately we were unable to visit the safety site so we conducted this expereiment at video taken from interenet.
![Helmet](https://github.com/EngrAwab/NeuroOptix/blob/main/img/Helmet%20detection%20.jpg)
### Distance Measuring
The OAK-D AI camera measures distances between objects using its stereo pair of global shutter cameras, providing accurate depth information. We can measure distance up to 7m accurately.
![Block Diagram](https://github.com/EngrAwab/NeuroOptix/blob/main/img/DSistance%20measuring.jpg)

## Results and Analysis
Neuro Optix continuously monitors worker compliance with safety protocols and detects potential hazards. OpenCV's advanced image processing capabilities enhance the robotic arm's functionality in tasks requiring precise object handling.

## Future Enhancements
### Integration with Drones
- **Monitoring Workers at Heights:** Drones will provide a holistic view of the construction site, enhancing safety.
- **Quality Assurance:** Drones will assist in quality inspections from above.


These future enhancements aim to extend the system’s functionality, ensuring safer and more efficient monitoring on construction sites.


