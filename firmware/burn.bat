REM uses flash mode DIO, ESP32C3
REM 2022-10-09, ESP32_Frequency_generation_2MHz_10MHz.ino firmware
REM burn test ok

:: To erase esp32 completely, do not rely on Arduino IDE and code upload, it has cluster and odd thing when uses FATFS, 
:: unless format SPIFFS or FATFS everytime on the fly
:: xiaolaba, 2020-MAR-02
:: Arduino 1.8.16, esptool and path,

REM %userprofile%

cls
prompt $xiao

set 

set comport=COM4
REM set esptoolpath="C:\Users\user0\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\3.1.0/esptool.exe"
REM set esptoolpath="%userprofile%\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\3.1.0/esptool.exe"
set esptoolpath="%userprofile%\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\4.2.1/esptool.exe"
set esptoolpath="esptool_4.2.1.exe"


set MCU=esp32c3
set BAUDRATE=921600
REM set BAUDRATE=512000


set project=lcd1

:: erase whole flash of esp32
%esptoolpath% --chip %MCU% ^
--port %comport% ^
--baud %BAUDRATE% ^
erase_flash

REM pause

REM burn firmware
%esptoolpath% --chip %MCU% ^
--port %comport% ^
--baud %BAUDRATE% ^
--before default_reset ^
--after hard_reset ^
write_flash -z ^
--flash_mode dio ^
--flash_freq 40m ^
--flash_size detect ^
0x0 %project%.ino.bootloader.bin ^
0x8000 %project%.ino.partitions.bin ^
0xe000 boot_app0.bin ^
0x10000 %project%.ino.bin

pause

REM 0xe000 C:\Users\user0\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.1-RC1\tools\partitions/boot_app0.bin 
REM 0x1000 C:\Users\user0\AppData\Local\Temp\arduino_build_160314/ESP32_Frequency_generation_2MHz_10MHz.ino.bootloader.bin 
REM 0x10000 C:\Users\user0\AppData\Local\Temp\arduino_build_160314/ESP32_Frequency_generation_2MHz_10MHz.ino.bin 
REM 0x8000 C:\Users\user0\AppData\Local\Temp\arduino_build_160314/ESP32_Frequency_generation_2MHz_10MHz.ino.partitions.bin 




REM C:\Users\user0\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\4.2.1/esptool.exe 
--chip esp32c3 
--port COM8 
--baud 921600 
--before default_reset 
--after hard_reset 
write_flash -e -z 
--flash_mode dio 
--flash_freq 80m 
--flash_size 4MB 
0x0 C:\Users\user0\AppData\Local\Temp\arduino_build_717640/lcd1.ino.bootloader.bin 
0x8000 C:\Users\user0\AppData\Local\Temp\arduino_build_717640/lcd1.ino.partitions.bin 
0xe000 C:\Users\user0\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.6/tools/partitions/boot_app0.bin 
0x10000 C:\Users\user0\AppData\Local\Temp\arduino_build_717640/lcd1.ino.bin 


REM C:\Users\user0\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\4.2.1/esptool.exe 
--chip esp32c3 
--port COM4 
--baud 512000 
--before default_reset 
--after hard_reset 
write_flash -e -z 
--flash_mode dio 
--flash_freq 40m 
--flash_size 4MB 
0x0 C:\Users\user0\AppData\Local\Temp\arduino_build_307176/ESP32C3_BLINK.ino.bootloader.bin 
0x8000 C:\Users\user0\AppData\Local\Temp\arduino_build_307176/ESP32C3_BLINK.ino.partitions.bin 
0xe000 C:\Users\user0\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.6/tools/partitions/boot_app0.bin 
0x10000 C:\Users\user0\AppData\Local\Temp\arduino_build_307176/ESP32C3_BLINK.ino.bin 
