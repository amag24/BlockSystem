#include "sensor.h"

Sensor::Sensor(int mpin, int tpin, float threshold) : _mpin(mpin), _tpin(tpin), _threshold(threshold), _detected(false), _last_change(std::chrono::system_clock::now())
{
    pinMode(_tpin, OUTPUT);
}

void Sensor::sense()
{
    //Reset
    pinMode(_mpin, OUTPUT);
    digitalWrite(_mpin, 0);
    digitalWrite(_tpin, 0);
    delay(0.0005);
    pinMode(_mpin, INPUT);
    delay(0.0005);

    //Fire pulse
    digitalWrite(_tpin, 1);
    _start = std::chrono::system_clock::now();
    while (!digitalRead(_mpin)){} //Wait to recieve signal 

    _end = std::chrono::system_clock::now();
    float reading = 0.02 * std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count();
    addReading(reading);
}

void Sensor::addReading(const float &reading)
{
    if (reading < 0.05){ 
        std::cout << "------LOW READING------ (threshold "<<_threshold<<")"<<std::endl;
    } else {
        _sensor_readings.push_back(reading);
        if (_sensor_readings.size() > 7) _sensor_readings.pop_front();
        int high=0, low = 0;
        for (auto& read : _sensor_readings){
            if (read > _threshold){
                high++;
            } else {
                low++;
            }
        }
        bool new_detection = ( high > low);
        //~ std::cout <<"Threshold " << _threshold<< " reading "<<reading<<" size "<<_sensor_readings.size()<<" detection "<<new_detection<<high<<low<<std::endl;

        if (new_detection != _detected) {_last_change = _end;}
        _detected = new_detection;
    }
}

void Sensor::printReport()
{
    std::cout <<"Threshold " << _threshold <<" size "<<_sensor_readings.size()<<" detection "<<_detected<<std::endl;
    for (auto& reading : _sensor_readings){
        std::cout << reading << std::endl;
    }
}

float Sensor::statusDuration() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _last_change.load()).count();
}
