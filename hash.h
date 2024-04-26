#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }



    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        int big = k.size();

      if (big == 0)
      {
          return 0;
      }

      HASH_INDEX_T newVal[big];
     
      for (int l = 0; l < big; ++l) {
        
        newVal[l] = letterDigitToNumber(k[l]); 
        //std::cout << "character: " << newVal[l] << std::endl;
    }


      HASH_INDEX_T nVal[5] = {0, 0, 0, 0, 0};

      int fullSubstrings = big / 6;
      //std::cout << "full : " << fullSubstrings << std::endl;
      int remainingChars = big % 6;
      //std::cout << "REM: " << remainingChars << std::endl;

      //HASH_INDEX_T holdVal[6] = {0};

      int endString;
      int startString;


      //hold the pow values
      double thirtySixPow[6] = {1, 36, 1296, 46656, 1679616, 60466176};
      unsigned long long substringValue = 0;
      HASH_INDEX_T hashResult = 0;

   
    if(fullSubstrings > 0)
    {
      for (int i = 0; i < fullSubstrings; i++)
        {
            substringValue = 0; 
            int p = 0; 


              endString = big - 1;
              startString = endString - 5;
            for (int j = endString; j >= startString; j--)
            {
                substringValue += thirtySixPow[p] * newVal[j];
                //std::cout << "VALUE: " << substringValue << std::endl;
                p++; 
            }
            
          
            nVal[4-i] = substringValue;
            //std::cout << "N_ARRAY VALUE: " << nVal[i] << std::endl;

            // Update indices for the next substring
            big -= 6;
            //endString = startString - 1;
            // std::cout << "END VALUE: " << endString << std::endl;
            // startString = endString - 5;
            // std::cout << "START VALUE: " << startString << std::endl;
        }




        if (remainingChars > 0)
      {
          HASH_INDEX_T substringValue = 0;
          int y = 0; 
          
          endString = remainingChars - 1;
          // startString = endString - 5;
          for (int j = endString; j >= 0; j--)
          {
              
              substringValue += thirtySixPow[y] * newVal[j];
              y++; 
          }

          nVal[4-fullSubstrings] = substringValue;
          hashResult += substringValue;
      }
    }





          else if (remainingChars > 0)
      {
        
          HASH_INDEX_T substringValue = 0;
          int y = 0; 
          
          endString = remainingChars - 1;
          // startString = endString - 5;
          for (int j = endString; j >= 0; j--)
          {
              
              substringValue += thirtySixPow[y] * newVal[j];
              //std::cout << substringValue << std::endl;
              y++; 
          }

          nVal[4] = substringValue;
          hashResult += substringValue;
      }








//hashing them with the r one
    hashResult = 0;
    for (int i = 0; i < 5; ++i)
    {
      //std::cout << "new values " << nVal[i] << std::endl; 
        hashResult += rValues[i] * nVal[i];
    }

    return hashResult;

}



    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char go = tolower(letter);
       
        if(isalpha(letter))
        {
          return go - 'a';
        }
        else if(isdigit(letter))
        {
          return letter - '0' + 26;
        } 
        else
        {
          return letter;
        }     

    }


    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
