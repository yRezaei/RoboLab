#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <memory>
#include <Poco/Platform.h>

#if (POCO_OS == POCO_OS_WINDOWS_NT)
#include <Poco/WindowsConsoleChannel.h>
#endif
#include <Poco/ConsoleChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>


namespace robolab {
	namespace system {

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define LOCATION __FILE__ " : " TOSTRING(__LINE__)

		enum LoggerEvent
		{
			LOG_ERROR,
			LOG_WARNING,
			LOG_INFORMATION,
			LOG_NOTICE
		};

		class Logging
		{
		private:
			static Poco::AutoPtr<Poco::Logger> logManager;
			static Poco::AutoPtr<Poco::Channel> logChannel;
			static Poco::AutoPtr<Poco::PatternFormatter> logformmatter;
			static Poco::AutoPtr<Poco::FormattingChannel> logFormattingChannel;
			static bool date;
			static bool time;
		private:
			static Poco::AutoPtr<Poco::Channel> createConsoleChannel();
			static void checkLogManager();
			static void setFormat();
		public:
			static void enableDate();
			static void disableDate();
			static void enableTime();
			static void disableTime();
			static void console(LoggerEvent type, const std::string& source, const std::string& msg = "RoboLab");
		};


	}
}

#endif // ! LOG_H
