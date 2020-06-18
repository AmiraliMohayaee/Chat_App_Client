#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H


#include "TCPConnection.h"


class TCPClient : public TCPConnection
{
public:
	TCPClient();
	bool Init(Uint16 port, const char* IPAddress);
	bool OpenSocket();

	bool Send(const std::string& msg);
	bool Recv();

	const std::string GetSentMsg();
	const std::string GetRecvMsg();

	void CloseSocket();

private:
	std::string m_sendMsg;
	std::string m_recvMsg;
};



#endif