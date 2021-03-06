/*
* demo-memory-int.cpp
*
*  Created on: 12 June 2017
*
*      compile with "g++ ABE_RTCPi.cpp demo-memory-int.cpp -o demo-memory-int"
*      run with "./demo-memory-int"
*
*  This demo shows how to write to and read from the internal battery backed memory on the DS1307 RTC chip
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "ABE_RTCPi.h"


int main(int argc, char **argv) {

	using namespace ABElectronics_CPP_Libraries;

	RTCPi rtc;

	int inval = 6254; // declare the input value

	printf("Number written to SRAM: %d\n", inval);

	unsigned char bytearray[sizeof(inval)]; // byte array to be stored in the RTC SRAM

	int a = 0;

	for (a = 0; a <= sizeof(inval); a++) {
		bytearray[a] = (inval >> a * 8) & 0xFF;
	}

	rtc.write_memory(0x08, bytearray); // write the byte array to the RTC SRAM
	
	
	int outval = 0; // declare the output value

	// read the RTC SRAM into a 4 byte array.  
	// The array is allocated by the rtc_read_memory function, use a pointer to point to the memory location of this array.
	unsigned char *readarray = rtc.read_memory(0x08, sizeof(inval));

	for (a = 0; a <= sizeof(outval); a++) { // convert the bytes from the readarray into a number
		outval |= readarray[a] << (a * 8);
	}

	free(readarray); // free the memory allocated to readarray

	printf("Number read from SRAM: %d", outval);

	return (0);
}
