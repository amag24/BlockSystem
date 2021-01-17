
import RPi.GPIO as GPIO
import datetime as dt
import time
import argparse
import signal
import sys
import logging
from rpi_rf import RFDevice 

from .lightsensor import getResistance
from BlockSystem import AbstractBlock

#Setup RF Transmitter
rfdevice = RFDevice(21)
rfdevice.enable_tx()

#Setup Photoresistor circuit
mpin=5
tpin=27
GPIO.setmode(GPIO.BCM)
GPIO.setup(tpin, GPIO.OUT)

class LiftHill(AbstractBlock):
    def __init__(self, blockname = "Lift"):
        super().__init__(blockname)
        
    def sense(self):
        return getResistance(mpin,tpin) < 40
    def stopTrain(self):
        rfdevice.tx_code(70972, 1, 185)
    def moveTrain(self):
        rfdevice.tx_code(70963, 1, 185)



    
    