  sr        =  48000
  kr        =  4800
  ksmps     =  10
  nchnls    =  2
  0dbfs     =  1


    instr 1
  itlen     =  32768
  ifsin     =  1
  asig      oscil     0.5,1000
  awndx      phasor    sr/itlen*p4
  arndx     phasor    sr/itlen*p5
asigscale  ablkscale asig, k(p4) 
            tabw      asig, awndx, ifsin, 1

  aout      tab       arndx, ifsin, 1

            outs      aout,aout
    endin
