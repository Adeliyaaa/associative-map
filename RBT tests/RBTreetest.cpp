#include "pch.h"
#include "CppUnitTest.h"
#include "../RBTree/RBT.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RBTreetest
{
	TEST_CLASS(RBTreetest)
	{
	public:
		RBTree <int, string> test;

		
		TEST_METHOD(find_and_insert_test)
		{
			test.insert(5, "August");
			bool expected = true;
			bool inreal = false;
			if (test.find(5) == true)
				inreal = true;
			Assert::AreEqual(inreal, expected);
		}

		TEST_METHOD(remove_test)
		{
			test.insert(5, "August");
			test.insert(17, "July");
			test.insert(67, "May");
			test.remove(5);
			bool expected = false, inreal = true;
			if (test.find(5) == false)
				inreal = false;
			Assert::AreEqual(inreal, expected);
		}

		TEST_METHOD(print_exception)
		{
			try {
				test.Print();
			}
			catch (const char* msg)
			{
				Assert::AreEqual("The tree is empty", msg);
			}
		}

		TEST_METHOD(clear_exception)
		{
			try {
				test.clear();
			}
			catch (const char* msg)
			{
				Assert::AreEqual("The tree is empty", msg);
			}
		}

		TEST_METHOD(remove_exception)
		{
			test.insert(5, "August");
			test.insert(17, "July");
			test.insert(67, "May");

			try {
				test.remove(20);
			}
			catch (const char* msg)
			{
				Assert::AreEqual("There's no key like that", msg);
			}
		}

	};
}
