GSOAP_CFLAGS= lib/gsoap/stdsoap2.c lib/gsoap/soapC.c lib/gsoap/soapServer.c

mydombox_CFLAGS = -w -Wall $(MYSQL_CFLAGS)
mydombox_LDADD=$(MYSQL_LDFLAGS) $(GSOAP_CFLAGS) -lcurl -lpthread

bin_PROGRAMS = mydombox
mydombox_SOURCES= \
	mydombox.c \
	mdb_config_reader.c mdb_config_reader.h \
	mdb_soapserver.c mdb_soapserver.h \
	mdb_tools.c mdb_tools.h \
	mdb_rfxtrx433.c mdb_rfxtrx433.h \
	mdb_enocean_usb300.c mdb_enocean_usb300.h \
	mdb_thermostat.c mdb_thermostat.h \
	mdb_decode_rfxcom_messages.c mdb_decode_rfxcom_messages.h \
	mdb_encode_messages.c mdb_encode_messages.h \
	mdb_decode_enocean_messages.c mdb_decode_enocean_messages.h \
	mdb_log.c mdb_log.h \
	mdb_mysql.c mdb_mysql.h \
	mdb_dvn.c mdb_dvn.h \
	mdb_rpidom.c mdb_rpidom.h \
	mdb_scheduler.c mdb_scheduler.h 