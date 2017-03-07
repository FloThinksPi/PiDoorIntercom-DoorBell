#!/usr/bin/env python

import RPi.GPIO as GPIO
import requests
from multiprocessing.dummy import Pool
from time import sleep

btnPin = 14
ledPin = 15

pool = Pool(1)

GPIO.setmode(GPIO.BCM)
GPIO.setup(btnPin, GPIO.IN, pull_up_down=GPIO.PUD_UP) #Fix , remove pullup
GPIO.setup(ledPin, GPIO.OUT, initial=GPIO.HIGH)
GPIO.add_event_detect(btnPin, GPIO.FALLING, bouncetime=1000)

def btn_pushed(channel):
    print 'PUSHED!'

    pool.apply_async(gong())

    blink()

def gong():
    requests.get('http://10.110.109.118/gong')
    return 0

def blink():

    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.HIGH)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.HIGH)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.HIGH)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.HIGH)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.HIGH)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.HIGH)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.HIGH)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.HIGH)
    sleep(0.25)
    GPIO.output(ledPin, GPIO.LOW)
    sleep(0.25)
    GPIO.output(15, GPIO.HIGH)
    return 0

GPIO.add_event_callback(btnPin, btn_pushed)

while True:
    sleep(0.1)
