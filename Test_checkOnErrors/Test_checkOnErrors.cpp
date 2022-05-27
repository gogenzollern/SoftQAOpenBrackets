#include "pch.h"
#include "CppUnitTest.h"
#include "../OpenBrackets/OpenBracketsHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestcheckOnErrors
{
	TEST_CLASS(TestcheckOnErrors)
	{
	public:
		
		TEST_METHOD(wrongDataFormat)
		{
				ErrorType expectedError = WRONG_DATA_FORMAT;
				
				// Входное дерево
				int inputSize = 6;
				int inputRoot = 1;
				vector<Node> inputTree = { {-1, -1, -1, ""}, {-1, 2, 3, "*"}, {1, -1, -1, "a"}, {1, -1, -1, "b"}, {-1, 5, 6, "+"}, {4, -1, -1, "c"}, {4, -1, -1, "d"}};

				ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

				Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(notBinaryTree)
		{
			ErrorType expectedError = NOT_BINARY_TREE;

			// Входное дерево
			int inputSize = 4;
			int inputRoot = 1;
			vector<Node> inputTree = { {-1, -1, -1, ""}, {-1, 2, 3, "*"}, {1, -1, -1, "a"}, {1, -1, -1, "b"}, {1, -1, -1, "c"}};

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(sameParentAndNodeID)
		{
			ErrorType expectedError = SAME_PARENT_AND_NODE_ID;

			// Входное дерево
			int inputSize = 3;
			int inputRoot = 1;
			vector<Node> inputTree = { {-1, -1, -1, ""}, {1, 2, 3, "+"}, {1, -1, -1, "c"}, {1, -1, -1, "b"}};

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(lackOfOperands)
		{
			ErrorType expectedError = LACK_OF_OPERANDS;

			// Входное дерево
			int inputSize = 2;
			int inputRoot = 1;
			vector<Node> inputTree = { {-1, -1, -1, ""}, {-1, 2, -1, "+"}, {1, -1, -1, "10"} };

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(nodeIdOutOfRange)
		{
			ErrorType expectedError = NODE_ID_OUT_OF_RANGE;

			// Входное дерево
			int inputSize = 5;
			int inputRoot = 0;
			vector<Node> inputTree = { {-1, 2, 3, "-"}, {1, 4, 5, "+"}, {1, NotExist, NotExist, "c"}, {2, NotExist, NotExist, "a"}, {2, NotExist, NotExist, "b"} };

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(invalidNodeSymb)
		{
			ErrorType expectedError = INVALID_NODE_SYMBOL;

			// Входное дерево
			int inputSize = 3;
			int inputRoot = 1;
			vector<Node> inputTree = { {-1, -1, -1, ""}, {-1, 2, 3, "+"}, {1, -1, -1, "(a*b)"}, {1, -1, -1, "-c-"} };

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(notRightLink)
		{
			ErrorType expectedError = NOT_RIGHT_LINK;

			// Входное дерево
			int inputSize = 3;
			int inputRoot = 1;
			vector<Node> inputTree = { {-1, -1, -1, ""}, {-1, 2, 3, "+"}, {1, -1, -1, "c"}, {6, -1, -1, "b"} };

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(unexpectableParent)
		{
			ErrorType expectedError = UNEXCEPTABLE_PARENT_ID;

			// Входное дерево
			int inputSize = 6;
			int inputRoot = 1;
			vector<Node> inputTree = {	{-1, -1, -1, ""}, 
										{-1, 3, 4, "+"}, 
										{5, 5, 6, "+"}, 
										{1, -1, -1, "a"},
										{1, -1, -1, "b"},
										{2, -1, -1, "c"},
										{2, -1, -1, "d"}, };

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(noRoot)
		{
			ErrorType expectedError = NO_ROOT;

			// Входное дерево
			int inputSize = 3;
			int inputRoot = 1;
			vector<Node> inputTree = { {-1, -1, -1, ""}, {12, 2, 3, "+"}, {1, -1, -1, "a"}, {1, -1, -1, "b"} };

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(treeSizeOutOfRange)
		{
			ErrorType expectedError = TREE_SIZE_OUT_OF_RANGE;

			// Входное дерево
			int inputSize = 31;
			int inputRoot = 31;
			vector<Node> inputTree = { {-1, -1, -1, ""}};
			initializeFullTree(inputTree);
			inputTree.push_back({-1, -1, -1, "a"});

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(invalidNumberOfNodes)
		{
			ErrorType expectedError = INVALID_NUMBER_OF_NODES;

			// Входное дерево
			int inputSize = 4;
			int inputRoot = 1;
			vector<Node> inputTree = { {-1, -1, -1, ""}, {-1, 2, 3, "+"}, {1, -1, -1, "a"}, {1, -1, -1, "b"} };

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}

		TEST_METHOD(noError)
		{
			ErrorType expectedError = NO_ERROR;

			// Входное дерево
			int inputSize = 3;
			int inputRoot = 1;
			vector<Node> inputTree = { {-1, -1, -1, ""}, {-1, 2, 3, "+"}, {1, -1, -1, "a"}, {1, -1, -1, "b"} };

			ErrorType error = checkOnErrors(inputSize, inputTree, inputRoot);

			Assert::IsTrue(error == expectedError);
		}
	};
}
