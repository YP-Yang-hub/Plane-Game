
#include "obstacle.h"
#include <thread>
#include <iostream>
#include <string>
#include "car.h"

    //copy cstr
    Obstacle::Obstacle(const Obstacle& src){
        _xpos = src._xpos;
        _ypos = src._ypos;
        _delay = src._delay;
        _active = src._active;
        _speed = src._speed;
        _limit = src._limit;
        _axis = src._axis;
           _cars = src._cars;
    };
  //copy assignment operator
    Obstacle& Obstacle::operator=(const Obstacle& src){
        if(this != &src){
            _xpos = src._xpos;
            _ypos = src._ypos;
            _delay = src._delay;
            _active = src._active;
            _speed = src._speed;
            _limit = src._limit;
            _axis = src._axis;
           _cars = src._cars;
       
        }

        return *this;
    };





    //move cstr
    Obstacle::Obstacle(Obstacle&& src){
        _xpos = src._xpos;
        _ypos = src._ypos;
        _delay = src._delay;
        _active = src._active;
        _speed = src._speed;
        _limit = src._limit;
        _axis = src._axis;
        _cars = src._cars;
       //default the value of the src object
        src._xpos = 0;
        src._ypos = 0;
        src._delay = 0;
        src._active = false;
        src._speed = 0;
        src._limit = 0;
        src._axis = "";
    };
    

    //move assignment operator
    Obstacle& Obstacle::operator=(Obstacle&& src){
        if(this != &src){
            _xpos = src._xpos;
            _ypos = src._ypos;
            _delay = src._delay;
            _active = src._active;
            _speed = src._speed;
            _limit = src._limit;
            _axis = src._axis;
            _cars = src._cars;
        
        //default the value of the src object
            src._xpos = 0;
            src._ypos = 0;
            src._delay = 0;
            src._active = false;
            src._speed = 0;
            src._limit = 0;
            src._axis = "";
            //src._cars.
        }

        return *this;
    };
    void Obstacle::move(){
        // horizontal
        // vertical
        while(_active){
            std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
            if (_axis == "horizontal"){
                int x = get_xpos();
                set_xpos( newPos(x));

                //std::cout << "Obstacle Thread #: " <<std::this_thread::get_id()<<" ---    Pos ="<< _xpos<<std::endl;
            }else{
                int y = get_ypos();
                set_ypos(newPos(y));

                //std::cout << "Obstacle Thread #: " <<std::this_thread::get_id()<<" ---   Pos = " <<_ypos<<std::endl;
            }

            for (int i = 0 ; i<2 ; i++){
                if((abs(get_xpos() - _cars[i]->get_xpos()) < _collision_distance  && (abs(get_ypos() - _cars[i]->get_ypos()) < _collision_distance ))){
                    _cars[i]->deactivate();
                }
            }
            //std::cout<<_cars.front()<<std::endl;
        }
    };

    int Obstacle::newPos(int pos){
        if (pos + _speed > _limit){

            pos = 0;// to make its edge visible

        }else if(pos + _speed < 0){
            
            pos = _limit;

        }else{

            pos += _speed;
        }
        return pos;

    };


    void Obstacle::setAxis(std::string axis){

        // horizontal or vertical
        _axis = axis;
    }

    void Obstacle::setDirection(int d){
        //+1 or -1
        _speed = d * abs(_speed);
    }

    void Obstacle::adjustDelay(int d){
        _delay += d;
    };

    int Obstacle::get_xpos(){
         
         return _xpos;
    }

    int Obstacle::get_ypos(){
       
         return _ypos;
    }


    void Obstacle::set_xpos(int x){
     
        _xpos = x;
    }


    void Obstacle::set_ypos(int y){
     
        _ypos = y;
    }



    