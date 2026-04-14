#include "CppUnitTest.h"

#include <Utilities/ThreadContext.h>
#include <string>
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(ThreadContextTests)
	{
	public:
		TEST_METHOD(ThreadContext_ClearLabel_WhenAlreadyEmpty_RemainsEmpty)
		{
			logger::ThreadContext::ClearLabel();

			Assert::AreEqual(std::string(""), logger::ThreadContext::GetLabel());
		}

		TEST_METHOD(ThreadContext_ClearLabel_ResetsCurrentThreadLabel)
		{
			logger::ThreadContext::SetLabel("Main");

			logger::ThreadContext::ClearLabel();

			Assert::AreEqual(std::string(""), logger::ThreadContext::GetLabel());
		}

		TEST_METHOD(ThreadContext_SetLabel_UpdatesCurrentThreadLabel)
		{
			std::string name = "Main";

			logger::ThreadContext::SetLabel(name);

			Assert::AreEqual(name, logger::ThreadContext::GetLabel());
		}

		TEST_METHOD(ThreadContext_SetLabel_OverwritesPreviousLabel)
		{
			std::string name = "Main";

			logger::ThreadContext::SetLabel(name);

			Assert::AreEqual(name, logger::ThreadContext::GetLabel());

			name = "Worker";

			logger::ThreadContext::SetLabel(name);

			Assert::AreEqual(name, logger::ThreadContext::GetLabel());
		}

		TEST_METHOD(ThreadContext_GetId_ReturnsCurrentThreadId)
		{
			std::thread::id id = std::this_thread::get_id();

			Assert::IsTrue(id == logger::ThreadContext::GetId());
		}

		TEST_METHOD(ThreadContext_GetInfo_ReturnsCurrentThreadInfo)
		{
			std::string name = "Main";

			logger::ThreadContext::SetLabel(name);

			std::thread::id id = std::this_thread::get_id();

			ThreadInfo ti = logger::ThreadContext::GetInfo();

			Assert::AreEqual(name, ti.optional_thread_label);
			Assert::IsTrue(id == ti.id);
		}

		TEST_METHOD(ThreadContext_GetInfo_AfterClear_ReturnsEmptyLabelForCurrentThread)
		{
			logger::ThreadContext::SetLabel("Main");

			logger::ThreadContext::ClearLabel();

			std::string name = "";
			std::thread::id id = std::this_thread::get_id();

			ThreadInfo ti = logger::ThreadContext::GetInfo();

			Assert::AreEqual(name, ti.optional_thread_label);
			Assert::IsTrue(id == ti.id);
		}

		TEST_METHOD(ThreadContext_NewThread_DoesNotInheritParentLabel)
		{
			logger::ThreadContext::SetLabel("Main");

			std::string childLabel;

			std::thread t([&]()
				{
					childLabel = logger::ThreadContext::GetLabel();
				});

			t.join();

			Assert::AreEqual(std::string(""), childLabel);
			Assert::AreEqual(std::string("Main"), logger::ThreadContext::GetLabel());
		}

		TEST_METHOD(ThreadContext_NewThread_ClearLabel_OnlyAffectsThatThread)
		{
			logger::ThreadContext::SetLabel("Main");

			std::string childLabel;

			std::thread t([&]()
				{
					logger::ThreadContext::SetLabel("Worker");
					logger::ThreadContext::ClearLabel();
					childLabel = logger::ThreadContext::GetLabel();
				});

			t.join();

			Assert::AreEqual(std::string(""), childLabel);
			Assert::AreEqual(std::string("Main"), logger::ThreadContext::GetLabel());
		}

		TEST_METHOD(ThreadContext_NewThread_HasIndependentLabel)
		{
			logger::ThreadContext::SetLabel("Main");

			std::string childLabel;

			std::thread t([&]()
				{
					logger::ThreadContext::SetLabel("Worker");
					childLabel = logger::ThreadContext::GetLabel();
				});

			t.join();

			Assert::AreEqual(std::string("Worker"), childLabel);
			Assert::AreEqual(std::string("Main"), logger::ThreadContext::GetLabel());
		}

		TEST_METHOD(ThreadIds_AreDifferentAcrossThreads)
		{
			std::thread::id id1 = std::this_thread::get_id();
			std::thread::id id2;

			std::thread t([&]()
				{
					id2 = std::this_thread::get_id();
				});

			t.join();

			Assert::IsTrue(id1 != id2);
		}

		TEST_METHOD(ThreadInfo_AreDifferentAcrossThreads)
		{
			logger::ThreadContext::SetLabel("Main");

			ThreadInfo ti1 = logger::ThreadContext::GetInfo();
			ThreadInfo ti2;

			std::thread t([&]()
				{
					logger::ThreadContext::SetLabel("Worker");
					ti2 = logger::ThreadContext::GetInfo();
				});

			t.join();

			Assert::IsTrue(ti1.id != ti2.id);

			Assert::AreNotEqual(ti1.optional_thread_label, ti2.optional_thread_label);
		}
	};
}