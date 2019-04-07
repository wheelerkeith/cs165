/***********************************************************************
* Program:
*    Assignment 17, Caesar Cipher
*    Brother Comeau, CS165
* Author:
*    Keith Wheeler
* Summary: 
*    This program is designed to store a secret message.  The message
*    is encrypted using the Caesar Cipher: a simple cipher that simply
*    adds 3 to ASCII value of the message.  For example, if the plain-text
*    message is "SECRET", the cipher text is "VHFUHW" because
*                 'V' = 'S' + 3
*                 'H' = 'E' + 3
*                 ...
*    Thus, if I am to decrypt the message, I simply subtract three from
*    each letter.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
using namespace std;

// getKey will prompt the user for the key
int getKey(int &key)
{
   cout << "Please enter the key to decrypt the message: ";
   cin >> key;
   return key;
}

// keyCorrect will make sure the key is correct
bool keyCorrect(int key)
{
   if (key == 3)
      return true;
   else
      cout << "Incorrect!  Try again"
           << endl;
      return false;
}

// convert will decypher they code according to the key
char convert(char message[], int key)
{
   for (int i = 0; i < message[i]; i++)
      message[i] -= key;
}

// display will show the converted message
void display(char message[])
{
   cout << "The translated message is: \""
        << message << "\""
        << endl;
}



/**********************************************************************
 * MAIN: This function calls 4 functions:
 *    getKey:     Prompt the user for the secret key
 *    keyCorrect: Determines if the user's guess is correct
 *    convert:    Convert our cipher text to plain text so the world can see
 *    display:    Display the converted message
 ***********************************************************************/
int main()
{
   // the key the user will guess
   int key;
   // the top secret message
   char message[] = "Fdhvdu#Flskhu#zdv#lqyhqwhg#durxqg#93EF";  

   // keep looping until the user guesses the key (ssshh!!  it is '3')
   do
      getKey(key);
   while (!keyCorrect(key));

   // convert the top secret message to the plain-text message
   convert(message, key);

   // show the user
   display(message);
      
   return 0;
}
