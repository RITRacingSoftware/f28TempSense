avrdude -c jtagmkI -p c128 -P /dev/cu.usbserial-A50600KG -b 115200 -F -e -U flash:w:$1:i -U lfuse:w:0xe2:m -U hfuse:w:0x19:m -U efuse:w:0xff:m 
# -U signature:w:0x1e9781:m