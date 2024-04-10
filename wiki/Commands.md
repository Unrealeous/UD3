**alarms [get/roll/reset]**<br>
* "get" displays a list of the last 50 significant events
* "reset" clears the event list
* "roll" enables "rolling mode"  Rolling mode will remain active and print events as they occur.  This can be canceled by pressing Ctrl+C or 'q'.
***
**bootloader**<br>
Restarts the UD3 in bootloader mode. This is designed to be called by Teslaterm when you drag a new firmware file (.cyacd) over the window.  If you run it manually in a terminal window the UD3 will wait for commands using a binary protocol from Cypress.  In this mode you can flash with the bootloader utility.<br>
***
**bus [on/off]**<br>
Turn the DC bus on/off via relay 1.  As currently coded, turning the bus off will wait for charge_delay before actually turning off the bus.  Of course, this requires the bus to be connected to the power source via relay 1's contacts.
***
**calib**<br>
Starts the driver voltage (DCIN) calibration wizard.  This will ask you to set the driver voltage to several values ranging from 7V to 24V to set the internal calibration parameters.  Be sure to save the with `eeprom save` if you want to retain the calibration across reboots.
***
**cls**<br>
Clears the terminal window.
***
**con [info/min/numcon]**<br>
Prints the ethernet connections.
* "info" prints the connection number and IP address for each connection
* "min" displays statistics for the min protocol in a realtime display.
* "numcon" displays the number of CLI sessions
***
**config_get**<br>
Internal use - sends the UD3 configuration to Teslaterm for the Settings dialog.  The configuration consists of all visible config settings formatted as strings, one per line.  Included information includes the param name, value, type, size, min, max, etc (one parameter per line).
***
**debug [[id]/min/fn]**<br>
Debug mode.  In general these commands are only for development use.  They will lock up the UD3 if executed indiscriminately.
* "min" displays debug messages for the min protocol.  This is intended to be used over USB.  If you use it over min it will create a loop and lock up the terminal.
* "fn" Allows you to get access the Fibernet CLI from the UD3.  To exit press CTRL+C.  To exit top or iotop in Fibernet just press "q".  This requires the Fibernet addon board.
* [id] With this you can sniff different MIN ID (a bit like ports on TCP).  Each terminal session has an ID of 0..3, MIDI has an ID of 20, SID has an ID of 21. The complete list can be found in min_id.h in the source code.
***
**display [assign [number][src]/clear [number]/select [number]]**<br>
Specifies what to show on the WS2812 LED light strip.  
* assign [number][src] The display is divided into 10 zones.  Each zone is 
***
**eeprom [load/save]**<br>
Save/Load the current configuration.  For example, "eeprom save" saves all configuration settings to the eeprom where they will be automatically loaded the next time the UD3 is powered up.
***
**features**<br>
Get supported features.  This is a list of 6 static strings similar to: protocol=2.0 build_time=Jan 14 2022;13:30:35 timebase=1000 time_count=up notelemetry_supported=1 min_sid_support=1.  There are binary characters in the message so it is not intended for use in a VT100 terminal.

The strings are sent using a binary message command of TT_FEATURE_GET.

Teslaterm queries with this command which type of UD3 it is connected to. Older Versions have other timebases and so on. 
***
**fuse_reset**<br>
Reset the internal software fuse (the i2t integrator).  The software fuse requires a Hall effect current sensor to be connected to the IBUS connector.  You set the maximum continuous current and the 10s limit from the breaker curve. The UD3 tries to limit the duty cycle to keep the fuse under 60% of the trip point.

The "Fuse" telemetry metric shows the fuse status as a percent.  When it reaches 100% the fuse is tripped.

If the controller can not keep the current low enough and the fuse reaches 100% the UD3 shuts the coil down.

The software fuse uses the following parameters:
* max_const_i
* max_fault_i

Note: This feature is still experimental and may not function correctly.
***
**get [param]**<br>
If a parameter is specified then this command will print the value of the parameter.  If no parameter is specified then the function prints all parameters with their current value.  See the parameter list for all possible parameters.
***
**help**<br>
Prints a list of all available commands.
***
**hwGauge [assign/clear/calibrate]**<br>
Configure the hardware gauge parameters.
* assign [number] [name]  Assigns a telemetry [name] to gauge [number] (0 to 5).  For example: `Assign 3 Current`
* clear [number]  Clears gauge [number]
* calibrate [number]  Interactively allows you to set the minimum and maximum value of the specified gauge.  Pressing + increments the value, - decrements the value, 0 sets value to 0, * sets value to max, enter advances to next step or exits when complete.

