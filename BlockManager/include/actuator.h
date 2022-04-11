#ifndef ACTUATOR_H
#define ACTUATOR_H

class Actuator {

public:
    Actuator()
    {
    }

    virtual ~Actuator()
    {
    }

public:
    
    virtual void stop() = 0;
    
    virtual void advance() = 0;

    virtual void reverse()
    {
    }

};

#endif //ACTUATOR_H
