#include "pch.h"
#include "CppUnitTest.h"
#include "../OpenBrackets/OpenBracketsHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestcrashOutput
{
	TEST_CLASS(TestcrashOutput)
	{
	public:

		TEST_METHOD(sendingErrorNO_ERROR)
		{
			bool isCrashOutputSuccess = crashOutput(NO_ERROR);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorINPUT_FILE_NOT_EXIST)
		{
			bool isCrashOutputSuccess = crashOutput(INPUT_FILE_NOT_EXIST);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorUNKNOWN_FILE_EXTENSION)
		{
			bool isCrashOutputSuccess = crashOutput(UNKNOWN_FILE_EXTENSION);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorOUTPUT_FILE_CREATION_FAILED)
		{
			bool isCrashOutputSuccess = crashOutput(OUTPUT_FILE_CREATION_FAILED);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorWRONG_DATA_FORMAT)
		{
			bool isCrashOutputSuccess = crashOutput(WRONG_DATA_FORMAT);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorNOT_BINARY_TREE)
		{
			bool isCrashOutputSuccess = crashOutput(NOT_BINARY_TREE);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorSAME_NODES_ID)
		{
			bool isCrashOutputSuccess = crashOutput(SAME_NODES_ID);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorSAME_PARENT_AND_NODE_ID)
		{
			bool isCrashOutputSuccess = crashOutput(SAME_PARENT_AND_NODE_ID);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorLACK_OF_OPERANDS)
		{
			bool isCrashOutputSuccess = crashOutput(LACK_OF_OPERANDS);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorINVALID_NODE_SYMBOL)
		{
			bool isCrashOutputSuccess = crashOutput(INVALID_NODE_SYMBOL);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorUNSUPPORTED_OPERATION)
		{
			bool isCrashOutputSuccess = crashOutput(UNSUPPORTED_OPERATION);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorUNEXCEPTABLE_PARENT_ID)
		{
			bool isCrashOutputSuccess = crashOutput(UNEXCEPTABLE_PARENT_ID);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorNO_ROOT)
		{
			bool isCrashOutputSuccess = crashOutput(NO_ROOT);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorTREE_SIZE_OUT_OF_RANGE)
		{
			bool isCrashOutputSuccess = crashOutput(TREE_SIZE_OUT_OF_RANGE);
			Assert::IsTrue(isCrashOutputSuccess);
		}

		TEST_METHOD(sendingErrorINVALID_NUMBER_OF_NODES)
		{
			bool isCrashOutputSuccess = crashOutput(INVALID_NUMBER_OF_NODES);
			Assert::IsTrue(isCrashOutputSuccess);
		}
	};
}
