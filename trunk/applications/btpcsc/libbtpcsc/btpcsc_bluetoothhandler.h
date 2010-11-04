/*
 * Copyright 2010 Manuel Eberl <manueleberl@gmx.de> for Giesecke & Devrient
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. 
 * You may obtain a copy of the License at 
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0 
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
 * See the License for the specific language governing permissions and 
 * limitations under the License. 
 */

/*****************************************************************
/
/ File   :   btpcsp_bluetoothhandler.h
/ Author :   Manuel Eberl <manueleberl@gmx.de>
/ Date   :   September 30, 2010
/ Purpose:   Provides a transparent reader bridge to a bluetooth
/            device.
/
******************************************************************/

#ifndef _btpcsc_bluetoothhandler_h_
#define _btpcsc_bluetoothhandler_h_

#ifdef __cplusplus
extern "C" {
#endif 

  #define MAX_ATR_SIZE 33

  typedef unsigned long      DWORD;
  typedef unsigned long*     PDWORD;
  typedef unsigned char      UCHAR;
  typedef unsigned char*     PUCHAR;
  typedef char*              LPSTR;
  typedef long               RESPONSECODE;
  typedef void               VOID;
  typedef struct _DEVICE_CAPABILITIES {
    
    LPSTR Vendor_Name;          /* Tag 0x0100        */
    LPSTR IFD_Type;		/* Tag 0x0101        */
    DWORD IFD_Version;		/* Tag 0x0102        */
    LPSTR IFD_Serial;		/* Tag 0x0103        */
    DWORD IFD_Channel_ID;  	/* Tag 0x0110        */
    
    DWORD Asynch_Supported;	/* Tag 0x0120        */
    DWORD Default_Clock;	/* Tag 0x0121        */
    DWORD Max_Clock;		/* Tag 0x0122        */
    DWORD Default_Data_Rate;	/* Tag 0x0123        */
    DWORD Max_Data_Rate;	/* Tag 0x0124        */
    DWORD Max_IFSD;		/* Tag 0x0125        */
    DWORD Synch_Supported;	/* Tag 0x0126        */
    DWORD Power_Mgmt;		/* Tag 0x0131        */
    DWORD Card_Auth_Devices;	/* Tag 0x0140        */
    DWORD User_Auth_Device;	/* Tag 0x0142        */
    DWORD Mechanics_Supported;	/* Tag 0x0150        */
    DWORD Vendor_Features;	/* Tag 0x0180 - 0x01F0   User Defined. */
    
  } DEVICE_CAPABILITIES, *PDEVICE_CAPABILITIES;
  
  typedef struct _ICC_STATE {
    
    UCHAR ICC_Presence;		/* Tag 0x0300        */
    UCHAR ICC_Interface_Status;	/* Tag 0x0301        */
    UCHAR ATR[MAX_ATR_SIZE];	/* Tag 0x0303        */
    UCHAR ICC_Type;		/* Tag 0x0304        */
    
  } ICC_STATE, *PICC_STATE;
  
  typedef struct _PROTOCOL_OPTIONS {
    
    DWORD Protocol_Type;	/* Tag 0x0201        */
    DWORD Current_Clock;	/* Tag 0x0202        */
    DWORD Current_F;		/* Tag 0x0203        */
    DWORD Current_D;		/* Tag 0x0204        */
    DWORD Current_N;		/* Tag 0x0205        */
    DWORD Current_W;		/* Tag 0x0206        */
    DWORD Current_IFSC;		/* Tag 0x0207        */
    DWORD Current_IFSD;		/* Tag 0x0208        */
    DWORD Current_BWT;		/* Tag 0x0209        */
    DWORD Current_CWT;		/* Tag 0x020A        */
    DWORD Current_EBC;		/* Tag 0x020B        */
  } PROTOCOL_OPTIONS, *PPROTOCOL_OPTIONS;
  
  typedef struct _SCARD_IO_HEADER {
    DWORD Protocol;
    DWORD Length;
  } SCARD_IO_HEADER, *PSCARD_IO_HEADER;



#define IFD_POWER_UP			500
#define IFD_POWER_DOWN			501
#define IFD_RESET			502
  
#define IFD_NEGOTIATE_PTS1		1
#define IFD_NEGOTIATE_PTS2		2
#define IFD_NEGOTIATE_PTS3              4

#define	IFD_SUCCESS			0
#define IFD_ERROR_TAG			600
#define IFD_ERROR_SET_FAILURE		601
#define IFD_ERROR_VALUE_READ_ONLY	602
#define IFD_ERROR_PTS_FAILURE		605
#define IFD_ERROR_NOT_SUPPORTED		606
#define IFD_PROTOCOL_NOT_SUPPORTED	607
#define IFD_ERROR_POWER_ACTION		608
#define IFD_ERROR_SWALLOW		609
#define IFD_ERROR_EJECT			610
#define IFD_ERROR_CONFISCATE		611
#define IFD_COMMUNICATION_ERROR		612
#define IFD_RESPONSE_TIMEOUT		613
#define IFD_NOT_SUPPORTED		614
#define IFD_ICC_PRESENT			615
#define IFD_ICC_NOT_PRESENT		616

#define TAG_IFD_SLOTS_NUMBER		0x0FAE
#define TAG_IFD_ATR                     0x0303
#define TAG_IFD_SLOT_THREAD_SAFE        0x0FAC
#define TAG_IFD_THREAD_SAFE             0x0FAD
#define TAG_IFD_SLOTS_NUMBER            0x0FAE
#define TAG_IFD_SIMULTANEOUS_ACCESS     0x0FAF
#define TAG_IFD_POLLING_THREAD          0x0FB0
#define TAG_IFD_POLLING_THREAD_KILLABLE 0x0FB1

#define DBG_CRITICAL 1
#define DBG_ERROR 2
#define DBG_WARNING 3
#define DBG_VERBOSE 4
#define DBG_APDU 5

#define COLOR_BLUE "\33[34m"
#define COLOR_RED "\33[31m"
#define COLOR_BRIGHT_RED "\33[01;31m"
#define COLOR_GREEN "\33[32m"
#define COLOR_NORMAL "\33[0m"

  RESPONSECODE IFDHCreateChannel ( DWORD, DWORD );
  RESPONSECODE IFDHCloseChannel ( DWORD );
  RESPONSECODE IFDHGetCapabilities ( DWORD, DWORD, PDWORD, 
				     PUCHAR );
  RESPONSECODE IFDHSetCapabilities ( DWORD, DWORD, DWORD, PUCHAR );
  RESPONSECODE IFDHSetProtocolParameters ( DWORD, DWORD, UCHAR, 
					   UCHAR, UCHAR, UCHAR );
  RESPONSECODE IFDHPowerICC ( DWORD, DWORD, PUCHAR, PDWORD );
  RESPONSECODE IFDHTransmitToICC ( DWORD, SCARD_IO_HEADER, PUCHAR, 
				   DWORD, PUCHAR, PDWORD, 
				   PSCARD_IO_HEADER );
  RESPONSECODE IFDHControl ( DWORD, PUCHAR, DWORD, 
			     PUCHAR, PDWORD );
  RESPONSECODE IFDHICCPresence( DWORD );
  
#ifdef __cplusplus
}
#endif 

#endif

