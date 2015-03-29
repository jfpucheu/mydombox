/* soapH.h
   Generated by gSOAP 2.8.15 from mydombox-2.0.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapH_H
#define soapH_H
#include "soapStub.h"
#ifdef __cplusplus
extern "C" {
#endif
#ifndef WITH_NOIDREF
SOAP_FMAC3 void SOAP_FMAC4 soap_markelement(struct soap*, const void*, int);
SOAP_FMAC3 int SOAP_FMAC4 soap_putindependent(struct soap*);
SOAP_FMAC3 int SOAP_FMAC4 soap_getindependent(struct soap*);
#endif
SOAP_FMAC3 void *SOAP_FMAC4 soap_getelement(struct soap*, int*);
SOAP_FMAC3 int SOAP_FMAC4 soap_putelement(struct soap*, const void*, const char*, int, int);
SOAP_FMAC3 int SOAP_FMAC4 soap_ignore_element(struct soap*);

SOAP_FMAC3 const char ** SOAP_FMAC4 soap_faultcode(struct soap *soap);

#ifndef SOAP_TYPE_byte
#define SOAP_TYPE_byte (3)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_byte(struct soap*, char *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_byte(struct soap*, const char*, int, const char *, const char*);
SOAP_FMAC3 char * SOAP_FMAC4 soap_in_byte(struct soap*, const char*, char *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put_byte(struct soap*, const char *, const char*, const char*);

#ifndef soap_write_byte
#define soap_write_byte(soap, data) ( soap_serialize_byte(soap, data), soap_begin_send(soap) || soap_put_byte(soap, data, "byte", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 char * SOAP_FMAC4 soap_get_byte(struct soap*, char *, const char*, const char*);

#ifndef soap_read_byte
#define soap_read_byte(soap, data) ( soap_begin_recv(soap) || !soap_get_byte(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE_int
#define SOAP_TYPE_int (1)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_int(struct soap*, int *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_int(struct soap*, const char*, int, const int *, const char*);
SOAP_FMAC3 int * SOAP_FMAC4 soap_in_int(struct soap*, const char*, int *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put_int(struct soap*, const int *, const char*, const char*);

#ifndef soap_write_int
#define soap_write_int(soap, data) ( soap_serialize_int(soap, data), soap_begin_send(soap) || soap_put_int(soap, data, "int", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 int * SOAP_FMAC4 soap_get_int(struct soap*, int *, const char*, const char*);

#ifndef soap_read_int
#define soap_read_int(soap, data) ( soap_begin_recv(soap) || !soap_get_int(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (33)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Fault(struct soap*, const char*, int, const struct SOAP_ENV__Fault *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_in_SOAP_ENV__Fault(struct soap*, const char*, struct SOAP_ENV__Fault *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *, const char*, const char*);

#ifndef soap_write_SOAP_ENV__Fault
#define soap_write_SOAP_ENV__Fault(soap, data) ( soap_serialize_SOAP_ENV__Fault(soap, data), soap_begin_send(soap) || soap_put_SOAP_ENV__Fault(soap, data, "SOAP-ENV:Fault", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_get_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *, const char*, const char*);

#ifndef soap_read_SOAP_ENV__Fault
#define soap_read_SOAP_ENV__Fault(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Fault(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (32)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Reason(struct soap*, const char*, int, const struct SOAP_ENV__Reason *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_in_SOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *, const char*, const char*);

#ifndef soap_write_SOAP_ENV__Reason
#define soap_write_SOAP_ENV__Reason(soap, data) ( soap_serialize_SOAP_ENV__Reason(soap, data), soap_begin_send(soap) || soap_put_SOAP_ENV__Reason(soap, data, "SOAP-ENV:Reason", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_get_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *, const char*, const char*);

#ifndef soap_read_SOAP_ENV__Reason
#define soap_read_SOAP_ENV__Reason(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Reason(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (29)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Detail(struct soap*, const char*, int, const struct SOAP_ENV__Detail *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_in_SOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *, const char*, const char*);

#ifndef soap_write_SOAP_ENV__Detail
#define soap_write_SOAP_ENV__Detail(soap, data) ( soap_serialize_SOAP_ENV__Detail(soap, data), soap_begin_send(soap) || soap_put_SOAP_ENV__Detail(soap, data, "SOAP-ENV:Detail", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_get_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *, const char*, const char*);

#ifndef soap_read_SOAP_ENV__Detail
#define soap_read_SOAP_ENV__Detail(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Detail(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (27)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Code(struct soap*, const char*, int, const struct SOAP_ENV__Code *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_in_SOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *, const char*, const char*);

#ifndef soap_write_SOAP_ENV__Code
#define soap_write_SOAP_ENV__Code(soap, data) ( soap_serialize_SOAP_ENV__Code(soap, data), soap_begin_send(soap) || soap_put_SOAP_ENV__Code(soap, data, "SOAP-ENV:Code", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_get_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *, const char*, const char*);

#ifndef soap_read_SOAP_ENV__Code
#define soap_read_SOAP_ENV__Code(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Code(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (26)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Header(struct soap*, const char*, int, const struct SOAP_ENV__Header *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_in_SOAP_ENV__Header(struct soap*, const char*, struct SOAP_ENV__Header *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *, const char*, const char*);

#ifndef soap_write_SOAP_ENV__Header
#define soap_write_SOAP_ENV__Header(soap, data) ( soap_serialize_SOAP_ENV__Header(soap, data), soap_begin_send(soap) || soap_put_SOAP_ENV__Header(soap, data, "SOAP-ENV:Header", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_get_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *, const char*, const char*);

#ifndef soap_read_SOAP_ENV__Header
#define soap_read_SOAP_ENV__Header(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Header(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#endif

#ifndef SOAP_TYPE___ns1__initDevice
#define SOAP_TYPE___ns1__initDevice (25)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default___ns1__initDevice(struct soap*, struct __ns1__initDevice *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize___ns1__initDevice(struct soap*, const struct __ns1__initDevice *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out___ns1__initDevice(struct soap*, const char*, int, const struct __ns1__initDevice *, const char*);
SOAP_FMAC3 struct __ns1__initDevice * SOAP_FMAC4 soap_in___ns1__initDevice(struct soap*, const char*, struct __ns1__initDevice *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put___ns1__initDevice(struct soap*, const struct __ns1__initDevice *, const char*, const char*);

#ifndef soap_write___ns1__initDevice
#define soap_write___ns1__initDevice(soap, data) ( soap_serialize___ns1__initDevice(soap, data), soap_begin_send(soap) || soap_put___ns1__initDevice(soap, data, "-ns1:initDevice", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct __ns1__initDevice * SOAP_FMAC4 soap_get___ns1__initDevice(struct soap*, struct __ns1__initDevice *, const char*, const char*);

#ifndef soap_read___ns1__initDevice
#define soap_read___ns1__initDevice(soap, data) ( soap_begin_recv(soap) || !soap_get___ns1__initDevice(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE___ns1__setLightingStatus
#define SOAP_TYPE___ns1__setLightingStatus (21)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default___ns1__setLightingStatus(struct soap*, struct __ns1__setLightingStatus *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize___ns1__setLightingStatus(struct soap*, const struct __ns1__setLightingStatus *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out___ns1__setLightingStatus(struct soap*, const char*, int, const struct __ns1__setLightingStatus *, const char*);
SOAP_FMAC3 struct __ns1__setLightingStatus * SOAP_FMAC4 soap_in___ns1__setLightingStatus(struct soap*, const char*, struct __ns1__setLightingStatus *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put___ns1__setLightingStatus(struct soap*, const struct __ns1__setLightingStatus *, const char*, const char*);

#ifndef soap_write___ns1__setLightingStatus
#define soap_write___ns1__setLightingStatus(soap, data) ( soap_serialize___ns1__setLightingStatus(soap, data), soap_begin_send(soap) || soap_put___ns1__setLightingStatus(soap, data, "-ns1:setLightingStatus", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct __ns1__setLightingStatus * SOAP_FMAC4 soap_get___ns1__setLightingStatus(struct soap*, struct __ns1__setLightingStatus *, const char*, const char*);

#ifndef soap_read___ns1__setLightingStatus
#define soap_read___ns1__setLightingStatus(soap, data) ( soap_begin_recv(soap) || !soap_get___ns1__setLightingStatus(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE___ns1__getLightingStatus
#define SOAP_TYPE___ns1__getLightingStatus (17)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default___ns1__getLightingStatus(struct soap*, struct __ns1__getLightingStatus *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize___ns1__getLightingStatus(struct soap*, const struct __ns1__getLightingStatus *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out___ns1__getLightingStatus(struct soap*, const char*, int, const struct __ns1__getLightingStatus *, const char*);
SOAP_FMAC3 struct __ns1__getLightingStatus * SOAP_FMAC4 soap_in___ns1__getLightingStatus(struct soap*, const char*, struct __ns1__getLightingStatus *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put___ns1__getLightingStatus(struct soap*, const struct __ns1__getLightingStatus *, const char*, const char*);

#ifndef soap_write___ns1__getLightingStatus
#define soap_write___ns1__getLightingStatus(soap, data) ( soap_serialize___ns1__getLightingStatus(soap, data), soap_begin_send(soap) || soap_put___ns1__getLightingStatus(soap, data, "-ns1:getLightingStatus", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct __ns1__getLightingStatus * SOAP_FMAC4 soap_get___ns1__getLightingStatus(struct soap*, struct __ns1__getLightingStatus *, const char*, const char*);

#ifndef soap_read___ns1__getLightingStatus
#define soap_read___ns1__getLightingStatus(soap, data) ( soap_begin_recv(soap) || !soap_get___ns1__getLightingStatus(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE__ns1__initDeviceResponse
#define SOAP_TYPE__ns1__initDeviceResponse (13)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default__ns1__initDeviceResponse(struct soap*, struct _ns1__initDeviceResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__ns1__initDeviceResponse(struct soap*, const struct _ns1__initDeviceResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__ns1__initDeviceResponse(struct soap*, const char*, int, const struct _ns1__initDeviceResponse *, const char*);
SOAP_FMAC3 struct _ns1__initDeviceResponse * SOAP_FMAC4 soap_in__ns1__initDeviceResponse(struct soap*, const char*, struct _ns1__initDeviceResponse *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put__ns1__initDeviceResponse(struct soap*, const struct _ns1__initDeviceResponse *, const char*, const char*);

#ifndef soap_write__ns1__initDeviceResponse
#define soap_write__ns1__initDeviceResponse(soap, data) ( soap_serialize__ns1__initDeviceResponse(soap, data), soap_begin_send(soap) || soap_put__ns1__initDeviceResponse(soap, data, "ns1:initDeviceResponse", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__initDeviceResponse * SOAP_FMAC4 soap_get__ns1__initDeviceResponse(struct soap*, struct _ns1__initDeviceResponse *, const char*, const char*);

#ifndef soap_read__ns1__initDeviceResponse
#define soap_read__ns1__initDeviceResponse(soap, data) ( soap_begin_recv(soap) || !soap_get__ns1__initDeviceResponse(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE__ns1__initDevice
#define SOAP_TYPE__ns1__initDevice (12)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default__ns1__initDevice(struct soap*, struct _ns1__initDevice *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__ns1__initDevice(struct soap*, const struct _ns1__initDevice *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__ns1__initDevice(struct soap*, const char*, int, const struct _ns1__initDevice *, const char*);
SOAP_FMAC3 struct _ns1__initDevice * SOAP_FMAC4 soap_in__ns1__initDevice(struct soap*, const char*, struct _ns1__initDevice *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put__ns1__initDevice(struct soap*, const struct _ns1__initDevice *, const char*, const char*);

#ifndef soap_write__ns1__initDevice
#define soap_write__ns1__initDevice(soap, data) ( soap_serialize__ns1__initDevice(soap, data), soap_begin_send(soap) || soap_put__ns1__initDevice(soap, data, "ns1:initDevice", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__initDevice * SOAP_FMAC4 soap_get__ns1__initDevice(struct soap*, struct _ns1__initDevice *, const char*, const char*);

#ifndef soap_read__ns1__initDevice
#define soap_read__ns1__initDevice(soap, data) ( soap_begin_recv(soap) || !soap_get__ns1__initDevice(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE__ns1__setLightingStatusResponse
#define SOAP_TYPE__ns1__setLightingStatusResponse (11)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default__ns1__setLightingStatusResponse(struct soap*, struct _ns1__setLightingStatusResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__ns1__setLightingStatusResponse(struct soap*, const struct _ns1__setLightingStatusResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__ns1__setLightingStatusResponse(struct soap*, const char*, int, const struct _ns1__setLightingStatusResponse *, const char*);
SOAP_FMAC3 struct _ns1__setLightingStatusResponse * SOAP_FMAC4 soap_in__ns1__setLightingStatusResponse(struct soap*, const char*, struct _ns1__setLightingStatusResponse *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put__ns1__setLightingStatusResponse(struct soap*, const struct _ns1__setLightingStatusResponse *, const char*, const char*);

#ifndef soap_write__ns1__setLightingStatusResponse
#define soap_write__ns1__setLightingStatusResponse(soap, data) ( soap_serialize__ns1__setLightingStatusResponse(soap, data), soap_begin_send(soap) || soap_put__ns1__setLightingStatusResponse(soap, data, "ns1:setLightingStatusResponse", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__setLightingStatusResponse * SOAP_FMAC4 soap_get__ns1__setLightingStatusResponse(struct soap*, struct _ns1__setLightingStatusResponse *, const char*, const char*);

#ifndef soap_read__ns1__setLightingStatusResponse
#define soap_read__ns1__setLightingStatusResponse(soap, data) ( soap_begin_recv(soap) || !soap_get__ns1__setLightingStatusResponse(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE__ns1__setLightingStatus
#define SOAP_TYPE__ns1__setLightingStatus (10)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default__ns1__setLightingStatus(struct soap*, struct _ns1__setLightingStatus *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__ns1__setLightingStatus(struct soap*, const struct _ns1__setLightingStatus *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__ns1__setLightingStatus(struct soap*, const char*, int, const struct _ns1__setLightingStatus *, const char*);
SOAP_FMAC3 struct _ns1__setLightingStatus * SOAP_FMAC4 soap_in__ns1__setLightingStatus(struct soap*, const char*, struct _ns1__setLightingStatus *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put__ns1__setLightingStatus(struct soap*, const struct _ns1__setLightingStatus *, const char*, const char*);

#ifndef soap_write__ns1__setLightingStatus
#define soap_write__ns1__setLightingStatus(soap, data) ( soap_serialize__ns1__setLightingStatus(soap, data), soap_begin_send(soap) || soap_put__ns1__setLightingStatus(soap, data, "ns1:setLightingStatus", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__setLightingStatus * SOAP_FMAC4 soap_get__ns1__setLightingStatus(struct soap*, struct _ns1__setLightingStatus *, const char*, const char*);

#ifndef soap_read__ns1__setLightingStatus
#define soap_read__ns1__setLightingStatus(soap, data) ( soap_begin_recv(soap) || !soap_get__ns1__setLightingStatus(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE__ns1__getLightingStatusResponse
#define SOAP_TYPE__ns1__getLightingStatusResponse (8)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default__ns1__getLightingStatusResponse(struct soap*, struct _ns1__getLightingStatusResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__ns1__getLightingStatusResponse(struct soap*, const struct _ns1__getLightingStatusResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__ns1__getLightingStatusResponse(struct soap*, const char*, int, const struct _ns1__getLightingStatusResponse *, const char*);
SOAP_FMAC3 struct _ns1__getLightingStatusResponse * SOAP_FMAC4 soap_in__ns1__getLightingStatusResponse(struct soap*, const char*, struct _ns1__getLightingStatusResponse *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put__ns1__getLightingStatusResponse(struct soap*, const struct _ns1__getLightingStatusResponse *, const char*, const char*);

#ifndef soap_write__ns1__getLightingStatusResponse
#define soap_write__ns1__getLightingStatusResponse(soap, data) ( soap_serialize__ns1__getLightingStatusResponse(soap, data), soap_begin_send(soap) || soap_put__ns1__getLightingStatusResponse(soap, data, "ns1:getLightingStatusResponse", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__getLightingStatusResponse * SOAP_FMAC4 soap_get__ns1__getLightingStatusResponse(struct soap*, struct _ns1__getLightingStatusResponse *, const char*, const char*);

#ifndef soap_read__ns1__getLightingStatusResponse
#define soap_read__ns1__getLightingStatusResponse(soap, data) ( soap_begin_recv(soap) || !soap_get__ns1__getLightingStatusResponse(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE__ns1__getLightingStatus
#define SOAP_TYPE__ns1__getLightingStatus (7)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default__ns1__getLightingStatus(struct soap*, struct _ns1__getLightingStatus *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__ns1__getLightingStatus(struct soap*, const struct _ns1__getLightingStatus *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__ns1__getLightingStatus(struct soap*, const char*, int, const struct _ns1__getLightingStatus *, const char*);
SOAP_FMAC3 struct _ns1__getLightingStatus * SOAP_FMAC4 soap_in__ns1__getLightingStatus(struct soap*, const char*, struct _ns1__getLightingStatus *, const char*);

SOAP_FMAC3 int SOAP_FMAC4 soap_put__ns1__getLightingStatus(struct soap*, const struct _ns1__getLightingStatus *, const char*, const char*);

#ifndef soap_write__ns1__getLightingStatus
#define soap_write__ns1__getLightingStatus(soap, data) ( soap_serialize__ns1__getLightingStatus(soap, data), soap_begin_send(soap) || soap_put__ns1__getLightingStatus(soap, data, "ns1:getLightingStatus", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__getLightingStatus * SOAP_FMAC4 soap_get__ns1__getLightingStatus(struct soap*, struct _ns1__getLightingStatus *, const char*, const char*);

#ifndef soap_read__ns1__getLightingStatus
#define soap_read__ns1__getLightingStatus(soap, data) ( soap_begin_recv(soap) || !soap_get__ns1__getLightingStatus(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason
#define SOAP_TYPE_PointerToSOAP_ENV__Reason (35)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Reason(struct soap*, const char *, int, struct SOAP_ENV__Reason *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*, const char*, const char*);

#ifndef soap_write_PointerToSOAP_ENV__Reason
#define soap_write_PointerToSOAP_ENV__Reason(soap, data) ( soap_serialize_PointerToSOAP_ENV__Reason(soap, data), soap_begin_send(soap) || soap_put_PointerToSOAP_ENV__Reason(soap, data, "SOAP-ENV:Reason", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason **, const char*, const char*);

#ifndef soap_read_PointerToSOAP_ENV__Reason
#define soap_read_PointerToSOAP_ENV__Reason(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerToSOAP_ENV__Reason(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail
#define SOAP_TYPE_PointerToSOAP_ENV__Detail (34)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Detail(struct soap*, const char *, int, struct SOAP_ENV__Detail *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*, const char*, const char*);

#ifndef soap_write_PointerToSOAP_ENV__Detail
#define soap_write_PointerToSOAP_ENV__Detail(soap, data) ( soap_serialize_PointerToSOAP_ENV__Detail(soap, data), soap_begin_send(soap) || soap_put_PointerToSOAP_ENV__Detail(soap, data, "SOAP-ENV:Detail", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail **, const char*, const char*);

#ifndef soap_read_PointerToSOAP_ENV__Detail
#define soap_read_PointerToSOAP_ENV__Detail(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerToSOAP_ENV__Detail(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code
#define SOAP_TYPE_PointerToSOAP_ENV__Code (28)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Code(struct soap*, const char *, int, struct SOAP_ENV__Code *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*, const char*, const char*);

#ifndef soap_write_PointerToSOAP_ENV__Code
#define soap_write_PointerToSOAP_ENV__Code(soap, data) ( soap_serialize_PointerToSOAP_ENV__Code(soap, data), soap_begin_send(soap) || soap_put_PointerToSOAP_ENV__Code(soap, data, "SOAP-ENV:Code", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code **, const char*, const char*);

#ifndef soap_read_PointerToSOAP_ENV__Code
#define soap_read_PointerToSOAP_ENV__Code(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerToSOAP_ENV__Code(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#endif

#ifndef SOAP_TYPE_PointerTo_ns1__initDeviceResponse
#define SOAP_TYPE_PointerTo_ns1__initDeviceResponse (23)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerTo_ns1__initDeviceResponse(struct soap*, struct _ns1__initDeviceResponse *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerTo_ns1__initDeviceResponse(struct soap*, const char *, int, struct _ns1__initDeviceResponse *const*, const char *);
SOAP_FMAC3 struct _ns1__initDeviceResponse ** SOAP_FMAC4 soap_in_PointerTo_ns1__initDeviceResponse(struct soap*, const char*, struct _ns1__initDeviceResponse **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerTo_ns1__initDeviceResponse(struct soap*, struct _ns1__initDeviceResponse *const*, const char*, const char*);

#ifndef soap_write_PointerTo_ns1__initDeviceResponse
#define soap_write_PointerTo_ns1__initDeviceResponse(soap, data) ( soap_serialize_PointerTo_ns1__initDeviceResponse(soap, data), soap_begin_send(soap) || soap_put_PointerTo_ns1__initDeviceResponse(soap, data, "ns1:initDeviceResponse", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__initDeviceResponse ** SOAP_FMAC4 soap_get_PointerTo_ns1__initDeviceResponse(struct soap*, struct _ns1__initDeviceResponse **, const char*, const char*);

#ifndef soap_read_PointerTo_ns1__initDeviceResponse
#define soap_read_PointerTo_ns1__initDeviceResponse(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerTo_ns1__initDeviceResponse(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE_PointerTo_ns1__initDevice
#define SOAP_TYPE_PointerTo_ns1__initDevice (22)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerTo_ns1__initDevice(struct soap*, struct _ns1__initDevice *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerTo_ns1__initDevice(struct soap*, const char *, int, struct _ns1__initDevice *const*, const char *);
SOAP_FMAC3 struct _ns1__initDevice ** SOAP_FMAC4 soap_in_PointerTo_ns1__initDevice(struct soap*, const char*, struct _ns1__initDevice **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerTo_ns1__initDevice(struct soap*, struct _ns1__initDevice *const*, const char*, const char*);

#ifndef soap_write_PointerTo_ns1__initDevice
#define soap_write_PointerTo_ns1__initDevice(soap, data) ( soap_serialize_PointerTo_ns1__initDevice(soap, data), soap_begin_send(soap) || soap_put_PointerTo_ns1__initDevice(soap, data, "ns1:initDevice", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__initDevice ** SOAP_FMAC4 soap_get_PointerTo_ns1__initDevice(struct soap*, struct _ns1__initDevice **, const char*, const char*);

#ifndef soap_read_PointerTo_ns1__initDevice
#define soap_read_PointerTo_ns1__initDevice(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerTo_ns1__initDevice(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE_PointerTo_ns1__setLightingStatusResponse
#define SOAP_TYPE_PointerTo_ns1__setLightingStatusResponse (19)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerTo_ns1__setLightingStatusResponse(struct soap*, struct _ns1__setLightingStatusResponse *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerTo_ns1__setLightingStatusResponse(struct soap*, const char *, int, struct _ns1__setLightingStatusResponse *const*, const char *);
SOAP_FMAC3 struct _ns1__setLightingStatusResponse ** SOAP_FMAC4 soap_in_PointerTo_ns1__setLightingStatusResponse(struct soap*, const char*, struct _ns1__setLightingStatusResponse **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerTo_ns1__setLightingStatusResponse(struct soap*, struct _ns1__setLightingStatusResponse *const*, const char*, const char*);

#ifndef soap_write_PointerTo_ns1__setLightingStatusResponse
#define soap_write_PointerTo_ns1__setLightingStatusResponse(soap, data) ( soap_serialize_PointerTo_ns1__setLightingStatusResponse(soap, data), soap_begin_send(soap) || soap_put_PointerTo_ns1__setLightingStatusResponse(soap, data, "ns1:setLightingStatusResponse", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__setLightingStatusResponse ** SOAP_FMAC4 soap_get_PointerTo_ns1__setLightingStatusResponse(struct soap*, struct _ns1__setLightingStatusResponse **, const char*, const char*);

#ifndef soap_read_PointerTo_ns1__setLightingStatusResponse
#define soap_read_PointerTo_ns1__setLightingStatusResponse(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerTo_ns1__setLightingStatusResponse(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE_PointerTo_ns1__setLightingStatus
#define SOAP_TYPE_PointerTo_ns1__setLightingStatus (18)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerTo_ns1__setLightingStatus(struct soap*, struct _ns1__setLightingStatus *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerTo_ns1__setLightingStatus(struct soap*, const char *, int, struct _ns1__setLightingStatus *const*, const char *);
SOAP_FMAC3 struct _ns1__setLightingStatus ** SOAP_FMAC4 soap_in_PointerTo_ns1__setLightingStatus(struct soap*, const char*, struct _ns1__setLightingStatus **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerTo_ns1__setLightingStatus(struct soap*, struct _ns1__setLightingStatus *const*, const char*, const char*);

#ifndef soap_write_PointerTo_ns1__setLightingStatus
#define soap_write_PointerTo_ns1__setLightingStatus(soap, data) ( soap_serialize_PointerTo_ns1__setLightingStatus(soap, data), soap_begin_send(soap) || soap_put_PointerTo_ns1__setLightingStatus(soap, data, "ns1:setLightingStatus", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__setLightingStatus ** SOAP_FMAC4 soap_get_PointerTo_ns1__setLightingStatus(struct soap*, struct _ns1__setLightingStatus **, const char*, const char*);

#ifndef soap_read_PointerTo_ns1__setLightingStatus
#define soap_read_PointerTo_ns1__setLightingStatus(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerTo_ns1__setLightingStatus(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE_PointerTo_ns1__getLightingStatusResponse
#define SOAP_TYPE_PointerTo_ns1__getLightingStatusResponse (15)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerTo_ns1__getLightingStatusResponse(struct soap*, struct _ns1__getLightingStatusResponse *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerTo_ns1__getLightingStatusResponse(struct soap*, const char *, int, struct _ns1__getLightingStatusResponse *const*, const char *);
SOAP_FMAC3 struct _ns1__getLightingStatusResponse ** SOAP_FMAC4 soap_in_PointerTo_ns1__getLightingStatusResponse(struct soap*, const char*, struct _ns1__getLightingStatusResponse **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerTo_ns1__getLightingStatusResponse(struct soap*, struct _ns1__getLightingStatusResponse *const*, const char*, const char*);

#ifndef soap_write_PointerTo_ns1__getLightingStatusResponse
#define soap_write_PointerTo_ns1__getLightingStatusResponse(soap, data) ( soap_serialize_PointerTo_ns1__getLightingStatusResponse(soap, data), soap_begin_send(soap) || soap_put_PointerTo_ns1__getLightingStatusResponse(soap, data, "ns1:getLightingStatusResponse", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__getLightingStatusResponse ** SOAP_FMAC4 soap_get_PointerTo_ns1__getLightingStatusResponse(struct soap*, struct _ns1__getLightingStatusResponse **, const char*, const char*);

#ifndef soap_read_PointerTo_ns1__getLightingStatusResponse
#define soap_read_PointerTo_ns1__getLightingStatusResponse(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerTo_ns1__getLightingStatusResponse(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE_PointerTo_ns1__getLightingStatus
#define SOAP_TYPE_PointerTo_ns1__getLightingStatus (14)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerTo_ns1__getLightingStatus(struct soap*, struct _ns1__getLightingStatus *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerTo_ns1__getLightingStatus(struct soap*, const char *, int, struct _ns1__getLightingStatus *const*, const char *);
SOAP_FMAC3 struct _ns1__getLightingStatus ** SOAP_FMAC4 soap_in_PointerTo_ns1__getLightingStatus(struct soap*, const char*, struct _ns1__getLightingStatus **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerTo_ns1__getLightingStatus(struct soap*, struct _ns1__getLightingStatus *const*, const char*, const char*);

#ifndef soap_write_PointerTo_ns1__getLightingStatus
#define soap_write_PointerTo_ns1__getLightingStatus(soap, data) ( soap_serialize_PointerTo_ns1__getLightingStatus(soap, data), soap_begin_send(soap) || soap_put_PointerTo_ns1__getLightingStatus(soap, data, "ns1:getLightingStatus", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 struct _ns1__getLightingStatus ** SOAP_FMAC4 soap_get_PointerTo_ns1__getLightingStatus(struct soap*, struct _ns1__getLightingStatus **, const char*, const char*);

#ifndef soap_read_PointerTo_ns1__getLightingStatus
#define soap_read_PointerTo_ns1__getLightingStatus(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerTo_ns1__getLightingStatus(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE_PointerToint
#define SOAP_TYPE_PointerToint (9)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToint(struct soap*, int *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToint(struct soap*, const char *, int, int *const*, const char *);
SOAP_FMAC3 int ** SOAP_FMAC4 soap_in_PointerToint(struct soap*, const char*, int **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToint(struct soap*, int *const*, const char*, const char*);

#ifndef soap_write_PointerToint
#define soap_write_PointerToint(soap, data) ( soap_serialize_PointerToint(soap, data), soap_begin_send(soap) || soap_put_PointerToint(soap, data, "int", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 int ** SOAP_FMAC4 soap_get_PointerToint(struct soap*, int **, const char*, const char*);

#ifndef soap_read_PointerToint
#define soap_read_PointerToint(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerToint(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
#endif

#define soap_default__QName(soap, a) soap_default_string(soap, a)

SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__QName(struct soap*, char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__QName(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in__QName(struct soap*, const char*, char **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put__QName(struct soap*, char *const*, const char*, const char*);

#ifndef soap_write__QName
#define soap_write__QName(soap, data) ( soap_serialize__QName(soap, data), soap_begin_send(soap) || soap_put__QName(soap, data, "byte", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 char ** SOAP_FMAC4 soap_get__QName(struct soap*, char **, const char*, const char*);

#ifndef soap_read__QName
#define soap_read__QName(soap, data) ( soap_begin_recv(soap) || !soap_get__QName(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifndef SOAP_TYPE_string
#define SOAP_TYPE_string (4)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_string(struct soap*, char **);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_string(struct soap*, char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_string(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in_string(struct soap*, const char*, char **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_string(struct soap*, char *const*, const char*, const char*);

#ifndef soap_write_string
#define soap_write_string(soap, data) ( soap_serialize_string(soap, data), soap_begin_send(soap) || soap_put_string(soap, data, "byte", NULL) || soap_end_send(soap), soap->error )
#endif

SOAP_FMAC3 char ** SOAP_FMAC4 soap_get_string(struct soap*, char **, const char*, const char*);

#ifndef soap_read_string
#define soap_read_string(soap, data) ( soap_begin_recv(soap) || !soap_get_string(soap, data, NULL, NULL) || soap_end_recv(soap), soap->error )
#endif


#ifdef __cplusplus
}
#endif

#endif

/* End of soapH.h */