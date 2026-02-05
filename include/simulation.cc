#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "solarsystem.h" //paths relative to this file
#include "twobodies.h"
#include "planets.h"

//This is the core of the project: we implement the functions to simulate the motions.
//In here is also the greeter for the main simulator and some dependent functions
//
//For the main() function, see src/main.cpp

void customSettings(std::vector<CelestialBody*>& bodies){
    //Function used in setInitialConditions to set the custom settings

    Planets planets;
    std::vector<CelestialBody*> list_of_planets = planets.list_of_planets;
    std::cout<<"\n\nCustom settings\n";
    std::cout<<"Number of bodies for the simulation n = ";
    unsigned int n = 999;
    std::cin>>n;
    for(int i = 0; i < n; i++){
	unsigned int planet;
	while(true){
	    std::cout<<"Body "<<i+1<<std::endl;
	    std::cout<<"  - 0) Sun\n  - 1) Mercury\n  - 2) Venus\n  - 3) Earth\n  - 4) Moon\n  - 5) Mars\n  - 6) Jupiter\n  - 7) Saturn\n  - 8) Uranus\n  - 9) Neptune\n  - 10) Custom body\n";
	    std::cout<<"NOTE: you should insert the bodies in reverse order of orbit radius for the visualizer to work correctly\n";
	    std::cout<<"Please choose one of the bodies listed above: ";
	    std::cin>>planet;
	    if(planet<=10 and planet >=0) break;
	    std::cout<<"Invalid input, try again\n\n";
	}
	if (planet<10){
	    CelestialBody* dummy_planet = new CelestialBody(*list_of_planets[planet]);
	    bodies.push_back(dummy_planet);
	    std::cout<<"Do you want to use the default state of "<<bodies[i]->getName()<<"? [y/n]: ";
	    char choice = 'y';
	    std::cin>>choice;
	    if(choice == 'n'){
		std::cout<<"Initial state of body "<<i+1<<std::endl;
		double x,y,z,vx,vy,vz;
		std::cout<<"x [m] = ";
		std::cin>>x;
		std::cout<<"y [m] = ";
		std::cin>>y;
		std::cout<<"z [m] = ";
		std::cin>>z;

		std::cout<<"vx [m/s] = ";
		std::cin>>vx;
		std::cout<<"vy [m/s] = ";
		std::cin>>vy;
		std::cout<<"vz [m/s] = ";
		std::cin>>vz;
		bodies[i]->setPos({x,y,z});
		bodies[i]->setVel({vx,vy,vz});
	    }
	}
	else if (planet == 10){
	    std::cout<<"Name of the body: ";
	    std::string custom_name = "default";
	    double custom_mass, x,y,z, vx,vy,vz;
	    std::cin>> custom_name;
	    std::cout<<"Mass of the body [kg] = ";
	    std::cin>>custom_mass;
	    std::cout<<"Initial state of body '"<<custom_name<<"\n";
	    std::cout<<"x [m] = ";
	    std::cin>>x;
	    std::cout<<"y [m] = ";
	    std::cin>>y;
	    std::cout<<"z [m] = ";
	    std::cin>>z;

	    std::cout<<"vx [m/s] = ";
	    std::cin>>vx;
	    std::cout<<"vy [m/s] = ";
	    std::cin>>vy;
	    std::cout<<"vz [m/s] = ";
	    std::cin>>vz;
	    CelestialBody* custom_body = new CelestialBody(custom_name,custom_mass,{x,y,z},{vx,vy,vz});
	    bodies.push_back(custom_body);
	}
	std::cout<<"-----------------------\n";
    }
    std::cout<<"We suggest to set the total time and time step so that the number of iterations is not more than 5e6\n";
}

void fourBodies(std::vector<CelestialBody*>& bodies){
    //this sets the preset 7: it is a stable 4 body problem
    //used in setInitialConditions()
    Planets planets;
    std::vector<CelestialBody*> list_of_planets = planets.list_of_planets;

    double m = planets.moon->getMass();

    CelestialBody* moon1 = new CelestialBody("moon1",m,{17936783,-35734331,0},{338,-31.6,0});
    CelestialBody* moon2 = new CelestialBody("moon2",m,{28985207,8193378,0},{-328,251,0});
    CelestialBody* moon3 = new CelestialBody("moon3",m,{-10820767,21909245,0},{121,-351,0});
    CelestialBody* moon4 = new CelestialBody("moon4",m,{-36101224,5631708,0},{-131,131,0});

    bodies.push_back(moon1);
    bodies.push_back(moon2);
    bodies.push_back(moon3);
    bodies.push_back(moon4);

    std::cout<<"Suggested simulation times are:\n";
    std::cout<<"Total time: 4.32e5s (i.e. 5 days)\nTime step: 1s\n\n";
}

