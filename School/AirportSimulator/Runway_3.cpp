#include "Runway_3.h"
#include "Plane.h"
#include "Utility.h"
#include "Runway.h"
using namespace std;

Runway_3::Runway_3(int limit)
/*
Post:  The Runway data members are initialized to record no
       prior Runway use and to record the limit on queue sizes.
*/

{
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
}


Error_code Runway_3::can_land(const Plane& current)
/*
Post:  If possible, the Plane current is added to the
       landing Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (landing.size() < queue_limit)
        result = landing.append(current);
    else
        result = fail;
    num_land_requests++;

    if (result != success)
        num_land_refused++;
    else
        num_land_accepted++;

    return result;
}


Error_code Runway_3::can_depart(const Plane& current)
/*
Post:  If possible, the Plane current is added to the
       takeoff Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (takeoffing.size() < queue_limit)
        result = takeoffing.append(current);
    else
        result = fail;
    num_takeoff_requests++;
    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;

    return result;
}


Runway_3_activity Runway_3::activity(int time, Plane& moving, Runway& arrival_runway)
/*
Post:  If the landing Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  land is returned. Otherwise,
       if the takeoff Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  takeoff is returned. Otherwise,
       idle is returned. Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Runway_3_activity in_progress;
    if (!landing.empty()) {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land3;
        landing.serve();
    }

    else if ( !arrival_runway.landing.empty() ) {
        arrival_runway.landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land3;
        arrival_runway.landing.serve();
    }

    else if (!takeoffing.empty()) {
        takeoffing.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = takeoff3;
        takeoffing.serve();
    }

    else {
        idle_time++;
        in_progress = idle3;
    }
    return in_progress;
}

void Runway_3::shut_down(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "Simulation has concluded after " << time << " time units." << endl
        << "Total number of planes processed "
        << (num_land_requests + num_takeoff_requests) << endl
        << "Total number of planes asking to land "
        << num_land_requests << endl
        << "Total number of planes asking to take off "
        << num_takeoff_requests << endl
        << "Total number of planes accepted for landing "
        << num_land_accepted << endl
        << "Total number of planes accepted for takeoff "
        << num_takeoff_accepted << endl
        << "Total number of planes refused for landing "
        << num_land_refused << endl
        << "Total number of planes refused for takeoff "
        << num_takeoff_refused << endl
        << "Total number of planes that landed "
        << num_landings << endl
        << "Total number of planes that took off "
        << num_takeoffs << endl
        << "Total number of planes left in landing queue "
        << landing.size() << endl
        << "Total number of planes left in takeoff queue "
        << takeoffing.size() << endl;
    cout << "Percentage of time runway idle "
        << 100.0 * ((float)idle_time) / ((float)time) << "%" << endl;
    cout << "Average wait in landing queue "
        << ((float)land_wait) / ((float)num_landings) << " time units";
    cout << endl << "Average wait in takeoff queue "
        << ((float)takeoff_wait) / ((float)num_takeoffs)
        << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
        << ((float)num_land_requests) / ((float)time)
        << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
        << ((float)num_takeoff_requests) / ((float)time)
        << " per time unit" << endl;
}

void Runway_3::shut_down3R(int time, const Runway& arrival_runway, Runway_2& departure_runway, Runway_3& extra_runway) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "Simulation has concluded after " << time << " time units." << endl
        << "Total number of planes processed "
        << (arrival_runway.getNum_land_requests() + arrival_runway.getNum_takeoff_requests() +
            departure_runway.getNum_takeoff_requests() + departure_runway.getNum_land_requests() +
            extra_runway.getNum_land_requests() + extra_runway.getNum_takeoff_requests() ) << endl
        << "Total number of planes asking to land "
        << (arrival_runway.getNum_land_requests() + departure_runway.getNum_land_requests() + 
            extra_runway.getNum_land_requests() ) << endl
        << "Total number of planes asking to take off "
        << (departure_runway.getNum_takeoff_requests() + arrival_runway.getNum_takeoff_requests() +
            extra_runway.getNum_takeoff_requests() ) << endl
        << "Total number of planes accepted for landing "
        << (arrival_runway.getNum_land_accepted() + departure_runway.getNum_land_accepted() +
            extra_runway.getNum_land_accepted() ) << endl
        << "Total number of planes accepted for takeoff "
        << (departure_runway.getNum_takeoff_accepted() + arrival_runway.getNum_takeoff_accepted() +
            extra_runway.getNum_takeoff_accepted() ) << endl
        << "Total number of planes refused for landing "
        << (arrival_runway.getNum_land_refused() + departure_runway.getNum_land_refused() +
            extra_runway.getNum_land_refused() ) << endl
        << "Total number of planes refused for takeoff "
        << (departure_runway.getNum_takeoff_refused() + arrival_runway.getNum_takeoff_refused() +
            extra_runway.getNum_takeoff_refused() ) << endl
        << "Total number of planes that landed "
        << (arrival_runway.getNum_landings() + departure_runway.getNum_landings() +
            extra_runway.getNum_landings() ) << endl
        << "Total number of planes that took off "
        << (departure_runway.getNum_takeoffs() + arrival_runway.getNum_takeoffs() +
            extra_runway.getNum_takeoffs() ) << endl
        << "Total number of planes left in landing queue "
        << (arrival_runway.landing.size() + departure_runway.landing.size() + extra_runway.landing.size()) << endl
        << "Total number of planes left in takeoff queue "
        << (departure_runway.takeoffing.size() + arrival_runway.takeoffing.size() + extra_runway.takeoffing.size()) << endl;
    cout << "Percentage of time landing runway idle "
        << 100.0 * ((float)arrival_runway.getIdle_time()) / ((float)time) << "%" << endl;
    cout << "Percentage of time take off runway idle "
        << 100.0 * ((float)departure_runway.getIdle_time()) / ((float)time) << "%" << endl;
    cout << "Percentage of time extra runway idle "
        << 100.0 * ((float)extra_runway.getIdle_time()) / ((float)time) << "%" << endl;
    cout << "Average wait in landing queue "
        << (((float)arrival_runway.getLand_wait()) + ((float)departure_runway.getLand_wait()) + ((float)extra_runway.getLand_wait())) /
        (((float)arrival_runway.getNum_landings()) + ((float)departure_runway.getNum_landings()) + ((float)extra_runway.getNum_landings())) << " time units";
    cout << endl << "Average wait in takeoff queue "
        << (((float)departure_runway.getTakeoff_wait()) + ((float)arrival_runway.getTakeoff_wait()) + ((float)extra_runway.getTakeoff_wait())) /
        (((float)departure_runway.getNum_takeoffs()) + ((float)arrival_runway.getNum_takeoffs()) + ((float)extra_runway.getNum_takeoffs()))
        << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
        << (((float)arrival_runway.getNum_land_requests()) / ((float)time) +
            ((float)departure_runway.getNum_land_requests()) / ((float)time) +
            ((float)extra_runway.getNum_land_requests()) / ((float)time) )
        << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
        << (((float)departure_runway.getNum_takeoff_requests()) / ((float)time) +
            ((float)arrival_runway.getNum_takeoff_requests()) / ((float)time) +
            ((float)extra_runway.getNum_takeoff_requests()) / ((float)time) )
        << " per time unit" << endl;
}

bool Runway_3::arrivalFull() const
{
    return landing.full();
}

bool Runway_3::departureFull() const
{
    return takeoffing.full();
}

bool Runway_3::arrivalEmpty() const
{
    return landing.empty();
}

bool Runway_3::departureEmpty() const
{
    return takeoffing.empty();
}



int Runway_3::getQueue_limit() const
{
    return queue_limit;
}

int Runway_3::getNum_land_requests() const
{
    return num_land_requests;
}

int Runway_3::getNum_takeoff_requests() const
{
    return num_takeoff_requests;
}

int Runway_3::getNum_landings() const
{
    return num_landings;
}

int Runway_3::getNum_takeoffs() const
{
    return num_takeoffs;
}

int Runway_3::getNum_land_accepted() const
{
    return num_land_accepted;
}

int Runway_3::getNum_takeoff_accepted() const
{
    return num_takeoff_accepted;
}

int Runway_3::getNum_land_refused() const
{
    return num_land_refused;
}

int Runway_3::getNum_takeoff_refused() const
{
    return num_takeoff_refused;
}

int Runway_3::getLand_wait() const
{
    return land_wait;
}

int Runway_3::getTakeoff_wait() const
{
    return takeoff_wait;
}

int Runway_3::getIdle_time() const
{
    return idle_time;
}

