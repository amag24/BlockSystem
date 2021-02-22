# BlockSystem
A brief library designed to serve as the backbone of a fully autonomous model roller coaster block system. At the moment it is only capable of handling simple linear blocks with one sensor and one method of controlling train motion.

The brief library in BlockSystem.py does all the heavy lifting for you. To apply to a new coaster, simply define a new class for each block that inherits the AbstractBlock class defined in BlockSystem.py. 

Then define the sense(), moveTrain(), and stopTrain() methods according to what your sensors and mechanisms need. (See Lifthill.py, Station.py, or Finalbrake.py).

Finally, instantiate each block, place them in a list, and link them with their "heir". Essentially, each block is fed a reference to the block immediately following it so that it may tell them when to enter the "Entering" mode. This is what enables the lift to start when the station still sees the departing train. 

Once the blocks are linked and assembled in a list, call autoRun with that list as an argument. 
(see coaster.py)

____________________________________________________________________________
Things that I would like to support in the future (check back for updates!):
____________________________________________________________________________
Multi-sensor blocks

Station gates, lights, & other animatables

Transfer/Trick Tracks

Shuttle blocks (like swing launches)

Manual Block/Full manual mode

Control Panel React App
