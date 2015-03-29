/* mdb_rpidom.c */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <syslog.h>
#include <termios.h>
#include <dirent.h>
#include <sys/fcntl.h>
#include <sys/types.h>
 
#include "mdb_log.h"
#include "mdb_decode_messages.h"
 
 
// Define port serie speed
#define BAUDRATE B1200

extern char PORT_RPIDOM[32];
extern int 	RPIDOM_TELE1_TYPE;
extern int 	RPIDOM_TELE2_TYPE;
extern int 	RPIDOM_1WIRE;
 
//-----------------------------------------------------------------------------
 
// Déaration pour le port sée.
int             fdrpidom ;
struct termios  termiosteleinfo ;
 
// Déaration pour les donné.
char ch[2] ;
char car_prec ;
char message[512] ;
char* match;
char datateleinfo[512] ;
 
// Fin Constantes/variables àhangé suivant abonnement.
 
char 	valeurs[20][18] ;
char	checksum[255] ;
int 	res ;
int	no_essais = 1 ;
int	nb_essais = 3 ;
int	erreur_checksum = 0 ;
 

/*
	Init port rs232		
*/

int initserie(void){
// Mode Non-Canonical Input Processing, Attend 1 caractè ou time-out(avec VMIN et VTIME).

	int device ;
 
        // Ouverture de la liaison serie (Nouvelle version de config.)
        if ( (device=open(PORT_RPIDOM, O_RDWR | O_NOCTTY)) == -1 ) 
	{
                log_ERROR("Unable to open Serial Port %s !", PORT_RPIDOM);
                exit(1) ;
        }
 
        tcgetattr(device,&termiosteleinfo) ;				// Lecture des parametres courants.
 
	cfsetispeed(&termiosteleinfo, BAUDRATE) ;			// Configure le dét en entrésortie.
	cfsetospeed(&termiosteleinfo, BAUDRATE) ;
 
	termiosteleinfo.c_cflag |= (CLOCAL | CREAD) ;			// Active réption et mode local.
 
	// Format sée "7E1"
	termiosteleinfo.c_cflag |= PARENB  ;				// Active 7 bits de donnees avec parite pair.
	termiosteleinfo.c_cflag &= ~PARODD ;
	termiosteleinfo.c_cflag &= ~CSTOPB ;
	termiosteleinfo.c_cflag &= ~CSIZE ;
	termiosteleinfo.c_cflag |= CS7 ;
 
	termiosteleinfo.c_iflag |= (INPCK | ISTRIP) ;			// Mode de control de parité 
	termiosteleinfo.c_cflag &= ~CRTSCTS ;				// Déctive control de flux matéel.
 
	termiosteleinfo.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG) ;	// Mode non-canonique (mode raw) sans echo.
 
	termiosteleinfo.c_iflag &= ~(IXON | IXOFF | IXANY | ICRNL) ;	// Déctive control de flux logiciel, conversion 0xOD en 0x0A.
 
	termiosteleinfo.c_oflag &= ~OPOST ;				// Pas de mode de sortie particulier (mode raw).
 
	termiosteleinfo.c_cc[VTIME] = 80 ;  				// time-out à8s.
	termiosteleinfo.c_cc[VMIN]  = 0 ;   				// 1 car. attendu.
 
	tcflush(device, TCIFLUSH) ;					// Efface les donné reçs mais non lues.
        tcsetattr(device,TCSANOW,&termiosteleinfo) ;			// Sauvegarde des nouveaux parametres
	return device ;
}
 
/*
	Read a serial teleinformation frame	
*/

int read_serial_tele_frame(int device){
	// (0d 03 02 0a => Code fin et dét trame)
	tcflush(device, TCIFLUSH) ;			// Efface les donné non lus en entré
	message[0]='\0' ;
	memset(valeurs, 0x00, sizeof(valeurs)) ; 
 
	do
	{
		car_prec = ch[0] ;
		res = read(device, ch, 1) ;
		if (! res)
		{	
			log_ERROR("Rpidom: No teleinformation start data") ;
			close(device);
			return 1 ;
		}
	 }
	while ( ! (ch[0] == 0x02 && car_prec == 0x03) ) ;	// Attend code fin suivi de dét trame téinfo .
 
	do
	{
		res = read(device, ch, 1) ;
		if (! res)
		{	
			log_ERROR("Rpidom: No teleinformation end data") ;
			close(device);
			return 1 ;
		}
		ch[1] ='\0' ;
		strcat(message, ch) ;
	}
	while (ch[0] != 0x03) ;				// Attend code fin trame téinfo.
	return 0;
}

