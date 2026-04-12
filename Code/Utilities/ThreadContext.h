#pragma once

#include "LogRecord.h"

#include <thread>
#include <string>

namespace logger
{
    class ThreadContext
    {
    public:
        static void SetLabel(const std::string& label)
        {
            s_threadLabel = label;
        }

        static void ClearLabel()
        {
            s_threadLabel.clear();
        }

        static const std::string& GetLabel()
        {
            return s_threadLabel;
        }

        static std::thread::id GetId()
        {
            return std::this_thread::get_id();
        }

        static ThreadInfo GetInfo()
        {
            ThreadInfo ti;
            ti.id = GetId();
            ti.optional_thread_label = s_threadLabel;
            return ti;
        }

    private:
        static thread_local std::string s_threadLabel;
    };

    inline thread_local std::string ThreadContext::s_threadLabel{};
}