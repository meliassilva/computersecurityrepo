/*******************************************************************
 * Header:
 *    Multiplicative Cipher
********************************************************************/
#ifndef CIPHER01_H
#define CIPHER01_H
#include "cipher.h"
#include <cassert>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher01 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Manahari Dahal"; }
   virtual std::string getCipherName() { return "Multiplicative Cipher"; }
   virtual std::string getEncryptAuth() { return "Alex Krentz"; }
   virtual std::string getDecryptAuth() { return "Ethan Picklesimer"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string citation = "";
      citation += "Christensen, C. (2006). Multiplicative Cipher.";
      citation += "Retrieved December 7, 2020, https://www.nku.edu/~christensen/section%206%20multiplicative%20ciphers.pdf. ";
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
      str =  "encrypt(plainText, password\n)";
      str += "    INITIALIZE passCombo string variable to \" !#$ % &'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~\"\n";
      str += "    SET key integer to the size of password\n";
      str += "    INITIALIZE textCipher string variable to zero;\n";
      str += "        FOR i in all values of plainText\n";
      str += "            integer variable alphabetIndex equals (passCombo.find(plainText[i])) * key) mod (size of passCombo)\n";
      str += "            textCipher += passCombo[alphabetIndex]\n";
      str += "    RETURN textCipher\n";
      // The decrypt pseudocode
      str +=  "decrypt(plainText, password\n)";
      str += "    INITIALIZE passCombo string variable to \" !#$ % &'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~\"\n";
      str += "    SET key integer to the size of password\n";
      str += "    INITIALIZE textCipher string variable to zero;\n";
      str += "        FOR i in all values of plainText\n";
      str += "            FOR j in all values of passCombo\n";
      str += "                SET integer cipher equals to (j * key) mod (size of passCombo)\n";
      str += "                    IF passCombo[cipher] equals cipherText[i]\n";
      str += "                        textCipher += passCombo[j]\n";
      str += "        RETURN textCipher\n";
      return str;
   }

   /**********************************************************
    * ENCRYPT
    * Encrypt using the Multiplicative Cipher.
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
      const std::string& password)
   {
      std::string passCombo = " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";
      int key = password.length();
      std::string textCipher = "";
      assert(key != 0);

      for (int i = 0; i < plainText.length(); i++)
      {
         int alphabetIndex = (passCombo.find(plainText[i]) * key) % (passCombo.length());
         textCipher += passCombo[alphabetIndex];
      }

      return textCipher;
   }

   /**********************************************************
    * DECRYPT
    * Decrypt the Multiplicative Cipher using the
    * decrypt pseudocode.
    **********************************************************/
   virtual std::string decrypt(const std::string& cipherText,
      const std::string& password)
   {
      std::string passCombo = " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";
      std::cout << passCombo << std::endl;
      int key = password.length();
      std::string plainText = "";
      assert(key != 0);

      for (int i = 0; i < cipherText.length(); i++)
      {
         for (int j = 0; j < passCombo.length(); j++)
         {
            int cipher = (j * key) % passCombo.length();
            if (passCombo[cipher] == cipherText[i])
               plainText += passCombo[j];
         }
      }

      return plainText;
   }
};

#endif // CIPHER01_H