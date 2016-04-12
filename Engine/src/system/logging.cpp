#include "logging.h"

#include "Poco/AutoPtr.h"

namespace robolab {
	namespace system {

		Poco::AutoPtr<Poco::Logger> Logging::logManager;
		Poco::AutoPtr<Poco::Channel> Logging::logChannel;
		Poco::AutoPtr<Poco::PatternFormatter> Logging::logformmatter;
		Poco::AutoPtr<Poco::FormattingChannel> Logging::logFormattingChannel;
		bool Logging::date = true;
		bool Logging::time = true;

		Poco::AutoPtr<Poco::Channel> Logging::createConsoleChannel() {
			if (POCO_OS == POCO_OS_WINDOWS_NT)
			{
				Poco::AutoPtr<Poco::WindowsColorConsoleChannel> windowsChannel(new Poco::WindowsColorConsoleChannel());
				windowsChannel->setProperty("traceColor", "gray");
				windowsChannel->setProperty("debugColor", "gray");
				windowsChannel->setProperty("informationColor", "lightGreen");
				windowsChannel->setProperty("noticeColor", "lightBlue");
				windowsChannel->setProperty("warningColor", "yellow");
				windowsChannel->setProperty("errorColor", "lightRed");
				windowsChannel->setProperty("criticalColor", "red");
				windowsChannel->setProperty("fatalColor", "red");
				return windowsChannel;
			}
			else if (POCO_OS == POCO_OS_LINUX) {
				Poco::AutoPtr<Poco::ColorConsoleChannel> unixChannel(new Poco::ColorConsoleChannel());
				unixChannel->setProperty("traceColor", "gray");
				unixChannel->setProperty("debugColor", "gray");
				unixChannel->setProperty("informationColor", "lightGreen");
				unixChannel->setProperty("noticeColor", "lightBlue");
				unixChannel->setProperty("warningColor", "yellow");
				unixChannel->setProperty("errorColor", "lightRed");
				unixChannel->setProperty("criticalColor", "red");
				unixChannel->setProperty("fatalColor", "red");
				return unixChannel;
			}
		}

		void Logging::checkLogManager() {
			if (!logManager) {
				logformmatter = new Poco::PatternFormatter;
				logformmatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: [%p] --> %t");
				logFormattingChannel = new Poco::FormattingChannel(logformmatter, createConsoleChannel());
				Poco::Logger::root().setChannel(logFormattingChannel);
				logManager = &Poco::Logger::get("RoboLab");
			}
		}

		void Logging::enableDate() {
			date = true;
			setFormat();
		}

		void Logging::disableDate() {
			date = false;
			setFormat();
		}

		void Logging::enableTime() {
			time = true;
			setFormat();
		}

		void Logging::disableTime() {
			time = false;
			setFormat();
		}

		void Logging::setFormat() {
			checkLogManager();
			if(date && time )
				logformmatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s : [%p] --> %t");
			if (date && !time)
				logformmatter->setProperty("pattern", "%Y-%m-%d %s : [%p] --> %t");
			if (!date && time)
				logformmatter->setProperty("pattern", "%H:%M:%S %s : [%p] --> %t");
		}

		void Logging::console(LoggerEvent type, const std::string& msg, const std::string& sourceName ) {
			checkLogManager();
			Poco::Message message;
			message.setSource(sourceName);
			message.setText(msg);
			switch (type)
			{
			case robolab::system::LOG_ERROR:
				message.setPriority(Poco::Message::PRIO_ERROR);
				break;
			case robolab::system::LOG_WARNING:
				message.setPriority(Poco::Message::PRIO_WARNING);
				break;

			case robolab::system::LOG_INFORMATION:
				message.setPriority(Poco::Message::PRIO_INFORMATION);
				break;
			case robolab::system::LOG_NOTICE:
				message.setPriority(Poco::Message::PRIO_NOTICE);
				break;
			}
			logManager->log(message);
		}

	}
}