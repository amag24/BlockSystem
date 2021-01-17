import time
#modes = {
#    "VACANT",   #There is no train in this block
#    "ENTERING", #I'm still considered empty, but I should start moving to help train in previous block depart
#    "APPROACHING", #Previous block is now empty, I own the train and am waiting to sense it
#    "HOLDING", #I can sense the train and the next block is occupied
#    "DEPARTING", #I can see the train and the next block is free
#    "UNKNOWN" #Initial state. Defaults to holding behavior
#   }

#Accepts a list of blocks (optimally in reverse order)
def autoRun(coaster):
    while True:
        for block in coaster:
            block.setStatus()
        updatestring = str(time.time()) + ":"
        for block in coaster:
            #block.setBehavior()
            updatestring += " " + block.name + ": " + block.status
            block.moveTrain()
        print(updatestring)


class AbstractBlock:
    def __init__(self, blockname = "Unnamed Block"):
        self.name = blockname
        self.status = "UNKNOWN"
        self.EStopFlag = False

    #Public Methods

    #Call this method to link this block to the next one along the coaster. All blocks have to be linked in order for the coaster to run 
    def isFollowedBy(self,nextBlock):
        self.heir = nextBlock

    #Emergency stop procedure. Stop any motion, mark that I've heard the order, and relay the order to my neighbor
    #Continues until all blocks have heard, then an exception should be raised right after this method
    def E_STOP(self):
        if not EstopFlag:
            self.stopTrain()
            self.EStopFlag = True
            self.heir.E_STOP()

    #The block that I am an heir to uses this method to tell me that it's handing me a train, or that it has finished doing so
    def handoff(self, active):
        if active:
            if self.status in ("VACANT","ENTERING"):
                self.status = "ENTERING"
            else:
                self.E_STOP()
                raise RuntimeError(self.name + ": E-STOPPED because I was asked to accept a train but I am in " + self.status)
        else:
            if self.status is "ENTERING":
                self.status = "APPROACHING"

    def setStatus(self):
        try:
            if self.sense(): #Look for the train. If we see something...
                if self.status is "UNKNOWN": #When script starts, make sure all trains are seen by the sensor in their respective blocks
                    self.status = "HOLDING"                    
                elif self.status is "VACANT":
                    self.E_STOP()
                    raise RuntimeError(self.name + ": E-STOPPED because I saw a train when I was supposed to be VACANT")
                else:
                    if self.heir.status in ("VACANT","ENTERING"): 
                        self.status = "DEPARTING"
                        self.heir.handoff(True)
                    else:
                        if self.status is "DEPARTING":
                            #Ensure that if a train is sensed by one block, it can't be sensed by the next. Otherwise it could lock up here.
                            raise Warning(self.name + ": I'm stuck because the next block saw the train too early as I was trying to depart")
                        self.status = "HOLDING"
            else: #If we don't see a train anywhere...
                if self.status is "UNKNOWN":
                    self.status = "VACANT"
                elif self.status is "HOLDING":
                    self.E_STOP()
                    raise RuntimeError(self.name + ":E-STOPPED because I lost sight of the train that I was supposed to be HOLDING")
                elif self.status is "DEPARTING":
                    self.status = "VACANT"
                    self.heir.handoff(False)
        except:
            raise RuntimeError(self.name + ": Failed while trying to get the status. Check if an heir has been assigned to this block.")
    
    def setAction(self):
        if self.status is "UNKNOWN":
            #This really should never happen
            raise Warning(self.name + ": I was told to act but I am in an UNKNOWN state for some reason. Defaulting to holding behavior...")
        if self.status in ("UNKNOWN","HOLDING","VACANT"):
            self.stopTrain()
        else: 
            self.moveTrain()

    #Virtual/Private:
    def sense(self):
        self.E_STOP()
        raise NotImplementedError(self.name + ": sense method should be overriden in a derived block class")
    def stopTrain(self):
        self.E_STOP()
        raise NotImplementedError(self.name + ": stopTrain method should be overriden in a derived block class")
    def moveTrain(self):
        self.E_STOP()
        raise NotImplementedError(self.name + ": moveTrain method should be overriden in a derived block class")

    
 
