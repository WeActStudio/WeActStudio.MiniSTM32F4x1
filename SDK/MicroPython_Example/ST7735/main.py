# main.py -- put your code here!
from ST7735 import TFT, TFTColor
from machine import SPI, Pin
from sysfont import sysfont
import time
import math

spi2 = SPI(2, baudrate=20000000, polarity=0, phase=0)
# spi2 = SPI(-1, baudrate=48000000, polarity=0, phase=0, sck=Pin('PB13'), mosi=Pin('PB15'), miso=Pin('PB14'))
cs = Pin('PA10', Pin.OUT, Pin.PULL_NONE)
dc = Pin('PA9', Pin.OUT, Pin.PULL_NONE)
rst = Pin('PA8', Pin.OUT, Pin.PULL_NONE)

lcd_led = Pin('PA15', Pin.OUT, Pin.PULL_NONE)
lcd_led.value(1)
Lcd_LEDCount = 0
LCD_LEDSet = 10


def LCD_LEDCtrl(timer):
    global Lcd_LEDCount, LCD_LEDSet
    Lcd_LEDCount = Lcd_LEDCount + 1
    if Lcd_LEDCount == 10:
        Lcd_LEDCount = 0
    if LCD_LEDSet > Lcd_LEDCount:
        lcd_led.value(0)
    else:
        lcd_led.value(1)


lcd_led_tim = pyb.Timer(2)
lcd_led_tim.init(freq=4000)  # Freq: 4KHz
lcd_led_tim.callback(LCD_LEDCtrl)
tft = TFT(spi2, dc, rst, cs)
tft.init_7735(TFT.REDTAB)
tft.rotation(2)
tft.rgb(True)


def display_weact_logo():
    tft.fill(TFT.BLACK)
    f = open('WeAct_logo_128_160.bmp', 'rb')
    if f.read(2) == b'BM':  # header
        dummy = f.read(8)  # file size(4), creator bytes(4)
        offset = int.from_bytes(f.read(4), 'little')
        hdrsize = int.from_bytes(f.read(4), 'little')
        width = int.from_bytes(f.read(4), 'little')
        height = int.from_bytes(f.read(4), 'little')
        buf = bytearray(width * 2)  # init buf
        if int.from_bytes(f.read(2), 'little') == 1:  # planes must be 1
            depth = int.from_bytes(f.read(2), 'little')
            if depth == 24 and int.from_bytes(f.read(4), 'little') == 0:  # compress method == uncompressed
                print("Image size:", width, "x", height)
                rowsize = (width * 3 + 3) & ~3
                if height < 0:
                    height = -height
                    flip = False
                else:
                    flip = True
                w, h = width, height
                if w > 128: w = 128
                if h > 160: h = 160
                tft._setwindowloc((0, 0), (w - 1, h - 1))
                count = 0
                for row in range(height):
                    if flip:
                        pos = offset + (height - 1 - row) * rowsize
                    else:
                        pos = offset + row * rowsize
                    if f.tell() != pos:
                        dummy = f.seek(pos)
                    for col in range(w):
                        bgr = f.read(3)
                        rgb_color = TFTColor(bgr[2], bgr[1], bgr[0])
                        buf[col * 2] = rgb_color >> 8
                        buf[col * 2 + 1] = rgb_color
                    tft.image(0, row, 128 - 1, row - 1, buf)


display_weact_logo()
tft.fill(TFT.BLACK)
tft.text((0, 0), "WeAct Studio", TFT.WHITE, sysfont, 1, nowrap=True)
tft.text((0, 20), "ST7735 128*160 RGB", TFT.WHITE, sysfont, 1, nowrap=True)
tft.text((0, 40), "Version:1.0", TFT.WHITE, sysfont, 1, nowrap=True)
tft.text((0, 60), "Micropython Test", TFT.WHITE, sysfont, 1, nowrap=True)

