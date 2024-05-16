#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_12.12_tree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestAddEmployee)
        {
            
            BinaryTree tree; 
            string lastName = "Smith";
            string initials = "J.K.";
            string position = "Developer";
            int startYear = 2023;
            double salary = 60000;

            tree.addEmployee(lastName, initials, position, startYear, salary);

           
        }
	};
}
