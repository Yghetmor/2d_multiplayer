#include "online_game.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

OnlineGame::OnlineGame(unsigned int instance_id)
    : Game(), m_instance_id{instance_id} {}

void OnlineGame::gameLoop()
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6969);
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        std::cout << "Invalid server address / Address not supported" << std::endl;
        return;
    }
    
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) != 0)
    {
        std::cout << "Couldn't connect to server" << std::endl;
        return;
    }
    std::cout << "Connected to server" << std::endl;

    // int instance_id = htonl(m_instance_id);
    if (send(client_socket, &m_instance_id, sizeof(m_instance_id), 0) != sizeof(m_instance_id)) 
    {
        std::cout << "Couldn't send insance id" << std::endl;
        return;
    }

    std::cout << "Connected to game instance" << std::endl;

    while (isRunning)
    {
        handleEvent();
    }
}

void OnlineGame::handleEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
        {
			isRunning = false;
        }

        m_player->handle_event(event);
	}
}
