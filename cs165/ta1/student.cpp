
#include <iostream>
#include "student.h"
/*************************
 * Student related method implementations
 *************************/
void display(const Student & curStudent)
{
   cout << curStudent.last << ", " << curStudent.first << " - ";
   cout << curStudent.gpa << endl;
}

