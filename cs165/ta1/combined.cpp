/***
 * File: combined.cpp
 ***/

#include <iostream>
#include <string>
using namespace std;

/*************************
 * Student struct
 *************************/
struct Student
{
   string first;
   string last;
   float gpa;
};

// Student related prototypes
void display(const Student & curStudent);


/*************************
 * Student related method implementations
 *************************/
void display(const Student & curStudent)
{
   cout << curStudent.last << ", " << curStudent.first << " - ";
   cout << curStudent.gpa << endl;
}


/************************
 * Main Driver
 ************************/
int main()
{
   Student s1;
   s1.first = "Emily";
   s1.last = "Smith";
   s1.gpa = 3.8;

   Student s2;
   s2.first = "Jacob";
   s2.last = "Jones";
   s2.gpa = 3.5;

   Student s3;
   s3.first = "Alex";
   s3.last = "Taylor";
   s3.gpa = 4.0;

   display(s1);
   display(s2);
   display(s3);

   return 0;
}

