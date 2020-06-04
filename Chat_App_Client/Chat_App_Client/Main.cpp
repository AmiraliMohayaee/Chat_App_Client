#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>


/////////////////////////////////////
//	Client-side code
/////////////////////////////////////

// container for storing outgoing server
// message
char incomingMsg[2000];


IPaddress ip;


TCPsocket socket = nullptr;


bool Initialize()
{
	// Initializing all SDL components
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL failed to initialise." << std::endl;
		return 0;
	}

	// Initializing SDL net 
	if (SDLNet_Init() == -1)
	{
		std::cout << "SDL Network failed to initialise." << std::endl;
		return 0;
	}

	return true;
}

void Shutdown()
{
	// Setting off SDL and SDL net 
	SDL_Quit();
	SDLNet_Quit();
}



int main(int argc, char* argv[])
{

	if (!Initialize())
	{
		return 0;
	}


	// 
	if (SDLNet_ResolveHost(&ip, "localhost", 1234) == -1)
	{
		std::cout << "Failed to open connection with host" << std::endl;
		system("pause");
		return 0;
	}

	// Establishing the server's listerner socket 
	// to prepare for connection with a client
	// This will happen after we assured that the 
	// server is created without errors
	socket = SDLNet_TCP_Open(&ip);


	if (socket == nullptr)
	{
		std::cout << "Could not crete a socket to server.\n" << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "Connection to server made." << std::endl << std::endl;


	if (SDLNet_TCP_Recv(socket, incomingMsg, 2000) <= 0)
	{
		std::cout << "Could not recieve message from Server.\n" << std::endl;
	}
	else
	{
		std::cout << "Message succesfully recieved: " << incomingMsg << std::endl;
	}


	SDLNet_TCP_Close(socket);

	Shutdown();

	system("Pause");
	return 0;
}