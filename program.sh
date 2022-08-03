#!/usr/bin/env bash
port="$(ls -1 /dev/tty.usbmode* | head -n 1)"
echo $port
avrdude -p "$1" -c avr109 -B 2mhz -P "${port}"  -U "flash:w:$2.hex"
