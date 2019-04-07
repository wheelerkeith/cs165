
#include <string>
#ifndef STUDENT_H
#define STUDENT_H
{
   /*************************
    * Student struct
    *************************/
   struct Student
   {
      std::string first;
      std::string last;
      float gpa;
   };
   
   //Student related prototypes
   void display(const Student & curStudent);
}
