# MAKEFILE

Proiektua konpilatu eta mikrokonrolagailura igotzeko Makefile bat erabiliko da. Honen barruan hainbat komando exekutatzen dira kodea konpilatu eta kargatzeko.

## Azalpena



#### Kodea konpilatu
Lehenengo kopilaziorako komandoa aldagai batean gordeko dugu geroago erabiltzeko, konpilazio garaian

    COMPILE = avr-gcc -Wall -Os -mmcu=atmega328p

Konpilazioko lehen pausoan *.o* fitxategiak lortuko ditugu. Lortutako horiek gero *.elf* bat erabiltzeko erabiliko da. Azkenik, aurretik lorutako fitxategiko *.data* eta *.text* *.hex* fitxategi batera pasako dira.


    $(COMPILE) -c file.c -o file.o
    $(COMPILE) -o file.elf file.o
    avr-objcopy -j .text -j .data -O ihex file.elf file.hex
    avr-size --format=avr --mcu=atmega328p file.elf

#### Kodea mikrora igo

Kodea mikrora igotzeko *avrdude* erabiliko da. komandoan parametro moduan hainbat ezaugarri pasa behar zaizkio mikroaren arabera eta portuaren arabera.

Parametroak:

* -p <device>: mikroaren izena
* -c <programmer>: programadorea, gure kasuan arduino
* -P <port>: portuaren izena
* -b <baud-rate>
* -U flash:w:file.hex:i

#### Erabilera
Erabiltzeko orduan oso simplea da. Terminal batean *make* idaztearekin nahikoa baita. Izan ere banan-banan exekuta daitzeke.

Konpilazioa:
    
    make compile

kodea igo:

    make upload

bideko fitxategiak garbitzeko:

    make clean

## Beharrezko softwarea

Honako hau da beharrezkoa den softwarearen zerrenda:

* avr-gcc
* avrdude

Hauek exekutatzeko beharrezkoak diren liburutegiak instalatzeko honako pausoak jarraitu behar dira.

Debian-en oinarritutako banaketak (Debian, Ubuntu)

    sudo apt update
    sudo apt install binutils-avr
    sudo apt install avr-libc
    sudo apt install avrdude
