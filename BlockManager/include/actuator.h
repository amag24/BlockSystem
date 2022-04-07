#ifndef ACTUATOR_H
#define ACTUATOR_H

class Actuator {

public:
    Actuator()
    {
       this->stop();
    }

    virtual ~Actuator()
    {
    }

public:
    
    virtual void stop() const = 0;
    
    virtual void advance() const = 0;

    virtual void reverse() const
    {
    }

};

#endif //ACTUATOR_H