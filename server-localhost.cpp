#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Success message sent to the browser
    std::string successMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 52\n\n"
                                 "<html><body><h1>Success! Server is running.</h1></body></html>";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Bind to 127.0.0.1
    address.sin_port = htons(8080);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Log the server's IP address and port
    std::cout << "Server running on IP: " << inet_ntoa(address.sin_addr)
              << ", Port: " << ntohs(address.sin_port) << std::endl;

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Server loop to accept and handle multiple connections
    while (true)
    {
        std::cout << "Waiting for a connection..." << std::endl;

        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        std::cout << "Connection accepted" << std::endl;

        // Read data from the client
        read(new_socket, buffer, 1024);
        std::cout << "Received request:\n"
                  << buffer << std::endl;

        // Send the success message
        send(new_socket, successMessage.c_str(), successMessage.size(), 0);
        std::cout << "Success message sent\n";

        // Close the connection
        close(new_socket);
    }

    return 0;
}