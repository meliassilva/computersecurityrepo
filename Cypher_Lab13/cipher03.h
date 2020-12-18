/********************************************************************
* Header:
*    Vigenere Cipher
********************************************************************/
#ifndef CIPHER03_H
#define CIPHER03_H
#include "cipher.h"

#include <stdlib.h>
#include <math.h> 
#include <cctype>


/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher03 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Alex Krentz"; }
   virtual std::string getCipherName() { return "Vigenere Cipher"; }
   virtual std::string getEncryptAuth() { return "Manahari Dahal"; }
   virtual std::string getDecryptAuth() { return "Trae Folkman"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string s;
      s += "LearnCryptography.com (2016), ";
      s += "\"Learn Cryptography - Vigenere Cipher\', \n   retrieved: ";
      s += "https://privacycanada.net/classical-encryption/vigenere-cipher/";
      return s;
   }

   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      // pseudocode for Vigenere Cipher
      std::string str;
      // encrypt
      str = "encrypt(message, password)";
      str += "   temp = password";
      str += "   x = message.size\n";
      str += "   FOR I";
      str += "      IF x = i";
      str += "         i = 0\n";
      str += "      IF temp.size = message.size\n";
      str += "         break\n";
      str += "      temp+= temp[i]\n";
      str += "   FOR j in all values of temp\n";
      str += "      if temp[j] NOT uppercase\n";
      str += "         temp[j] <- 72\n";
      str += "   string cipher_text";
      str += "   FOR p is all values of plainText\n";
      str += "      x <- (plainText[p] + temp[p]) % 26\n";
      str += "      x += 'A'";
      str += "      cipher_text += x";
      str += "   RETURN cipherText\n\n";

      // The decrypt pseudocode
      str += "decrypt(cipherText, password)\n";
      str += "   string plain_text";
      str += "   FOR p is all values of cipherText\n";
      str += "      x <- (cipherText[p] - password + 26) % 26\n";
      str += "      plain_text += x\n";
      str += "   RETURN plain_text\n\n";
      return str;
   }

   virtual std::string generateKey(const std::string& plainText,
      const std::string& password)
   {
      std::string key = password;
      int x = plainText.size();

      for (int i = 0; ; i++)
      {
         if (x == i)
            i = 0;
         if (key.size() == plainText.size())
            break;
         key.push_back(key[i]);
      }
      for (int i = 0; i < key.size(); i++)
      {
         if (key[i] != isupper(key[i]))
            key[i] = 72;
      }
      return key;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: A function that encrypts the plaintext
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
      const std::string& password)
   {
      std::string key = generateKey(plainText, password);

      std::string cipher_text;

      for (int i = 0; i < plainText.size(); i++)
      {
         if (isalpha(plainText[i]))
         {
            char x = plainText[i];
            if (islower(x))
               x = toupper(x);
            // converting in range 0-25 
            x = (x + key[i]) % 26;
            // convert into alphabets(ASCII) 
            x += 'A';

            if (islower(plainText[i]))
               x = tolower(x);

            cipher_text.push_back(x);
         }
         else
            cipher_text.push_back(plainText[i]);
      }
      return cipher_text;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string& cipherText,
      const std::string& password)
   {
      std::string orig_text;
      std::string key = generateKey(cipherText, password);

      for (int i = 0; i < cipherText.size(); i++)
      {
         if (isalpha(cipherText[i]))
         {
            char x = cipherText[i];
            if (islower(x))
               x = toupper(x);
            // converting in range 0-25 
            x = (x - key[i] + 26) % 26;
            // convert into alphabets(ASCII) 
            x += 'A';

            if (islower(cipherText[i]))
               x = tolower(x);

            orig_text.push_back(x);
         }
         else
            orig_text.push_back(cipherText[i]);
      }
      return orig_text;
   }
};

#endif // CIPHER03_H