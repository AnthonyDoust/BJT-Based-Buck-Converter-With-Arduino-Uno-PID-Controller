#include <PID_v1.h>

int inputpin = A1;
int PWMoutpin = 9;

unsigned long previoustime;
unsigned long time;
unsigned long timediff;
int interval = 50;

// Set these variables to match your input and output voltages
float targetVoltage = 6; // set this to your desired voltage
float voltage = 12.33; // 12.33 due to the voltage input being a little higher than 12v. set to what ever input voltage is being used

int dutyout;
float VoltageOut;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=0.1, Ki=0.0, Kd=0.0; // 0.025, 0.1, 0.01 is good starting point
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {

  pinMode(PWMoutpin, OUTPUT);
  digitalWrite(PWMoutpin, HIGH);   // ensure PNP is OFF during setup, before Timer1 takes over

  // Clear Timer1 Control Registers
  TCCR1A = 0;
  TCNT1  = 0;

  // Set Fast PWM Mode 14 (WGM13=1, WGM12=1, WGM11=1, WGM10=0)
  // Set non-inverting mode for both Channel A and Channel B (COM1A1=1, COM1B1=1)
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // CS10=1 sets Prescaler to 1

  // Set the TOP value for 250kHz
  ICR1 = 63;

  Serial.begin(115200);

  //initialize the variables we're linked to
  Input = analogRead(inputpin);
  
  Setpoint = (((targetVoltage)*1023)/voltage); // equation to convert voltage to 1023 analog val

  myPID.SetMode(AUTOMATIC);   //turn the PID on
  myPID.SetSampleTime(5); // sample time of the PID controller
  myPID.SetOutputLimits(0, 63); // limits of the PID output

}

void loop() {

  // keep track of current time and the difference between previous and current
time = millis();
timediff = time - previoustime;

// interval to check the RPM
if (time - previoustime >= interval) {

  previoustime = time;

  Input = analogRead(inputpin);

  VoltageOut = (Input * (voltage/1023)); // equation converting input analog value to voltage

  // serial plotter outputs for troubleshooting and tuning
  Serial.print("Target Voltage:");
  Serial.print(targetVoltage);
  Serial.print(",Voltage Out:");
  Serial.println(VoltageOut);

  Serial.print("Output: ");
  Serial.println(Output);

}

myPID.Compute();
OCR1A = 63 - (int)Output;
Serial.print("Output:"); Serial.print(Output, 4);
Serial.print(" OCR1A:"); Serial.println(OCR1A);

}
