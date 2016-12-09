/************************************************************************
*file: Depo.h
*purpose: Depo class declaration
*author: Melnyk Andriy
*written: 09/03/2014
*last modified: 09/03/2014
*************************************************************************/

#pragma once
#include "List.h"
#include "Bus.h"

class Depo	{

#define PRINT_BUSES(lst,msg)	cout << msg << endl;	\
								cout << setw(20) << "Driver" << setw(20) << "Bus number" << setw(20) << "Route number" << endl;	\
								List<Bus> :: iterator iter = lst.begin();	\
								for ( ; iter != lst.end() ; iter++ ) {	\
									cout << *iter;	}

#define CHANGE_STATUS(from,to)	List<Bus> :: iterator iter = from.begin();	\
								while (iter != from.end() ) {		\
									if ( (*iter).data.GetRoute() != NULL && \
										 routeNumb ==  string((*iter).data.GetRoute()) ) {	\
										from.splice(iter,to);	\
										return true; } \
									iter++; } \
								return false;

#define DEF_REF_INTERFACE(ref) 	bool GoOnRoute(string ref routeNumb);	\
								bool BackToDepo(string ref routeNumb);	\
								bool ChangeDriver(string ref ODrName,string ref NDrName);

public:
	//Depo() =delete;
	//Depo(Depo const&) = delete;
	~Depo() { }
	Depo(string csv) {
		inDepo.LoadFromCsv(csv.c_str());
	}
	//Depo& operator=(Depo const&) = delete;

	void PrintOnRoute() const;
	void PrintInDepo() const;
	inline int NumbDepo() { return inDepo.size(); }
	inline int NumbRoute() { return onRoute.size(); }	
	inline void AddBusToDepo(const Bus& bs) {
		inDepo.push_front(bs);
	}
	DEF_REF_INTERFACE(&);
	DEF_REF_INTERFACE(&&);

private: 
	List<Bus> inDepo;
	List<Bus> onRoute;
};

