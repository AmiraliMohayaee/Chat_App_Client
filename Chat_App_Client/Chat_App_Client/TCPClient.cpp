#include "TCPClient.h"
#include <iostream>


TCPClient::TCPClient()
{
}

bool TCPClient::Init(Uint16 port, const char* IPAddress)
{
	if (SDLNet_ResolveHost(&m_ip, IPAddress, port) == -1)
	{
		std::cout << "Client Could not connect." << std::endl;
		return false;
	}
	else
	{
		std::cout << "Server found. Connection being made..." << std::endl;
		return true;
	}
}

bool TCPClient::OpenSocket()
{
	m_socket = SDLNet_TCP_Open(&m_ip);


	if (m_socket == nullptr)
	{
		std::cout << "Could not open client's socket." << std::endl;
		return false;
	}
	else
	{
		std::cout << "Client socket ready for connection..." << std::endl;
		return true;
	}
}

bool TCPClient::Send(const std::string& msg)
{
	int length = msg.length() + 1;

	if (SDLNet_TCP_Send(m_socket, msg.c_str(), length) < length)
	{
		std::cout << "Message could not be sent. Possble loss of data." << std::endl;
		return false;
	}
	else
	{
		m_sendMsg = msg;
		std::cout << "Message succesfully sent." << std::endl;
		return true;
	}
}

const std::string TCPClient::GetSentMsg()
{
	return m_sendMsg;
}

const std::string TCPClient::GetRecvMsg()
{
	return m_recvMsg;
}

bool TCPClient::Recv()
{
	// container for storing outgoing server
	// message
	char incomingMsg[100];

	if (SDLNet_TCP_Recv(m_socket, incomingMsg, 100) <= 0)
	{
		std::cout << "Could not recieve message from Server.\n" << std::endl;
		return false;
	}
	else
	{
		m_recvMsg = incomingMsg;
		//std::cout << "Message succesfully recieved: " << incomingMsg << std::endl;
		return true;
	}
}

void TCPClient::CloseSocket()
{
	SDLNet_TCP_Close(m_socket);
}