#pragma once

enum Plane_status { null, arriving, departing };

class Plane {
public:
	Plane();
	Plane(int flt, int time, Plane_status status);
	Plane(int flt, int time, Plane_status status, int fuel);
	void refuse() const;
	void land(int time) const;
	void fly(int time) const;
	int started() const;
	int getFuel() const;

private:
	int flt_num;
	int clock_start;
	int plane_fuel;
	Plane_status state;
};