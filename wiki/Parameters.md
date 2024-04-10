**autotune_s**<br>
The number of samples averaged together per frequency step in auto tune mode.
<br>Default = 1
***
**baudrate**<br>
The serial communication baud rate.  Be sure to configure your terminal software (Putty, Teslaterm, etc) to use this same value when connecting via the serial connector.<br>Default = 460800
***
**boff**<br>
Burst mode offtime in [ms].  This is the amount of time to keep the interrupter off before starting the next burst.
<br>Default = 500
***
**bon**<br>
Burst mode ontime in [ms]. 0=off.  Burst mode uses the current pw and pwd parameters for the time specified here (bon).  It then turns off the interrupter for the time specified in boff before repeating.  The idea is to allow pw to be increased to get more powerful pulses with a relatively long off time to keep the bridge from overheating.

In other words, when this is 0 (the default) the interrupter is continuously on and off according to pw/pwd.  When this is non-zero it allows the interrupter to use pw/pwd for bon time, then turns everything off for boff time.  Then repeat.
<br>Default = 0
***
**charge_delay**<br>
Delay time for the charge end relay (relay 2) in [ms].  This is the amount of time before the charge end relay is activated (in order to bypass the inrush precharge resistors).  This is to avoid tripping circuit breakers when the bus is first turned on because the large bus caps appear as a short and pull a huge amount of current for a short time.
<br>Default = 1000
***
**ct1_burden**<br>
CT1 (feedback) burden resistance in [ohms] for the feedback current transformer.  This is provided by R41 on the board.
<br>Default = 3.3
***
**ct1_ratio**<br>
CT1 (feedback) ratio: This is the ratio of the feedback current transformer.  The feedback transformer needs to output about 1.5A at absolute peak current. You would enter 1000 here for a 1:1000 transformer.
<br>Default = 600
***
**ct2_burden**<br>
CT2 (bus) burden resistance in [ohms] of the DC current transformer.  Only used if ct2_type = 0 (current mode).  The equation used to determine the current is:<br>
`I = measured voltage on IBUS pin * ct2_ratio / ct2_burden.`
<br>Default = 50
***
**ct2_current**<br>
CT2 (bus) current in [amps] @ ct_voltage.  Only used if ct2_type = 1 (voltage mode).  The equation used to determine the current is:<br>
`I = ([measured voltage on IBUS pin] - ct2_offset) * ct2_current / (ct2_voltage - ct2_offset).`
<br>Default = 0
***
**ct2_offset**<br>
CT2 (bus) offset voltage in [volts].  Only used if ct2_type = 1 (voltage mode).  The equation used to determine the current is:<br>
`I = ([measured voltage on IBUS pin] - ct2_offset) * ct2_current / (ct2_voltage - ct2_offset).`
<br>Default = 0
***
**ct2_ratio**<br>
CT2 (bus) ratio of the DC current transformer.  This is the number of turns in the DC-Bus current transformer (the IBUS connector).  Note that this is DC current and requires a Hall-effect type sensor.  Only used if ct2_type = 0 (current mode).  The equation used to determine the current is:<br>
`I = measured voltage on IBUS pin * ct2_ratio / ct2_burden.`
<br>Default = 1000
***
**ct2_type**<br>
CT2 (bus) current transformer type
* 0 = current.  For type 0 you need a Hall-effect sensor similar to a LEM LF 306-S.  This mode uses the ct2_ratio and ct2_burden parameters.
* 1 = voltage: For voltage mode, you must remove R48 on the back of the UD3 and use a voltage mode CT.  This mode uses the ct2_current, ct2_offset, and ct2_voltage parameters.

Note that both these sensors require the DC bus to be passed through the center of the sensor which will affect the layout of the bridge.
<br>Default = 0
***
**ct2_voltage**<br>
CT2 (bus) voltage in [volts] @ ct_current.  Only used if ct2_type = 1 (voltage).  The equation used to determine the current is:<br>
`I = ([measured voltage on IBUS pin] - ct2_offset) * ct2_current / (ct2_voltage - ct2_offset).`
<br>Default = 4.0
***
**ct3_burden**<br>
CT3 (sec) burden resistance in [ohms] of the secondary current transformer.
<br>&#x274c;TODO: I don't think CT3 (the CT for the secondary coil) is actually mapped anywhere.  It is pin 49 on the MCU which is unconnected on the PCB.
<br>Default = 3.3
***
**ct3_ratio**<br>
CT3 (sec) ratio of the secondary current transformer.
<br>&#x274c;TODO: I don't think CT3 is actually mapped anywhere.  It is pin 49 on the MCU which is unconnected on the PCB.
<br>Default = 30
***
**ena_display**<br>
Enables the WS2812 LED strip light display.  The WS2812 output signal is accessible on pin 7 of the Expansion 1 connector.  Use the `display` command to configure what is shown on the light strip.
* 0 = off
* 1 = on
* 2,3,4,5 enables the display with increasing levels of dimness.
<br>Default = 0
***
**ena_ext_int**<br>
Enable external interrupter.
* 0 = disabled
* 1 = enabled
* 2 = inverted<br>

