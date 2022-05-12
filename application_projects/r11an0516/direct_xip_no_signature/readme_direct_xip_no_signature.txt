Steps to run the example project in this folder:

1. Import projects to a workspace
2. Open the configuration.xml file from project ra_mcuboot_ra2e1_dxip
3. Click Generate Project Content
4. Overwrite bootutil.h and image.h (located in \direct_xip_no_signature\ra_mcuboot_ra2e1_dxip\ra\mcu-tools\MCUboot\boot\bootutil\include\bootutil) with the two files bootutil.h and image.h included in this folder.
5. Compile the project ra_mcuboot_ra2e1_dxip
6. Open the configuration.xml file from project blinky_primary
7. Click Generate Project Content
8. Compile the blinky_with_signature project
9. Open the configuration.xml file from project blinky_secondary
10. Click Generate Project Content
11. Compile the blinky_with_signature_new
12. Debug the application from project blinky_primary
13. Pause the debugging session 
14. Download the blinky_primary.bin.signed to address 0x2000
15. Resume the program execution, all leds should be clinking
16. Pause the execution
17. Download the blinky_secondary.bin.signed to address 0x4000
18. Resume the program execution, the blue led should be blinking
