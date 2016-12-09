/************************************************************************
*file: Bus.cpp
*purpose: implements methods of class Depo
*author: Melnyk Andriy
*written: 09/03/2014
*last modified: 09/03/2014
*************************************************************************/

#include "Depo.h"
#include <iomanip>

#define DEF_CHANGE_DRIVER(ref)	 bool Depo::ChangeDriver(string ref ODrName,string ref NDrName) {	\
									if (NDrName.length() == NULL) return false;	\
									List<Bus> :: iterator iter = inDepo.begin();	\
									while ( iter != inDepo.end() ) {	\
										if ( (*iter).data.GetDriver() != NULL &&	\
												strcmp(ODrName.c_str(), (*iter).data.GetDriver()) == 0 ) {	\
											(*iter).data.SetDriver(NDrName.c_str()); \
											return true;	\
										} iter++;	\
									} return false;	\
								}

#define DEF_ST_CHANGER(name,from,to,ref)	bool Depo::name(string ref routeNumb) {		\
												CHANGE_STATUS(from,to); }

void Depo::PrintOnRoute() const {
	PRINT_BUSES(onRoute,"Active buses : ");
}

void Depo::PrintInDepo() const {
	PRINT_BUSES(inDepo,"Buses which located in depo :");
}

DEF_ST_CHANGER(GoOnRoute,inDepo,onRoute,&);
DEF_ST_CHANGER(BackToDepo,onRoute,inDepo,&);
DEF_ST_CHANGER(GoOnRoute,inDepo,onRoute,&&);
DEF_ST_CHANGER(BackToDepo,onRoute,inDepo,&&);
DEF_CHANGE_DRIVER(&);
DEF_CHANGE_DRIVER(&&);