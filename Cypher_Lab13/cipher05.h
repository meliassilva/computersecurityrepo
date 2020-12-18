/********************************************************************
* Header:
*    Affine Cipher
********************************************************************/
#ifndef CIPHER05_H
#define CIPHER05_H

#include <map>
#include <cassert>
#include "cipher.h"

#define ASCII_FIRST 32
#define ASCII_LAST 126

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher05 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Caleb S. Fullmer"; }
   virtual std::string getCipherName() { return "Affine Cipher"; }
   virtual std::string getEncryptAuth() { return "Ethan Picklesimer"; }
   virtual std::string getDecryptAuth() { return "Manahari Dahal"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string citation = "";
      citation += "Resources which describe the requirements of the affine cipher.\n";
      citation += "    \"Affine Cipher,\" http://practicalcryptography.com/. Available: http://practicalcryptography.com/ciphers/affine-cipher/ \n";
      citation += "    \"Affine Cipher History and Description,\" University of Rhode Island. Available: Available: https://www.cs.uri.edu/cryptography/classicalaffine.htm \n";
      citation += "    \"Affine Ciphers,\" Arizona State University. Available: https://math.asu.edu/sites/default/files/affine.pdf   \n\n";
      citation += "Resources which describe the extended gcd algorithm and getting\n";
      citation += "the modular multiplicative inverse.\n";
      citation += "    \"The Euclidean Algorithm and Multiplicative Inverses,\" University of Utah. Available: https://www.math.utah.edu/~fguevara/ACCESS2013/Euclid.pdf \n";
      citation += "    John Bowers, \"Extended Euclidean Algorithm Example,\" uploaded to YouTube. Available: https://www.youtube.com/watch?v=6KmhCKxFWOs \n\n";
      citation += "These resources give C++ implementations of the gcd and extended gcd\n";
      citation += "to get modular multiplacitive inverse. These implementations were used\n";
      citation += "because our attempted implementation failed.\n";
      citation += "    Samual Sam, \"C++ Program to Find GCD,\" https://www.tutorialspoint.com/. Available: https://www.tutorialspoint.com/cplusplus-program-to-find-gcd \n";
      citation += "    \"Modular multiplicative inverse,\" https://www.geeksforgeeks.org/. Available: https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/ \n\n";
      citation += "These resources document the use of the C++ map data type and were helpful\n";
      citation += "for implementing maps in our functions.\n";
      citation += "    \"std::map,\" http://www.cplusplus.com/. Available: http://www.cplusplus.com/reference/map/map/ \n";
      citation += "    \"Map in C++ Standard Template Library (STL),\" https://www.geeksforgeeks.org/. Available: https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/ \n";
      citation += "    \"C++ : How to Initialize a map in one line using initialzer_list ?,\" https://thispointer.com/. Available: https://thispointer.com/how-to-initialize-a-map-with-stdinitialzer_list/ \n\n\n";
      return citation;
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;
      
      str = "// For mapping chars to numbers.\n\n";
      
      str +=  "// Map char keys to number values. Maps chars in alphabet to numbers\n";
      str += "// between 0 and numChars (where numChars is the number of characters in the\n)";
      str += "// alphabet minus 1.)\n";
      str += "https://thispointer.com/how-to-initialize-a-map-with-stdinitialzer_list/ \n";
      str += "PRIVATE STATIC CONST charsToNums <- {{char, int}, {char, int}, ..., {char, int}};\n\n";
      
      str += "// Map number keys to char values. Inverse of previous map.";
      str += "PRIVATE STATIC CONST numsToChars <- {{int, char}, {int, char}, ..., {int, char}}\n\n";
      
      str += "ASSERT charsToNums.size == numToChars.size\n\n\n\n";

      // TODO: please format your pseudocode
      // The encrypt pseudocode
      str += "Encryption Pseudocode:\n";
      str += "/****************************************\n";
      str += "* gcd(m n)\n";
      str += "* computes the greatest common denominator\n";
      str += "* of m and n.\n";
      str += "* https://www.tutorialspoint.com/cplusplus-program-to-find-gcd \n";
      str += "*****************************************/\n";
      str += "PRIVATE integer gcd(m n)                   \n";
      str += "   IF n > m                                \n";
      str += "      temp = m                             \n";
      str += "      m = n                                \n";
      str += "      n = temp                             \n";
      str += "   IF m % n == 0                           \n";
      str += "      RETURN n                             \n";
      str += "   RETURN gcd(n, m % n)                    \n\n\n";
      
      str += "/****************************************\n";
      str += "* getA(password, alphabetSize)\n";
      str += "* Gets the value 'a' required for the\n";
      str += "* encryption. 'a' must be coprime to the\n";
      str += "* size of the alphabet.\n";
      str += "*****************************************/\n";
      str += "PRIVATE integer getA(password)                  \n";
      str += "   IF password.size == 0                          \n";
      str += "      RETURN 0                                    \n";
      str += "   a = charToNum[password[0]] + 1                 \n";
      str += "   IF password.size > 1                           \n";
      str += "      a += charToNum[password[password.size - 1]] \n";
      str += "   WHILE gcd(a, charToNum.size) != 1              \n";
      str += "      a++                                         \n";
      str += "      IF a < 1                                     \n";
      str += "         a = 1                                     \n";
      str += "   RETURN a                                    \n\n\n";
      
      str += "/*****************************************\n";
      str += "* convertPassToB(password, a)\n";
      str += "******************************************/\n";
      str += "PRIVATE integer convertPassToB(password, a)  \n";
      str += "   IF password.size == 0                      \n";
      str += "      RETURN 0                                 \n";
      str += "   b = 0                                      \n";
      str += "   FOR letter in password                     \n";
      str += "      b += charToNum[letter] + 1               \n";
      str += "   // Attempt to add more randomness and variation to password.\n";
      str += "   b *= (password.size / 2) + 1                 \n";
      str += "   b -= a / password.size                        \n";
      str += "   RETURN b                                  \n\n\n";
      
      str += "/*****************************************\n";
      str += "* convertMessageToCipher(message)\n";
      str += "******************************************/\n";
      str += "PUBLIC string encrypt(plainText, password)      \n";
      str += "   cipherText = ""                                     \n";
      str += "   a = getA(password)                               \n";
      str += "   b = convertPassToB(password, a)                  \n";
      str += "   FOR letter in plainText                          \n";
      str += "      cipher += numToChar[((a * charToNum[letter]) + b) % charToNum.size]\n";
      str += "   RETURN cipherText                            \n\n\n\n";
         
      // The decrypt pseudo 
      str += "Decryption Pseudocode";
      str += "/*****************************************\n";
      str += "* getAInverse(a)\n";
      str += "******************************************/\n";
      str += "PRIVATE integer gcdExtend(a, m, *x, *y)          \n";
      str += "   // Use the implementation from https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/ \n";
      str += "   // It is in the C implementation for method 2.  \n";
      str += "   IF a == 0                                     \n";
      str += "      *x = 0                                     \n";
      str += "      *y = 1                                     \n";
      str += "      RETURN m                                   \n";
      str += "   x1                                            \n";
      str += "   y1                                            \n";
      str += "   gcd = gcdExtend(m % a, a, &x1, &y1)           \n";
      str += "   *x = y1 - (b / a) * x1                        \n";
      str += "   *y = x1                                   \n\n\n";
      
      str += "/******************************************\n";
      str += "* modInverse(a, m)\n";
      str += "* Note: Must return integer pointer/array\n";
      str += "*******************************************/\n";
      str += "PRIVATE integer modInverse(a, m)    \n";
      str += "   // Use the implementation from https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/ \n";
      str += "   // It is in the C implementation for method 2.  \n";
      str += "   x                                          \n";
      str += "   y                                          \n";
      str += "   g = gcdExtend(a, m, &x, &y)                \n";
      str += "   IF g != 1                                  \n";
      str += "      RETURN 0                                \n";
      str += "   ELSE                                       \n";
      str += "      // This equation accounts for instances where x is negative. \n";
      str += "      RETURN (x % m + m) % m              \n\n\n";
      
      str += "/*****************************************\n";
      str += "* decrypt(cipherText, password)\n";
      str += "******************************************/\n";
      str += "PUBLIC string decrypt(cipherText, password)    \n";
      str += "   plainText = ""                                   \n";
      str += "   a = getA(password)                               \n";
      str += "   b = convertPassToB(password, a)                  \n";
      str += "   aInverse = modInverse(a, charToNum.size)         \n";
      str += "   FOR letter in cipherText                         \n";
      str += "      tempVal = (aInverse * (charToNum[letter] + charToNum.size() - b)) \n";
      str += "      WHILE tempVal < 0                             \n";
      str += "         tempVal += charToNum.size                  \n";
      str += "      plainText += numToChar[tempVal % charToNum.size] \n";
      str += "   RETURN plainText                                 \n\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * Convert the message to cipherText.
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      createCharToNum();
      createNumToChar();
      assert(charToNum.size() == numToChar.size());

      std::string cipherText = "";
      int a = getA(password);
      int b = convertPassToB(password, a);

      for (int i = 0; i < plainText.length(); i++)
         cipherText += numToChar[((a * charToNum[plainText[i]]) + b) % charToNum.size()];

      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * Convert the cipherText to plainText.
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {
      std::string plainText = "";
      int a = getA(password);
      int b = convertPassToB(password, a);
      int aInverse = modInverse(a, charToNum.size());
      for (int i = 0; i < cipherText.length(); i++)
      {
         int tempVal = (aInverse * (charToNum[cipherText[i]] + charToNum.size() - b));
         while (tempVal < 0)
            tempVal += charToNum.size();
         plainText += numToChar[tempVal % charToNum.size()];
      }
      return plainText;
   }

private:
   // For mapping chars to numbers.

   // Map char keys to number values. Maps chars in alphabet to numbers
   // between 0 and numChars (where numChars is the number of characters in the
   // alphabet minus 1.)
   // https://thispointer.com/how-to-initialize-a-map-with-stdinitialzer_list/
   std::map<char, int> charToNum;

   // Map number keys to char values. Inverse of previous map.
   std::map<int, char> numToChar;

   /**********************************************************
    * createCharToNum()
    * Create a map of all characters and matching integers.
    **********************************************************/
   virtual void createCharToNum()
   {
      for (int i = ASCII_FIRST; i <= ASCII_LAST; i++)
      {
         charToNum.insert(std::pair<char, int>('\0' + i, i - ASCII_FIRST));
      }
   }
   /**********************************************************
    * createNumToChar()
    * Create a map of all integers matching chars.
    **********************************************************/
   virtual void createNumToChar()
   {
      for (int i = ASCII_FIRST; i <= ASCII_LAST; i++)
      {
         numToChar.insert(std::pair<int, char>(i - ASCII_FIRST, '\0' + i));
      }
   }

   /**********************************************************
    * gcd(m, n)
    * Computes the greatest common denominator of m and n.
    * https://www.tutorialspoint.com/cplusplus-program-to-find-gcd
    **********************************************************/
   virtual int gcd(int m, int n)
   {
      if (n > m)
      {
         int temp = m;
         m = n;
         n = temp;
      }

      if (m % n == 0)
         return n;

      return (gcd(n, m % n));
   }

   /****************************************
    * getA(password, alphabetSize)
    * Gets the value 'a' required for the
    * encryption. 'a' must be coprime to the
    * size of the alphabet.
    *****************************************/
   virtual int getA(const std::string password)
   {
      if (password.length() == 0)
         return 0;

      int a = charToNum[password[0]] + 1;

      if (password.length() > 1)
         a += charToNum[password[password.length() - 1]];

      while (gcd(a, charToNum.size()) != 1)
      {
         a++;

         if (a < 1)
            a = 1;
      }
      return a;
   }

   /*****************************************
    * convertPassToB(password, a)
    * Get b from password and a.
    ******************************************/
   int convertPassToB(const std::string password, const int a)
   {
      if (password.length() == 0)
         return 0;

      int b = 0;
      for (int i = 0; i < password.length(); i++)
      {
         b += charToNum[password[i]] + 1;
      }

      // Attempt to add more randomness and variation to password.
      b *= (password.length() / 2) + 1;
      b -= a / password.length();

      return b;
   }




   /**********************************************************************************
    * Functions required for decrypt
    * *********************************************************************************/

   /************************************************
    * A function for extended Euclidean Algorithm
    ************************************************/
   int gcdExtended(int a, int b, int* x, int* y)
   {
      // Base case
      if ( a == 0)
      {
         *x = 0; 
         *y = 1;

         return b;
      }

      // Storing results of recursive call
      int x1, y1;
      int gcd = gcdExtended(b % a, a, &x1, &y1);

     // Recursive call to update x and y 
      *x = y1 - (b / a) * x1; 
      *y = x1; 

      return gcd;
   }

   /*****************************************
    * A function to find modulo inverse of a
    *****************************************/
   int modInverse(int a, int mod)
   {
      int x, y; 
      int g = gcdExtended(a, mod, &x, &y); 
      if (g != 1) 
         std::cout << "No inverse";
         
      return (x % mod + mod) % mod; 
   }

};

#endif // CIPHER05_H