﻿# IoT-Smart_parking

This seminar project focuses on an IoT-based smart parking system. The system comprises three IR sensors, one servo motor, and an LED. The control interface is a web page built using HTML, CSS, and JavaScript. The executive component is a NodeMCU ESP8266, communicating via Firebase.

## Project Goals

The goal of this project is to streamline the process of finding available parking spaces in a parking lot, as well as facilitating the reservation of a parking spot. Two IR sensors are responsible for opening and closing the barrier, which can also be controlled via the web page. The third IR sensor simulates a parking space and records entry and exit times. All this information is collected and processed by the NodeMCU, which activates the servo motor for barrier control. The LED serves as an indicator of occupancy, with a lit LED signifying an available parking space, allowing users to quickly locate empty spots.

## Web Application Functionality

The web application enables users to reserve a parking space by clicking on a button representing an empty parking spot. If all spaces are occupied, reservations cannot be created, and the entry barrier will not open until a parking space becomes available. Clicking the "Open Barrier" button allows entry, but only if a reservation has been made beforehand.
