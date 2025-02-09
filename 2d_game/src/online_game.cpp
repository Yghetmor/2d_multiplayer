#include "online_game.h"
#include "projectile.h"
#include <cstdint>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

OnlineGame::OnlineGame(unsigned int instance_id)
    : Game(), m_instance_id{instance_id} {}

void OnlineGame::gameLoop()
{
    // Creating TCP socket to connect to game instance on server
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

    if (send(client_socket, &m_instance_id, sizeof(m_instance_id), 0) != sizeof(m_instance_id)) 
    {
        std::cout << "Couldn't send instance id" << std::endl;
        return;
    }

    std::cout << "Connected to game instance" << std::endl;

    uint16_t udp_port = 40000;

    // Creating UDP socket to receive entity info on
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in udp_address;
    udp_address.sin_family = AF_INET;
    udp_address.sin_port = htons(udp_port);
    if (inet_pton(AF_INET, "127.0.0.1", &udp_address.sin_addr) <= 0)
    {
        std::cout << "Invalid server address / Address not supported" << std::endl;
        return;
    }

    if (connect(udp_socket, (struct sockaddr*)&udp_address, sizeof(udp_address)) != 0)
    {
        std::cout << "Couldn't connect to server with UDP" << std::endl;
        return;
    }


    while (isRunning)
    {
        m_monsters.clear();
        m_projectiles.clear();
        m_player->reset_clicked();

        handleEvent();
        m_player->update_position(&m_camera);
        m_camera.update(m_player->get_x(), m_player->get_y(), m_player->get_width(), m_player->get_height());

        send_player_pos(udp_socket);
        unpack_positions(udp_socket);

        draw();
    }

    close(client_socket);
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

void OnlineGame::unpack_positions(int socket)
{
    uint8_t buf[1024];
    int rec_count = recv(socket, &buf, sizeof(buf), 0);
    while (rec_count < 2)
    {
        rec_count += recv(socket, &buf + rec_count, sizeof(buf) - rec_count, 0);
    }

    uint16_t rec_len = static_cast<uint16_t>(buf[0]) + (static_cast<uint16_t>(buf[1]) << 8);
    while (rec_count < rec_len + 2)
    {
        rec_count += recv(socket, &buf + rec_count, sizeof(buf) - rec_count, 0);
    }

    uint8_t *moving_buf_pointer = &buf[2];
    bool is_done = false;
    while (!is_done)
    {
        switch (*moving_buf_pointer)
        {
        case '+':
            break;
        case '-':
            moving_buf_pointer += 1;
            unpack_monster(&moving_buf_pointer);
            break;
        case '*':
            moving_buf_pointer += 1;
            unpack_projectile(&moving_buf_pointer);
            break;
        default:
            is_done = true;
        }
    }

}

void OnlineGame::unpack_monster(uint8_t **buf)
{
    uint16_t pos_x;
    uint16_t pos_y;
    int8_t health;
    uint16_t angle;

    pos_x = static_cast<uint16_t>(**buf) + (static_cast<uint16_t>((*((*buf) + 1))) << 8);
    *buf += 2;
    pos_y = static_cast<uint16_t>(**buf) + (static_cast<uint16_t>((*((*buf) + 1))) << 8);
    *buf += 2;
    health = (int8_t)(**buf);
    *buf += 1;
    angle = static_cast<uint16_t>(**buf) + (static_cast<uint16_t>((*((*buf) + 1))) << 8);
    *buf += 2;

    m_monsters.push_back(new Monster(pos_x, pos_y, m_monster_texture, angle, health));
}

void OnlineGame::unpack_projectile(uint8_t **buf)
{
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t angle;

    pos_x = static_cast<uint16_t>(**buf) + (static_cast<uint16_t>(*((*buf) + 1)) << 8);
    *buf += 2;
    pos_y = static_cast<uint16_t>(**buf) + (static_cast<uint16_t>(*((*buf) + 1)) << 8);
    *buf += 2;
    angle = static_cast<uint16_t>(**buf) + (static_cast<uint16_t>(*((*buf) + 1)) << 8);
    *buf += 2;

    m_projectiles.push_back(new Projectile(pos_x, pos_y, angle, m_projectile_texture));
}

void OnlineGame::send_player_pos(int socket)
{
    std::vector<unsigned char> player_info = m_player->format_position();
    player_info.push_back(m_player->is_clicked());
    if (send(socket, &player_info[0], player_info.size(), 0) != player_info.size())
    {
        std::cout << "Error sending player info to server" << std::endl;
    }
}
