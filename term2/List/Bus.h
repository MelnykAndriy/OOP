/************************************************************************
*file: Bus.h
*purpose: definition of class Bus
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 02/02/2014
*************************************************************************/

#pragma once
#include <string.h>
#include <iostream>
#include <string>
#pragma warning (disable: 4996)

using namespace std;
 
class Bus {

#define COPY_CHAR_PTR(ch_ptr) (ch_ptr)?(strcpy(new char[strlen(ch_ptr) + 1],ch_ptr)):(NULL)

#define COPY(from) 	driver = COPY_CHAR_PTR(from.driver); \
					bus_number = COPY_CHAR_PTR(from.bus_number); \
					route_number = COPY_CHAR_PTR(from.route_number);

#define CMP(eq,logic) 	strcmp(obj.driver,this->driver) eq 0 logic  \
						strcmp(obj.bus_number,this->bus_number) eq 0 logic \
						strcmp(obj.route_number,this->route_number) eq 0 

#define CLEAR() 	delete[] driver; \
					delete[] bus_number; \
					delete[] route_number;

#define INIT(dr,numb,route)	this->driver = strcpy(new char[strlen(dr) + 1],dr); \
							this->bus_number = strcpy(new char[strlen(numb) + 1],numb);  \
							this->route_number = strcpy(new char[strlen(route) + 1],route); 
public:
	Bus() { driver = bus_number = route_number = NULL;}
	~Bus();
	Bus(const Bus &copy);
	Bus(const char* driver,const char* bus_number,const char* route_number);

	Bus& operator=(const Bus &copy);
	bool operator==(const Bus &obj);
	bool operator!=(const Bus &obj);
	bool SetBus(const char* driver,const char* bus_number,const char* route_number);
	bool SetBus(const Bus &copy);
	void SetDriver(const char* NDriver);


	inline const char* GetDriver() {
		return driver;
	}
	inline const char* GetNumb() {
		return bus_number;
	}
	inline const char* GetRoute() {
		return route_number;
	}

	friend ostream& operator<<(ostream& stream, const Bus& obj);
	friend istream& operator>>(istream& stream, Bus& obj);
private:
	char* driver;
	char* bus_number;
	char* route_number;
};

#pragma warning (default : 4996)