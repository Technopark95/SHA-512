#include <iostream>
#include <sstream>
#include <bitset>
#include <cmath>
#include <conio.h>

using namespace std;

  unsigned int Message[80];
  
  
 string gethex(string bin)   {
 	
 	if (bin == "0000") return "0";
 	if (bin == "0001") return "1";
 	if (bin == "0010") return "2";
 	if (bin == "0011") return "3";
 	if (bin == "0100") return "4";
 	if (bin == "0101") return "5";
 	if (bin == "0110") return "6";
 	if (bin == "0111") return "7";
 	if (bin == "1000") return "8";
 	if (bin == "1001") return "9";
 	if (bin == "1010") return "a";
 	if (bin == "1011") return "b";
 	if (bin == "1100") return "c";
 	if (bin == "1101") return "d";
 	if (bin == "1110") return "e";
 	if (bin == "1111") return "f";
 		
 } 
  
string bintohex (unsigned int deci) {
  	
  	
  	string EQBIN = bitset<32>(deci).to_string();
  	
  	
 string hexstring = "";
 
 string temp ;
 
	for (unsigned int i = 0; i < EQBIN.length(); i += 4) {
		
    temp = EQBIN.substr(i, 4);

    hexstring += gethex(temp);
 	
 	
}

return hexstring;

 
  	
}
  

unsigned   int BintoDec (string bin)  {
	

    unsigned   int value = bitset<32>(bin).to_ullong();
    
  
    return value ;
	
}

unsigned    int rotate_left(unsigned   int x , unsigned   int n) {
	
	
	return (x << n) | (x >> (32-n));
}





void seperator ( unsigned int  storable[], string getBlock)  {
	
	int chunknum = 0;
	
	for (unsigned int i = 0; i < getBlock.length(); i += 32 ,++chunknum) {
		
    storable[chunknum] =  BintoDec(getBlock.substr(i, 32));

    
}

//extent 16 blocks to 80 by below operation:
for  (int g = 16 ; g < 80 ; ++g )   {
	
	
	
	unsigned int WordA = storable[g -3];
	unsigned int WordB = storable[g -8];
	unsigned int WordC = storable[g -14];
	unsigned int WordD = storable[g -16];
	
	unsigned int AxorBxorCxorD = WordA^WordB^WordC^WordD;
	
	
	unsigned int rotatedXORednewword = rotate_left(AxorBxorCxorD,1);
	
	
	storable[g] = rotatedXORednewword;
	
}
	
	
}


unsigned   int F (unsigned    int B , unsigned    int C ,   unsigned   int D)  {
	
	
	return (B&C) | ( ~B & D);
	
	
	
}

unsigned   int G (unsigned   int B , unsigned   int C ,  unsigned   int D)  {
	
	
	return B^C^D;
	
	
	
}



unsigned   int H (unsigned   int B , unsigned   int C ,  unsigned   int D)  {
	
	
	return (((B&C) | (B & D)) | (C&D));
	
	
	
}




unsigned   int I (unsigned   int B , unsigned   int C ,  unsigned   int D)  {
	
	
	return B^C^D;
	
	
	
}




void  FF (unsigned   int a , unsigned   int &b ,unsigned   int c , unsigned   int d ,   unsigned int &e, unsigned int p  ){

	
	unsigned int MessagedDecimal = Message[p];

	e = ( (((rotate_left(a,5) + F(b,c,d)) + e) + 0x5a827999) + MessagedDecimal);
	
    b = rotate_left(b,30);
	
	
	
}


void  GG (unsigned   int a , unsigned   int &b ,unsigned   int c , unsigned   int d  , unsigned int &e, unsigned int p  ){
	
	unsigned int MessagedDecimal = Message[p];

	e = ( (((rotate_left(a,5) + G(b,c,d)) + e) + 0x6ed9eba1) + MessagedDecimal);
	
    b = rotate_left(b,30);
	
	
	//0x6ed9eba1
	
	
}



void  HH (unsigned   int a , unsigned   int &b ,unsigned   int c , unsigned   int d ,unsigned int &e, unsigned int p ){
	
	
	 unsigned int MessagedDecimal = Message[p];
	
	e = ( (((rotate_left(a,5) + H(b,c,d)) + e) + 0x8f1bbcdc) + MessagedDecimal);
	
    b = rotate_left(b,30);
	
	
	
	//0x8f1bbcdc
}



