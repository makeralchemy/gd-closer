
// intialize published variables
String version        = "0.1.27";        // current code version
String gdoor_status   = "uninitialized"; // current garage door status
String argument       = "uninitialized"; //argument to last operation
String last_operation = "uninitialized"; // last operation performed
String updated_gmt    = "uninitialized"; // last time door status updated (GMT)
String updated_pdt    = "uninitialized"; // last time door status updated (PDT)
String updated_pst    = "uninitialized"; // last time door status updated (PST)
String auth_status    = "";              // authorization status from closegd function

const int PDT_OFFSET = -7 * 3600;        // offset to GMT for pacific daylight-savings time
const int PST_OFFSET = -8 * 3600;        // offset to GMT for pacific standard time

const bool OP_SUCCESS = 0;               // operation succeeded
const bool OP_FAIL    = 1;               // operation failed

const String AUTH_CODE = "xxxx";         // authorization code to open the garage door (not the real code)

int RELAY1 = D3;      // relay for the garage door button
int RELAY2 = D4;      // unused relay
int RELAY3 = D5;      // unused relay
int RELAY4 = D6;      // unused relay

int HEARTBEAT_LED = D7;

time_t current_time;

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

  
  Particle.variable("version", version);                 // version number of this program
  Particle.variable("argument", argument);               // argument passed to the functions
  Particle.variable("gdoorstatus", gdoor_status);        // garage door status
  Particle.variable("last_operation", last_operation);   // last function called
  Particle.variable("stat-gmt", updated_gmt);            // last time status was updated - GMT
  Particle.variable("stat-pdt", updated_pdt);            // last time status was updated - PDT
  Particle.variable("stat-pst", updated_pst);            // last time status was updated - PST
  Particle.variable("close_authz", auth_status);         // authorization status for door closing operation
  
  Particle.function("setgdopen", setgdopen);             // set garage door status to 'open'
  Particle.function("setgdclosed", setgdclosed);         // set garage door status to 'closed'
  Particle.function("closegdoor", closegdoor);           // close the garage door
}


void loop() {
    // blink led on and off every second to indicate
    // photon is still alive
    digitalWrite(HEARTBEAT_LED, HIGH);      // turn led on
    delay(1000);                            // wait a second
    digitalWrite(HEARTBEAT_LED, LOW);       // turn led off
    delay(1000);                            // wait a second
}

void update_last_action_timestamp() {
    current_time = Time.now();
    updated_gmt = Time.format(current_time, "%b-%d %H:%M");
    updated_pdt = Time.format(current_time + PDT_OFFSET, "%b-%d %I:%M %p");
    updated_pst = Time.format(current_time + PST_OFFSET, "%b-%d %I:%M %p");
}

// Set the garage door status to open.
// This will be called via a POST from the Raspberry Pi that 
// monitors the garage door.
bool setgdopen(String command) {
    argument = command;
    gdoor_status = "open";
    last_operation = "setgdopen";
    update_last_action_timestamp();
    auth_status = "";                  // authorization does not apply to this function
    return OP_SUCCESS;
}

// Set the garage door status to closed.
// This will be called via a POST from the Raspberry Pi that 
// monitors the garage door.
bool setgdclosed(String command) {
    argument = command;
    gdoor_status = "closed";
    last_operation = "setgdclosed";
    update_last_action_timestamp();
    auth_status = "";                   // authorization does not apply to this function
    return OP_SUCCESS;
}

// Called to close the garage door. 
// First check to see if the argument matches the authorization code, if not don't
// open the door and return an error code.
// Check to see if it's open before pushing the button to control the garage door.  
// Return a status code indicating whether the command is accepted.
bool closegdoor(String command) {
    argument = command;
    last_operation = "closegdoor";
    if (argument.equals(AUTH_CODE)) {
        auth_status = "Success";
        if (gdoor_status == "open") {
            pushbutton();
            update_last_action_timestamp();
            return OP_SUCCESS;
        } else {
            // door is already closed. return an error.
            return OP_FAIL;
        }
    } else {
        auth_status = "Failed";
        return OP_FAIL; // invalid passcode
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
