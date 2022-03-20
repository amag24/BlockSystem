import RPi.GPIO as GPIO
import time

def getResistance(mpin,tpin):
    samples = []
    for test in range(0,5):
        GPIO.setup(mpin, GPIO.OUT)
        GPIO.output(mpin, False)
        GPIO.output(tpin, False)
        time.sleep(0.002)
        GPIO.setup(mpin, GPIO.IN)
        time.sleep(0.002)
        GPIO.output(tpin, True)
        starttime=time.time()
        endtime=time.time()
        while (GPIO.input(mpin) == GPIO.LOW):
            endtime=time.time()
        measureresistance=endtime-starttime 
        cap=0.0000001
        adj=2.130620985
        samples.append( 200-((measureresistance/cap)*adj/1000))
        
    return (sum(samples)/len(samples))
