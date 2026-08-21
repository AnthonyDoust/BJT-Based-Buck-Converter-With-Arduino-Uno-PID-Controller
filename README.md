# BJT-Based-Buck-Converter-With-Arduino-Uno-PID-Controller

This Buck converter uses a Arduino MC running a PID controller to adjust the PWM output to reach a customisable desired voltage, using a voltage divider in the feedback loop. The circuit and accompanying Arduino code is set up for a 12V input, However, it can be adjusted for any voltage by changing the voltage divider and the voltage variable in line 13. 

Due to the use of the BJT Transistors, the switching noise is very high, and thus the buck converter shouldn't be used to power sensitive loads.

Uses the PID_v1 made by Brett Beauregard.


Max Ratings:

Power: 0.5W

Current: 0.6A

Voltage: 35V







Components:

2N3904 NPN transistor

2N4403 PNP Transistor

100uH Inductor

1n4007 Diode

2x 1n4148 Diode

1x 0.1uF capacitor

1x 100pF capacitor

1x 10uF capacitor

1x 100uF capacitor

4x 1k Ohm Resistors

1x 470 Ohm resistor

1x 4.7k Ohm resistor

