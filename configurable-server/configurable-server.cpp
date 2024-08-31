#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

std::map<std::string, std::string> loadConfig(const std::string &configFilePath)
{
    std::map<std::string, std::string> config;
    std::ifstream file(configFilePath);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Unable to open config file" << std::endl;
        return config;
    }

    while (std::getline(file, line))
    {
        size_t pos = line.find('=');
        if (pos != std::string::npos)
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            config[key] = value;
        }
    }

    return config;
}

std::string readHTMLFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return ""; // Return an empty string if the file cannot be opened
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file content into the buffer
    return buffer.str();
}

int main()
{
    // Load configuration
    std::map<std::string, std::string> config = loadConfig("server.conf");
    int port = std::stoi(config["port"]);
    std::string webDir = config["web_directory"];

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Open a log file
    std::ofstream logFile("server.log", std::ios::app); // Open in append mode

    if (!logFile)
    {
        std::cerr << "Unable to open log file" << std::endl;
        return 1;
    }

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        logFile << "socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Attaching socket to the specified port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        logFile << "setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Bind to 127.0.0.1
    address.sin_port = htons(port);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        logFile << "bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Log the server's IP address and port
    logFile << "Server running on IP: " << inet_ntoa(address.sin_addr)
            << ", Port: " << ntohs(address.sin_port) << std::endl;

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        logFile << "listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Server loop to accept and handle multiple connections
    while (true)
    {
        logFile << "Waiting for a connection..." << std::endl;

        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            logFile << "accept failed" << std::endl;
            exit(EXIT_FAILURE);
        }

        logFile << "Connection accepted" << std::endl;

        // Read the client's request
        read(new_socket, buffer, 1024);
        logFile << "Received request:\n"
                << buffer << std::endl;

        // Parse the request to get the file path
        std::string request(buffer);
        size_t pos = request.find(" ");
        size_t pos2 = request.find(" ", pos + 1);
        std::string requestedFile = request.substr(pos + 1, pos2 - pos - 1);

        // If no specific file is requested, serve index.html by default
        if (requestedFile == "/")
        {
            requestedFile = "/index.html";
        }

        std::string filePath = webDir + requestedFile;

        // Read the requested file from the web directory
        std::string fileContent = readHTMLFile(filePath);
        std::string response;

        if (!fileContent.empty())
        {
            // HTTP response with the file content
            response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + std::to_string(fileContent.size()) + "\n\n" + fileContent;
        }
        else
        {
            // File not found response
            std::string notFoundMessage = "<html><body><h1>404 Not Found</h1></body></html>";
            response = "HTTP/1.1 404 Not Found\nContent-Type: text/html\nContent-Length: " + std::to_string(notFoundMessage.size()) + "\n\n" + notFoundMessage;
        }

        // Send the response
        send(new_socket, response.c_str(), response.size(), 0);
        logFile << "Response sent for " << requestedFile << "\n";

        // Close the connection
        close(new_socket);
    }

    logFile.close();
    return 0;
}