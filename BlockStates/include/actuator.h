#ifndef ACTUATOR_H
#define ACTUATOR_H

class Actuator {

public:
    Actuator()
    {
       this->stop(); 
    }

public:
    
    virtual void stop() const = 0;
    
    virtual void advance() const = 0;

};

#endif //ACTUATOR_H