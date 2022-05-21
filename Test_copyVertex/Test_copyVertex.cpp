#include "pch.h"
#include "CppUnitTest.h"
#include "../OpenBrackets/OpenBracketsHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestcopyVertex
{
	TEST_CLASS(TestcopyVertex)
	{
	public:
		
		// Копирование вершины из начала вектора
		TEST_METHOD(copyingVertexFromVectorBeginning) 
		{
			int root = 1;
			int copyingVertexIndex = 1;
 			vector<Node> inputVector = { {NotExist, NotExist, NotExist, "\0"}, {-1, 2, 3, "*"}, {1, NotExist, NotExist, "a"}, {1, 4, 5, "+"}, {3, NotExist, NotExist, "b"}, {3, NotExist, NotExist, "c"}};
			int expectedPos = 6;

			vector<Node> expectedVector = { {-1, -1, -1, "\0"},
											{-1, 7, 8, "*"},
											{1, -1, -1, "a"},
											{1, 9, 10, "+"},
											{3, -1, -1, "b"},
											{3, -1, -1, "c"},
											{-1, 2, 3, "*"},
											{1, -1, -1, "a"},
											{1, 4, 5, "+"},
											{3, -1, -1, "b"},
											{3, -1, -1, "c"} };

			int pos = copyVertex(inputVector, copyingVertexIndex);
			bool isEqualVectors = isEqualTrees(expectedVector, root, inputVector, root);
			Assert::AreEqual(expectedPos, pos);
			Assert::IsTrue(isEqualVectors);
		}

		// Копирование вершины из конца вектора
		TEST_METHOD(copyingVertexFromVectorEnding)
		{
			int root = 1;
			int copyingVertexIndex = 5;
			vector<Node> inputVector = { {NotExist, NotExist, NotExist, "\0"}, {-1, 2, 3, "*"}, {1, NotExist, NotExist, "a"}, {1, 4, 5, "+"}, {3, NotExist, NotExist, "b"}, {3, NotExist, NotExist, "c"} };
			int expectedPos = 6;

			vector<Node> expectedVector = { {-1, -1, -1, "\0"},
											{-1, 2, 3, "*"},
											{1, -1, -1, "a"},
											{1, 4, 5, "+"},
											{3, -1, -1, "b"},
											{3, -1, -1, "c"},
											{3, -1, -1, "c"} };

			int pos = copyVertex(inputVector, copyingVertexIndex);
			bool isEqualVectors = isEqualTrees(expectedVector, root, inputVector, root);
			Assert::AreEqual(expectedPos, pos);
			Assert::IsTrue(isEqualVectors);
		}

		// Копирование вершины из середины вектора
		TEST_METHOD(copyingVertexFromVectorMiddle)
		{
			int root = 1;
			int copyingVertexIndex = 3;
			vector<Node> inputVector = { {NotExist, NotExist, NotExist, "\0"}, {-1, 2, 3, "*"}, {1, NotExist, NotExist, "a"}, {1, 4, 5, "+"}, {3, NotExist, NotExist, "b"}, {3, NotExist, NotExist, "c"} };
			int expectedPos = 6;

			vector<Node> expectedVector = { {-1, -1, -1, "\0"},
											{-1, 2, 3, "*"},
											{1, -1, -1, "a"},
											{1, 7, 8, "+"},
											{3, -1, -1, "b"},
											{3, -1, -1, "c"},
											{1, 4, 5, "+"},
											{3, -1, -1, "b"},
											{3, -1, -1, "c"} };

			int pos = copyVertex(inputVector, copyingVertexIndex);
			bool isEqualVectors = isEqualTrees(expectedVector, root, inputVector, root);
			Assert::AreEqual(expectedPos, pos);
			Assert::IsTrue(isEqualVectors);
		}

		// Значение копируемой вершины: алфавитные символы
		TEST_METHOD(copyingVertexFromVectorAlphabetValue)
		{
			int root = 1;
			int copyingVertexIndex = 5;
			vector<Node> inputVector = { {NotExist, NotExist, NotExist, "\0"}, {-1, 2, 3, "*"}, {1, NotExist, NotExist, "a"}, {1, 4, 5, "+"}, {3, NotExist, NotExist, "b"}, {3, NotExist, NotExist, "alpHabet"} };
			int expectedPos = 6;

			vector<Node> expectedVector = { {-1, -1, -1, "\0"},
											{-1, 2, 3, "*"},
											{1, -1, -1, "a"},
											{1, 4, 5, "+"},
											{3, -1, -1, "b"},
											{3, -1, -1, "alpHabet"},
											{3, -1, -1, "alpHabet"} };

			int pos = copyVertex(inputVector, copyingVertexIndex);
			bool isEqualVectors = isEqualTrees(expectedVector, root, inputVector, root);
			Assert::AreEqual(expectedPos, pos);
			Assert::IsTrue(isEqualVectors);
		}

		// Значение копируемой вершины: цифровые символы
		TEST_METHOD(copyingVertexFromVectorCyfralValue)
		{
			int root = 1;
			int copyingVertexIndex = 3;
			vector<Node> inputVector = { {NotExist, NotExist, NotExist, "\0"}, {-1, 2, 3, "*"}, {1, NotExist, NotExist, "a"}, {1, 4, 5, "+"}, {3, NotExist, NotExist, "b"}, {3, NotExist, NotExist, "12345"} };
			int expectedPos = 6;

			vector<Node> expectedVector = { {-1, -1, -1, "\0"},
											{-1, 2, 3, "*"},
											{1, -1, -1, "a"},
											{1, 4, 5, "+"},
											{3, -1, -1, "b"},
											{3, -1, -1, "12345"},
											{3, -1, -1, "12345"} };

			int pos = copyVertex(inputVector, copyingVertexIndex);
			bool isEqualVectors = isEqualTrees(expectedVector, root, inputVector, root);
			Assert::AreEqual(expectedPos, pos);
			Assert::IsTrue(isEqualVectors);
		}

		// Значение копируемой вершины: смешанные символы
		TEST_METHOD(copyingVertexFromVectorMixedValue)
		{
			int root = 1;
			int copyingVertexIndex = 3;
			vector<Node> inputVector = { {NotExist, NotExist, NotExist, "\0"}, {-1, 2, 3, "*"}, {1, NotExist, NotExist, "a"}, {1, 4, 5, "+"}, {3, NotExist, NotExist, "b"}, {3, NotExist, NotExist, "alpHabet12345"} };
			int expectedPos = 6;

			vector<Node> expectedVector = { {-1, -1, -1, "\0"},
											{-1, 2, 3, "*"},
											{1, -1, -1, "a"},
											{1, 4, 5, "+"},
											{3, -1, -1, "b"},
											{3, -1, -1, "alphabet12345"},
											{3, -1, -1, "alpHabet12345"} };

			int pos = copyVertex(inputVector, copyingVertexIndex);
			bool isEqualVectors = isEqualTrees(expectedVector, root, inputVector, root);
			Assert::AreEqual(expectedPos, pos);
			Assert::IsTrue(isEqualVectors);
		}

		// Отсутствие вершины с запрашиваемым для копирования индексом в векторе
		TEST_METHOD(noVertexWithCurrentCopyingIndexInVector)
		{
			int root = 1;
			int copyingVertexIndex = -12;
			vector<Node> inputVector = { {NotExist, NotExist, NotExist, "\0"}, {-1, 2, 3, "*"}, {1, NotExist, NotExist, "a"}, {1, 4, 5, "+"}, {3, NotExist, NotExist, "b"}, {3, NotExist, NotExist, "c"} };
			int expectedPos = -1;

			vector<Node> expectedVector = { {NotExist, NotExist, NotExist, "\0"}, {-1, 2, 3, "*"}, {1, NotExist, NotExist, "a"}, {1, 4, 5, "+"}, {3, NotExist, NotExist, "b"}, {3, NotExist, NotExist, "c"} };

			int pos = copyVertex(inputVector, copyingVertexIndex);
			bool isEqualVectors = isEqualTrees(expectedVector, root, inputVector, root);
			Assert::AreEqual(expectedPos, pos);
			Assert::IsTrue(isEqualVectors);
		}

		// Идентификаторы в дереве заданы не последовательно
		TEST_METHOD(copyingVertexFromVectorWithNotConsequentiallyIDOfNodes)
		{
			int root = 1;
			int copyingVertexIndex = 3;
			vector<Node> inputVector = { {NotExist, NotExist, NotExist, "\0"}, {NotExist, NotExist, NotExist, "\0"}, {3, NotExist, NotExist, "a"}, 
										{-1, 2, 4, "*"}, {3, 5, 6, "+"}, {4, NotExist, NotExist, "b"}, {4, NotExist, NotExist, "c"} };
			int expectedPos = 7;

			vector<Node> expectedVector = { {-1, -1, -1, "\0"},
											{-1, -1, -1, "\0"},
											{3, -1, -1, "a"},
											{-1, 8, 9, "*"},
											{3, 10, 11, "+"},
											{4, -1, -1, "b"},
											{4, -1, -1, "c"},
											{-1, 2, 4, "*"},
											{3, -1, -1, "a"},
											{3, 5, 6, "+"},
											{4, -1, -1, "b"},
											{4, -1, -1, "c"} };

			int pos = copyVertex(inputVector, copyingVertexIndex);
			bool isEqualVectors = isEqualTrees(expectedVector, root, inputVector, root);
			Assert::AreEqual(expectedPos, pos);
			Assert::IsTrue(isEqualVectors);
		}
	};
}
