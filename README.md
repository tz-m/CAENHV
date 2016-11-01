# CAENHV
Control of V6521N and V6521P via command line tools and simple txt file

##### requirements:
CAENUSBdrvB -- most important, for connecting with the V1718 board
CAENVMElib -- second-most important, libraries for interacting with the boards
CAENComm -- possibly important? Doesn't hurt to have it...


Important info:

-- Most likely, have to do "sudo make; sudo make install" for the CAENUSBdrvB package.
-- Double check the "port number" for the USB connection to the V1718. Would be changed in sethv.h header. Not sure how the number is determined. try "lsusb" and "dmesg | grep -i usb" to look at the options.
-- Double check the address of the boards, set with the turney hex things, and set the values in the board header files.