/*
	Test checksum d'un message (Return 1 si checkum ok)	
*/

int checksum_ok(char *etiquette, char *valeur, char checksum) {
	unsigned char sum = 32 ;		// Somme des codes ASCII du message + un espace
	int i ;
 
	for (i=0; i < strlen(etiquette); i++) sum = sum + etiquette[i] ;
	for (i=0; i < strlen(valeur); i++) sum = sum + valeur[i] ;
	sum = (sum & 63) + 32 ;
	if ( sum == checksum) return 1 ;	// Return 1 si checkum ok.

		log_DEBUG("Rpidom: Checksum lu:%02x   calculé02x", checksum, sum) ;

	return 0 ;
}
 
/*
	Read rpidom teleinformation monophase values
*/
int read_mono(){
	int id ;
	erreur_checksum = 0 ;
	
	int NB_VALEURS = 12;
	char etiquettes_mono[12][16] = {"ADCO", "OPTARIF", "ISOUSC", "HCHP", "HCHC", "PTEC", "IINST", "IMAX", "PAPP", "HHPHC", "MOTDETAT", "ADPS"} ;
 
	for (id=0; id<NB_VALEURS; id++)
	{
		if ( (match = strstr(message, etiquettes_mono[id])) != NULL)
		{
			sscanf(match, "%s %s %s", etiquettes_mono[id], valeurs[id], checksum) ;
			if ( strlen(checksum) > 1 ) checksum[0]=' ' ;	// sscanf ne peux lire le checksum àx20 (espace), si longueur checksum > 1 donc c'est un espace.
			if ( ! checksum_ok(etiquettes_mono[id], valeurs[id], checksum[0]) ) 
			{
				log_DEBUG("Rpidom: Data teleinfo [%s] Corrupt (try: %d)", etiquettes_mono[id], no_essais) ;
				erreur_checksum = 1 ;
				return 0 ;
			}
		}
	}
	// Remplace chaine "HP.." ou "HC.." par "HP ou "HC".
	valeurs[5][2] = '\0' ;
	
	log_DEBUG("Rpidom teleinformation data: \n") ; for (id=0; id<NB_VALEURS; id++) log_DEBUG("%s='%s'", etiquettes_mono[id], valeurs[id]) ;

	return 1 ;
}

/*
	Read rpidom teleinformation triphase values
*/
int read_tri(){
	int id ;
	erreur_checksum = 0 ;
	
	int NB_VALEURS = 20;
	char etiquettes_tri[20][16] = {"ADCO", "OPTARIF", "ISOUSC", "HCHP", "HCHC", "PTEC", "IINST1", "IINST2", "IINST3", "IMAX1", "IMAX2", "IMAX3", "PMAX", "PAPP", "HHPHC", "MOTDETAT", "PPOT", "ADIR1", "ADIR2" ,"ADIR3"} ;
	
	for (id=0; id<NB_VALEURS; id++)
	{
		if ( (match = strstr(message, etiquettes_tri[id])) != NULL)
		{
			sscanf(match, "%s %s %s", etiquettes_tri[id], valeurs[id], checksum) ;
			if ( strlen(checksum) > 1 ) checksum[0]=' ' ;	// sscanf ne peux lire le checksum àx20 (espace), si longueur checksum > 1 donc c'est un espace.
			if ( ! checksum_ok(etiquettes_tri[id], valeurs[id], checksum[0]) ) 
			{
				log_DEBUG("Rpidom: Data teleinfo [%s] Corrupt (try: %d)", etiquettes_tri[id], no_essais) ;
				erreur_checksum = 1 ;
				return 0 ;
			}
		}
	}
	// Remplace chaine "HP.." ou "HC.." par "HP ou "HC".
	valeurs[5][2] = '\0' ;

	log_DEBUG("Rpidom teleinformation data: \n") ; for (id=0; id<NB_VALEURS; id++) log_DEBUG("%s='%s'", etiquettes_tri[id], valeurs[id]) ;

	return 1 ;
}
 
