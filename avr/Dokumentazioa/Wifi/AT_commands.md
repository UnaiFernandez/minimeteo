|   Command   |   Variant   |  Response  |  Function  |
| ----------- | ----------- | ---------- | ---------- |
|     AT      |   Execute   |     OK     | Test if AT system works correctly  |
| AT+RST      | Execute     | OK         |  Reset the module|
|**ESP-01 Access Point moduan programatu**|
|*Wifi modua aukeratu*|
|AT+CWMODE=?  |   Test      |+CWMODE:(1-3) OK| List valid modes|
|AT+CWMODE?   |   Query     |+CWMODE:mode OK| Query AP’s info which is connect by ESP8266|
|AT+CWMODE=2  |   Execute   |   OK       | Set AP’s info which will be connect by ESP8266.|
|*AP-aren izena eta pasahitza aukeratu*|
|AT+CWSAP=?| Query |  +CWSAP:ssid,pwd,ch,ecn OK  |Query configuration of ESP8266 softAP mode. |
|AT+CWSAP=ssid,pwd,channel,encryption| Execute | OK | Set configuration of softAP mode. |
|*Moduluaren IP helbidea*|
| AT+CIPAP?   | Query   | +CIPAP:ip OK | Get ip address of ESP8266 softAP.
| AT+CIPAP=ip | Execute | OK  | Set ip addr of ESP8266 softAP.|
|*Konexio bat baino gehiago ahalbidetu*|
|AT+CIPMUX= mode | Set | OK | Enable / disable multiplex mode (up to 4 conenctions)
|AT+CIPMUX?| Query | +CIPMUX:mode OK | Print current multiplex mode.|
|*TCP Zerbitzari bat sorut*|
|AT+CIPSERVER=enable,port | Set | OK | Configure ESP8266 as TCP server |
|*TCP Zerbitzariaren timeouta zehazteko*|
|AT+CIPSTO?| Query | +CIPSTO: time | Query server timeout |
|AT+CIPSTO=time | Set | OK | Set server timeout |
|*TCP bidez mezu bat bidaltzeko*|
|AT+CIPSEND=id,lenght| Set | SEND OK | Set length of the data that will be sent. For normal send (multiple connection) |
|*TCP konexio bat isteko*|
|AT+CIPCLOSE=id| Set | OK | Close TCP or UDP connection.For multiply connection mode |
