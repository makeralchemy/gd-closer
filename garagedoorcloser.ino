// intialize published variables
String version = "0.1.10";
String gdoor_status = "uninitialized";
String argument = "uninitialized";
String last_operation = "uninitialized";
String updated_gmt = "uninitialized"; // last time door status updated (GMT)

int RELAY1 = D3;      // relay for the garage door button
int RELAY2 = D4;
int RELAY3 = D5;
int RELAY4 = D6;

int HEARTBEAT_LED = D7;

void setup() {
  pinMode(HEARTBEAT_LED, OUTPUT);
  digitalWrite(HEARTBEAT_LED, LOW);
  
  //Initilize the relay control pins as output
  pinMode(RELAY1, OUTPUT);      // garage door button
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  // Initialize all relays to an OFF state
  digitalWrite(RELAY1, LOW);      // garage door button
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);
  
  // Setup time synchronization
  Particle.syncTime();
  waitFor(Particle.syncTimeDone, 30000); // wait for up to 30 seconds

  
  Particle.variable("version", version);                    // version number of this program
  Particle.variable("argument", argument);                  // argument passed to the functions
  Particle.variable("gdoorstatus", gdoor_status);           // garage door status
  Particle.variable("last_operation", last_operation);      // last function called
  Particle.variable("updated_gmt", updated_gmt);            // last time status was updated - GMT
  
  Particle.function("setgdopen", setgdopen);          // set garage door status to 'open'
  Particle.function("setgdclosed", setgdclosed);      // set garage door status to 'closed'
  Particle.function("closegdoor", closegdoor);        // close the garage door
}

void loop() {
    // blink led on and off every second to indicate
    // photon is still alive
    digitalWrite(HEARTBEAT_LED, HIGH);      // turn led on
    delay(1000);                            // wait a second
    digitalWrite(HEARTBEAT_LED, LOW);       // turn led off
    delay(1000);                            // wait a second
}

// Set the garage door status to open.
// This will be called via a POST from the Raspberry Pi that 
// monitors the garage door.
bool setgdopen(String command) {
    argument = command;
    gdoor_status = "open";
    last_operation = "setgdopen";
    updated_gmt = Time.format(Time.now(), "%b-%d %H:%M");
    return 0;
}

// Set the garage door status to closed.
// This will be called via a POST from the Raspberry Pi that 
// monitors the garage door.
bool setgdclosed(String command) {
    argument = command;
    gdoor_status = "closed";
    last_operation = "setgdclosed";
    updated_gmt = Time.format(Time.now(), "%b-%d %H:%M");
    return 0;
}

// Called to close the garage door.  Check to see if it's open
// before pushing the button to control the garage door.  Return 
// a status code indicating whether the command is accepted.
bool closegdoor(String command) {
    argument = command;
    last_operation = "closegdoor";
    if (gdoor_status == "open") {
        pushbutton();
        return 0;
    } else {
        // door is already closed. return an error.
        return 1;
    }
}

// Code to be added to control the physical garage door.
void pushbutton() {
    // close the relay to simulate a button push
    digitalWrite(RELAY1, HIGH);
    // keep closed for a quarter of a second
    delay(250);
    // open the relay to simulate releasing the button
    digitalWrite(RELAY1, LOW);
}
