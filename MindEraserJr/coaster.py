
import BlockSystem
from .station import Station
from .lifthill import LiftHill
from .finalbrake import FinalBrake

MindErasor2 = [FinalBrake(),LiftHill(),Station()]
for block in range(len(MindErasor2)):
    MindErasor2[block].isFollowedBy(MindErasor2[block-1])


BlockSystem.autoRun(MindErasor2)

    
    
