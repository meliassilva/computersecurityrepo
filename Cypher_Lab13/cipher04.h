/********************************************************************
* Header:
*    Keyword Cipher
********************************************************************/
#ifndef CIPHER04_H
#define CIPHER04_H

#include "cipher.h"
#include <string>
#include <map>
#include <cctype>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher04 : public Cipher
{
private:
   std::string encoder(std::string key)
   {
      std::string encoded = "";
      char array[26] = { 0 };
      int arrSize = 26;

      for (int i = 0; i < key.size(); i++)
      {
         if (key[i] >= 'A' && key[i] <= 'Z')
         {
            if (array[key[i] - 65] == 0)
            {
               encoded += key[i];
               array[key[i] - 65] = 1;
            }
         }
         else if (key[i] >= 'a' && key[i] <= 'z')
         {
            if (array[key[i] - 97] == 0)
            {
               encoded += key[i] - 32;
               array[key[i] - 97] = 1;
            }
         }
      }

      for (int i = 0; i < arrSize; i++)
      {
         if (array[i] == 0)
         {
            array[i] = 1;
            encoded += char(i + 65);
         }
      }

      return encoded;
   }



public:
   virtual std::string getPseudoAuth() { return "Trae Folkman"; }
   virtual std::string getCipherName() { return "Keyword Cipher"; }
   virtual std::string getEncryptAuth() { return "Caleb S. Fullmer"; }
   virtual std::string getDecryptAuth() { return "Caleb S. Fullmer"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string citation = "";
      citation += "Christensen, C. (2006). Key Word Ciphers. Retrieved December 8, 2020, from https://www.nku.edu/~christensen/section%204%20keyword%20ciphers.pdf \n";
      citation += "Keyword Cipher. (2019, May 29). Retrieved December 10, 2020, from https://www.geeksforgeeks.org/keyword-cipher/ \n\n";
      return citation;
   }

   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // TODO: please format your pseudocode
      // The encrypt pseudocode
      str = "function to get encoded text";
      str += "encoder(key)\n";
      str += " encoded= "" \n";
      str += "array: size = 26 \n";
      str += "FOR (key size) \n";
      str += "IF (key[i] > 'A' && < 'Z' \n";
      str += "IF (array at index key at index [i] - ascii value 'A' is 0)\n";
      str += "encoded += [key at index [i]]\n";
      str += "array at index [key at index [i] - ascii value 'A'] = 1\n";
      str += "ELSE IF (key[i] > 'a' && < 'z' \n";
      str += "IF (array at index [key at index [i] - ascii value 'a'] is 0)\n";
      str += "encoded += [key at index [i]] subtract ascii value 'space'\n";
      str += "array at index [key at index [i] - ascii value 'a'] = 1\n";
      str += "FOR (length of letters in alphebet) \n";
      str += "IF (array[i] == 0)\n";
      str += "IF (array at index [i])\n";
      str += "array at index [i] = 1\n";
      str += "encoded += char(i + 65)\n";
      str += "return encoded\n";

      str += "function to encrypt \n";
      str += "encryption(message, encoded) \n";
      str += "string cipher \n";
      str += "FOR (size of message)\n";
      str += "IF (message > 'a' && < 'z')\n";
      str += "int position = message at index [i] subtract ascii value\n";
      str += "cipher += encoded at index [position]\n";
      str += "ELSE IF (message > 'A' && < 'Z')\n";
      str += "int position = message at index [i] subtract ascii value\n";
      str += "cipher += encoded at index [position]\n";
      str += "return cipher";


      // The decrypt pseudocode
      str += "Function to decrypt";
      str += "decode (message, encoded) \n";
      str += "map <char, char> enc \n";
      str += "FOR (size of encoded) \n";
      str += "Hold the position of every character (A-Z) from encoded string \n";
      str += "end of loop \n";
      str += "decipher = "" \n";
      str += "FOR (size of message) \n";
      str += "IF (message[i] < 'a' && > 'z') \n";
      str += "int position = enc at index message at index [i] subtract ascii of 'space' \n";
      str += "decipher += plaintext at index [position] \n";
      str += "ELSE IF (message[i] < 'A' && > 'Z') \n";
      str += "int position = enc at index message at index [i] \n";
      str += "decipher = plaintext at index [position] \n";
      str += "ELSE \n";
      str += "decipher += message at index [i] \n";
      str += "return decipher\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
      const std::string& password)
   {
      std::string cipherText = "";
      std::string encoded = encoder(password);

      for (int i = 0; i < plainText.size(); i++)
      {
         if (plainText[i] >= 'a' && plainText[i] <= 'z')
         {
            cipherText += tolower(encoded[plainText[i] - 97]);
         }
         else if (plainText[i] >= 'A' && plainText[i] <= 'Z')
         {
            cipherText += encoded[plainText[i] - 65];
         }
         else
         {
            cipherText += plainText[i];
         }
      }

      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string& cipherText,
      const std::string& password)
   {
      std::string decoded = encoder(password);
      std::string plainText = "";
      std::map<char, char> enc = std::map<char, char>();

      for (int i = 0; i < decoded.size(); i++)
      {
         enc.insert(std::pair<char, char>(decoded[i], i + 65));
      }

      for (int i = 0; i < cipherText.size(); i++)
      {
         if (cipherText[i] >= 'a' && cipherText[i] <= 'z')
         {
            plainText += tolower(enc[cipherText[i] - 32]);
         }
         else if (cipherText[i] >= 'A' && cipherText[i] <= 'Z')
         {
            plainText += enc[cipherText[i]];
         }
         else
         {
            plainText += cipherText[i];
         }
      }

      return plainText;
   }
};

#endif // CIPHER04_H