import board
import busio
import adafruit_pca9685
import RPi.GPIO as GPIO
import datetime as dt
import time
from adafruit_servokit import ServoKit
from .lightsensor import getResistance
from BlockSystem import AbstractBlock

#Setup Servo
i2c = busio.I2C(board.SCL, board.SDA)
hat = adafruit_pca9685.PCA9685(i2c)
kit = ServoKit(channels=16)

#Setup Photoresistor 
mpin=16
tpin=23
GPIO.setmode(GPIO.BCM)
GPIO.setup(tpin, GPIO.OUT)

class Station(AbstractBlock):
    def __init__(self, blockname = "Station"):
        super().__init__(blockname)
        
    def sense(self):
        return getResistance(mpin,tpin) < 40
    def stopTrain(self):
        kit.continuous_servo[1].throttle = 0
    def moveTrain(self):
        kit.continuous_servo[1].throttle = 1




    
    
