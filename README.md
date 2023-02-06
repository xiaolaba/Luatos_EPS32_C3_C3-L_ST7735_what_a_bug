# Luatos_EPS32_C3_C3-L_ST7735_what_a_bug
Luatos core-esp32c3 and core-esp32c3L, very different response by LCD ST7735

tested with a few LCD ST7735 libray, but no luck.  

there are two different boards manufactured by Luatos
![CORE-ESP32-C3_L.JPG](CORE-ESP32-C3_L.JPG)  


the code, the same, the buring flash process the same, one is working and the other hang on reboot, did not work. bu why was that ?  


Luatos 那個 ESP32C3 板子, 本來以為很容易, 結果上馬就翻車. 接上 ST7735 的 LCD, 有 CH343 的那個板沒事. 純粹 USB 的那板就是點不了 LCD, 燒寫完畢直接沒有啟動的樣子. 以為板子壞了, 換了幾個板都一樣, 真不知道貓膩哪裡了. 用或不用 GUI庫, 情形都相同. 給他燒了 LED跑馬燈, 確定沒問題, 燒寫後自動運行完全沒問題. 有大俠知道C3這顆祕密嗎. 還是遺漏了甚麼..  

Io12 / Io13 LED跑馬燈, 源碼及燒錄工具, https://github.com/xiaolaba/Luatos_EPS32_C3_C3-L_blinking_test  

### 這板板  
https://wiki.luatos.com/chips/esp32c3/board.html  

### 這電路圖  
https://wiki.luatos.com/chips/esp32c3/hardware.html  

### 這源碼  
抄襲 https://github.com/WINKCM/Arduino-ESP32-TFTLCD-ST7735  
自行改過的  
[lcd1.ino](lcd1.ino)  
[LCD1.cpp](LCD1.cpp)   
[lcd1.h](lcd1.h)  

### 這樣改  
```
// xiaolaba
// luatos Core ESP32-C3, USB-UART CH340G, test done, ok
// luatos Core ESP32-C3L, no CH340G, no working ??
#define SCL 2
#define SDA 3
#define RES 10
#define DC 6
#define CS 7
#define BL 11
```

### 接線圖  
![circuit.JPG](circuit.JPG)  


### 這結果
simple test code of repo and library TFT_eSPI demo code TFT_Clock  
same bug, same result,  
![NG.JPG](NG.JPG)  


### Luatos 的原廠 demo 測試, 狀況依然 
![Luatos_core_V1002_test_result/Luatos_esp32c3_firmware_burn_test.JPG](Luatos_core_V1002_test_result/Luatos_esp32c3_firmware_burn_test.JPG)  
