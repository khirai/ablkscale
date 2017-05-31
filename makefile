test.wav :  ablkscale.so phasor_debug.orc phasor_debug.sco
	csound --opcode-lib=./ablkscale.so phasor_debug.orc phasor_debug.sco

ablkscale.so : ablkscale.c ablkscale.h
	gcc -g -O2 -shared -o ablkscale.so -fPIC ablkscale.c  -I /usr/local/include/csound

