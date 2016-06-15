/*
* logging.h
*
* Copyright 2016 Yashar Abbasalizadeh Rezaei <yashar.a.rezaei@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*
*/
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
