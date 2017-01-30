#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>

using namespace std;

//Separates the sign base from everything else!
//Checks to see if the - sign exists because if it does, the position is different.
char checkArgument(string number, bool sign){
	if(sign){
		return number[1];
	}
	else{
		return number[0];
	}
}

//Checks if minus exists. If it does, separates the rest by just number and everything else (sign, type).
bool minusExists(string &justNum, string userString){
	if(userString[0] == '-'){
		justNum = userString.substr(2);
		return true;
	}
	else{
		justNum = userString.substr(1);
		return false;
	}
}

//Checks for the operator!! * is included!
int checkOper(string oper){
	if(oper == "+"){
		return 1;
	}
	else if(oper == "-"){
		return 2;
	}
	else if(oper == "*"){
		return 3;
	}
	else
		return 0;
}

//Checks whether the input is binary. All numbers has to be 0 or 1
bool checkbinary(string binary){
	for(int i = 0; i < binary.length(); i++){
		if(!(binary[i] == '1' || binary[i] == '0')){
			return false;
		}
	}
	return true;
}

//Converts binary to decimal!
//Algorithm: If a position has 1 instead of 0,
//It's 2^position+1 added to the total.
int binToDec(string binaryN){
	int decimal = 0;
	for(int i = binaryN.length()-1; i >=0; i--){
		if(binaryN[i] == '1'){
			decimal = decimal + pow(2, (binaryN.length()-i-1));
		}
	}
	return decimal;
}

//Checks whether the input is octal. All numbers has to be from 0-7.
bool checkoctal(string octal){
	for(int i = 0; i < octal.length(); i++){
		if(!isdigit(octal[i])){
			return false;
		}
		else{
			if(octal[i] == '8' || octal[i] == '9'){
				return false;
			}
		}
	}
	return true;
}

//Converts octal to decimal.
//All numbers, regardless of value in that position, is multiplied by 8 and added.
int octToDec(string octN){
	int decimal = 0;
	for(int i = 0; i < octN.length(); i++){
		decimal *=8;
		decimal +=(octN[i] - '0');
	}
	return decimal;
}

//Checks if the input is a hex!
//All digits apply, but if it's not a digit, the only values allowed are from A-F.
bool checkhex(string hex){
	for(int i = 0; i < hex.length(); i++){
		if(!isdigit(hex[i])){
			if(!(hex[i] == 'A' || hex[i] == 'B' || hex[i] == 'C' || hex[i] == 'D' || hex[i] == 'E' || hex[i] == 'F' || hex[i] == 'a' || hex[i] == 'b' || hex[i] == 'c' || hex[i] == 'd' || hex[i] == 'e' || hex[i] == 'f')){
				return false;
			}
		}
	}
	return true;
}

//Converts hex to decimal!
//All digits apply and when it does, adds 16^position+1 * that number.
//If not a digit, then they each have their own value from A-F.
int hexToDec(string hexN){
	int decimal = 0;
	for(int i = hexN.length()-1; i >=0; i--){
		if(isdigit(hexN[i])){
			decimal += (hexN[i] - '0') * pow(16, (hexN.length()-i-1));
		}
		else{
			switch(hexN[i]){
				case 'A':
				case 'a':{
					decimal += 10 * pow(16, (hexN.length()-i-1));
					break;
				}
				case 'B':
				case 'b':{
					decimal += 11 * pow(16, (hexN.length()-i-1));
					break;
				}
				case 'C':
				case 'c':{
					decimal += 12 * pow(16, (hexN.length()-i-1));
					break;
				}
				case 'D':
				case 'd':{
					decimal += 13 * pow(16, (hexN.length()-i-1));
					break;
				}
				case 'E':
				case 'e':{
					decimal += 14 * pow(16, (hexN.length()-i-1));
					break;
				}
				case 'F':
				case 'f':{
					decimal += 15 * pow(16, (hexN.length()-i-1));
					break;
				}
				default:{
					cout << "Weird character base!" << endl;
					break;
				}
			}
		}
	}
	return decimal;
}

//Checks whether it's a decimal!
//All positions.. have to be a digit.
bool checkdecimal(string decimal){
	for(int i = 0; i < decimal.length(); i++){
		if(!isdigit(decimal[i])){
			return false;
		}
	}
	return true;
}

//Converts string to decimal!
//I didn't want to use stoi so I did it myself.
int strToDec(string strN){
	int decimal = 0;
	for(int i = 0; i < strN.length(); i++){
		if(!isdigit(strN[i])){
			return 0;
		}
		else{
			decimal = decimal * 10 + (strN[i] - '0');
		}
	}
	return decimal;
}