There are currently 15 different telemetry metrics: Fuse, FRes, Driver_Voltage, Bus_State, Voltage2, Primary, Voices, Voltage, Temp1, Temp2, Current, Power, TX_Datarate, RX_Datarate, Dutycycle

These use I2C to control a PCA9685 servo controller to set a PWM signal corresponding to the gauge value.  The I2C SDA and SCL signals are accessible on the Expansion 1 connector, pins 3 and 5 respectively.

You must enable the hardware gauges with `set pca9685 1` for this to work.
***
**kill [set/reset/get]**<br>
* set inhibits the operation of the UD3
* reset clears all faults and enables operation of the UD3.  This is the command you need to use to allow the UD3 to start working again after a fault is detected.
* get prints the kill bit status.  The value will be 0 if the UDB3 is enabled, or 1 if the UDB3 is in the disabled (killed) state.  The disabled state is usually because of a fault condition or because the "kill set" command was issued.
***
**load_default**<br>
Loads the default parameters from flash memory.  These are the hard-coded firmware defaults.  Use this if you want to return the UD3 to it's initial factory configuration.  This does NOT update the eeprom so these parameters will be discarded after the next processor reset.  Use eeprom save if you want the factory defaults to remain persistent.
***
**ntc**<br>
This interactively calibrates the THR1 thermistor.  You will need a precision 10 kOhm resistor connected to the THR1 connector to complete the procedure.  The calibration results will be used for both the THR1 and THR2 thermistors.  This process updates the value of the ntc_idac parameter, which can also be set directly if you prefer.  This needs to be saved with `eeprom save` if you want it to remain active between reboots.
***
**nvm [blocks/maps]**<br>
For debugging - this prints the contents of the internal MIDI data structures stored in flash.  This database defines the sounds of the MIDI voices and is loaded by dragging a .mcf file onto the Teslaterm window.  Since the database is stored in flash, this only needs to be done once (or whenever the flash memory is erased).  If no database is loaded, the UD3 will use a simple internal note on/off database.
***
**qcw [start/stop]**<br>
Starts/Stops QCW operation with the repetition rate stored in qcw_repeat [ms].  Values <100 ms results in a single shot.
***
**ramp [clear/draw/line/point]**<br>
Customize the shape of the QCW ramp.
* clear: sets the entire ramp to 0
* draw: draws a graphical representation of the ramp in the Teslaterm chart window.  A red vertical line is drawn at the max qcw pulse width.
* line x1, y1, x2, y2: connects x1, y1 to x2,y2 by a straight line segment
* point x y: sets an individual point within the ramp

x coordinates range from 0 to 399.  One x unit = 125 us.<br>
y coordinates range from 0 to 255.  0 is minimum power, 255 is max
***
**relay [3/4 1/0]**<br>
Switch user relay 3 or 4 on (1) or off (0).  For example `relay 3 1` will turn relay 3 on.
***
**reset**<br>
Restarts the processor.  This will cause the serial connection to be dropped.
***
**set [param] [value]**<br>
Sets `param` to `value`.  See the parameter list documentation or type "get" by itself to see a list of possible params.
***
**signals**<br>
For debugging.  This displays various internal signals in a real time display on the terminal that looks similar to this:

