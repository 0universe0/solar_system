# Solar System

## DISCLAIMER!

This repository is orphaned, as we want to preserve the state of the project at the end of the course cited below.
To see how this little project will continue, check out [this](https://github.com/pirosapphic/solar_system_reborn) fork of the repository.

## geocentrism rocks!

Final project for the "Computing Techniques for Physics" course in the Bachelor's Degree in Physics at the University of Turin.
The goal is to simulate the solar system in C++, implementing a way to visualize the orbits of the planets in 2 and 3 dimensions using ROOT.
Coincidentally we also verify the validity of the second and third Kepler's laws.

### Luca Tempesta, Alessandro Romanini, Paolo Rocchietti March.

## Structure

The project is subdivided in directories:

* src: containing source files (.cpp)
* include: containig header files (.h, .cc)
* bin: containing compiled executables
* root: containing ROOT files
  * media: containig .mp4 and .png files of some configurations 
* csv: containing the .csv files that store the simulations' output

Make will be used to guarantee the automation of the compiling process.
## How to use
Firstly, you need to clone this repository with the command

<code>git clone https://www.github.com/0universe0/solar_system.git</code>. 

### N body simulator
To access the main simulator, you need to compile the code and libraries by running <code>make</code>
in the main directory, you can then execute the binary <code>./bin/main</code> to access the simulator: 
there you will be prompted with some presets and an option to fully customize the simulation (including custom bodies).
When the simulator is done, you can visualize the data in three ways:
* Running the root macro <code>root ./root/bodiesGraphic2D.cpp</code>, that will plot the projection on the XY plane of the orbits.
* Running the root macro <code>root ./root/bodiesGraphic3D.cpp</code>, that will fully plot the orbits in 3D.
* Running the root animation macro (see below).

NOTE: it is advisable to keep the number of total iterations below 5e6 and the time step below 1e4 seconds (the fantastic loading bar is your friend ;) ).

### Second Kepler law of planetary motion
To verify the second law, you can execute the specific root macro with
<code>root ./root/secondKepler.cpp</code>
that will show that the areal velocity of closed orbits is constant over time (simulating the Earth-Sun and Moon-Earth systems).

### Third Kepler law of planetary motion
To verify the third law, you can execute the specific root macro with
<code>root ./root/thirdKepler.cpp</code>
that will show that, for closed orbits, T^2 is proportional to a^3 (where a is the major semiaxis and the T is the period of the orbit) by a constant k dependent on the mass of the bigger body of the binary system (even though this is inaccurate for the orbits of the gas giants, like Jupiter).

### Animation macro
In the <code>root</code> directory there are some macros that allow to visualize the different configurations simulated:
* <code>root ./root/animation2D.cpp</code> is the general purpouse animation macro: you can use it for custom simulations (note that the sunEarthMoon preset won't work).
* <code>root ./root/animationInnerSolarSystem.cpp</code> is the specific animation macro for the inner Solar System.
* <code>root ./root/animationOuterSolarSystem.cpp</code> is the specific animation macro for the outer Solar System.
* <code>root ./root/animationSunEarthMoon.cpp</code> is the specific animation macro for the Sun, Earth and Moon system.

All the animation macros produce a .gif file in <code>./root/media</code> that can be converted in a .mp4 video format by using the <code>ffmpeg</code> utility:

<code>ffmpeg -i /path/to/file_name.gif /path/to/file_name.mp4</code>
