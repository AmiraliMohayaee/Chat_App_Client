#include "ChatClient.h"
#include <iostream>
#include <string>


ChatClient::ChatClient()
{
	m_sendMsg = "";
	m_recvMsg = "";

	IsTyping = false;

	m_client = new TCPClient();
}

ChatClient::~ChatClient()
{
	delete m_client;
}

bool ChatClient::Startup(Uint16 port, const char* IP)
{
	if (!m_client->Initialize())
	{
		std::cout << "Failed to initialize SDL." << std::endl;
		return false;
	}

	if (!m_client->Init(port, IP))
	{
		std::cout << "Failed to Create Server." << std::endl;
		return false;
	}

	if (!m_client->OpenSocket())
	{
		return false;
	}
}

void ChatClient::Chat()
{
	// Setting up threading for send and recieve
	SendThread = std::thread(&ChatClient::SendingMsg, this);
	RecvThread = std::thread(&ChatClient::RecievingMsg, this);
	SendThread.detach();
	RecvThread.detach();

	bool isChatActive = true;

	while (isChatActive)
	{
		if (m_sendMsg == "end")
		{
			isChatActive = false;
		}
	}
}

void ChatClient::EnterIP(std::string add)
{
	// Allow for user to input IP add
	std::cout << "Please enter the IP of the host: ";
	std::getline(std::cin, add);

	m_address = add;
}

const std::string ChatClient::GetServerAddress()
{
	return m_address;
}

void ChatClient::SendingMsg()
{
	while (m_sendMsg != "end")
	{
		// Enter a message into chat
		std::cout << ">";
		std::getline(std::cin, m_sendMsg);
		// Send message to client
		//std::lock_guard<std::mutex> lock(m_lock);
		m_client->Send(m_sendMsg);
		//SDL_Delay(100);
	}

	std::cout << "Server Exited the chat application. Shutting down..." << std::endl;
}

void ChatClient::RecievingMsg()
{
	while (m_recvMsg != "end")
	{
		//std::lock_guard<std::mutex> lock(m_lock);
		// Receive message from client
		m_client->Recv();
		m_recvMsg = m_client->GetRecvMsg();
		std::cout << m_recvMsg << std::endl;
		//SDL_Delay(500);
	}

	std::cout << "Client Exited the chat application. Shutting down..." << std::endl;
}

void ChatClient::Shutdown()
{
	if (SendThread.joinable())
		SendThread.join();
	if (RecvThread.joinable())
		RecvThread.join();

	m_client->CloseSocket();
	m_client->Shutdown();
}