The external interrupter is connected to pin 6 of the Expansion 2 header.
<br>Default = 0

&#x274c;TODO: This may not be working.  See notes in interrupter.c.  It seems that the input signal is inverted for the normal case (ena_ext_int=1) and NOT inverted for the inverted case (ena_ext_int=2)
***
**ivo_uart**<br>
Inverts the serial RX and TX signals:
* 00 = RX not inverted, TX not inverted
* 01 = RX not inverted, TX inverted
* 10 = RX inverted, TX not inverted
* 11 = RX inverted, TX inverted<br>

Default = 00
***
**lead_time**<br>
Switching lead time (phase lead) in [ns].  Reasonable values are around 500 for small bricks and 1000 for large bricks.  

This is internally converted to an integer number of processor bus cycles.  Since the processor runs at 64MHz, this means the value entered here will be truncated to an integer number of processor cycles (15.625 ns).  Therefore you will only see an effect at lead_time's of 16, 32, 47, 63, 79, 94, 110, 125, 141, 157, 172, 188, 204, ...

Furthermore, there is a propagation delay of 6 processor cycles (94 ns) in the internal hardware, so any lead time < 94 ns will have no effect.  As an example, specifying a lead_time of 300 ns here will result in an actual lead time of:
((int)(300 / 15.625) - 6) * 15.625 = 203.125 ns.
<br>Default = 200
***
**max_const_i**<br>
Maximum constant current in [amps]. 0=off.  This is for the software fuse.  The software fuse requires a hall effect current sensor to be connected to the IBUS connector.
<br>Default = 0
***
**max_dc_curr**<br>
Maximum DC-Bus current in [amps].  Set to 0 to disable.  This requires a Hall effect sensor connected to the IBUS connector.
<br>Default = 0
***
**max_fault_i**<br>
Maximum fault current in [amps] for 10s.  This is for the software fuse which requires a hall effect current sensor to be connected to the IBUS connector.
<br>Default = 25.0
***
**max_fb_errors**<br>
The number of feedback errors allowed before shutting down with a sysfault.  Set to 0 to disable.  A feedback error occurs when there is no pulse on the CT connector.
<br>Default = 0
***
**max_qcw_current**<br>
Maximum QCW current in [amps]: If this value is exceeded the UD3 will use pulse skipping (switching off one side of the bridge) until the current is reduced to this value.
<br>Default = 300
***
**max_qcw_duty**<br>
Maximum QCW duty cycle as a percentage.
<br>Default = 35.0
***
**max_qcw_pw**<br>
Maximum QCW pulse width in [ms].  The interrupter will be kept on for this amount of time in QCW mode.
<br>Default = 10
***
**max_tr_current**<br>
Maximum transient mode (DRSSTC) current in [amps].  If this value is exceeded the UD3 will use pulse skipping (switching off one side of the bridge) until the current is reduced to this value.
<br>Default = 400
***
**max_tr_duty**<br>
Maximum transient mode duty cycle as a percentage.  The duty cycle is (onTime*100)/(onTime+offTime)
<br>Default = 10.0
***
**max_tr_prf**<br>
Maximum transient mode (DRSSTC) frequency in [Hz].  A pulse consists of a number of cycles  at the resonant frequency (on time) followed by an off time to keep the bridge from overheating.  This parameter specifies how often this on/off cycle is repeated.
<br>Default = 800
***
**max_tr_pw**<br>
Maximum transient mode (DRSSTC) pulse width ("on" time) in [us].  A pulse consists of several cycles at the resonant frequency and controls the power/volume of the coil.  <br>Default = 1000
***
**min_enable**<br>
Enable MIN Protocol.
* 0 = disable
* 1 = enable<br>

