#include "Utility.h"
#include "Queue.h"
#include "Extended_queue.h"
#include "Runway.h"
#include "Plane.h"
#include "Random.h"
#include "Runway_2.h"
#include "Runway_3.h"

#include <iostream>
using namespace std;

int main_1p();
int main_2p();
int main_3p();
int main_4p();
int main_5p();
void initialize(int& end_time, int& queue_limit, double& arrival_rate, double& departure_rate);
void run_idle(int time);

int main(int argc, char* argv[]) {

    int ohjelmanaloitus = 0;
    char vastaus;
 
    do {
        cout << "Enter number [1-5] to match the increment you want to run." << endl;
        cin >> ohjelmanaloitus;
        while (ohjelmanaloitus < 1 || ohjelmanaloitus > 5) {
            cout << "Invalid input." << endl;
            cout << "Enter number [1-5] to match the increment you want to run." << endl;
            cin >> ohjelmanaloitus;
        }
        switch (ohjelmanaloitus) {
        case 1:
            main_1p();
            break;
        case 2:
            main_2p();
            break;
        case 3:
            main_3p();
            break;
        case 4:
            main_4p();
            break;
        case 5:
            main_5p();
            break;
        }
        cout << "Suoritetaanko uusi simulaatio? [y/n]" << endl;
        cin >> vastaus;
        while (vastaus != 'y' && vastaus != 'Y' && vastaus != 'n' && vastaus != 'N') {
            cout << "Invalid input." << endl;
            cout << "Suoritetaanko uusi simulaatio? [y/n]" << endl;
            cin >> vastaus;
        }
    } while (vastaus != 'n' && vastaus != 'N');

	return 0;
}

int main_1p()     //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/

{
    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway small_airport(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;
        switch (small_airport.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
    }
    small_airport.shut_down(end_time);

    return 0;
}

int main_2p()
{
    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway arrival_runway(queue_limit);
    Runway_2 departure_runway(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrival_runway.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (departure_runway.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;
        switch (arrival_runway.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
        switch (departure_runway.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto the Runway at current_time.
        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }

    }
    departure_runway.shut_down2R(end_time, arrival_runway, departure_runway);
    //departure_runway.shut_down(end_time);
    //arrival_runway.shut_down(end_time);

    return 0;
}

int main_3p()
{
    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway arrival_runway(queue_limit);
    Runway_2 departure_runway(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrival_runway.can_land(current_plane) != success)
                if (!departure_runway.arrivalFull()) {
                    departure_runway.can_land(current_plane);
                }
                else {
                    current_plane.refuse();
                }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (departure_runway.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;
        switch (departure_runway.activity_3p_arrival(current_time, moving_plane, arrival_runway)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
        switch (departure_runway.activity_3p_departure(current_time, moving_plane, arrival_runway)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }

    }
    departure_runway.shut_down2R(end_time, arrival_runway, departure_runway);

    return 0;
}

int main_4p()
{
    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway arrival_runway(queue_limit);
    Runway_2 departure_runway(queue_limit);
    Runway_3 extra_runway(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrival_runway.can_land(current_plane) != success)
                if (!extra_runway.arrivalFull() ) {
                    extra_runway.can_land(current_plane);
                }
                else {
                        current_plane.refuse();
                }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (departure_runway.can_depart(current_plane) != success)
                if (arrival_runway.arrivalEmpty() && extra_runway.arrivalEmpty() ) {
                    extra_runway.can_depart(current_plane);
                }
                else {
                    current_plane.refuse();
                }
        }

        Plane moving_plane;
        switch (arrival_runway.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
        switch (departure_runway.activity_4p(current_time, moving_plane, extra_runway, arrival_runway)) {
            //  Let at most one Plane onto the Runway at current_time.
        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
        switch (extra_runway.activity(current_time, moving_plane, arrival_runway)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }

    }
    extra_runway.shut_down3R(end_time, arrival_runway, departure_runway, extra_runway);

    return 0;
}

int main_5p()
{
    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    int fuel_refuse_limit = 4;
    bool emergencyFlag = false;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway small_airport(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        emergencyFlag = false;
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving, variable.random_integer(1, 15));
                if (current_plane.getFuel() < fuel_refuse_limit && !emergencyFlag) {
                    small_airport.emergencyLanding(current_plane);
                    emergencyFlag = true;
                }
                else if (small_airport.can_land(current_plane) != success) {
                    current_plane.refuse();
                }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        if (!emergencyFlag) {
            Plane moving_plane;
            switch (small_airport.activity_5p(current_time, moving_plane)) {
                //  Let at most one Plane onto the Runway at current_time.
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
            }
        }
    }
    small_airport.shut_down(end_time);

    return 0;
}

void initialize(int& end_time, int& queue_limit,
    double& arrival_rate, double& departure_rate)
    /*
    Pre:  The user specifies the number of time units in the simulation,
          the maximal queue sizes permitted,
          and the expected arrival and departure rates for the airport.
    Post: The program prints instructions and initializes the parameters
          end_time, queue_limit, arrival_rate, and departure_rate to
          the specified values.
    Uses: utility function user_says_yes
    */

{
    cout << "This program simulates an airport with only one runway." << endl
        << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run? " << flush;
    cin >> end_time;

    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time? " << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time? " << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0) {
            cerr << "These rates must be nonnegative." << endl;
        }

        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void run_idle(int time)
/*
Post: The specified time is printed with a message that the runway is idle.
*/
{
    cout << time << ": Runway is idle." << endl;
}