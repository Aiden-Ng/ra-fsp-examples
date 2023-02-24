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
	 
	This Example Project demonstrates CAN-FD operations on Renesas RA MCUs using 2 RA boards.
        On pressing any key on the RTTViewer(connected to any one of the 2 boards), data is transmitted from Board1 to Board2.
        On data reception, Board2 displays the received data on the RTTViewer and Board2 transmits updated data back to Board1 as an acknowledgment. 
        Board1 on reception of data, changes mode from CAN frame to CAN-FD frame and transmits data to board2.
        On reception, board2 transmits updated data back to board1 as an acknowledgment. On successful transmission and reception,
        Boards prints the transmitted & received data on to RTTViewer.

2. Hardware Connections:
       Require 2 RA boards to run the project

       Supported RA Boards: ek-ra6m5, ek-ra4e2, ek-ra6e2 
 
       EK_RA6M5:
       Short E33, E34 & E35 inorder to use onboard CAN Transreceivers 

       J33:1 of board 1 to J33:1 of board 2
       J33:2 of board 1 to J33:2 of board 2
       J33:3 of board 1 to J33:3 of board 2

       EK_RA4E2 / EK_RA6E2:
       
       J32:1 of board 1 to J32:1 of board 2
       J32:2 of board 1 to J32:2 of board 2
       J32:3 of board 1 to J32:3 of board 2

      Note:
      1. In this example project, the same code runs on both boards. The board from which the user initiates the transmission becomes the board1
      and board which receives the data becomes board2.
      2. User is expected to enter data of size not exceeding above 15 bytes.
       ﻿
1) Segger RTT block address may needed to download and observe EP operation using a hex file with RTT-Viewer.
   RTT Block address for hex file committed in repository are as follows:
   a. e2studio: 0x2000011c
   b. Keil: Not Available 
   c. IAR: Not Available
 
2) If an EP is modified, compiled, and downloaded please find the block address (for the variable in RAM called _SEGGER_RTT) 
   in .map file generated in the build configuration folder (Debug/Release).
