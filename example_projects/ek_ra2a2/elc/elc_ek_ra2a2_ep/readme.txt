/***********************************************************************************************************************
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
* **********************************************************************************************************************/

1. Project Overview:
        The example project demonstrates the typical use of the ELC HAL module APIs.
        ELC Software Event, GPT8 and GPT9 events are linked using ELC. The start source for GPT8 and GPT9 is ELC Software Event and
        the stop source for GPT8 is GPT9 counter overflow. GPT8 runs in PWM mode and GPT9 runs in one-shot mode.
        On giving valid RTT input, an ELC Software Event is generated that triggers LED blinking.
        LED stops blinking after 5 sec when GPT9 expires.
		
2. Hardware Settings:
    	Hardware Connection
 
    	For EK-RA2L1:
   	Connect P414(J1 Pin 04) --> P505(J3 Pin 06)

    	For EK-RA2E1:
    	Connect P212 to P913 (User LED3)﻿

    	For EK-RA6M5:
    	Connect P414(J1 Pin 32) to P006 (J4-28)

    	For FPB-RA4E1:
    	Connect P104 (J4 Pin 21) -–> P407 (J3 Pin 25) (LED2) 

    	For FPB-RA2E3:
    	Connect P102(J4 Pin 10) to P213 (J3 Pin 7) (LED1)

    	For EK-RA2A2:
    	Connect P105(J4 Pin 16) to P307 (J3 Pin 16) (LED1)

Note:
1) Segger RTT block address may be needed to download and observe EP operation using a hex file with RTT-Viewer.
   RTT Block address for hex file committed in repository are as follows:
   a. e2studio: 0x2000044c
   b. Keil: 	Not Available 
   c. IAR: 	Not Available
 
2) If an EP is modified, compiled, and downloaded please find the block address (for the variable in RAM called _SEGGER_RTT) 
   in .map file generated in the build configuration folder (Debug/Release).
