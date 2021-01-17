import board
import busio
import adafruit_pca9685
import RPi.GPIO as GPIO
import datetime as dt
import time
from adafruit_servokit import ServoKit

import argparse
import signal
import sys
import logging
from rpi_rf import RFDevice 

#Setup Servo
i2c = busio.I2C(board.SCL, board.SDA)
hat = adafruit_pca9685.PCA9685(i2c)
kit = ServoKit(channels=16)

rfdevice = RFDevice(21) #default gpio pin 
rfdevice.enable_tx()

#Setup Photoresistor circuit
mpin=17
tpin=27
GPIO.setmode(GPIO.BCM)
cap=0.0000001
adj=2.130620985
GPIO.setup(tpin, GPIO.OUT)

def getResistance():
    i=0
    t=0
#     for iteration in range(1,5):
    GPIO.setup(mpin, GPIO.OUT)
    GPIO.output(mpin, False)
    GPIO.output(tpin, False)
    time.sleep(0.01)
    GPIO.setup(mpin, GPIO.IN)
    time.sleep(0.01)
    GPIO.output(tpin, True)
    starttime=time.time()
    endtime=time.time()
    while (GPIO.input(mpin) == GPIO.LOW):
        endtime=time.time()
    measureresistance=endtime-starttime    
    res= 200-((measureresistance/cap)*adj/1000)
    i=i+1
    t=t+res
    average=t/i
    i=0
    t=0
    return res
rfdevice.tx_code(70963, 1, 185)
while True:
    if getResistance() < 40:
        rfdevice.tx_code(70972, 1, 185)
        time.sleep(5)
        rfdevice.tx_code(70963, 1, 185)
        time.sleep(5)




    
    