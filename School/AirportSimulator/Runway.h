#pragma once
#include "Extended_queue.h"

enum Runway_activity { idle, land, takeoff };

class Runway {
public:
	Runway(int limit);
	Error_code can_land(const Plane& current);
	Error_code can_depart(const Plane& current);
	Error_code emergencyLanding(const Plane& current);
	Runway_activity activity(int time, Plane& moving);
	Runway_activity activity_5p(int time, Plane& moving);
	void shut_down(int time) const;
	bool arrivalFull() const;
	bool departureFull() const;
	bool arrivalEmpty() const;
	bool departureEmpty() const;

	int getQueue_limit() const;
	int getNum_land_requests() const;
	int getNum_takeoff_requests() const;
	int getNum_landings() const;
	int getNum_takeoffs() const;
	int getNum_land_accepted() const;
	int getNum_takeoff_accepted() const;
	int getNum_land_refused() const;
	int getNum_takeoff_refused() const;
	int getLand_wait() const;
	int getTakeoff_wait() const;
	int getIdle_time() const;
	int getCrashed() const;

private:
	Extended_queue landing;
	Extended_queue takeoffing;
	int queue_limit;
	int num_land_requests;        //  number of planes asking to land
	int num_takeoff_requests;     //  number of planes asking to take off
	int num_landings;             //  number of planes that have landed
	int num_takeoffs;             //  number of planes that have taken off
	int num_land_accepted;        //  number of planes queued to land
	int num_takeoff_accepted;     //  number of planes queued to take off
	int num_land_refused;         //  number of landing planes refused
	int num_takeoff_refused;      //  number of departing planes refused
	int land_wait;                //  total time of planes waiting to land
	int takeoff_wait;             //  total time of planes waiting to take off
	int idle_time;                //  total time runway is idle
	int crashed;
	friend class Runway_2;
	friend class Runway_3;
	friend int main_2p();
};