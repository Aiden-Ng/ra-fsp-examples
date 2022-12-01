/***********************************************************************************************************************
* Copyright [2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
* **********************************************************************************************************************/

1. Project Overview:

      This project demonstrates the basic functionality of the USBX Peripheral Printer driver on Renesas RA MCUs based on 
      Renesas FSP using Azure RTOS. An RA MCU board will be connected to the PC where the RA board acts as a peripheral printer 
      and the PC (Windows System) acts as a host device. A print command for a test file will be sent from the host PC, and 
      printing data will be transferred from the host PC to MCU. RA MCU will display Windows machine printer information, 
      settings, and printing data on the J-Link RTT Viewer. Error and info messages will be printed on J-Link RTT Viewer.

      Following is the sequence used by the application.

        1. Connect two USB Cables to the PC : One for USB Debug port and other for USB HS/FS port.
        2. In Device Manger, printer should be detected as "Generic / Text Only" under Print queues section.
        3. On the Host PC, select any text file or print Test page from the printer properties and execute print command.
        4. MCU will receive the print command and start printing the data.
        5. The printer settings and printing data will be displayed on the J-Link RTT Viewer.


2. Hardware Requirement:

	1. RA MCU board
        2. 2x Micro usb cables
        3. Host System (Windows PC) with at least 2 USB ports

3. Hardware Connections:

 	Supported Board EK_RA6M5:		
	1. Connect RA board to Host PC machine using micro usb cable.
        2. Connect another cable to the High speed port of the RA MCU board.

4. Hardware settings for the project:
	
    Jumper Settings:
     	
	EK-RA6M5 (High Speed)
	1. Jumper J7: Connect pins 2-3
        2. Connect Jumper J17 pins
	3. Connect the micro USB end of the micro USB device cable to micro-AB USB High Speed 
	   port (J6) of the board. Connect the other end of this cable to USB port of the host PC.

NOTE:
1) Segger RTT block address may be needed to download and observe EP operation using a hex file with RTT-Viewer.
   RTT Block address for hex file committed in repository are as follows:
   a. e2studio: 0x20000214

