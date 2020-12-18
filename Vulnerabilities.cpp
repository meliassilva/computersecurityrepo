#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
//#include <stringapiset.h>



using namespace std;
/***************************************
 * ARRAY VULNERABILTY
 * 1. There must be an array and an array index variable
 * 2. The array index variable must be reachable through external input.
 * 3. There must not be bounds checking on the array index variable.
 ****************************************/
bool arrayVulnerability(int index)
{
   // 1. There must be an array and an array index variable
   int array[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
   int selfDestruct = 0;

   // Show origional array value.
   cout << "Index " << index << " was " << array[index] << endl;

   // 2. The array index variable must be reachable through external input.
   // 3. There must not be bounds checking on the array index variable.
   array[index] = 1;

   // Show new array value.
   cout << "Is now " << array[index] << endl;

   return selfDestruct;
}


/***************************************
 * Display hacked status.
 * **************************************/
void CheckHacked(bool hacked)
{
   if (hacked)
      cout << "You have been hacked!" << endl;
   else
      cout << "You were not hacked this time." << endl;
}


/**************************************
 * ARRAY WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arrayWorking()
{
   cout << "Array Working:\n";
   CheckHacked(arrayVulnerability(9));
}


/**************************************
 * ARRAY EXPLOIT
 * 1. The attacker provides an array index value outside the expected range
 * 2. The attacker must be able to provide input or redirect
 *    existing input into the array at the index he provided
 * 3. The injected value must alter program state in a way
 *    that is desirable to the attacker
 *************************************/
void arrayExploit()
{
   cout << "Array Exploit:\n";
   // 1. The attacker provides an array index value outside the expected range
   // 2. The attacker must be able to provide input or redirect
   //    existing input into the array at the index he provided
   // 3. The injected value must alter program state in a way
   //    that is desirable to the attacker
   CheckHacked(arrayVulnerability(11));
}










string * dangerousStr = new string("You are hacked.");


/***************************************
 * POINTER SUBTERFUGE
 * 1. There must be a pointer used in the code.
 * 2. There must be a way for the user to input an
 *    overwrite to the pointer.
 * 3. The pointer must be dereferenced once it is overwritten.
 ***************************************/
void subterfugeVulnerability(int arrayIndex, long input)
{
   cout << dangerousStr << endl;
   cout << (long)dangerousStr << endl;
   cout << input << endl;

   // 1. There must be a pointer used in the code.
   string * safeStr = new string("You are safe.");

   // 2. There must be a way for the user to input an
   //    overwrite to the pointer.
   int array[2] = { 1, 2 };

   array[arrayIndex] = input;

   // 3. The pointer must be dereferenced once it is overwritten.
   cout << *safeStr << endl;
}


/****************************************
 * SUBTERFUGE WORKING
 * Tests if subterfugeVulnerability works with vaild input.
 ****************************************/
void subterfugeWorking()
{
   cout << "Subterfuge Working:\n";
   subterfugeVulnerability(0, 15);
}


/****************************************
 * SUBTERFUGE EXPLOIT
 * 1. The attacker must exploit a vulnerability allowing unintended access to the pointer.
 * 2. The attacker must be able to provide a new pointer referring to data altering the normal flow of the program.
 ****************************************/
void subterfugeExploit()
{
   cout << "Subterfuge Exploit:\n";
   // I think you have to go two over the array because we allocated data in it.

   // 1. The attacker must exploit a vulnerability allowing unintended access to the pointer.
   // 2. The attacker must be able to provide a new pointer referring to data altering the normal flow of the program.
   subterfugeVulnerability(3, (long)dangerousStr);
}












bool stealAllMyMoney;


/***************************************
 * ARC Injection
 * 1. There must be a function pointer used in the code
 * 2. Through some vulnerability, there must be a way for user input to
      overwrite the function pointer. This typically happens through a stack
      buffer vulnerability.
 * 3. After the memory is overwritten, the function pointer must be   4202714
      dereferenced.
 ****************************************/
void safe()
{
   stealAllMyMoney = false;
}


void dangerous()
{
   stealAllMyMoney = true;
}


/***************************************
 * ARC VULNERABILITY
 * 1. There must be a function pointer used in the code
 * 2. Through some vulnerability, there must be a way for user input to
      overwrite the function pointer. This typically happens through a stack
      buffer vulnerability.
 * 3. After the memory is overwritten, the function pointer must be   4202714
      dereferenced.
 ****************************************/
void arcVulnerability(int index, long input)
{
   long buffer[4];
   // 1. There must be a function pointer used in the code
   void(*pointerFunction)() = safe;

   // 2. Through some vulnerability, there must be a way for user input to
   //    overwrite the function pointer. This typically happens through a stack
   //    buffer vulnerability.
   buffer[index] = input;


   cout << &buffer[-1] << endl;
   cout << &pointerFunction << endl;


   // 3. After the memory is overwritten, the function pointer must be dereferenced.   4202714
   pointerFunction();

   cout << "I want my money stollen? " << stealAllMyMoney << endl;
}


/**************************************
 * ARC WORKING
 * Call arcVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arcWorking()
{
   cout << "ARC Working:\n";
   arcVulnerability(3, 4202714);
}


/**************************************
 * ARC EXPLOIT
 * 1. The attacker must exploit a vulnerability allowing unintended access to
      the function pointer
 * 2. The attacker must have the address to another function which is to be
      used to replace the existing function pointer.
 *************************************/
void arcExploit()
{
   cout << "ARC Exploit:\n";
   // 1. The attacker must exploit a vulnerability allowing unintended access to
   //    the function pointer
   // 2. The attacker must have the address to another function which is to be
   //    used to replace the existing function pointer.
   arcVulnerability(-1, (long)&dangerous);
}














/*************************************
 * VTABLE VULNERABILTY
 * 1. The vulnerable class must be polymorphic.
 * 2. The class must have a buffer as a member variable.
 * 3. Through some vulnerability, there must be a way for user input to overwrite parts of the V-Table.
 * 4. After a virtual function pointer is overwritten, the virtual function must be called.
 *
 * This website discusses how to get the address of a class's V-Table
 *    https://reverseengineering.stackexchange.com/questions/5956/how-to-find-the-location-of-the-vtable
 ****************************************/
class vTableVulnerability //make a class with virtual function and derived class.
{
protected:
   // 2. The class must have a buffer as a member variable.
   long buffer[2];

public:
   virtual int getWorked2() { cout << "Wrong\n"; return 1; };

   virtual int getWorked1() { cout << "Right\n"; return 1; };
};



// 1. The vulnerable class must be polymorphic.
class vulnerableCard : public vTableVulnerability
{
private:
   int suit = 0;
   int id = 0;

public:
   
   // Just some random variables as though this was a meaninful class.
   int getId() { return id; }
   int getSuit() { return suit; }

   void setBuffer(int bufferIndex, long input)
   {
      buffer[bufferIndex] = input;
      cout << "Buffer Set." << endl;
   }


   long int * getBuffer() {
      cout << &buffer[0] << endl;
      return &(buffer[0]);
   }
};


/**********************************************
 * V-TABLE SMASHING FUNCTION
 **********************************************/
void testVTable(long bufferIndex, long input)
{
   vulnerableCard danger;


   // 3. Through some vulnerability, there must be a way for user input to overwrite parts of the V - Table.
   danger.setBuffer(bufferIndex, input);

   // 4. After a virtual function pointer is overwritten, the virtual function must be called.
   danger.getWorked1();
   danger.getWorked2();
   cout << "No spraying occoured.\n";
}


/**************************************
 * VTABLE WORKING
 * Call vTableVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void vTableWorking()
{
   cout << "vTable Working Test:\n";
   testVTable(0, 123412);

}


/**************************************
 * VTABLE EXPLOIT
 * 1. Through some vulnerability, the V-Table pointer or a function pointer within the V-Table must be overwritten.
 * 2. For V - Table spraying, the attacker must input nonsense data which will cause the program to crash.
 *************************************/
void vTableExploit()
{
   cout << "vTable Exploit Test:\n";

   // 1. Through some vulnerability, the V - Table pointer or a function pointer within the V - Table must be overwritten.
   // 2. For V - Table spraying, the attacker must input nonsense data which will cause the program to crash.
   testVTable(-4, 1111111111111);
}













/***************************************
 * STACK SMASHING
 * 1. There must be a buffer (such as an array) on the stack.
 * 2. The buffer must be reachable from an external input.
 * 3. The mechanism to fill the buffer from the external input must not
      correctly check for the buffer size.
 * 4. The buffer must be overrun (extend beyond the intended limits of the
      array).
 ****************************************/
void stackVulnerability(long * input)
{
   // There must be a buffer (such as an array) on the stack.
   long buffer[4];
   cout << ((void*)dangerous); // address 0x4014b8
   for (int i = 0; i < sizeof(input) / sizeof(input[0]); i++) // The mechanism to fill the buffer from the 
                                            //external input must not correctly check for the buffer size.
   {
      // The buffer must be reachable from an external input.
      buffer[i] = input[i];  //The buffer must be overrun (extend beyond the intended limits of thearray).
   }
}
/**************************************
 * STACK WORKING
 * Call stackVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void stackWorking()
{
   long input[] = { 1, 1, 1, 1 };
   stackVulnerability(input);
   cout << "\nNo stack smashing";
}
/**************************************
 * STACK EXPLOIT
 * 1. The attacker must provide more data into the outwardly facing buffer
      than the buffer is designed to hold
 * 2. The attacker must know where the stack pointer resides on the stack.
      This should be just beyond the end of the buffer.
 * 3. The attacker must insert machine language instructions in the buffer.
      This may occur before, after, or even around the stack pointer. The
      machine language could be already compiled code in the program.
 * 4. The attacker must overwrite the stack pointer. The old value, directing
      the flow of the program after the function is returned, must be changed
      from the calling function to the provided machine language in step 3
 *************************************/
void stackExploit()
{
   long input[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
   stackVulnerability(input);
   cout << "\nstack exploit";
}












/*************************************
 * HEAP VULNERABILTY
 * 1. There must be two adjacent heap buffers.
 * 2. The first buffer must be reachable through external input.
 * 3. The mechanism to fill the buffer from the external input must not correctly check for the buffer size.
 * 4. The second buffer must be released before the first.
 * 5. The first buffer must be overrun (extend beyond the intended limits of the array).
 ****************************************/
void heapVulnerability(string x)
{
   // 1. There must be two adjacent heap buffers.
   char *name = new char[11];
   char *name2 = new char[11];
   cout << "Assigning string " << x << " to a heap item of size 11." << endl;
   // 2. The first buffer must be reachable through external input.
   assert(name < name2);
   // 3. The mechanism to fill the buffer from the external input must not correctly check for the buffer size.
   for (int i = 0; i < x.length(); i++)
   {
      // 5. The first buffer must be overrun (extend beyond the intended limits of the array).
      name[i] = x[i];
   }
   // 4. The second buffer must be released before the first.
   delete[] name2;
   delete[] name;
}


/**************************************
 * HEAP WORKING
 * Call heapVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void heapWorking()
{
   string name = "John";
   heapVulnerability(name);
   cout << "The vulnerability is not affected by the string 'John'." << endl;
}


/**************************************
 * HEAP EXPLOIT
 * 1. The attacker must provide more data into the outwardly facing heap buffer than the buffer is designed to hold.
 * 2. The attacker must know the layout of the Memory Control Block (MCB) (essentially a linked list) residing just after the buffer.
 * 3. The attacker must provide a new MCB containing both the location of the memory overwrite and the new data to be overwritten.
 *************************************/
void heapExploit()
{
   string name = "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
   cout << "The heap will crash with the string '" << name << "'.\n";
   // 1. The attacker must provide more data into the outwardly facing heap buffer than the buffer is designed to hold.
   // 2. attacker must know the layout of the Memory Control Block (MCB) (essentially a linked list) residing just after the buffer.
   // 3. The attacker must provide a new MCB containing both the location of the memory overwrite and the new data to be overwritten.
   heapVulnerability(name);
   cout << "The vulnerability is not affected by the string '" << name << "'.\n";
}














/******************************************
 * INTEGER OVERFLOW VULNERABILITY
 * 1. There must be a security check represented by an expression.
 * 2. The expression must have the potential for overflow.
 * 3. At least one of the numbers used to compute the sentinel must be reachable through external input.
 ******************************************/
void intOverFlow(char i, char gradeToChange)
{
   if (i < 0)
   {
      cout << "Indexes less than 0 not allowed.\n";
      return;
   }

   char grades[4] = { 'A', 'B', 'C', 'D' };
   char paliden1 = (char)2;
   char paliden2 = (char)4;
   char fail = paliden1 + i;

   cout << "The grade to change is " << (int)i << endl;
   cout << "The index is " << fail << endl;


   // 1. There must be a security check represented by an expression.
   // 2. The expression must have the potential for overflow.
   // 3. At least one of the numbers used to compute the sentinel must be reachable through external input.
   if ((char)(paliden1 + i) >= (char)paliden2) // put overflow here. use char
      cout << "Invalid grade!\n";
   else
   {
      cout << "The old grade was " << grades[fail] << endl;
      grades[fail] = gradeToChange;
      cout << "The new grade is " << grades[fail] << endl;
   }
}


/****************************************
 * integerWorking()
 * Tests the function intOverFlow with
 * valid inputs.
 ****************************************/
void intergerWorking()
{
   cout << "Int Working:\n";
   intOverFlow(1, 'B');
}


/******************************************
 * INTEGER EXPLOIT
 * 1. Provides input (buffer size or single value) that is directly or indirectly used in vulnerable expression.
 * 2. The input must exceed the valid bounds of the data-type, resulting in an overflow or underflow condition.
 ******************************************/
void intExploit()
{
   cout << "Int Exploit:\n";
   // 1. Provides input(buffer size or single value) that is directly or indirectly used in vulnerable expression.
   // 2. The input must exceed the valid bounds of the data - type, resulting in an overflow or underflow condition.
   intOverFlow(127, 'F');
}
















/************************************************************************
 * ANSI-Unicode Vulnerability
 * 1. There must be a buffer where the basetype is greater than one.
 * 2. Validation of the buffer must check the size of the buffer
 *    rather than the number of elements in the buffer.
 ***********************************************************************/
void ansiVulnerability(string input)
{
   // 1. There must be a buffer where the basetype is greater than one.
   long buffer[4];
   bool safe = true;
   cout << "Safe: " << (safe ? "True" : "False") << endl;
   // 2. Validation of the buffer must check the size of the buffer
   //    rather than the number of elements in the buffer.
   for (int i = 0; i < sizeof(buffer) && i < input.length(); i++)
   {
      buffer[i] = input[i];
   }
   cout << "Safe: " << (safe ? "True" : "False") << endl;
}
/*******************************************************************
 * ANSI-Unicode Working
 ******************************************************************/
void ansiWorking()
{
   string working = "12";
   cout << "AnsiWorking: " << working << endl;
   ansiVulnerability(working);
}
/*******************************************************************
 * ANSI-Unicode Exploit
 * 1. The attacker must provide more than half as much data into the
 *    outwardly facing buffer as it is designed to hold.
 * 2. From here, stack or heap smashing can commence.
 ******************************************************************/
void ansiExploit()
{
   // 1. The attacker must provide more than half as much data into the
   //    outwardly facing buffer as it is designed to hold.
   string exploit = "12345";
   cout << "AnsiExploit: " << exploit << endl;
   // 2. From here, stack or heap smashing can commence.
   ansiVulnerability(exploit);
}












/************************************************
 * menu()
 * This helps declutter the testing. It is particularly
 * useful since some vulnerabilities (such as heap spraying)
 * kill the program.
 ************************************************/
void menu()
{
   int input = 0;

   cout << "Please enter the vulnerability you would like to check,\n";
   cout << "1. Array Index\n" << "2. Pointer Subterfuge\n" << "3. ARC Injection\n";
   cout << "4. V-Table Spraying\n" << "5. Stack Smashing\n" << "6. Heap Spraying\n";
   cout << "7. Integer Overflow\n" << "8. ANSI-Unicode\n";


   while (input == 0)
   {
      cin >> input;

      if (cin.fail())
      {
         cin.clear();
         cin.ignore(10000, '\n');

         cout << "Invalid input. Please only enter numbers.\n";
      }
      else if ((input < 1) || (input > 8))
      {
         input = 0;
         cout << "Invalid input. Please enter a number between 1 and 8.\n";
      }
   }


   switch (input)
   {
   case 1:
      // Works
      arrayWorking();
      arrayExploit();
      break;
   case 2:
      // Works
      subterfugeWorking();
      subterfugeExploit();
      break;
   case 3:
      // Works
      arcWorking();
      arcExploit();
      break;
   case 4:
      // Works
      vTableWorking();
      vTableExploit();
      break;
   case 5:
      // Works I think.
      stackWorking();
      stackExploit();
      break;
   case 6:
      // Works
      heapWorking();
      heapExploit();
      break;
   case 7:
      // Works
      intergerWorking();
      intExploit();
      break;
   case 8:
      // Works I think.
      ansiWorking();
      ansiExploit();
      break;
   default:
      cout << "Error: Invalid input.\n";
      break;
   }
}





int main()
{
   menu();
   return 0;
}