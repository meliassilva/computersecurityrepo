/***********************************************************************
 * COMPONENT:
 *    MESSAGES
 * Author:
 *    Mario Elias
 * Summary:
 *    This class stores the notion of a collection of messages
 ************************************************************************/

#pragma once

#include <string>     // for convenience
#include <list>       // to store the messages
#include "control.h"  // all the Bell-LaPadula code
#include "message.h"  // all the code about a single message

/***********************************************
 * MESSAGES
 * The collection of high-tech messages
 ***********************************************/
class Messages
{
public:
   // constructor: read a file to fill the messages
   Messages(const char * fileName) { readMessages(fileName); }

   // display the list of messages
   void display(Control subject) const;

   // show a single message
   void show(Control subject, int id) const;

   // update one single message
   void update(Control subject,
               int id,
               const std::string & text);

   // remove a single message
   void remove(Control subject, int id);

   // add a new message
   void add(const std::string & text,
            const std::string & author,
            const std::string & date);

private:
   // the list of messages
   std::list <Message> messages;

   // read the messages from a file
   void readMessages(const char * fileName);
};