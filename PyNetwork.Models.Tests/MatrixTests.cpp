#include "CppUnitTest.h"
#include <vector>
#include "PyNet.Models/Matrix.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PyNet::Models::Tests
{
	TEST_CLASS(MatrixTests)
	{
	public:
	
		TEST_METHOD(Constructor_GivenDoubleArray_ReturnsMatrixWithCorrectValues)
		{
			double testArray[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

			auto myMatrix = std::make_unique<PyNet::Models::Matrix>(10, 1, testArray);

			for (auto i = 0; i < 10; i++) {
				Assert::AreEqual(testArray[i], myMatrix->GetValue(i, 0));
			}

			Assert::AreEqual(10, myMatrix->Rows);
			Assert::AreEqual(1, myMatrix->Cols);
		}
	};
}