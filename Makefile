FILENAME   = src/main
FILENAME2  = src/USART
FILENAME3  = src/wifi
FILENAME4  = src/timers
FILENAME5  = src/DHT11
PORT       = /dev/ttyACM0
DEVICE     = atmega328
PROGRAMMER = arduino
BAUD       = 115200
COMPILE    = avr-gcc -Wall -Os -mmcu=$(DEVICE)


default: compile upload clean

compile:
	@echo "====== MINIMETEO ======"
	@echo "[!] Compiling..."
	@echo "--------------------------"
	@ $(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	@echo "[+] $(FILENAME)"
	@ $(COMPILE) -c $(FILENAME2).c -o $(FILENAME2).o
	@echo "[+] $(FILENAME2)"
	@ $(COMPILE) -c $(FILENAME3).c -o $(FILENAME3).o
	@echo "[+] $(FILENAME3)"
	@ $(COMPILE) -c $(FILENAME4).c -o $(FILENAME4).o
	@echo "[+] $(FILENAME4)"
	@ $(COMPILE) -c $(FILENAME5).c -o $(FILENAME5).o
	@echo "[+] $(FILENAME5)"
	@echo "--------------------------"
	@echo ""
	@ $(COMPILE) -o $(FILENAME).elf $(FILENAME).o $(FILENAME2).o $(FILENAME3).o $(FILENAME4).o $(FILENAME5).o
	@ avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	@ avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	@echo "[!] Uploading..."
	@echo "--------------------------"
	@ avrdude -F -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

clean:
	@echo "[!] Cleaning..."
	@ rm src/*.o src/*.elf src/*.hex
