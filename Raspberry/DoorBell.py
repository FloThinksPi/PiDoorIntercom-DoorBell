#!/usr/bin/python3

import RPi.GPIO as GPIO
import requests
from multiprocessing.dummy import Pool
from time import sleep

# Pin setup
btnPin = 14
ledPin = 15
# Button blinking settings
numBlink = 8 # Number of ON-OFF loops
blinkTime = 0.3 # Time(seconds) to sleep between each gpio state switch
#Gong URL
gongURL = 'http://YOURIP/gong'

# Misc
pool = Pool(1)
GPIO.setmode(GPIO.BCM)
GPIO.setup(btnPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(ledPin, GPIO.OUT, initial=GPIO.HIGH)
GPIO.add_event_detect(btnPin, GPIO.FALLING, bouncetime=1000)

def btn_pushed(channel):
    pool.apply_async(gong())
    blink()

def gong():
    requests.get(gongURL)
    return 0

def blink():

    for x in range(numBlink):
        GPIO.output(ledPin, GPIO.LOW)
        sleep(blinkTime)
        GPIO.output(ledPin, GPIO.HIGH)
        sleep(blinkTime)

    GPIO.output(ledPin, GPIO.HIGH) # Be high again at the end
    return 0

GPIO.add_event_callback(btnPin, btn_pushed)

while True:
    sleep(0.1)
