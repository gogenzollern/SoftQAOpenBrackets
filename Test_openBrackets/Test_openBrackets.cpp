#include "pch.h"
#include "CppUnitTest.h"
#include "../OpenBrackets/OpenBracketsHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestopenBrackets
{
	TEST_CLASS(TestopenBrackets)
	{
	public:
		
		TEST_METHOD(noBrackets)
		{
			// Ожидаемое дерево
			int expectedRoot = -1;
			vector<Node> expectedTree = { {-1, 2, 3, "-"}, {1, 4, 5, "+"}, {1, NotExist, NotExist, "c"}, {2, NotExist, NotExist, "a"}, {2, NotExist, NotExist, "b"} };

			// Получаемое дерево
			int outputRoot = -1;
			vector<Node> outputTree = { {-1, 2, 3, "-"}, {1, 4, 5, "+"}, {1, NotExist, NotExist, "c"}, {2, NotExist, NotExist, "a"}, {2, NotExist, NotExist, "b"} };

			bool isEqualTree = isEqualTrees(expectedTree, expectedRoot, outputTree, outputRoot);

			Assert::IsTrue(isEqualTree);
		}
	};
}
