from machine import Pin
from utime import sleep

# LEDピンの設定
red_led = Pin(6, Pin.OUT)
blue_led = Pin(4, Pin.OUT)
green_led = Pin(5, Pin.OUT)

# タクトスイッチのピン設定
red_button = Pin(21, Pin.IN, Pin.PULL_UP)
blue_button = Pin(20, Pin.IN, Pin.PULL_UP)
green_button = Pin(19, Pin.IN, Pin.PULL_UP)

while True:
    if red_button.value() == 0:
        red_led.on()
    else:
        red_led.off()

    if blue_button.value() == 0:
        blue_led.on()
    else:
        blue_led.off()

    if green_button.value() == 0:
        green_led.on()
    else:
        green_led.off()

    sleep(0.01)