MIN is a multi-user binary protocol over the serial connection.  This is used by Teslaterm and UD3Node.  If this is enabled on a VT100 terminal you will see garbage on the serial line (so don't do it unless you want to use Teslaterm).  Note that this is ignored for the USB connection, so if you want to reset it to 0 you can always connect via USB and set min_enable 0.

If this parameter is changed then you need to save with `eeprom save`, then restart with the `reset` command.  The switch to/from MIN is only performed when the UD3 first boots up - not when the params are changed.
<br>Default = 0
***
**min_tr_current**<br>
Minimum transient mode current in [amps] (only used for MIDI modulation).
<br>Default = 100
***
**ntc_b**<br>
NTC beta [k] value.  This value must be obtained from the thermistor's data sheet.
<br>Default = 3977
***
**ntc_idac**<br>
The current passed through the thermistors in [uA] to measure the temperature.  Note that this value can also be updated via the ntc command if you don't know the proper value to specify here.
<br>Default = 185
***
**ntc_r25**<br>
NTC R25 value.  This is the resistance of the thermistor at 25 degrees centigrade in [kOhms], usually obtained from the data sheet.
<br>Default = 10.000
***
**offtime**<br>
Offtime for MIDI in [us]: This is the minimal offtime between two MIDI pulses.
<br>Default = 3
***
**pca9685**<br>
Enables/disables the hardware gauges.  See the hwGauge command for more info.
* 0 = off
* 1 = on<br>

Default = 0
***
**pid_curr_i**<br>
The I term of the PID controller used to control the duty cycle necessary to keep the current within range.  Only used if max_dc_curr is >0.
<br>Default = 5
***
**pid_curr_p**<br>
The P term of the PID controller used to control the duty cycle necessary to keep the current within range.  Only used if max_dc_curr is >0.
<br>Default = 50
***
**ps_scheme**<br>
Power supply scheme:
* 2 = Monitors the bus voltage and enables the charge end relay (relay 2) when the it stops climbing and stabilizes.  This requires the bus voltage to be connected to the connector at the bottom of the left side of the UD3 (don't forget the external resistors here!).  Note that the charge_end relay will NOT be triggered if the bus voltage is <= 20V.
* 4 = mains powered without a built-in precharging relay
* 5 = fixed delay.  Enables the charge end relay (relay 2) after the time specified in the charge_delay setting<br>

Default = 2
***
**pw**<br>
Pulse width (on time) for transient and MIDI mode in [us].  The pulse width is how long a burst of resonant cycles will be sent to the primary.  This defines the power/volume.
<br>Default = 0
***
**pwd**<br>
Pulse width delay: Delay between pulses for transient mode in [us].  This is the period of the pulse (on + off time).  This is what defines the audible pitch of the coil.
<br>Default = 50000
***
**pwp**<br>
Pulse width as a percent of the maximum allowed pulse width.  This is equal to 100 * pw / max_tr_pw.  Changing this will change pw accordingly.
<br>Default = 0
***
**qcw_coil**<br>
Is this a QCW coil?
* 0 = no
* 1 = yes
<br>Default = 0
***
**qcw_hold**<br>
QCW ramp time to start ramp in units of [125 us].  This is the horizontal offset for the start of the ramp in increments of 125 us.

Changing this parameter will discard any customizations made with the ramp command
<br>Default = 0
***
**qcw_max**<br>
QCW ramp end value.  This is the max value for the Y axis of the ramp.
Units are 0 to 255 where 0=minimum power, 255=maximum.

Changing this parameter will discard any customizations made with the ramp command
<br>Default = 255
***
**qcw_offset**<br>
QCW ramp start value.  This is the vertical offset at the start of the ramp.
Units are 0 to 255 where 0=minimum power, 255=maximum.

Changing this parameter will discard any customizations made with the ramp command
<br>Default = 0
***
**qcw_ramp**<br>
QCW ramp increment per 125 us.  The ramp consists of 400 discrete steps of 125 us each.  This parameter specifies how much the power increases per step, so it is essentially a linear slope of qcw_ramp / 125 us.  The power ranges from 0 (off) to 255 (full pulse width).

Changing this parameter will discard any customizations made with the ramp command.
<br>Default = 2
***
**qcw_repeat**<br>
QCW pulse repeat time in [ms].  This is the time to wait before the next qcw pulse.  Anything less than 100 will result in a single shot.
<br>Default = 500
***
**r_bus**<br>
The value of the external resistors in [kOhms] connected to the "Bus voltage + and -" pins (bottom of left side of UD3 PCB).  You need 100k on each pin for every 100 volts of input.  If your bus has a max of 800v then you need an 800k resistor on the "-" pin and an 800k resistor on the "+" pin, and you must set this parameter to 800.

Currently this parameter is used for both the bus voltage AND the battery voltage, so all 4 pins must use the same value resistors.
<br>Default = 500
***
**start_cycles**<br>
Number of start cycles with the internal oscillator.  This is used to send a few pulses to the bridge in order to get an initial feedback pulse on the CT input.  The start cycles can be set to 0 or 1 in some cases, but most setups work best with at least 2 to 4 start cycles for DRSSTC and up to 8 cycles for QCW.  The frequency of the start pulses may be set via the start_freq param.
<br>Default = 3
***
**start_freq**<br>
The start oscillator resonant frequency in [kHz].  This is used when first starting up the interrupter before feedback has been received.  The resonant frequency of the primary can be found via the tune command.  For example: `set start_freq 54.4`.
<br>Default = 63.0
***
**synth**<br>
Selects the synthesizer used to play music.  This is sent automatically by Teslaterm based on the type of MIDI file.
* 0 = off
* 1 = MIDI
* 2 = SID
<br>Default = 1
***
**synth_filter**<br>
Synthesizer filter string.  This is a string of characters that specifies the notes and channels this UD3 will respond to.  This allows different UD3's to respond to different notes when playing music.

Recognized sequences are:
* c[CH] Enables channel [CH].  For example "c1c3" enables channels 1 and 3.  If no channels are specified then all channels are enabled.
* f<[FREQ] sets the minimum frequency to [FREQ].  For example f<100 sets the minimum frequency to 100.  Any frequency less than 100 is not handled by this UD3.
* f>[FREQ] sets the maximum frequency to [FREQ].  For example f>500 sets the minimum frequency to 500.  Any frequency greater than 500 is not handled by this UD3.

The sequences are concatenated together into a single filter string.  For example, `c2f<200f>1000` restricts this UD3 to channel 2 only with a frequency range of 200 to 1000 Hz.
<br>Default = f<0f>20000
***
**temp1_max**<br>
Maximum temperature for THR1 in degrees Celsius: This is the trip point for overtemperature.  Set to 0 to disable
<br>Default = 40
***
**temp1_setpoint**<br>
Setpoint for fan in degrees Celsius.  When the THR1 thermistor reads more than this amount it will apply 24V to the Fan connector.
<br>Default = 30
***
**temp2_max**<br>
Maximum temperature for THR2 in degrees Celsius.  This is the trip point for overtemperature.  Set to 0 to disable.
<br>Default = 40
***
**temp2_mode**<br>
THR2 setpoint mode.  This specifies what to do when the temp2 sensor is >= temp2_setpoint.
* 0 = disabled (do nothing)
* 1 = FAN (the fan will turn on if either THR1 >= temp1_setpoint, or THR2 >= temp2_setpoint
* 3 = Activate Relay3
* 4 = Activate Relay4
<br>Default = 0
***
**temp2_setpoint**<br>
The setpoint for THR2 in degrees Celsius.  0 = disabled.  When this temperature is reached the operation specified in temp2_mode will be performed.
<br>Default = 30
***
**tune_delay**<br>
The delay between auto-tune pulses in [ms].
<br>Default = 50
***
**tune_end**<br>
The upper frequency limit for auto tuning in [kHz].  For example: `set tune_end 100`.
<br>Default = 100
***
**tune_pw**<br>
The pulse width used during auto-tuning in [us].
<br>Default = 50
***
**tune_start**<br>
The lower frequency for auto-tuning in [kHz].  For example: `set tune_start 30`.
<br>Default = 40
***
**ud_name**<br>
Name of the Coil (up to 15 chars).  Used in the MIN protocol for the EVENT_GET_INFO event and the CMD_HELLO_WORLD command.
<br>Default = "UD3-Tesla"
***
**vol_mod**<br>
The volume modulation scheme.  Volume modulation scales down the output power of the bridge.  The volume comes from the synth.
* 0 = pulse width modulation.  The interrupter "on" time is modulated by the volume
* 1 = current modulation.  The interrupter pulse width is left at the max and the bridge current is scaled down by the volume by disabling one side of the bridge using pulse skipping.

Default = 0
***
**watchdog**<br>
Enables or disables the watchdog timer
* 0 = disabled
* 1 = enabled

The "watchdog" is a 1 second timer (by default) that puts the system into a faulted state if it ever expires.  To keep the timer from expiring, an external controller needs to continually send the special byte sequence `0xf0, 0x0f, 0x00`.  If the byte sequence is not received in time the UD3 assumes the controller has become disconnected and stops immediately with a sysfault.

Teslaterm automatically sends the required byte sequence when using the MIN protocol, but a normal terminal (like Putty) will not send the sequence and the watchdog must be disabled manually using `set watchdog 0` followed by `kill reset` to clear the sysfault.
<br>Default = 1
***
**watchdog_timeout**<br>
The elapsed time before the watchdog timer expires in [ms].  See the "watchdog" parameter for more details.
<br>Default = 1000