```
Signal state [CTRL+C] for quit:
**************************
UVLO pin: true  Crystal clock: false
Sysfault driver undervoltage: true
Sysfault Temp 1: false Temp 2: false
Sysfault fuse: false charging: false
Sysfault watchdog: true  updating: false
Sysfault bus uvlo: false feedback: false
Sysfault interlock: true  link: false combined: true
Feedback errors:    0
Relay 1: false Relay 2: false Relay 3: false Relay 4: false
Fan: false Bus status: Off
Temp 1: -255*C Temp 2: -255*C
Vbus: 0 mV Vbatt: 0 mV
Ibus: 0 mV Vdriver: 5250 mV
```
The bus voltage display shows the attenuated result of the "bus voltage - and +" terminals in mV.  These terminals are connected to a 100:1 differential amplifier.  If a 500K resistor is used on the two connected wires then the bus voltage will be reduced by a factor of 100, so 10 volts in will show as 100 mV.
***
**status [start/stop]**<br>
Displays a status window in VT100 mode (q for quit).  This is a non-blocking (you can continue to enter commands) overlay at the top of the terminal window.  If the overlay wraps make sure your terminal window is wide enough - the overlay starts at row 1 column 90.  The displayed metrics include Bus Voltage, Battery Voltage, Temp 1, Temp2, Bus status, Average power, Average Current, Primary Current, MIDI Voices, FRes
```
╔════════════════════════╗
║Bus Voltage:          0V║
║Battery Voltage:      0V║
║Temp 1:          -255 *C║
║Temp 2:          -255 *C║
║Bus status:          OFF║
║Average power:        0W║
║Average Current:    0.0A║
║Primary Current:      0A║
║MIDI voices:         0/4║
║Fres:            63.1kHz║
╚════════════════════════╝
```
The overlay is updated every 500ms.
***
**synthmon**<br>
Displays the synthesizer status on the terminal.  The display looks similar to:
```
Synthesizer monitor    [CTRL+C] for quit
-----------------------------------------------------------
Ch: 1 Freq: 123    Prog: 38Name: DEFMAP          Vol: ooooooo   
Ch: 2 Freq: 988    Prog: 79Name: DEFMAP          Vol: oooooooo  
Ch: 3 Freq: 62     Prog: 35Name: DEFMAP          Vol: ooooooo   
Ch: 4 Freq: 247    Prog: 52Name: DEFMAP          Vol: oooo      
```
***
**telemetry [list/ls/gauge [n] [name]/chart [n] [name]]**<br>
Assign telemetry metrics to a chart or gauge.  This is only intended for use with Teslaterm or a terminal capable of understanding the sent binary messages.

A telemetry item is a single metric that can be displayed as a gauge or chart (lines in the oscilloscope) in Teslaterm.  For example, to change the topmost gauge in Teslaterm to show the driver voltage: `telemetry 0 Driver_Voltage`.

* list shows the currently assigned telemetry metrics
* ls shows a list of the available metric names
* gauge n [name] assigns gauge n to the named metric.  Set name to "none" to deassign the gauge.  n can have values of 0 to 6.
* chart n [name] assigns chart n to the named metric.  Set name to "none" to deassign the chart.  n can have values of 0 to 3.

There are currently 15 different telemetry metrics.  Note that these are case sensitive: Fuse, FRes, Driver_Voltage, Bus_State, Voltage2, Primary, Voices, Voltage, Temp1, Temp2, Current, Power, TX_Datarate, RX_Datarate, Dutycycle

Note: The changes made here are not currently saved to eeprom.
***
**top**<br>
Shows real time performance statistics for the tasks running on the UD3.  The display includes the number of tasks, the overall CPU load as a percent, the total, free, and used memory.

For each task this displays the PID (process ID), the state (running or blocked), the percent of the CPU used by the task (total), the total time used by the task (in ticks), the task's stack high water mark (the closer this is to 0, the closer the task has come to overflowing its stack), and the heap memory used by the task.

Press Ctrl+C to exit.
***
**tr [start/stop]**<br>
Enables/disables transient mode (normal DRSSTC).  Transient mode uses the pulsewidth (parameter: pw) and delay between the pulses (parameter: pwd).
***
**tterm [start/stop/mqtt/notelemetry]**<br>
Changes terminal mode:
* start: Teslaterm mode, sends telemetry messages and the status message
* notelemetry: starts Teslaterm mode, no telemetry, no status message
* mqtt: starts Teslaterm mode, sends telemetry and event messages, no status message
* stop: switches to VT100 mode, no telemetry, no status message

The Teslaterm modes sends the telemetry messages every 100ms or 400ms (depending on the setting).  Temperature is sent at the slower rate for example.

Warning - these messages contain a lot of binary data.  Enabling a Teslaterm mode in a VT100 terminal (like Putty) will result in a lot of gibberish and lock up the terminal/UD3.
***
**tune [prim/sec]**<br>
Autotunes the primary or secondary coil.  The coil sweeps through the range given by tune_start and tune_end and finds the resonant frequency which is displayed in a frequency response graph on the terminal.

WARNING: the bridge will be hard switched - not for use with high bus voltage!!!!

The "sec" option requires some custom hardware connections and is being phased out.  The signal is mapped to pin 49 of the MCU but it is not actually routed anywhere on the UD3 board.
