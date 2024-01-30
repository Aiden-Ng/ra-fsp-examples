/***********************************************************************************************************************
* 
* Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
*
* This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas Electronics Corp.
* and its affiliates (“Renesas”).  No other uses are authorized.  This software is protected under all applicable laws, 
* including copyright laws.
* Renesas reserves the right to change or discontinue this software.
* THE SOFTWARE IS DELIVERED TO YOU “AS IS,” AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT 
* PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES OF 
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.  TO THE MAXIMUM 
* EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE (OR ANY PERSON 
* OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING, WITHOUT LIMITATION, 
* ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES;
* ANY LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF 
* THE POSSIBILITY OF SUCH LOSS,DAMAGES, CLAIMS OR COSTS.
* 
**********************************************************************************************************************/

1. Project Overview:

	This project demonstrates the basic functionalities of USB PHID driver on Renesas RA MCUs based on Renesas FSP.
	The project configures RA board as a Keyboard. On pressing any key from RTTViewer, MCU sends the host PC 
	characters from a - z & numbers 0 - 9.

2. Hardware Requirement:

	micro USB Cable : 2 nos
	
3. Hardware connection :
	
	EK-RA2A1,EK-RA4M1,EK-RA6M1,EK-RA6M2:(support only full speed)
	Connect the micro USB end of the micro USB device cable to micro-AB USB Full Speed 
	port (J9) of the board.  Connect the other end of this cable to USB port of the 
	host PC. 
	
	EK-RA6M3,EK-RA6M3G,EK-RA6M4,EK-RA6M5,EK-RA4M3,EK-RA4M2:(support only full speed)
	Jumper J12 placement is pins 2-3
	Connect jumper J15 pins 
	Connect the micro USB end of the micro USB device cable to micro-AB USB Full Speed 
	port (J11) of the board.  Connect the other end of this cable to USB port of the 
	host PC. 

    Link to Errata:https://www.renesas.com/us/en/document/mat/ek-ra6m3-v1-errata?language=en&r=1168086

Note :
1. Open Device Manager, and check 'Human Interface Devices', to see ' USB Input Device' has been detected.
2. lower case a - z and numbers 0 - 9 is send from MCU to the host PC.