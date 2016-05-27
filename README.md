# microchip_MiWi
Microchip MiWi example
Example of MiWi is doing a echo with checking the ack of all device.
All RFD/FFDs LED will toggle when any RFD/FFD button 1 is pressed.

This is a simple project to try out Microchip MiWi P2P, Mesh and MiWi Pro
This is a stripped down sanitized version of a much larger project
PAN is a PIC24FJ256GB108
FFD is a PIC24FJ64GA104  same hardware and software just diffent defines
RFD is a PIC24FJ64GA104  same hardware and software just diffent defines

What it does?
PAN Button pressed and held for 7 seconds reset miwi connection
PAN Button pressed and held for 2 seconds changes mode to enable all
PAN Button pressed for less then 2 seconds changes mode to enable previous
PAN LED is Green when there is a device in it connection table
PAN LED is Red when there are no devices in it connection table
PAN LED is Blinks green when the mode is enable all
PAN MiWI recieved messages are retransmitted to other devices in connection table
		 if all devices recieved message with ack then it is sent back to the originator
		 
RFD/FFD Button 2 trys to join network
RFD/FFD Button 1 sends out through miwi the LED that is off
RFD/FFD LED Blinks if it couldn't join network
RFD/FFD LED shows color sent by MiWi
RFD/FFD MiWi sends when button is pressed
RFD/FFD MiWi recieved messages sets LEDs

Example:
Three RFD/FFD and one PAN
All devices are on network
Pan Connection table
DEV1,
DEV2,
DEV3

if button 1 is pressed on DEV2 the PAN recieves and sends out
DEV1
DEV3
if both DEV1 and DEV3 gives an ack then it sends it to DEV2
The message will cause the LED to toggle
