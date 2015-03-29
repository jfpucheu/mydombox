//
//  mdb_rpidom.h
//  
//
//  Created by Jeff on 05/05/14.
//
//

#ifndef _mdb_rpidom_h
#define _mdb_rpidom_h

int initserie(void);
int read_serial_tele_frame(int device);
int checksum_ok(char *etiquette, char *valeur, char checksum);
int read_mono();
int read_tri();
int read_rpidom_teleport(int port);
int read_rpidom_1wire();
void* rpidom();

#endif
