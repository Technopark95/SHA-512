#include <iostream>
#include <sstream>
#include <bitset>
#include <cmath>
#include <conio.h>

typedef unsigned long long int int64;

using namespace std;



int64 Message[80];


const int64 Constants[80] = {
             0x428a2f98d728ae22 ,  0x7137449123ef65cd ,  0xb5c0fbcfec4d3b2f ,  0xe9b5dba58189dbbc ,
             0x3956c25bf348b538 ,  0x59f111f1b605d019 ,  0x923f82a4af194f9b ,  0xab1c5ed5da6d8118 ,
             0xd807aa98a3030242 ,  0x12835b0145706fbe ,  0x243185be4ee4b28c ,  0x550c7dc3d5ffb4e2 ,
             0x72be5d74f27b896f ,  0x80deb1fe3b1696b1 ,  0x9bdc06a725c71235 ,  0xc19bf174cf692694 ,
             0xe49b69c19ef14ad2 ,  0xefbe4786384f25e3 ,  0x0fc19dc68b8cd5b5 ,  0x240ca1cc77ac9c65 ,
             0x2de92c6f592b0275 ,  0x4a7484aa6ea6e483 ,  0x5cb0a9dcbd41fbd4 ,  0x76f988da831153b5 ,
             0x983e5152ee66dfab ,  0xa831c66d2db43210 ,  0xb00327c898fb213f ,  0xbf597fc7beef0ee4 ,
             0xc6e00bf33da88fc2 ,  0xd5a79147930aa725 ,  0x06ca6351e003826f ,  0x142929670a0e6e70 ,
             0x27b70a8546d22ffc ,  0x2e1b21385c26c926 ,  0x4d2c6dfc5ac42aed ,  0x53380d139d95b3df ,
             0x650a73548baf63de ,  0x766a0abb3c77b2a8 ,  0x81c2c92e47edaee6 ,  0x92722c851482353b ,
             0xa2bfe8a14cf10364 ,  0xa81a664bbc423001 ,  0xc24b8b70d0f89791 ,  0xc76c51a30654be30 ,
             0xd192e819d6ef5218 ,  0xd69906245565a910 ,  0xf40e35855771202a ,  0x106aa07032bbd1b8 ,
             0x19a4c116b8d2d0c8 ,  0x1e376c085141ab53 ,  0x2748774cdf8eeb99 ,  0x34b0bcb5e19b48a8 ,
             0x391c0cb3c5c95a63 ,  0x4ed8aa4ae3418acb ,  0x5b9cca4f7763e373 ,  0x682e6ff3d6b2b8a3 ,
             0x748f82ee5defb2fc ,  0x78a5636f43172f60 ,  0x84c87814a1f0ab72 ,  0x8cc702081a6439ec ,
             0x90befffa23631e28 ,  0xa4506cebde82bde9 ,  0xbef9a3f7b2c67915 ,  0xc67178f2e372532b ,
             0xca273eceea26619c ,  0xd186b8c721c0c207 ,  0xeada7dd6cde0eb1e ,  0xf57d4f7fee6ed178 ,
             0x06f067aa72176fba ,  0x0a637dc5a2c898a6 ,  0x113f9804bef90dae ,  0x1b710b35131c471b ,
             0x28db77f523047d84 ,  0x32caab7b40c72493 ,  0x3c9ebe0a15c9bebc ,  0x431d67c49c100d4c ,
             0x4cc5d4becb3e42b6 ,  0x597f299cfc657e2a ,  0x5fcb6fab3ad6faec ,  0x6c44198c4a475817
    };
  


int64 BintoDec (string bin)  {
	

    int64 value = bitset<64>(bin).to_ullong();
    
  
    return value ;
	
}


int64 rotate_right (int64 x , int n)  {
	
	
	
	return (x >> n) | (x << (64-n));
	
	
	
	
}


int64 shift_right (int64 x , int n)  {
	
	
	
	return (x >> n);
	
	
	
	
}



