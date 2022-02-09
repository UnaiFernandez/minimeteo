lmake_compatibility_version("1.0.0")

FILENAME   = "main"
FILENAME2  = "USART"
PORT       = "/dev/ttyACM0"
DEVICE     = "atmega328p"
PROGRAMMER = "arduino"
BAUD       = "115200"
COMPILE    = "avr-gcc -Wall -Os -mmcu=$(DEVICE)"

function build()
    -- Configure the compiler
    lmake_set_compiler("avr-gcc")
    lmake_set_compiler_flags("-Wall -Os -mmcu=atmega328p")
    lmake_set_compiler_out("./%.o")

    -- Gather all the source files and compile them
    local source_files = lmake_find("./*.c")
    lmake_compile(source_files)

    -- Configure the linker
    lmake_set_linker("avr-gcc")
    lmake_set_linker_flags("-Wall -Os -mmcu=atmega328p")
    lmake_set_linker_out(FILENAME)

    -- Gather all the object files and link them
    local obj_files = lmake_find("./*.o")
    lmake_link(obj_files)

    -- Convert the linked object into a file that the device can understand
    lmake_exec("avr-objcopy -j .text -j .data -O ihex " ..FILENAME .. " " .. FILENAME .. ".hex")
    lmake_exec("avr-size --format=avr --mcu=atmega328p " .. FILENAME)
end

function upload()
    lmake_exec("avrdude -F -v -p atmega328p -c arduino -P " .. PORT .. " -b " .. BAUD .. " -U flash:w:".. FILENAME ..".hex:i")
end

function clean()
    local files_to_remove = "main.c.o  main.hex USART.c.o main"
    lmake_exec("rm -f " .. files_to_remove)
end
