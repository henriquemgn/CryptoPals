#include<iostream>
#include<cstring>
#include <map>
#include <functional>
#include <vector>
#include <cassert>
#include "Mag.h"

using namespace std;


int main()
{
    mag::bytearray ba = mag::bytearray::from_hex("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    string hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    //mag::bytearray ba1 = mag::bytearray::from_hex("1c0111001f010100061a024b53535009181c");
    //mag::bytearray ba2 = mag::bytearray::from_hex("686974207468652062756c6c277320657965");

   // assert((ba1^ba2).to_hex() == "746865206b696420646f6e277420706c6179");

    //ba.decrypt();
    ba.decryptFile();
    ba.to_base64();
}
