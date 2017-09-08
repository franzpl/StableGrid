// Mains frequency measurement (Germany 50 Hz)
// measurement of fluctuations in mains frequency
// interrupt handler: mains frequency

#include <TimeLib.h>

const char TIME_HEADER = 'T'; // for serial time sync message
int TIME_REQUEST = 7; // ASCII bell character requests a time sync message 


volatile unsigned long pulseCounter = 0; 
volatile unsigned long currentMicros;
volatile unsigned long previousMicros = 0;
volatile unsigned long duration = 0;

unsigned long _duration;
unsigned long _pulseCounter;
 // determine the time of averaging length
unsigned long measuringTime =  1000; // ms
unsigned long currentRuntime = 0;
unsigned long previousRuntime = 0; 

int overflow_state = 0; 


float freq; 

void setup() {

Serial.begin(115200);
setSyncProvider(requestSync);  //set function to call when sync required
Serial.println("Send the message: 'date +T%s -d +2hours > /dev/tty?' from the Terminal ");

attachInterrupt(0, mains_freq_handler, RISING); // Pin 2 

}

void loop() {
  

 // number of milliseconds since the 
 // Arduino board began running the current program
currentRuntime = millis();
if (Serial.available()) {
   processSyncMessage();
  }
 

if (currentRuntime - previousRuntime >= measuringTime && timeStatus()!= timeNotSet) {


  
  previousRuntime = currentRuntime;
  _duration = duration;
  _pulseCounter = pulseCounter;
  duration = 0;
  pulseCounter = 0;

  if(!overflow_state) {
  freq = 1e6 * _pulseCounter / (float(_duration)); 

  Serial.print(freq, 3);
  digitalClockDisplay();

}
  else {
    overflow_state = 0; }
  
}

}

void mains_freq_handler() {

  if (previousMicros > micros()) {
  overflow_state = 1;
 }

  currentMicros = micros();
  duration += currentMicros - previousMicros;
  previousMicros = currentMicros;
  pulseCounter++; 
 
  
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(" ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());

  Serial.print(" ");
  Serial.print(day());

  Serial.print(" ");
  Serial.print(month());

  Serial.print(" ");
  Serial.print(year()); 

  Serial.println();
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(" ");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}


time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial message
}

