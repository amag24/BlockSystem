import board
import busio
import adafruit_pca9685
import datetime as dt
import time
import RPi.GPIO as GPIO
from adafruit_servokit import ServoKit
from lightsensor import getResistance
from BlockSystem import AbstractBlock

#Setup Servo
i2c = busio.I2C(board.SCL, board.SDA)
hat = adafruit_pca9685.PCA9685(i2c)
kit = ServoKit(channels=16)
kit.servo[0].set_pulse_width_range(600, 2400)

#Setup Photoresistor 
mpin=6
tpin=25
GPIO.setmode(GPIO.BCM)
GPIO.setup(tpin, GPIO.OUT)

class FinalBrake(AbstractBlock):
    def __init__(self, blockname = "Gravity"):
        super().__init__(blockname)

    def sense(self):
        res = getResistance(mpin,tpin)
        #print(self.name + ": " + str(res))
        return res < 180
    def stopTrain(self):
        kit.servo[0].angle = 135
    def moveTrain(self):
        kit.servo[0].angle = 155




    
    
