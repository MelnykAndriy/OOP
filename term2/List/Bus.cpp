/************************************************************************
*file: Bus.cpp
*purpose: implements methods of class Bus
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 09/03/2014
*************************************************************************/

#include "Bus.h"
#include <iomanip>
#pragma warning (disable: 4996)

Bus::Bus(const Bus &copy) {
	COPY(copy);
}

Bus::Bus(const char* driver,const char* bus_number,const char* route_number)  { 
	if (driver && bus_number && route_number) {
		INIT(driver,bus_number,route_number);
	} else {
		driver = bus_number = route_number = NULL;
	}
}

Bus& Bus::operator=(const Bus &copy) {
	if (driver) {
		CLEAR();
	}
	COPY(copy);
	return *this;
}

bool Bus::operator==(const Bus &obj) {
	return CMP(==,&&);
}

bool Bus::operator!=(const Bus &obj) {
	return CMP(!=,||);
}

bool Bus::SetBus(const char* driver,const char* bus_number,const char* route_number) {
	if (driver && bus_number && route_number) {
		CLEAR();
		INIT(driver,bus_number,route_number);
		return true;
	}
	return false;
}

bool Bus::SetBus(const Bus &copy) {
	if (copy.driver) {
		CLEAR();
		COPY(copy);
		return true;
	}
	return false;
}

Bus::~Bus(void) {
	CLEAR();
}

ostream& operator<<(ostream& stream, const Bus& obj) {
	return stream << setw(20) << obj.driver << setw(20) << obj.bus_number << setw(20) << obj.route_number << endl;
}

istream& operator>>(istream& stream,Bus& obj) {
	if ( stream.good()) {
		string buf;
		getline(stream,buf,'\n');
		size_t first = buf.find_first_of(';') ,second  = buf.find_last_of(';');
		if (first == string::npos ||first == second ||
			first == 0 || second == buf.length() - 1 ||
			first == second - 1 ) return stream;
	
		string firstStr = buf.substr(0,first);
		string secondStr = buf.substr(first + 1,second - first - 1);
		string thirdStr = buf.substr(second + 1 ,buf.length() - 1);


		obj = Bus(buf.substr(0,first).c_str(),
				  buf.substr(first + 1,second - first - 1).c_str(),
				  buf.substr(second + 1 ,buf.length() - second - 1).c_str());
	}

	return stream;
}

void Bus::SetDriver(const char* NDriver) {
	if (NDriver != NULL) {
		delete driver;
		driver = COPY_CHAR_PTR(NDriver);
	}
}

#pragma warning (default : 4996)