--- 模块功能：lvgldemo
-- @module lvgl
-- @author Dozingfiretruck
-- @release 2021.01.25

-- LuaTools需要PROJECT和VERSION这两个信息
PROJECT = "lvgldemo"
VERSION = "1.0.0"

log.info("main", PROJECT, VERSION)

-- sys库是标配
_G.sys = require("sys")

--[[
-- LCD接法示例, 以Air105开发板的HSPI为例
LCD管脚       Air105管脚
GND          GND
VCC          3.3V
SCL          (PC15/SPI0_SCK)
SDA          (PC13/SPI0_MOSI)
RES          (PC12)
DC           (PE8)
CS           (PC14)
BL           (PE9)


// xiaolaba 2023-11-12
-- LCD接法示例, 以 ESP32C3 or C3L开发板的HSPI为例
LCD管脚      ESP32 IO PIN            合宙 ESP32C3 / C3L
GND          GND                     17   
VCC          3.3V                    18
SCL          (GPIO 2  /SPI0_SCK)     19
SDA          (GPIO 3  /SPI0_MOSI)    20
RES          (GPIO 10 /SPI0_MISO)    21, uses as GPIO
DC           (GPIO 6)                22
CS           (GPIO 7  /SPI0_CS)      23, uses as GPIO
BL           (GPIO 11)               24, backligh control


提示:
1. 只使用SPI的时钟线(SCK)和数据输出线(MOSI), 其他均为GPIO脚
2. 数据输入(MISO)和片选(CS), 虽然是SPI, 但已复用为GPIO, 并非固定,是可以自由修改成其他脚
]]

--添加硬狗防止程序卡死
wdt.init(9000)--初始化watchdog设置为9s
sys.timerLoopStart(wdt.feed, 3000)--3s喂一次狗

log.info("hello luatos")

--spi_lcd = spi.deviceSetup(SPI_CLK, SPI_CS, 0, 0, 8, 40*1000*1000, spi.MSB, 1, 0)
spi_lcd = spi.deviceSetup(2, 7, 0, 0, 8, 40*1000*1000, spi.MSB, 1, 0)

--[[ 此为合宙售卖的2.4寸TFT LCD 分辨率:240X320 屏幕ic:GC9306 购买地址:https://item.taobao.com/item.htm?spm=a1z10.5-c.w4002-24045920841.39.6c2275a1Pa8F9o&id=655959696358]]
-- lcd.init("gc9a01",{port = "device",pin_dc = 6, pin_pwr = 11,pin_rst = 10,direction = 0,w = 240,h = 320,xoffset = 0,yoffset = 0},spi_lcd)

--[[ 此为合宙售卖的1.8寸TFT LCD LCD 分辨率:128X160 屏幕ic:st7735 购买地址:https://item.taobao.com/item.htm?spm=a1z10.5-c.w4002-24045920841.19.6c2275a1Pa8F9o&id=560176729178]]
--lcd.init("st7735",{port = "device",pin_dc = 6, pin_pwr = 11,pin_rst = 10, direction = 0, w = 128, h = 160, xoffset = 0, yoffset = -50},spi_lcd)

--[[ 此为合宙售卖的1.8寸TFT LCD LCD 分辨率:128X160 屏幕ic:st7735 购买地址:https://item.taobao.com/item.htm?spm=a1z10.5-c.w4002-24045920841.19.6c2275a1Pa8F9o&id=560176729178]]
lcd.init("st7735",{port = "device",pin_dc = 6, pin_pwr = 11,pin_rst = 10, direction = 1, w = 160, h = 240, xoffset = 0, yoffset = -100 },spi_lcd)

--[[ 此为合宙售卖的1.54寸TFT LCD LCD 分辨率:240X240 屏幕ic:st7789 购买地址:https://item.taobao.com/item.htm?spm=a1z10.5-c.w4002-24045920841.20.391445d5Ql4uJl&id=659456700222]]
-- lcd.init("st7789",{port = "device",pin_dc = 6, pin_pwr = 11,pin_rst = 10,direction = 0,w = 240,h = 240,xoffset = 0,yoffset = 0},spi_lcd)

--[[ 此为合宙售卖的0.96寸TFT LCD LCD 分辨率:160X80 屏幕ic:st7735s 购买地址:https://item.taobao.com/item.htm?id=661054472686]]
--lcd.init("st7735v",{port = "device",pin_dc = 6, pin_pwr = 11,pin_rst = 10,direction = 1,w = 160,h = 80,xoffset = 0,yoffset = 24},spi_lcd)
--如果显示颜色相反，请解开下面一行的注释，关闭反色
--lcd.invoff()
--如果显示依旧不正常，可以尝试老版本的板子的驱动
--lcd.init("st7735s",{port = "device",pin_dc = 6, pin_pwr = 11,pin_rst = 10,direction = 2,w = 160,h = 80,xoffset = 0,yoffset = 0},spi_lcd)

--[[ 此为合宙售卖的2.4寸TFT LCD 分辨率:240X320 屏幕ic:GC9306 购买地址:https://item.taobao.com/item.htm?spm=a1z10.5-c.w4002-24045920841.39.6c2275a1Pa8F9o&id=655959696358]]
-- lcd.init("gc9306",{port = "device",pin_dc = 6, pin_pwr = 11,pin_rst = 10,direction = 0,w = 240,h = 320,xoffset = 0,yoffset = 0},spi_lcd)

-- 不在上述内置驱动的, 看demo/lcd_custom

log.info("lvgl", lvgl.init())

local scr = lvgl.obj_create(nil, nil)

local btn = lvgl.btn_create(scr)
local btn2 = lvgl.btn_create(scr)
local btn3 = lvgl.btn_create(scr)
local btn4 = lvgl.btn_create(scr)

--testing C3 / C3L display almost ok
lvgl.obj_align(btn, lvgl.scr_act(), lvgl.ALIGN_CENTER, 0, 0)
lvgl.obj_align(btn2, lvgl.scr_act(), lvgl.ALIGN_CENTER, 0, 30)
lvgl.obj_align(btn3, lvgl.scr_act(), lvgl.ALIGN_CENTER, 0, 60)
lvgl.obj_align(btn4, lvgl.scr_act(), lvgl.ALIGN_CENTER, 0, 90)

local label = lvgl.label_create(btn)
local label2 = lvgl.label_create(btn2)
local label3 = lvgl.label_create(btn3)
local label4 = lvgl.label_create(btn4)

lvgl.label_set_text(label, "Luatos V1005")
lvgl.label_set_text(label2, "Hi xiaolaba ")
lvgl.label_set_text(label3, "ESP32C3 / C3L")
lvgl.label_set_text(label4, "2023-11-12")

lvgl.scr_load(scr)



-- 用户代码已结束---------------------------------------------
-- 结尾总是这一句
sys.run()
-- sys.run()之后后面不要加任何语句!!!!!