void seperator ( int64  storable[], string getBlock)  {
	
	int chunknum = 0;
	
	for (unsigned int i = 0; i < getBlock.length(); i += 64 ,++chunknum) {
		
    storable[chunknum] =  BintoDec(getBlock.substr(i, 64));


	
}

//extent 16 blocks to 80 by below operation:
for  (int g = 16 ; g < 80 ; ++g )   {
	
	
	
	int64 WordA = rotate_right( storable[g - 2],19) ^ rotate_right( storable[g - 2],61) ^ shift_right( storable[g - 2],6);
	int64 WordB = storable[g -7];
	int64 WordC = rotate_right( storable[g - 15],1) ^ rotate_right( storable[g - 15],8) ^ shift_right( storable[g - 15],7);
	int64 WordD = storable[g -16];
	
	int64 T = WordA+WordB+WordC+WordD;
	
	storable[g] = T;
	
	
}


	
	
}
  
  
  
int64 maj ( int64 a , int64 b , int64 c )    {
	
	
	
	
	return (a&b)^(b&c)^(c&a); 
	
}


int64 Ch ( int64 e , int64 f , int64 g )    {
	
	
	
	
	return (e&f)^(~e&g); 
	
}
  
  
int64 sigmaE (int64 e)  {
	
	
return rotate_right(e  , 14) ^ rotate_right(e  , 18) ^ rotate_right(e  , 41);
	
	
	
} 


int64 sigmaA (int64 a)  {
	
	
return rotate_right(a  , 28) ^ rotate_right(a  , 34) ^ rotate_right(a  , 39);
	
	
	
}   




  
void Func( int64 a , int64 b , int64 c , int64 &d , int64 e , int64 f , int64 g , int64 &h , int K)  {
	
	
	int64 T1 = h + Ch(e,f,g) + sigmaE(e) + Message[K] + Constants[K];
	
	int64 T2 = sigmaA(a) + maj(a,b,c);
	
	d = d + T1;
	
	h = T1 + T2;
	

}
  

  
  
