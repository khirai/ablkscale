test.wav :  ablkscale.so phasor_debug.orc phasor_debug.sco
	csound --opcode-lib=./ablkscale.so phasor_debug.orc phasor_debug.sco

ablkscale.so : ablkscale.c ablkscale.h
	gcc -fPIC -O2 -shared -o ablkscale.so ablkscale.c  -I /usr/local/include/csound

