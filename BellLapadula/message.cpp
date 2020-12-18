/***********************************************************************
 * COMPONENT:
 *    MESSAGE
 * Author:
 *    Mario Elias
 * Summary:
 *    This class stores the notion of a message
 ************************************************************************/

#include <iostream>   // standard input and output
#include <cassert>    // because I am paraniod
#include "message.h"  // for the header file
using namespace std;

/**************************************************
 * MESSAGE DEFAULT CONSTRUCTOR
 * Set a message to empty
 **************************************************/
Message ::  Message()
{
   empty = true;
   text = "Empty";
   id = idNext++;
}


/**************************************************
 * MESSAGE NON-DEFAULT CONSTRUCTOR
 * Create a message and fill it
 **************************************************/
Message::Message(const string & textControl,
                 const string & text,
                 const string & author,
                 const string & date)
{
   this->text = text;
   this->author = author;
   this->date = date;
   this->id = idNext++;
   this->assetControl = convert(textControl);
   empty = false;
}

/**************************************************
 * MESSAGE :: DISPLAY PROPERTIES
 * Display the attributes/properties but not the
 * content of this message
 **************************************************/
void Message::displayProperties(Control subject) const
{
   // skip this one if there is nothing to see
   if (empty)
      return;
   
   // display the message
   cout << "\t[" << id << "] ";

   if (securityConditionRead(assetControl, subject))
      cout << "Message from " << author << " at " << date;
   else 
      cout << "Classified";

   cout << endl;
}

/**************************************************
 * MESSAGE :: DISPLAY TEXT
 * Display the contents or the text of the message
 **************************************************/
void Message::displayText(Control subject) const
{
   cout << "\tMessage: "
        << (securityConditionRead(assetControl, subject) ? text : "Classified")
        << endl;
}

/**************************************************
 * MESSAGE :: UPDATE TEXT
 * Update the contents or text of the message
 **************************************************/
void Message::updateText(Control subject, const string & newText)
{
   if (securityConditionWrite(assetControl, subject)) 
      text = newText;
   else
      cout << "\tDENIED! You do not have permission to update this message" << endl;

}

/**************************************************
 * MESSAGE :: CLEAR
 * Delete the contents of a message and mark it as empty
 *************************************************/
void Message::clear(Control subject)
{
   if (securityConditionWrite(assetControl, subject))
   {
      text = "Empty";
      author.clear();
      date.clear();
      empty = true;
   }
   else
      cout << "\tDENIED! You do not have permission to delete this message" << endl;

}

/**************************************************
 * MESSAGE :: CONVERT
 * Convert textControl to Enum
 *************************************************/
Control Message::convert(const std::string& textControl)
{
   if(textControl == "Public") return Public;
   else if(textControl == "Confidential") return Confidential;
   else if(textControl == "Privileged") return Privileged;
   else if(textControl == "Secret") return Secret;
}

/**************************************************
 * MESSAGE :: Security Condition Read
 * Can the subject read the asset
 *************************************************/
bool Message::securityConditionRead(Control assetControl, /* asset */ Control subjectControl /* user */) const
{
   return subjectControl >= assetControl;
}

/**************************************************
 * MESSAGE :: Security Condition Write
 * Can the subject write to the asset
 *************************************************/
bool Message::securityConditionWrite(Control assetControl, /* asset */ Control subjectControl /* user */) const
{
   return subjectControl <= assetControl; // opposite of the Read!
}

int Message::idNext = 100;