void II (unsigned   int a , unsigned   int &b ,unsigned   int c , unsigned   int d , unsigned int &e, unsigned int p){
	
	
	unsigned int MessagedDecimal = Message[p];
	
	e = ( (((rotate_left(a,5) + I(b,c,d)) + e) + 0xca62c1d6) + MessagedDecimal);
	
    b = rotate_left(b,30);
	
	
	
	//0xca62c1d6
	
}





 string  SHA1 (string myString)   {
 	
 	

 
     unsigned   int A = 0x67452301;
     unsigned   int B = 0xefCDAB89;
     unsigned   int C = 0x98BADCFE;
     unsigned   int D = 0x10325476;
     unsigned   int E = 0xC3D2E1F0;
    
	  unsigned int AA ,BB,CC,DD ,EE;
    
    

	
	stringstream fixedstream;
	
  
  for (  int i = 0; i < myString.size(); ++i){
      fixedstream << bitset<8>(myString[i]);
  }
	
	string s512;
	
	s512 = fixedstream.str();
	
	  int orilen = s512.length();
	
	  int tobeadded;
	
		  int modded = s512.length() % 512;
	
	if (  512 - modded  >= 64 ) {
		

	 tobeadded  =  512 - modded;
	 

}

else	if (  512 - modded  < 64 ) {
		
		
		tobeadded =  1024 - modded ;
	
	}
	
	
	s512 += "1";
	
	
	 for(  int y = 0 ; y < tobeadded-65 ; y++) {
  	s512 += "0";
  }
  
  
  
  
  string lengthbits = std::bitset<64>(orilen).to_string(); //to binary
  
    s512 += lengthbits;
    

    
    int blocksnumber = s512.length() / 512 , chunknum=0;
    
    string  Blocks[blocksnumber];


   	for (  int i = 0; i < s512.length(); i += 512 ,++chunknum) {
		
	
    Blocks[chunknum] =  s512.substr(i, 512);
    
    
    
}





    
   
for (int letsgo = 0 ; letsgo < blocksnumber ; ++letsgo ) {
	


    seperator(Message ,Blocks[0]);
    
    
for (  int i = 0; i < 80 ;++i) {
		
	
  cout << i<< "   "<< Message[i] <<endl;
    
    
    
}
  
    AA =A;
    BB =B;
    CC =C;
    DD =D;
    EE =E;
      
  
    FF(A,B,C,D,E,0);
    FF(E,A,B,C,D,1);
    FF(D,E,A,B,C,2);
    FF(C,D,E,A,B,3);
    FF(B,C,D,E,A,4);
    FF(A,B,C,D,E,5);
    FF(E,A,B,C,D,6);
    FF(D,E,A,B,C,7);
    FF(C,D,E,A,B,8);
    FF(B,C,D,E,A,9);
    FF(A,B,C,D,E,10);
    FF(E,A,B,C,D,11);
    FF(D,E,A,B,C,12);
    FF(C,D,E,A,B,13);
    FF(B,C,D,E,A,14);
    FF(A,B,C,D,E,15);
    FF(E,A,B,C,D,16);
    FF(D,E,A,B,C,17);
    FF(C,D,E,A,B,18);
    FF(B,C,D,E,A,19);
   
    
    //Round 2
    GG(A,B,C,D,E,20);
     
    GG(E,A,B,C,D,21);
    GG(D,E,A,B,C,22);
    GG(C,D,E,A,B,23);
    GG(B,C,D,E,A,24);
    GG(A,B,C,D,E,25);
    GG(E,A,B,C,D,26);
    GG(D,E,A,B,C,27);
    GG(C,D,E,A,B,28);
    GG(B,C,D,E,A,29);
    GG(A,B,C,D,E,30);
    GG(E,A,B,C,D,31);
    GG(D,E,A,B,C,32);
    GG(C,D,E,A,B,33);
    GG(B,C,D,E,A,34);
    GG(A,B,C,D,E,35);
    GG(E,A,B,C,D,36);
    GG(D,E,A,B,C,37);
    GG(C,D,E,A,B,38);
    GG(B,C,D,E,A,39);
    
    
    
    //Round 3
    HH(A,B,C,D,E,40);
    HH(E,A,B,C,D,41);
    HH(D,E,A,B,C,42);
    HH(C,D,E,A,B,43);
    HH(B,C,D,E,A,44);
    HH(A,B,C,D,E,45);
    HH(E,A,B,C,D,46);
    HH(D,E,A,B,C,47);
    HH(C,D,E,A,B,48);
    HH(B,C,D,E,A,49);
    HH(A,B,C,D,E,50);
    HH(E,A,B,C,D,51);
    HH(D,E,A,B,C,52);
    HH(C,D,E,A,B,53);
    HH(B,C,D,E,A,54);
    HH(A,B,C,D,E,55);
    HH(E,A,B,C,D,56);
    HH(D,E,A,B,C,57);
    HH(C,D,E,A,B,58);
    HH(B,C,D,E,A,59);
    
    
    
    //Round 4
    II(A,B,C,D,E,60);
    II(E,A,B,C,D,61);
    II(D,E,A,B,C,62);
    II(C,D,E,A,B,63);
    II(B,C,D,E,A,64);
    II(A,B,C,D,E,65);
    II(E,A,B,C,D,66);
    II(D,E,A,B,C,67);
    II(C,D,E,A,B,68);
    II(B,C,D,E,A,69);
    II(A,B,C,D,E,70);
    II(E,A,B,C,D,71);
    II(D,E,A,B,C,72);
    II(C,D,E,A,B,73);
    II(B,C,D,E,A,74);
    II(A,B,C,D,E,75);
    II(E,A,B,C,D,76);
    II(D,E,A,B,C,77);
    II(C,D,E,A,B,78);
    II(B,C,D,E,A,79);
    
     A = A + AA;
     B = B + BB;
     C = C + CC;
     D = D + DD;
     E = E + EE;
     
     

}

  stringstream output;
  

output <<bintohex(A) << bintohex(B) <<bintohex(C)<<bintohex(D)<<bintohex(E);


    return output.str();
	
}


int main ()  {
	
	
	  
  cout << "Enter Message : ";
  

 cout<< SHA1("anoop");
	
}