void setInitialConditions(std::vector<CelestialBody*>& bodies){
    //This is the greeter and the function that sets the initial conditions for the simulations	
    //Used in src/main.cpp

    Planets planets;
    std::vector<CelestialBody*> list_of_planets = planets.list_of_planets;
    unsigned int input = 0;
    while(true){
	std::cout << "Welcome to the n-body simulator!\nYou can choose a preset or setup a custom simulation.\n\n";
	std::cout << "  - 1) Earth - Moon\n";
	std::cout << "  - 2) Sun - Earth\n";
	std::cout << "  - 3) Sun - Earth - Moon\n";
	std::cout << "  - 4) Solar System (full)\n";
	std::cout << "  - 5) Inner Solar System\n";
	std::cout << "  - 6) Outer Solar System\n";
	std::cout << "  - 7) Four body system\n";
	std::cout << "  - 8) Custom\n\n";
	std::cout << "Choose one of the options above: ";
	std::cin>>input;
	std::cout << std::endl;
	if(input <= 8 and input > 0) break;
	std::cout<<"Invalid option, try again\n";
    }
    if (input == 1){
	bodies.push_back(planets.earth);
	bodies.push_back(planets.moon);
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 2.7e6s (i.e. 28 days)\nTime step: 10s\n\n";
    }
    else if (input == 2){
	bodies.push_back(planets.sun);
	bodies.push_back(planets.earth);
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 3.16e7s (i.e. 1 earth-year)\n Time step: 100s\n\n";
    }
    else if (input == 3){
	bodies.push_back(planets.sun);
	bodies.push_back(planets.earth);
	bodies.push_back(planets.moon);
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 3.16e7s (i.e. 1 orbit of Earth)\nTime step: 100s\n\n";
    }
    else if (input == 4){
	bodies = list_of_planets; //in order of distance from the sun,
				  //but with the moon between earth and mars: see planets.h
	std::cout<<"WARNING: this simulation is really big and resource intensive.\nIt is not advised to run more than 5e6 iterations.\n";
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 5e9s (i.e. 1 orbit of Neptune)\nTime step: 8000s\n\n";
    }				      
    else if (input == 5){
	bodies.push_back(planets.sun);
	bodies.push_back(planets.mercury);
	bodies.push_back(planets.venus);
	bodies.push_back(planets.earth);
	bodies.push_back(planets.moon);
	bodies.push_back(planets.mars);
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 6e7s (i.e. 1 orbit of Mars)\nTime step: 100s\n\n";
    }
    else if (input == 6){
	bodies.push_back(planets.sun);
	bodies.push_back(planets.jupiter);
	bodies.push_back(planets.saturn);
	bodies.push_back(planets.uranus);
	bodies.push_back(planets.neptune);
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 5e9s (i.e. 1 orbit of Neptune)\nTime step: 1e4s\n\n";
    }

    else if (input == 7){
	fourBodies(bodies);
    }

    else {
	customSettings(bodies);
    }
    bodies.shrink_to_fit();
}

std::vector<std::vector<double>> equivalentBodySimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt){
    //This is part of the two body problem.
    //This function simulates the motion of the equivalent body with the reduced mass \mu
    //and returns a vector of vectors so that pos[i] is the position vector of the body at t=i*dt
    //unlike twoBodiesSimulation, this function does not modify the members of
    //p1 and p2, besides putting them in their COM reference frame.

    //Used to verify kepler's laws, see root/secondKepler.cpp and root/thirdKepler.cpp
    unsigned int steps = totalt / dt;
    std::vector<std::vector<double>> pos(steps, std::vector<double>(3));
    changeToCOM(p1,p2); //probably do not need this, as I do not need to convert
			//back to p1 and p2
    CelestialBody* equivalent = new CelestialBody;
    *equivalent = toEquivalentBody(p1,p2);
    std::vector<double> acceleration;
    for (int i = 0; i < steps; i++){
	//Progress bar
	double percentage = (double) (i+1)/steps; //dynamic casting!
	int perc_int = 100*percentage;
	int barlen = 50;
	int bar = std::ceil(percentage*barlen);
	std::cout<<"\rLoading... [";
	for(int m = 1; m <= bar; m++){
	    std::cout<<"■";
	}
	for(int m = 1; m <= barlen-bar; m++){
	    std::cout<<" ";
	}
	std::cout<<"] "<<std::setprecision(3)<<perc_int<<"%";
	//Progress bar ends
	pos[i] = equivalent->getPos();
	acceleration = gravityAcceleration(*equivalent, p1.getMass(),p2.getMass());
	equivalent->updateVel(acceleration,dt);
	equivalent->updatePos(dt);
    }
    pos.shrink_to_fit();
    return pos;
}

void twoBodiesSimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt, std::string output_file){
    //This is the two body simulator, that uses the equivalent body of reduced mass \mu orbiting
    //the center of mass of the system. This was implemented separately from n>2 because it is less resource intensive.
    //It simulates the motion of p1 and p2 and puts the result in output_file (as a .csv)
    //The differential equations of motion are integrated with Euler's method.

    //It is called in nBodiesSimulation for n==2

    //std::string output_file should be in the form "relative/path/to/output.csv"
    unsigned int steps = totalt/dt;
    std::vector<std::vector<double>> pos1(steps, std::vector<double>(3));
    std::vector<std::vector<double>> pos2(steps, std::vector<double>(3));
    //the first index is the time step, so that pos1[i] is the position vector of p1 @ t=i*dt

    changeToCOM(p1,p2);	//fundamental!
    CelestialBody* equivalent = new CelestialBody();
    *equivalent = toEquivalentBody(p1,p2);
    std::vector<double> acceleration;
    std::ofstream out_file(output_file); //to export data
    out_file<<"#x1,y1,z1,x2,y2,z2"<<std::endl; //header of the csv file
    for (int i = 0; i < steps; i++){
	//Progress bar
	double percentage = (double) (i+1)/steps; //dynamic casting!
	int perc_int = 100*percentage;
	int barlen = 50;
	int bar = std::ceil(percentage*barlen);
	std::cout<<"\rLoading... [";
	for(int m = 1; m <= bar; m++){
	    std::cout<<"■";
	}
	for(int m = 1; m <= barlen-bar; m++){
	    std::cout<<" ";
	}
	std::cout<<"] "<<std::setprecision(3)<<perc_int<<"%";
	//Progress bar ends

	pos1[i] = p1.getPos();
	pos2[i] = p2.getPos();
	acceleration = gravityAcceleration(*equivalent,p1.getMass(),p2.getMass());
	equivalent->updateVel(acceleration,dt);
	equivalent->updatePos(dt);
	fromEquivalentBody(*equivalent,p1,p2);
	//Now we write to the csv file
	out_file<<std::setprecision(15)<<pos1[i][0]<<","<<pos1[i][1]<<","<<pos1[i][2]<<","<<pos2[i][0]<<","<<pos2[i][1]<<","<<pos2[i][2]<<std::endl;
    }
    out_file.close();
    std::cout<<"\nSuccessfully simulated the motion of the bodies "<<p1.getName()<<" and "<<p2.getName()<<std::endl;
    std::cout<<"Number of iterations: "<<steps<<std::endl;
	std::cout<<"The simulated data is stored by columns (x,y,z) in "<<output_file<<".\nTo visualize it, you can run the dedicated root macros with\n  - root ./root/bodiesGraphic3D.cpp\n  - root ./root/bodiesGraphic2D.cpp\n";
    std::cout<<"  - root ./root/animation2D.cpp (and others, see README.md)\n";
}

void changeToCOM(std::vector<CelestialBody*>& bodies){
    //Overloading of the function implemented in twobodies.cc
    //It re-centres the system of bodies to their center of mass
    double mass_sum = 0;
    std::vector<double> pos_sum = {0,0,0};
    std::vector<double> vel_sum = {0,0,0};
    const int n = bodies.size();
    for(int i = 0; i<n; i++){
	mass_sum += bodies[i]->getMass();

	pos_sum[0] += bodies[i]->getPos()[0] * bodies[i]->getMass();
	pos_sum[1] += bodies[i]->getPos()[1] * bodies[i]->getMass();
	pos_sum[2] += bodies[i]->getPos()[2] * bodies[i]->getMass();

	vel_sum[0] += bodies[i]->getVel()[0] * bodies[i]->getMass();
	vel_sum[1] += bodies[i]->getVel()[1] * bodies[i]->getMass();
	vel_sum[2] += bodies[i]->getVel()[2] * bodies[i]->getMass();
    }
    std::vector<double> pos_COM(3);
    std::vector<double> vel_COM(3);
    for(int i = 0; i < 3; i++){
	pos_COM[i] = pos_sum[i] / mass_sum;
	vel_COM[i] = vel_sum[i] / mass_sum;
    }
    for(int i = 0; i<n; i++){
	std::vector<double> new_pos(3);
	std::vector<double> new_vel(3);
	for(int j = 0; j < 3; j++){
	    new_pos[j] = bodies[i]->getPos()[j] - pos_COM[j]; 
	    new_vel[j] = bodies[i]->getVel()[j] - vel_COM[j]; 
	}
	bodies[i]->setPos(new_pos);
	bodies[i]->setVel(new_vel);
    }
}


