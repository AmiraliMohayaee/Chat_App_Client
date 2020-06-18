#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <string>
#include "TCPClient.h"
#include <thread>
#include <mutex>

class ChatClient
{
public:
	ChatClient();
	~ChatClient();
	bool Startup(Uint16 port, const char* IP);
	void Chat();

	void EnterIP(const std::string add);
	const std::string GetServerAddress();


	void SendingMsg();
	void RecievingMsg();

	void Shutdown();
	

private:
	std::string m_sendMsg;
	std::string m_recvMsg;
	std::string m_address;

	bool IsTyping;

	TCPClient* m_client;

	std::mutex m_lock;
	std::thread SendThread;
	std::thread RecvThread;
};

#endif