/*
	Read rpidom teleinformation port 1 or 2	
*/
int read_rpidom_teleport(int port){
        int countertype;

        if ( port == 1 )
        {
                countertype = RPIDOM_TELE1_TYPE;
                write(fdrpidom,"A",1); //send command to rpifom to read port : port

        }
        else if ( port == 2 )
        {
                countertype = RPIDOM_TELE2_TYPE;
                write(fdrpidom,"B",1); //send command to rpifom to read port : port

        }
        else
        {
                log_ERROR("Rpidom: Problem to get Rpidom teleinfo port") ;
        }

        log_INFO("Rpidom: Starting reading port teleinformation: %d  type: %d \n", port,countertype) ;

		if ( countertype == 1 )
        {
			 do
			 {
				// Lit trame téinfo.
				if (read_serial_tele_frame(fdrpidom)==0)
				{
					if ( read_mono() ) 			// Lit valeurs des équettes de la liste.
					{
						
					}
				}
			 no_essais++ ;
			 }
			 while ( (erreur_checksum) && (no_essais <= nb_essais) ) ;
        }
        else if ( countertype == 3 )
        {
			do
			{
				// Lit trame téinfo.
				if (read_serial_tele_frame(fdrpidom)==0)
				{	 
					if ( read_tri() ) 			// Lit valeurs des équettes de la liste.
					{
						message_EDF3(valeurs);	
					}
				}
			no_essais++ ;
			}
			 while ( (erreur_checksum) && (no_essais <= nb_essais) ) ;

        }
        else
        {
                log_ERROR("Rpidom: Problem to get Rpidom teleinfo counter type (mono or tri)") ;
        }
}


int read_rpidom_1wire() {

	DIR *dir;
	struct dirent *dirent;
	char buf[256];     // Data from device
	char tmpData[5];   // Temp C * 1000 reported by device 
	const char path[] = "/sys/bus/w1/devices"; 
	ssize_t numRead;
	int i = 0;
	int devCnt = 0;

	log_DEBUG("RPIDOM: Starting reading 1wire Port");
	// 1st pass counts devices
	dir = opendir (path);

	if (dir != NULL)
	{
		while ((dirent = readdir (dir))) {
			// 1-wire devices are links beginning with 28-
			if (dirent->d_type == DT_LNK &&
				strstr(dirent->d_name, "28-") != NULL) {
				i++;
			}
		}
		(void) closedir (dir);
	}
	else
	{
		log_ERROR("RPIDOM: Couldn't open the w1 devices directory");
		return 1;
	}
	devCnt = i;
	i = 0;

	// 2nd pass allocates space for data based on device count
	char dev[devCnt][16];
	char devPath[devCnt][128];
	dir = opendir (path);

	if (dir != NULL)
	{
		while ((dirent = readdir (dir))) {
			// 1-wire devices are links beginning with 28-
			if (dirent->d_type == DT_LNK && 
				strstr(dirent->d_name, "28-") != NULL) { 
				strcpy(dev[i], dirent->d_name);
					   // Assemble path to OneWire device
				sprintf(devPath[i], "%s/%s/w1_slave", path, dev[i]);
				i++;
			}
		}
		(void) closedir (dir);
	}
	else
	{
		log_ERROR("RPIDOM: Couldn't open the w1 devices directory");
		return 1;
	}
	i = 0;

	// Read temp continuously
	// Opening the device's file triggers new reading
	while(i < devCnt) {
	
		log_ERROR("RPIDOM: Starting Working with w1 device %s.",devPath[i]);
		
		int fd = open(devPath[i], O_RDONLY);
		if(fd == -1)
		{
			log_ERROR("RPIDOM: Couldn't open the w1 device %s.",devPath[i]);
			return 1;
		}
		while((numRead = read(fd, buf, 256)) > 0) 
		{
			message_1W28(dev[i],buf);
		}
		close(fd);
		i++;
	}
return 0;
}

 
void* rpidom(){
 
	while (1){
		fdrpidom = initserie();
		
		if ( RPIDOM_TELE1_TYPE != 0 ){
			read_rpidom_teleport(1);
		}
		if ( RPIDOM_TELE2_TYPE != 0 ){
			read_rpidom_teleport(2);
		}
		if ( RPIDOM_1WIRE == 1 ){
			read_rpidom_1wire();
		}		
			
		close(fdrpidom) ;
		sleep (60);
	}
	return NULL;
}
