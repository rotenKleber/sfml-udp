#include <iostream>
#include <cstddef>
#include <SFML/Network.hpp>

class Server
{
public:
	Server() {
				value = 0;
				socket.bind(8001);
				};
				
	void run();
	
	sf::UdpSocket socket;
	
private:
	int value;
};

void Server::run()
{
	std::cout << "\n*** Server Created ***\n";
	std::cout << "Enter value: ";

	std::cin >> value;

	sf::Packet packet;
	packet << value;

	sf::IpAddress recipient = "127.0.0.1";
	unsigned short port = 8000;

	socket.send(packet, recipient, port);
}


class Client
{
public:
	Client() {
				socket.bind(8000);
				};
	
	void run();
	sf::UdpSocket socket;	
};

void Client::run()
{
	std::cout << "\n*** Client Created ***\n";
	
	while(1)
	{
		sf::Packet packet;
		
		sf::IpAddress sender = "127.0.0.1";
		unsigned short port = 8001;
		
		socket.receive(packet, sender, port);
		
		std::cout << packet << ", ";
	}
}

int main()
{
	Server* server = nullptr;
	Client* client = nullptr;
	
	std::cout << "==== Project UDP ====\n";
	
	char mode;
	
	do
	{
	std::cout << "Server (S) or Client (C)? ";
	
	std::cin >> mode;
	
	std::cout << std::endl;
	
	} while( !(mode == 's' || mode == 'c') );
	
	if(mode == 's')
	{
		server = new Server();
		
		server->run();
	}
	else if(mode == 'c')
	{
		client = new Client();
		
		client->run();
	}
	
	if(server != nullptr)
		delete server;
		
	if(client != nullptr)
		delete client;
	
	return 0;
}
