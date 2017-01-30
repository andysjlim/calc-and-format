#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int hexa_to_deci(char * hexN){
	int decimal = 0;
	for(int i = strlen(hexN); i >=0; i--){
		if(isdigit(hexN[i])){
			decimal += (hexN[i] - '0') * pow(16, (strlen(hexN)-i-1));
		}
		else{
			switch(hexN[i]){
				case 'A':
				case 'a':{
					decimal += 10 * pow(16, (strlen(hexN)-i-1));
					break;
				}
				case 'B':
				case 'b':{
					decimal += 11 * pow(16, (strlen(hexN)-i-1));
					break;
				}
				case 'C':
				case 'c':{
					decimal += 12 * pow(16, (strlen(hexN)-i-1));
					break;
				}
				case 'D':
				case 'd':{
					decimal += 13 * pow(16, (strlen(hexN)-i-1));
					break;
				}
				case 'E':
				case 'e':{
					decimal += 14 * pow(16, (strlen(hexN)-i-1));
					break;
				}
				case 'F':
				case 'f':{
					decimal += 15 * pow(16, (strlen(hexN)-i-1));
					break;
				}
				default:{
					break;
				}
			}
		}
	}
	return decimal;
}