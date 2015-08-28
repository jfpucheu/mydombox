//
//  mdb_thermostat.h
//  
//
//  Created by Jeff on 15/04/13.
//
//

#ifndef _mdb_thermostat_h
#define _mdb_thermostat_h

float last_tp( int th_id );

float scenario( int sc_id );

void thermostat_calc( int th_id);

void thermostat();

#endif
