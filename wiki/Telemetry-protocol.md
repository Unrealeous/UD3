**Telegram types:**<br>
TT_GAUGE: 0x01<br>
TT_GAUGE_CONF: 0x02<br>
TT_CHART: 0x03<br>
TT_CHART_DRAW: 0x04<br>
TT_CHART_CONFIG: 0x05<br>
TT_CHART_CLEAR: 0x06<br>
TT_CHART_LINE: 0x07<br>
TT_CHART_TEXT: 0x08<br>
TT_CHART_TEXT_CENTER: 0x09<br>
TT_STATUS: 0x0A<br>
TT_CONFIG_GET: 0x0B<br>
<br>
**Units:**<br>
TT_UNIT_NONE: 0x00<br>
TT_UNIT_V: 0x01<br>
TT_UNIT_A: 0x02<br>
TT_UNIT_W: 0x03<br>
TT_UNIT_Hz: 0x04<br>
TT_UNIT_C: 0x05<br>
<br>

**Gauge/Chart:**<br>
1 byte start: 0xFF<br>
1 byte length: 0x04<br>
1 byte type: TT_GAUGE/TT_CHART<br>
1 byte gauge number<br>
1 byte LSB value (int)<br>
1 byte MSB value (int)<br>
<br>
**Plot chart points:**<br>
1 byte start: 0xFF<br>
1 byte length: 0x02<br>
1 byte type: TT_CHART_DRAW<br>
1 byte: 0x00<br>
<br>
**Chart clear:**<br>
1 byte start: 0xFF<br>
1 byte length: 0x02<br>
1 byte type: TT_CHART_CLEAR<br>
1 byte: 0x00<br>
<br>
**Chart configuration:**<br>
1 byte start: 0xFF<br>
1 byte length<br>
1 byte type: TT_CHART_CONFIG<br>
1 byte chart number<br>
1 byte LSB value min (int)<br>
1 byte MSB value min (int)<br>
1 byte LSB value max (int)<br>
1 byte MSB value max (int)<br>
1 byte LSB value offset (int)<br>
1 byte MSB value offset (int)<br>
1 byte unit<br>
x bytes descriptor (string)<br>
<br>
**Gauge configuration:**<br>
1 byte start: 0xFF<br>
1 byte length<br>
1 byte type: TT_GAUGE_CONFIG<br>
1 byte gauge number<br>
1 byte LSB value min (int)<br>
1 byte MSB value min (int)<br>
1 byte LSB value max (int)<br>
1 byte MSB value max (int)<br>
x bytes descriptor (string)<br>
<br>
**Configuration dump:**<br>
1 byte start: 0xFF<br>
1 byte length<br>
1 byte type: TT_CONFIG_GET<br>
x bytes help text<br>
1 byte: ';'<br>
x bytes values (all values as string): [param name];[value];[type];[size];[min];[max]<br>
<br>