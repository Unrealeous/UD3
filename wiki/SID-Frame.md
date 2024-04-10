**Version 1:**<br>
Frame start: 0xFF 0xFF 0xFF 0xFF<br>
followed by 30 register bytes
| Byte | Register |
|------|-----------|
|0|SID_FREQLO1|
|1|SID_FREQHI1|
|2|SID_PWLO1|
|3|SID_PWHI1|
|4|SID_CR1|
|5|SID_AD1|
|6|SID_SR1|
|7|SID_FREQLO2|
|8|SID_FREQHI2|
|9|SID_PWLO2|
|10|SID_PWHI2|
|11|SID_CR2|
|12|SID_AD2|
|13|SID_SR2|
|14|SID_FREQLO3|
|15|SID_FREQHI3|
|16|SID_PWLO3|
|17|SID_PWHI3|
|18|SID_CR3|
|19|SID_AD3|
|20|SID_SR3|
|21|SID_FCLO|
|22|SID_FCHI|
|23|SID_Res_Filt|
|24|SID_Mode_Vol|
|25|Timecode [ms] (MSB)|
|26|Timecode [ms]|
|27|Timecode [ms]|
|28|Timecode [ms] (LSB)|
|29|End (fixed 0x00)|
