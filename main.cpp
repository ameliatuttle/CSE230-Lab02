//
//  main.cpp
//  LAB 02 : APOLLO 11 PHYSICS
//
//  Created by Amelia Tuttle on 5/2/24.
//

#include <iostream>
#include <cassert>
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 **************************************************/
double computeDistance(double s, double v, double a, double t)
{
    return s + (v * t) + (.5 * a * (t * t));
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 ***************************************************/
double computeAcceleration(double f, double m)
{
    assert(m != 0.0);
    return f / m;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 ***********************************************/
double computeVelocity(double v, double a, double t)
{
    return v + (a * t);
}

/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 ***********************************************/
double computeVerticalComponent(double a, double total)
{
    return cos(a) * total;
}

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 ***********************************************/
double computeHorizontalComponent(double a, double total)
{
    return sin(a) * total;
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 ***********************************************/
double computeTotalComponent(double x, double y)
{
    return sqrt((x * x) + (y * y));
}

/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 **************************************************/
double computeRadiansFromDegrees(double d)
{
    return (d / 360.0) * (2.0 * M_PI);
}

/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 ***************************************************/
double prompt(const string & message)
{
    double response;
    
    cout << message;
    cin >> response;
    
    return response;
}

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx =       prompt("What is your horizontal velocity (m/s)? ");
    double dy =       prompt("What is your vertical velocity (m/s)? ");
    double y =        prompt("What is your altitude (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v;                   // Total velocity
    
    // Assume x is 0
    double x = 0;
    
    // Compute thrust acceleration
    accelerationThrust = computeAcceleration(THRUST, WEIGHT);
    
    // Set the time count to be display showing seconds
    int second = 1;

    // Display calculations or 5 seconds, re-prompt for angle, then display calculations for next 5 seconds
    for (int i = 1; i <=2; ++i){
        
        // Re-prompt for angle the second time
        if (i == 2){
            aDegrees = prompt("\nWhat is the new angle of the LM where 0 is up (degrees)? ");
        }
        
        // Display message before 5 second calculations
        cout << "\nFor the next 5 seconds with the main engine on, the position of the lander is:\n\n";
        
        // Go through the simulator five times
        for (int j = 1; j <= 5; ++j){
            
            
            // Convert degrees to radians
            aRadians = computeRadiansFromDegrees(aDegrees);
            
            // Compute horizontal and vertical components of thrust acceleration
            ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
            ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);
            
            // Compute total horizontal and vertical accelerations
            ddx = ddxThrust;
            ddy = ddyThrust + GRAVITY;
            
            // Find new velocities
            dx = computeVelocity(dx, ddx, 1);
            dy = computeVelocity(dy, ddy, 1);
            
            // Compute velocity
            v = computeTotalComponent(dx, dy);
            
            // Find new positions
            x = computeDistance(x, dx, ddx, 1);
            y = computeDistance(y, dy, ddy, 1);
            
            // Output
            cout.setf(ios::fixed | ios::showpoint);
            cout.precision(2);
            cout << "\t"<< second <<"s - x,y:(" <<  x << ", " <<  y << ")m  dx,dy:(" << dx << ", " << dy << ")m/s  speed:"<< v <<"m/s  angle:"<< aDegrees <<"deg\n";
            
            // Increase second count
            ++second;
        }
    }

   return 0;
}