void nBodiesSimulation(std::vector<CelestialBody*>& bodies, double totalt, double dt, std::string output_file){
    //Main simulator, this calls twoBodiesSimulation for n=2
    //We use Euler's method to integrate the equations of motion:
    //for each time step, we calculate the acceleratiom that each body is subject to
    //because of the gravitational pull of all others, we then update all the velocities
    //and positions and start again with the next time step.

    //It is basically a brute-force solution, with a very big complexity

    //std::string output_file should be in the form "relative/path/to/output.csv"
    double G = 6.67259e-11; 
    //"Lasciate ogni speranza, voi ch'entrate"
    if (bodies.size() == 2) {
	twoBodiesSimulation(*bodies[0], *bodies[1], totalt, dt, output_file);
    } else {
	changeToCOM(bodies);
	const int n_bodies = bodies.size();
	unsigned int steps = totalt / dt;
	std::ofstream out_file(output_file);
	out_file << "#This file contains simulated data from /bin/main: the bodies are in order and each body has one column for each of the coordinates" << std::endl;//header of the csv file
																				       // ----------------------------------------------------------------------------------
	for (int n = 0; n<steps; n++) {
	    //Progress bar
	    double percentage = (double) (n+1)/steps; //dynamic casting!
	    int perc_int = 100*percentage;
	    int barlen = 50; //total characters
	    int bar = std::ceil(percentage*barlen); //number of characters to be drawn
	    std::cout<<"\rLoading... ["; //\r puts the cursor back to the beginning of the line
	    for(int m = 1; m <= bar; m++){
		std::cout<<"■";
	    }
	    for(int m = 1; m <= barlen-bar; m++){
		std::cout<<" ";
	    }
	    std::cout<<"] "<<std::setprecision(3)<<perc_int<<"%";
	    //progress bar ends

	    for (int i=0; i<n_bodies; i++) {
		//We iterate on the bodies to calculate their accelerations
		//Firstly, we store the position from the previous iteration to the output file
		out_file<<std::setprecision(15)<<bodies[i]->getPos()[0]<<","<<bodies[i]->getPos()[1]<<","<<bodies[i]->getPos()[2]<<",";

		std::vector<double> acc = {0,0,0};
		bodies[i]->setVirtualAcc({0.,0.,0.}); //we reset the virtual acceleration

		for (int j = 0; j<n_bodies; j++) {
		    //We then iterate on all other bodies and calculate the acceleration of bodies[i]
		    //based on the relative position of all the other bodies.

		    // Need to skip the current body during calculation of acc
		    if (bodies[j] == bodies[i]) {
			continue;
		    }
		    double distance_cubed = std::pow(bodies[j]->getPos()[0] - bodies[i]->getPos()[0], 2) + std::pow(bodies[j]->getPos()[1] - bodies[i]->getPos()[1], 2) + std::pow(bodies[j]->getPos()[2] - bodies[i]->getPos()[2], 2);
		    //std::cout << std::sqrt(distance_cubed) << std::endl;
		    distance_cubed = std::pow(distance_cubed, 1.5);


		    acc[0] +=  G * (bodies[j]->getMass() * (bodies[j]->getPos()[0] - bodies[i]->getPos()[0]) ) / distance_cubed; 
		    acc[1] +=  G * (bodies[j]->getMass() * (bodies[j]->getPos()[1] - bodies[i]->getPos()[1]) ) / distance_cubed; 
		    acc[2] +=  G * (bodies[j]->getMass() * (bodies[j]->getPos()[2] - bodies[i]->getPos()[2]) ) / distance_cubed; 
		    //this sums the contributes to the acceleration from all other bodies
		}

		// At this point we need to keep record of the calculated acceleration for body i
		// We store the calculated virtual acceleration into the body's private variable.
		bodies[i]->setVirtualAcc(acc);          
	    }

	    // Once we have calculated the total acceleration on all bodies for the current dt we can update pos and vel for each body
	    for (int i = 0; i<n_bodies; i++) {
		bodies[i]->updateVel(bodies[i]->getVirtualAcc(), dt);
		bodies[i]->updatePos(dt);
	    }
	    // last comma could be a problem, in case need to delete last line character
	    out_file<<std::endl; //one line for each iteration
	}//closing of the iterations loop
	 // -------------------------------------------------------------------------------
	out_file.close();

	std::cout<<"\nSuccessfully simulated the motion of the bodies!\n";
	std::cout<<"Number of iterations: "<<steps<<std::endl;
	std::cout<<"The simulated data is stored by columns (x,y,z) in "<<output_file<<".\nTo visualize it, you can run the dedicated root macros with\n  - root ./root/bodiesGraphic3D.cpp\n  - root ./root/bodiesGraphic2D.cpp\n";
    std::cout<<"  - root ./root/animation2D.cpp (and others, see README.md)\n";
    }  

}
