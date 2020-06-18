#include <iostream>
#include "ChatClient.h"
#include "Utility.h"

/////////////////////////////////////
//	Client-side code
/////////////////////////////////////

int main(int argc, char* argv[])
{
	Utility::ResizeWindow(800, 800);

	ChatClient chat;

	std::cout << "+============================================+" << std::endl;
	std::cout << R"(=Beginning Chat App Client=)" << std::endl;
	std::cout << R"(Enter the IP of the Server below)" << std::endl;
	std::cout << R"(To Retry a connection, type 'retry')" << std::endl;
	std::cout << R"(To Exit the application, type 'quit')" << std::endl;
	std::cout << "+============================================+" << std::endl;
	

	std::string address;

	chat.EnterIP(address);

	chat.Startup(1234, chat.GetServerAddress().c_str());
	chat.Chat();
	chat.Shutdown();

	return 0;
}