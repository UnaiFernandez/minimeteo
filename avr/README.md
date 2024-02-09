# minimeteo
Open-source small meteo station for Atmega328p based boards. It measures temperature and humidity with a DHT11 sensor, and wind speed with a RS485 MODBUS anemometer. All the gathered data is sent via wifi using a ESP8266 module, to a tcp client.

## Installation

1.- Clone the repo
  
    git clone https://github.com/UnaiFernandez/minimeteo.git
  
## Compile and upload the code

### Prerequisites



### Make

Compile the code
    
    make build

upload the code to the board

    make upload
    
### Lmake

## Installation

Clone the repo and compile it using make Visit [Lmake](https://github.com/IkerGalardi/LMake) for more info

    git clone https://github.com/IkerGalardi/LMake
    cd LMake
    make
    
To compile the code for the weather station just type

    lmake build
    
and type the following to upload

    lmake upload 

