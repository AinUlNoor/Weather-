#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
using namespace std;
const int port = 8080;
const int buffersize = 1024;
void handle_client(int client_socket)
 {
    char buffer[buffersize] = {0};
    recv(client_socket, buffer, buffersize, 0);
    string request(buffer);
    string delimiter = " ";
    size_t pos = request.find(delimiter);
    string method = request.substr(0, pos);
    request.erase(0, pos + delimiter.length());
    pos = request.find(delimiter);
    string file_name = request.substr(0, pos);
    if (file_name == "/") 
	{
        file_name = "/index.html";
    }
    ifstream file("www" + file_name);
    string response;
    if (file) 
	{
        string html_content((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
        response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + html_content;
    } 
	else
	 {
        response = "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n<html><body><h1>404 Not Found</h1></body></html>";
    }

    send(client_socket, response.c_str(), response.length(), 0);
    close(client_socket);
}
int main() 
{
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	 {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) 
	{
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
}
    if (listen(server_fd, 10) < 0)
	 {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    vector<thread> threads;
    while (true)
	 {
        if ((client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) 
		{
            perror("accept failed");
            continue;
        }
        threads.emplace_back(thread(handle_client, client_socket));
    }

    for (auto& t : threads) 
	{
        if (t.joinable()) 
		{
            t.join();
        }
    }

    return 0;
}