//Before operation, to make it easier, change everything to decimal!
int conversionToDec(string base, string justNum){
	int decimal = 0;
	if(base == "b"){
		if(checkbinary(justNum)){
			decimal = binToDec(justNum);
			return decimal;
		}
		else 
		{
			cout << "One of them not a binary." << endl;
			return 0;
		}
	}
	else if(base=="o"){
		if(checkoctal(justNum)){
			decimal = octToDec(justNum);
			return decimal;
		}
		else{
			cout << "One of them not an octal" << endl;
			return 0;
		}
	}
	else if(base=="d"){
		if(checkdecimal(justNum)){
			decimal = strToDec(justNum);
			return decimal;
		}
		else{
			cout << "One of them not a decimal" << endl;
			return 0;
		}
	}
	else if(base=="x"){
		if(checkhex(justNum)){
			decimal = hexToDec(justNum);
			return decimal;
		}
		else{
			cout << "One of them not a hex" << endl;
			return 0;
		}
	}
	else{
		cout << "Weird base!" << endl;
		return 0;
	}
}

//The calculation part after converted to decimal.
int calculator(string oper, int numero1, int numero2, bool sign1, bool sign2){
	int total = 0;
	int n1 = numero1;
	int n2 = numero2;
	if(sign1){
		n1 = n1*(-1);
	}
	if(sign2){
		n2 = n2*(-1);
	}
	if(oper == "+"){
		total = n1+n2;
	}
	else if(oper == "-"){
		total = n1-n2;
	}
	else if(oper == "*"){
		total = n1*n2;
	}
	else{
		cout << "Weird operator! Error." << endl;
	}
	return total;
}

//Convert dec to binary.
string decToBin(int decN){
	string binary;
	while(decN != 0){
		binary = (decN%2 == 0 ? "0":"1")+binary;
		decN/=2;
	}
	return binary;
}

//Convert dec to octal!
string decToOct(int decN){
	string octal;
	while(decN != 0){
		octal = to_string(decN%8)+octal;
		decN/=8;
	}
	return octal;
}

//Convert dec to hex.
string decToHex(int decN){
	string hex;
	while(decN != 0){
		if(decN%16 <= 9){
			hex = to_string(decN%16)+hex;
		}
		else{
			switch(decN%16){
				case 10:{
					hex = "A" + hex;
					break;
				}
				case 11:{
					hex = "B" + hex;
					break;
				}
				case 12:{
					hex = "C" + hex;
					break;
				}
				case 13:{
					hex = "D" + hex;
					break;
				}
				case 14:{
					hex = "E" + hex;
					break;
				}
				case 15:{
					hex = "F" + hex;
					break;
				}
				default:{
					cout << "Can't be here" << endl;;
				}
			}
		}
		decN/=16;
	}
	return hex;
}

//After operation, changes back to desired output base.
//If weird, then it will output the error.
string conversionFromDec(string base, int totalInDec){
	string totalInStr;
	if(base == "b"){
		totalInStr = decToBin(totalInDec);
		return totalInStr;
	}
	else if(base == "o"){
		totalInStr = decToOct(totalInDec);
		return totalInStr;
	}
	else if(base == "x"){
		totalInStr = decToHex(totalInDec);
		return totalInStr;
	}
	else if(base == "d"){
		totalInStr = to_string(totalInDec);
		return totalInStr;
	}
	else{
		cout << "Weird output base!" << endl;
		return "";
	}
}

int main(int argc, char**argv){
	//Declaration of all variables
	bool sign1, sign2; //False = positive, True = negative
	string n1 = argv[2];
	string n2 = argv[3];
	int DECn1, DECn2; //Decimal of n1 and n2.
	string base1, base2;

	sign1 = minusExists(n1, argv[2]);
	sign2 = minusExists(n2, argv[3]);
	base1 = checkArgument(argv[2], sign1);
	base2 = checkArgument(argv[3], sign2);
	DECn1 = conversionToDec(base1, n1);
	DECn2 = conversionToDec(base2, n2);
	int total = calculator(argv[1], DECn1, DECn2, sign1, sign2);
	string outputTotal = conversionFromDec(argv[4], total);
	if(outputTotal == ""){
		return 0;
	}
	if(total < 0){
		cout << "-" << argv[4] << outputTotal.substr(1) << endl;
	}
	else{
		cout << argv[4] << outputTotal << endl;
	}

	return 0;
}