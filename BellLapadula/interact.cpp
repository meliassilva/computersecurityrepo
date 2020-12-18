/***********************************************************************
 * COMPONENT:
 *    INTERACT
 * Author:
 *    Mario Elias
 * Summary:
 *    This class allows one user to interact with the system
 ************************************************************************/

#include <iostream>   // standard input and output
#include <string>     // for convenience
#include <cassert>    // because I am paraniod
#include <stdlib.h>   // for atoi
#include "messages.h" // to interact with the collection of messages
#include "control.h"  // all the Bell-LaPadula stuff
#include "interact.h" // the interact class and User structure

using namespace std;

/**************************************************************
 * USERS
 * All the users currently in the system
 *************************************************************/
const User users[] =
{
   { "AdmiralAbe",     "password", Secret },
   { "CaptainCharlie", "password", Privileged },
   { "SeamanSam",      "password", Confidential },
   { "SeamanSue",      "password", Confidential },
   { "SeamanSly",      "password", Confidential }
};

const int ID_INVALID = -1;

/****************************************************
 * INTERACT constructor
 * Authenticat ethe user and get him/her all set up
 ***************************************************/
Interact::Interact(const string & userName,
                   const string & password,
                   Messages & messages)
{
   authenticate(userName, password);
   this->userName = userName;
   this->pMessages = &messages;
}

/****************************************************
 * INTERACT :: SHOW
 * show a single message
 ****************************************************/
void Interact::show() const
{
   pMessages->show(subject, promptForId("display"));
}

/****************************************************
 * INTERACT :: DISPLAY
 * display the set of messages
 ***************************************************/
void Interact::display() const
{
   pMessages->display(subject);
}

/****************************************************
 * INTERACT :: ADD
 * add a single message
 ****************************************************/
void Interact::add()
{
   pMessages->add(promptForLine("message"),
                  userName,
                  promptForLine("date"));
}

/****************************************************
 * INTERACT :: UDPATE
 * update a single message
 ****************************************************/
void Interact::update()
{
   int id = promptForId("update");
   pMessages->update(subject,
                     id,
                     promptForLine("message"));
}

/****************************************************
 * INTERACT :: REMOVE
 * remove one message from the list
 ***************************************************/
void Interact::remove()
{
   pMessages->remove(subject, promptForId("delete"));
}

/****************************************************
 * INTERACT :: DISPLAY USERS
 * display the set of users in the system
 ***************************************************/
void displayUsers()
{
   for (int idUser = 0; idUser < sizeof(users) / sizeof(users[0]); idUser++)
      cout << "\t" << users[idUser].name << endl;
}

/****************************************************
 * INTERACT :: PROMPT FOR LINE
 * prompt for a line of input
 ****************************************************/
string Interact::promptForLine(const char * verb) const
{
   string line;
   cout << "Please provide a " << verb << ": ";
   getline(cin, line);
   return line;
}

/****************************************************
 * INTERACT :: PROMPT FOR ID
 * prompt for a message ID
 ***************************************************/
int Interact::promptForId(const char * verb) const
{
   string id;
   cout << "Select the message ID to " << verb << ": ";
   cin  >> id;
   cin.ignore();
   return atoi(id.c_str());
}

/****************************************************
 * INTERACT :: AUTHENTICATION
 * authenticate the user: find their control level
 ****************************************************/
void Interact::authenticate(const string & userName,
                            const string & password)
{
   int id = idFromUser(userName);
   subject = subjecFromUser(userName, password);
}

/****************************************************
 * INTERACT :: ID FROM USER
 * Find the ID of a given user
 ****************************************************/
int Interact::idFromUser(const string & userName) const
{
   for (int idUser = 0; idUser < sizeof(users) / sizeof(users[0]); idUser++)
      if (userName == string(users[idUser].name))
         return idUser;
   return ID_INVALID;
}

/****************************************************
 * INTERACT :: Subject from User
 * Find the Subject Control of a given user
 ****************************************************/
Control Interact::subjecFromUser(const string & userName, const string & password)
{
   for (int idUser = 0; idUser < sizeof(users) / sizeof(users[0]); idUser++)
      if (userName == string(users[idUser].name) && password == string(users[idUser].password))
         return users[idUser].subject;

   return Public;