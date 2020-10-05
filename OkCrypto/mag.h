#ifndef BYTEARRAY_HPP
#define BYTEARRAY_HPP
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <cstddef>
#include <iomanip>
#include <fstream>

namespace mag
{
  class bytearray
  {
  private:
    std::vector<uint8_t> _values;

    void push_back(const uint8_t& val) {
      _values.push_back(val);
    }


  public:

    static bytearray from_hex(const std::string& val)

    {
        bytearray ba;
        for(size_t i = 0; i < val.size(); i+=2){
               const std::string h = "0123456789abcdef";
               char rep = val[i];
               char rep1 = val[i+1];

               int a = h.find_first_of(rep);
               int b = h.find_first_of(rep1);

               int sum = a * 16 + b;

               ba.push_back(sum);
        }
        return ba;
    }

    std::string to_base64()
    {
        int _valueslength = _values.size();
        int digit1 = 0;
        int digit2 = 0;
        int digit3 = 0;
        int digit4 = 0;
        std::string final64;

        std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        for(int i = 0; i < _valueslength; i+=3){
            digit1= digit2= digit3= digit4 = 0;
            digit1 =_values[i] >> 2; // adds 2 zeroes to the left so that the first 6 values are the ones taken
            digit2 = ((_values[i] & 0x3) << 4 )| (_values[i+1] >> 4); // getting last 2 digits and moving them, and then moving to get the first 4 digits
            digit3 = ((_values[i+1] & 15) << 2)| (_values[i+2] >> 6);
            digit4 = (_values[i+2] & 0x3F);

            final64 += base64[digit1];
            final64 += base64[digit2];
            final64 += base64[digit3];
            final64 += base64[digit4];
        }

        return final64;
    }

    std::string to_hex()
    {
        int _valueslength = _values.size();
        int digit1 = 0;
        int digit2 = 0;
        std::string finalhex;

        std::string hex = "0123456789abcdef";
        for(int i = 0; i < _valueslength; i+=1){
            digit1= digit2 = 0;

            digit1 =_values[i] >> 4;
            digit2 = _values[i] & 15;

            finalhex += hex[digit1];
            finalhex += hex[digit2];

       // std::cout << finalhex << "\n";
        }
        return finalhex;
    }

    std::string decryptFile(){

        std::string textTest;
        std::ifstream MyReadFile;
        MyReadFile.open("/Users/henri/OneDrive/Documentos/OkCrypto/4.txt");

        while (getline (MyReadFile, textTest)) {
                int textTestlength = textTest.size();
                std::string textResult;
                std::map<char,int> CurrentMap;
                std::map<char,int> NewMap;

                for(int key =97; key <= 122; key++){
                        for (int i=0; i < textTestlength; i++){
                            textResult += textTest[i]^key;
                            char UpperChar = toupper(textResult[i]);

                            if (CurrentMap.count(UpperChar == 0)){
                                CurrentMap[UpperChar] = 1;
                            }
                            else{
                                CurrentMap[UpperChar] += 1;
                            }

                            for (auto it = CurrentMap.begin(); it != CurrentMap.end(); it++){
                                  char val1 = it -> first;
                                  int val2 = it -> second;
                                  std::cout << val1 << " " << val2 << "\n";
                                }CurrentMap.clear();

                        } std::cout << "\n ";

                    }
                 }MyReadFile.close();
              return "1";
             }

    std::string decrypt(){


        std::string result;
        int _valueslength = _values.size();


        for(int key =97; key <= 122; key++){

            for(int i = 0; i < _valueslength; i++ ){
                result +=_values[i]^key;

                if (((std::isalnum(result[i]) == false)) && ((std::isspace(result[i]) == false) && (std::iscntrl(result[i]) == false))){
                    //std::cout << result<<" - " <<result[i]<< " " << static_cast<int>(result[i]) << "\n";
                    result = "";

                    break;
                }
            }

            if(result != ""){
                std::cout << "With key: " << key <<" \nresult: " << result << "\n";
                return result;
                result = "";
            }
        }
                return "error";
    }



    bytearray& operator^=(const bytearray& rhs)
    {
        int _valueslength = _values.size();

        for(int i=0; i < _valueslength; i++){
            _values[i]^=rhs._values[i];
        }

      // actual addition of rhs to *this
      return *this;
    }
  };
  inline bytearray operator^(bytearray lhs, const bytearray& rhs)
  {
    lhs ^= rhs;
    return lhs;
  }


}

#endif
