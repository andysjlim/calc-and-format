#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>

using namespace std;

//The first bit indicates the negative.
//The algorithm is as followed:
//For every bits except the first one, if the bit is "1",
//The total number is added by 2^(position of that one).
//The last one, if it's 1, is subtracted from that.
//Else, it is added like normal.
string IntentionalSequence(string sequence){
	int intentionalint;
	for(int i =31; i >=0;i--){
		if(i ==0){
			if(sequence[i] == '1'){
				intentionalint -= pow(2,31);
			}
		}
		else{
			if(sequence[i] == '1'){
			intentionalint += pow(2,31-i);
			}
		}
	}
	string intentionalstring = to_string(intentionalint);
	return intentionalstring;
}

//All numbers have to be represented in scientific notation.
//Negative number cannot be inputted here because the sign bit is not included.
//Just the mantissa * exponent is included here.
//To get to the single digit precision,
//For numbers > 1, divide by 10 until number is <10 && >0.
//For each time the number is divided, the exponent should be increased.
//For numbers < 1 && > 0, multiply by 10 until number is <1 and >0.
//Then the exponent is the number of times multiplied * -1.
//If all doesn't fit, it's a 0, thus notated by 0.0e0.
string sciExpress(double total){
	double temp = total;
	int actualexponent=0;
	string sci; 
	if(temp >1){
		while(!(temp < 10 && total > 0)){
			temp /= 10;
			actualexponent++;
		}
		sci = to_string(temp) + "e"+to_string(actualexponent);
		return sci;
	}
	else if(temp < 1 && temp > 0){
		while(!(temp >1)){
			temp *= 10;
			actualexponent++;
		}
		sci = to_string(temp)+"e-"+to_string(actualexponent);
		return sci;
	}
	else {
		return "0.0e0";
	}
}

//Everything is divided by sign, mantissa, and exponent.
//Sign == (-1)^sign.
//Exponent == 8-bit binary representation in decimal.
//Mantissa == 2^-(position+1) There is an imaginary 1 in the front so adds.
//Exponent * Mantissa = number regardless of sign.
//Exponent * Mantissa * sign = actual number.
//Returns the scientific expression of that number as indicated above function.
string FloatingSequence(string sequence){
	string strsign = sequence.substr(0,1);
	int intsign = strsign[0] - '0';
	string strexponent = sequence.substr(1,8);
	int intexponent = 0;
	for(int i = strexponent.length()-1; i>=0; i--){
		if(strexponent[i] == '1'){
		intexponent += pow(2, (strexponent.length()-i-1));
	}
	}
	intexponent -= 127;
	string strmantissa = sequence.substr(9);
	double intmantissa = 0.0;
	for(int i = 0; i < strmantissa.length(); i++){
		if(strmantissa[i] == '1'){
		//cout << intmantissa << " <-- before adding" << endl;
		intmantissa += pow(2, -(i+1));
		//cout << intmantissa << " <-- After adding 2 ^-" << i << endl;
		}
	}
	if(intmantissa != 0){
		intmantissa += 1;
	}

	long total =  pow(2, intexponent) * intmantissa;
	string strtotal;
	strtotal = sciExpress(total);
	printf("%ld\n", total);
	if(intsign == 1){
		return "-"+strtotal;
	}
	else{
		return strtotal;
	}

}

//Reiterates functions depending on the output type.
//If neither, returns error messages.
string conversion(string sequence, string type){
	if(type =="int"){
		return IntentionalSequence(sequence);
	}
	else if(type =="float"){
		return FloatingSequence(sequence);
	}
	else{
		cout << "Weird output type!!";
		return "";
	}
}

//Checks whether the binary number is right!!
bool cheker(string binary){
	if(binary.length() != 32){
		return false;
	}
	for(int i = 0; i < 32; i++){
		if(!(binary[i] == '1' || binary[i] == '0')){
			return false;
		}
	}
	return true;
}

int main(int argc, char**argv){
	bool checker = cheker(argv[1]);
	if(checker){	
		string output = conversion(argv[1], argv[2]);
		cout << output;
	}
	else{
		cout << "Weird binary input!";
	}
	return 0;
}