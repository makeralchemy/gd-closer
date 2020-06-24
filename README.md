# gdcloser

gdcloser is a Particle Photon-based IoT device  for closing garage doors. gdcloser is intended to be used with garage door monitoring software like [https://github.com/makeralchemy/gdmonitor](https://github.com/makeralchemy/gdmonitor).
gdcloser uses Particle cloud variables and functions to monitor the state of the garage door and, when requested, will close the garage door. By keeping track of the state of the garage door, gdcloser will not open the door.

## How it works
gdcloser uses a simple C program to monitor the state of the garage door via Particle cloud functions and variables. When the function to close the door is called, gdcloser checks to see if the state of the door is 'open' and, if so, uses an output to control a relay that simulates pushing a button on a garage door open. CURL commands or Python programs are used by a garage door monitoring program like gdmonitor to set the Particle cloud functions to set the state of the garage door. CURL commands or Python commands can be used to request the garage door close. These functions can be called by the Particle Android or iOS app. The Particle cloud variables can be viewed on the Particle app as well.

## Getting Started

These instructions will show how to setup and use the gdcloser. Understanding how to use the Particle web IDE is assumed.

### Prerequisites

TBW

    Examples...

### Installing

TBW



## Deployment

TBW

## License

This project is licensed under the MIT license.