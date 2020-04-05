#ifndef CAR_H
#define CAR_H

#include <string>
#include <mutex>

class Car{

public:

    Car(int x, int y,int limit, int speed, std::string axis):_xpos(x), _ypos(y), _limit(limit), _speed(speed), _axis(axis){}
    
    //copy cstr
    Car(Car& src);
    
    void move();
    int newPos(int pos);


    void deactivate(){_active = false;}
    void setDirection(int d);
    void setAxis(std::string axis);
    void adjustDelay(int d);
    int get_xpos();
    void set_xpos(int x);
    int get_ypos();
    void set_ypos(int y);
    bool get_success();
    bool isActive();
    void set_active(bool a);

private:
    int _xpos, _ypos;
    int _delay = 25;
    bool _active = true;
    int _speed;
    int  _limit;
    std::string _axis;
    bool _succeeded = false;
    std::mutex mtx;
};


#endif