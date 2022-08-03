I've forked this firmware's source because I need to adjust it for use
with a Siemens T100. The ITA2 mapping is slightly off for this model
of teleprinter, now you can send `C-g` and ring your bell to your heart's content.

I've also added support for `DC2` (`C-r`) and `DC4` (`C-t`) to enable
and disable the current loop and motor via relays. The current loop relay
will enable first, then the LEDs will flash for four seconds, and the
motor relay will enable. This gives it a moment so the teleprinter
runs with the loop closed from the start. For powering the relays off,
the inverse occurs, but the delay is only three seconds.

If you are automating communications with the teleprinter, allow for
appropriate pauses before sending characters. Flow control here means
adding a delay in your code, sorry.

Because I am using a Pro Micro, I had to adjust things for an atmega32u4.
My particular fuse settings wile flashing the CDC firmware to it are as
follows:

    avrdude -v \
      -patmega32u4 -cbuspirate \
      -P /dev/tty.usbserial-AK06X1J4 \
      -e \
      -U flash:w:BootloaderCDC.hex \
      -U lfuse:w:0xDE:m \
      -U hfuse:w:0xD1:m \
      -U efuse:w:0xC3:m

Use a fuse calculator if you are unsure of what you are doing.

- DRA

--------------

For full info and docs, see http://heepy.net/index.php/USB-teletype

quickstart:

signal from loop is received on SOFTUART_RXPIN, signal toward loop output on
SOFTUART_TXPINNUM. LED indicators are on TX_LEDPIN and RX_LEDPIN

To work with custom board, the default avr dfu bootloader has to be replaced
with a different one that doesn't need HWB brought out.

Set the fuses:

avrdude -p atmega16u2 -P /dev/ttyACM0 -c stk500v2 -e -U hfuse:w:0xd0:m
avrdude -p atmega16u2 -P /dev/ttyACM0 -c stk500v2 -e -U lfuse:w:0xde:m
(mileage may vary with other AVR MCUs, please consult the docs)

Install the bootloader:

cd ~/git/avr-lufa/lufa/Bootloaders/CDC/
make clean; make
Connect ISP programmer and run:
avrdude -p atmega16u2 -P /dev/ttyACM0 -c stk500v2 -e -U flash:w:BootloaderCDC.hex

Install this software:
Remove ISP programmer, connect only USB cable.
cd ~/git/avr-lufa/lufa_serial/
make clean; make
make program

If you program it using the ISP programmer afterward, you'll need to reinstall the
bootloader too.

---

This is an attempt to get a useful USB CDC ACM endpoint on AVR using the
latest LUFA USB stack. Eventual target is atmega32u2 so I can use it on the
usb-to-tty loop adapter board. Compiles and works correctly on both 32u2 and 32u4.

It needs the current LUFA distro from
http://www.github.com/abcminiuser/lufa/archive/LUFA-151115.zip
unzipped into ../lufa

epv 2/11/2016

2/13/16
added softuart from usbtty2 project.
Sending and receiving work fine.

added test stuff to switch to and from commandline mode using "%"

still need to do:

1. actual config mode: (implemented, still adding to it)

translating vs transparent mode, so you can use it with HeavyMetal in place of cp2102 (done)
enable/disable auto-cr, cr->crlf (not sure i care)
set auto-cr column? (later)
select character set maps? (later)
speed? Might be able to set baud rate just by setting OCR1A = 83333 / baudrate (done)

16000000 / 64 / (3 _ 45.45) = 1833 // 60 WPM
16000000 / 64 / (3 _ 50.00) = 1667 // 66 WPM
16000000 / 64 / (3 _ 56.90) = 1464 // 75 WPM
16000000 / 64 / (3 _ 74.20) = 1123 // 100 WPM

Maybe a setting for inverting or not inverting the RX and/or TX sense? (not sure i care)

2. implement unshift on space, i think (done)

3. switch to/from config mode by hardware button vs "%" key. (done)

4. ASCII mode for m33's. (implemented, appears to work with linux serial port, no 33 to test with, need more framing info)
   also no idea how real machines handle or don't handle parity.
