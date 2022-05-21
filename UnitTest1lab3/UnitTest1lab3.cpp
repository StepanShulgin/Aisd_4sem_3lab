#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\stepa\source\repos\Aisd_4sem_3lab\Aisd_4sem_3lab\the_Floyd-Warshell_algorithm.h"
#include "C:\Users\stepa\source\repos\Aisd_4sem_3lab\Aisd_4sem_3lab\List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1lab3
{
	TEST_CLASS(UnitTest1lab3)
	{
	public:
		
		TEST_METHOD(isInListTest)
		{
			List<string> TestList;
			TestList.push_back("Testing");
			Assert::IsTrue(TestList.isInList("Testing") == 0);
			TestList.clear();
			Assert::IsTrue(TestList.isInList("Testing") == 2147483647);
		}


		TEST_METHOD(mainAlgorithmTest)
		{
			Floyd_Warshell Test;
			Test.read();
			Test.mainAlgorithm();
			Assert::IsTrue(Test.getBestCost("St. Petersburg", "Khabarovsk") == "50");
			Assert::IsTrue(Test.getBestPath("St. Petersburg", "Khabarovsk") == "St. Petersburg->Moscow->Khabarovsk");
			Assert::IsTrue(Test.getBestPath("St. Petersburg", "Astrakhan") == "There is no such route");
			
		}

		TEST_METHOD(getBestCostTest)
		{
			Floyd_Warshell Test;
			Test.read();
			Test.mainAlgorithm();
			Assert::IsTrue(Test.getBestCost("St. Petersburg", "Khabarovsk") == "50");
			Assert::IsTrue(Test.getBestCost("St. Petersburg", "Astrakhan") == "There is no such route");

		}

		TEST_METHOD(getBestPathTest)
		{
			Floyd_Warshell Test;
			Test.read();
			Test.mainAlgorithm();
			Assert::IsTrue(Test.getBestPath("St. Petersburg", "Khabarovsk") == "St. Petersburg->Moscow->Khabarovsk");
			Assert::IsTrue(Test.getBestPath("St. Petersburg", "Astrakhan") == "There is no such route");

		}
	};
}