int main ()  {
  	
  	
  	
  	int64 A = 0x6a09e667f3bcc908;
  	int64 B = 0xbb67ae8584caa73b;
  	int64 C = 0x3c6ef372fe94f82b;
  	int64 D = 0xa54ff53a5f1d36f1;
  	int64 E = 0x510e527fade682d1;
  	int64 F = 0x9b05688c2b3e6c1f;
  	int64 G = 0x1f83d9abfb41bd6b;
	int64 H = 0x5be0cd19137e2179;
	
	int64 AA,BB,CC,DD,EE,FF,GG,HH;
  	
  		
	stringstream fixedstream;
	
	string myString = "anoop";
  
  for (  int i = 0; i < myString.size(); ++i){
      fixedstream << bitset<8>(myString[i]);
  }
	
	string s1024;
	
	s1024 = fixedstream.str();
	
	  int orilen = s1024.length();
	  
	
	  int tobeadded;
	
		  int modded = s1024.length() % 1024;
	
	if (  1024 - modded  >= 128 ) {
		

	 tobeadded  =  1024 - modded;
	 

}

else	if (  1024 - modded  < 128 ) {
		
		
		tobeadded =  2048 - modded ;
	
	}
	

	
	s1024 += "1";
	
	
	 for(  int y = 0 ; y < tobeadded-129 ; y++) {
  	s1024 += "0";
  }
  
  
  
  
  string lengthbits = std::bitset<128>(orilen).to_string(); //to binary
  
    s1024 += lengthbits;
    

   
  	    
    int blocksnumber = s1024.length() / 1024 , chunknum=0;
    
    string  Blocks[blocksnumber];




   	for (  int i = 0; i < s1024.length(); i += 1024 ,++chunknum) {
		
    Blocks[chunknum] =  s1024.substr(i, 1024);
    


    
}



            


for (int letsgo = 0 ; letsgo < blocksnumber ; ++letsgo ) {
	

                
seperator(Message,Blocks[letsgo]);


 	AA = A;
 	BB = B;
 	CC = C;
 	DD = D;
 	EE = E;
 	FF = F;
 	GG = G;
 	HH = H;
 	
 	
 	
 	            Func(A,B,C,D,E,F,G,H,0);
                Func(H,A,B,C,D,E,F,G,1);
                Func(G,H,A,B,C,D,E,F,2);  
                Func(F,G,H,A,B,C,D,E,3);
                Func(E,F,G,H,A,B,C,D,4);
                Func(D,E,F,G,H,A,B,C,5);
                Func(C,D,E,F,G,H,A,B,6);
                Func(B,C,D,E,F,G,H,A,7);
			    Func(A,B,C,D,E,F,G,H,8);
                Func(H,A,B,C,D,E,F,G,9);
                Func(G,H,A,B,C,D,E,F,10);
                Func(F,G,H,A,B,C,D,E,11);
                Func(E,F,G,H,A,B,C,D,12);
                Func(D,E,F,G,H,A,B,C,13);
                Func(C,D,E,F,G,H,A,B,14);
                Func(B,C,D,E,F,G,H,A,15);
				Func(A,B,C,D,E,F,G,H,16);
                Func(H,A,B,C,D,E,F,G,17);
                Func(G,H,A,B,C,D,E,F,18);
                Func(F,G,H,A,B,C,D,E,19);
                Func(E,F,G,H,A,B,C,D,20);
                Func(D,E,F,G,H,A,B,C,21);
                Func(C,D,E,F,G,H,A,B,22);
                Func(B,C,D,E,F,G,H,A,23);                
                Func(A,B,C,D,E,F,G,H,24);
                Func(H,A,B,C,D,E,F,G,25);
                Func(G,H,A,B,C,D,E,F,26);
                Func(F,G,H,A,B,C,D,E,27);
                Func(E,F,G,H,A,B,C,D,28);
                Func(D,E,F,G,H,A,B,C,29);
                Func(C,D,E,F,G,H,A,B,30);
                Func(B,C,D,E,F,G,H,A,31);
                Func(A,B,C,D,E,F,G,H,32);
                Func(H,A,B,C,D,E,F,G,33);
                Func(G,H,A,B,C,D,E,F,34);
                Func(F,G,H,A,B,C,D,E,35);
                Func(E,F,G,H,A,B,C,D,36);
                Func(D,E,F,G,H,A,B,C,37);
                Func(C,D,E,F,G,H,A,B,38);
                Func(B,C,D,E,F,G,H,A,39);
                Func(A,B,C,D,E,F,G,H,40);
                Func(H,A,B,C,D,E,F,G,41);
                Func(G,H,A,B,C,D,E,F,42);
                Func(F,G,H,A,B,C,D,E,43);
                Func(E,F,G,H,A,B,C,D,44);
                Func(D,E,F,G,H,A,B,C,45);
                Func(C,D,E,F,G,H,A,B,46);
                Func(B,C,D,E,F,G,H,A,47);
                Func(A,B,C,D,E,F,G,H,48);
                Func(H,A,B,C,D,E,F,G,49);
                Func(G,H,A,B,C,D,E,F,50);
                Func(F,G,H,A,B,C,D,E,51);
                Func(E,F,G,H,A,B,C,D,52);
                Func(D,E,F,G,H,A,B,C,53);
                Func(C,D,E,F,G,H,A,B,54);
                Func(B,C,D,E,F,G,H,A,55);
                Func(A,B,C,D,E,F,G,H,56);
                Func(H,A,B,C,D,E,F,G,57);
                Func(G,H,A,B,C,D,E,F,58);
                Func(F,G,H,A,B,C,D,E,59);
                Func(E,F,G,H,A,B,C,D,60);
                Func(D,E,F,G,H,A,B,C,61);
                Func(C,D,E,F,G,H,A,B,62);
                Func(B,C,D,E,F,G,H,A,63);
                Func(A,B,C,D,E,F,G,H,64);
                Func(H,A,B,C,D,E,F,G,65);
                Func(G,H,A,B,C,D,E,F,66);
                Func(F,G,H,A,B,C,D,E,67);
                Func(E,F,G,H,A,B,C,D,68);
                Func(D,E,F,G,H,A,B,C,69);
                Func(C,D,E,F,G,H,A,B,70);
                Func(B,C,D,E,F,G,H,A,71);
                Func(A,B,C,D,E,F,G,H,72);
                Func(H,A,B,C,D,E,F,G,73);
                Func(G,H,A,B,C,D,E,F,74);
                Func(F,G,H,A,B,C,D,E,75);
                Func(E,F,G,H,A,B,C,D,76);
                Func(D,E,F,G,H,A,B,C,77);
                Func(C,D,E,F,G,H,A,B,78);
                Func(B,C,D,E,F,G,H,A,79);


    A += AA;
 	B += BB;
 	C += CC;
 	D += DD;
 	E += EE;
 	F += FF;
 	G += GG;
 	H += HH;




}

 
  	
  	
  	cout << hex << A << "" << B << "" << C << "" << D << "" << E << ""<< F<< "" << G<< "" <<H;
  	
  	

  	
}
  

