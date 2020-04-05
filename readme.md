
# CPPND: Capstone Plane Game 

This project was built based on the starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
The original starter repo provided by Udacity is: (https://github.com/udacity/CppND-Capstone-Snake-Game.git)

# The idea of this game:
1. There are two planes (multithread) trying to reach the destination (flag).
2. The user can use arrow keys to controll the plane.
3. There are multiple moving obstacles. If the plane collide with the obstacle,the plane will stop permanently.
4. The user use Ctrl key to shift from car to car(two cars in total).
5. When the two cars reached the destination, a new level is started with more obstacles.


# Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./DualGame`.



## The Rubric Criteria:

### A README with instructions is included with the project
Done

### The README indicates which project is chosen.
Done

### The README includes information about each rubric point addressed.
Done

### The submission must compile and run.
Done (on Udacity workspace and local complier)

### The project demonstrates an understanding of C++ functions and control structures.
Done

### The project reads data from a file and process the data, or the program writes data to a file.
Done ( the highest score is recorded in a file "result.txt", read by the function getHighestScore)

### The project accepts user input and processes the input.
Done (user input is mainly by Ctrl and arrow keys, processed by SDL)

### The project uses Object Oriented Programming techniques.
Done 

### Classes use appropriate access specifiers for class members.
Done

### Class constructors utilize member initialization lists.
Done

### Classes abstract implementation details from their interfaces.
Done

### Classes encapsulate behavior.
Done

### Templates generalize functions in the project.
Done ( randomizer genRand() method is generic )

### The project makes use of references in function declarations.
Done

### The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
Done

### The project follows the Rule of 5.
Done ( copy and move constructors are applied for the obstacle object)


### The project uses move semantics to move data, instead of copying it, where possible.
Done ( when creating objects in the scope of the for-loop and inserting them in a vector outside the loop)

### The project uses smart pointers instead of raw pointers.
Done ( the plane uses a shared_ptr)

### The project uses multithreading.
Done (two different planes represented by different threads)

### A mutex or lock is used in the project.
Done

### A condition variable is used in the project.
Done (notify_all)