/********************************************************************
* Header:
*    Rail Fence Cipher
********************************************************************/
#ifndef CIPHER02_H
#define CIPHER02_H
#include "cipher.h"
/********************************************************************
* CLASS
*******************************************************************/
class Cipher02 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Ethan Picklesimer"; }
   virtual std::string getCipherName() { return "Rail Fence Cipher"; }
   virtual std::string getEncryptAuth() { return "Trae Folkman"; }
   virtual std::string getDecryptAuth() { return "Alex Krentz"; }

   /***********************************************************
   * GET CIPHER CITATION
   * Returns the citation from which we learned about the cipher
   ***********************************************************/
   virtual std::string
      getCipherCitation()
   {
      return std::string("Godarah, Samarth et al, An Improved Algorithmic Implementation of Rail Fence Cipher, International Journal of Future Generation Communication and Networking, 2018, http://article.nadiapub.com/IJFGCN/vol11_no2/3.pdf \nRembert, Ludovic, Transposition Ciphers, PrivacyCanada.net, November 26, 2020, https://privacycanada.net/classical-encryption/transposition-ciphers/ \nSiahaan, Andysah, Rail Fence Cryptography in Securing Information, International Journal of Scientific & Engineering Research, July 2016 https://osf.io/preprints/inarxiv/h5jnz/");
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
      str = "encrypt(plainText, password)\n";
      str += "   rails <- getRailCount(message, password)\n";
      str += "   cipherText <- plainText\n";
      str += "   cIndex <- 1\n";
      str += "   pLength <- length(plainText)\n";
      str += "   FOR i in 1 to rails\n";
      str += "      flag <- true\n";
      str += "      pIndex <- i\n";
      str += "      WHILE pIndex <= pLength\n";
      str += "         cipherText[cIndex - 1] <- plainText[pIndex - 1]\n";
      str += "         Increment cIndex\n";
      str += "         IF i = 1 or i = rails then\n";
      str += "            pIndex <- pIndex + (rails - 1) * 2\n";
      str += "         ELSE\n";
      str += "            IF flag then\n";
      str += "               pIndex <- pIndex + (rails - i) * 2\n";
      str += "               flag <- false\n";
      str += "            ELSE\n";
      str += "            pIndex <- pIndex + ((i - 1) * 2)\n";
      str += "            flag <- true\n";
      str += "   RETURN cipherText\n\n";

      // The decrypt pseudocode
      str += "decrypt(cipherText, password)\n";
      str += "   rails <- getRailCount(message, password)\n";
      str += "   plainText <- cipherText\n";
      str += "   cIndex <- 1\n";
      str += "   cLength <- length(cipherText)\n";
      str += "   FOR i in 1 to rails\n";
      str += "      flag <- true\n";
      str += "      pIndex <- i\n";
      str += "      WHILE pIndex <= cLength\n";
      str += "         plainText[pIndex - 1] <- cipherText[cIndex - 1]\n";
      str += "         Increment cIndex\n";
      str += "         IF i = 1 or i = rails then\n";
      str += "            pIndex <- pIndex + (rails - 1) * 2\n";
      str += "         ELSE\n";
      str += "            IF flag then\n";
      str += "               pIndex <- pIndex + (rails - i) * 2\n";
      str += "               flag <- false\n";
      str += "            ELSE\n";
      str += "            pIndex <- pIndex + ((i - 1) * 2)\n";
      str += "            flag <- true\n";
      str += "   RETURN plainText\n\n";

      // password-key converter
      str += "getRailCount(message, password)\n";
      str += "   FOR each character c in password\n";
      str += "      Increment sum by c\n";
      str += "   rails = sum mod message.length";
      str += "   IF rails < 2";
      str += "      rails = 2";
      str += "   RETURN rails\n\n";
      return str;
   }

   /**********************************************************
   * ENCRYPT
   * TODO: ADD description
   **********************************************************/
   int getRailCount(const std::string message, const std::string password)
   {
      int railCount = 0;
      for (int i = 0; i < password.size(); i++)
      {
         railCount += password[i];
      }

      railCount %= message.length();
      if (railCount < 2)
         railCount = 2;

      return railCount;
   }


   virtual std::string
      encrypt(const std::string& plainText,
         const std::string& password)
   {
      std::string cipherText = plainText;
      // TODO - Add your code here

      int rails = getRailCount(plainText, password) % plainText.length();
      cipherText = plainText;
      bool flag;
      int pIndex;
      int cIndex = 1;
      int pLength = plainText.length();

      for (int i = 1; i <= rails; i++)
      {
         flag = true;
         pIndex = i;

         while (pIndex <= pLength)
         {
            cipherText[cIndex - 1] = plainText[pIndex - 1];
            cIndex++;

            if (i == 1 || i == rails)
            {
               pIndex = pIndex + (rails - 1) * 2;
            }
            else
            {
               if (flag)
               {
                  pIndex = pIndex + (rails - i) * 2;
                  flag = false;
               }

               else
               {
                  pIndex = pIndex + ((i - 1) * 2);
                  flag = true;
               }
            }
         }
      }
      return cipherText;
   }

   /**********************************************************
* DECRYPT
* TODO: ADD description
**********************************************************/
   virtual std::string
      decrypt(const std::string& cipherText,
         const std::string& password)
   {
      std::string plainText = cipherText;
      int rails = getRailCount(cipherText, password) % plainText.length();
      int cIndex = 1;
      int cLength = cipherText.size();
      for (int i = 1; i <= rails; i++)
      {
         bool flag = true;
         int pIndex = i;
         while (pIndex <= cLength)
         {
            plainText[pIndex - 1] = cipherText[cIndex - 1];
            cIndex++;
            if (i == 1 || i == rails)
            {
               pIndex = pIndex + (rails - 1) * 2;
            }
            else
            {
               if (flag)
               {
                  pIndex = pIndex + (rails - i) * 2;
                  flag = false;
               }
               else
               {
                  pIndex = pIndex + ((i - 1) * 2);
                  flag = true;
               }
            }
         }
      }
      return plainText;
   }
};

#endif // CIPHER02_H
