

def getResistance(mpin,tpin):
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
    cap=0.0000001
    adj=2.130620985
    res= 200-((measureresistance/cap)*adj/1000)
    return res
