#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <Ws2tcpip.h>

#include "winsock2.h"
#include "HeaderC.h"

#pragma comment(lib, "Ws2_32.lib")

/*
	Server Functions TCP

initialize WSA - WSAStartup()
Create a socket - socket()
Bind the socket - bind()
Listen on the socket - listen()
Accept a connection - accept(), connect()
Send and recive data - recv(), send(), recvfrom(), sendto()
Disconnect - closesocket()

*/

/*
	Client Functions TCP 

initialize WSA - WSAStartup()
Create a socket - socket()
Connect to the server - connect()
Send and recive data - recv(), send(), recvfrom(), sendto()
Disconnect - closesocket()

*/

int clientTCP() {

	WSADATA	wsaData; // initialize WSA
	int wsaerr;

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0) {
		std::cout << "Winsock not found!" << std::endl;
	}
	else {
		std::cout << "Found Winsock dll! " << std::endl;
		std::cout << "status: " << wsaData.szSystemStatus << std::endl;
	}

	SOCKET clientSocket = INVALID_SOCKET; // create a socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET) {

		std::cout << "Error at Socket: " << WSAGetLastError() << std::endl;
		WSACleanup();

		return 0;
	}
	else {

		std::cout << "Socket() is OK! " << std::endl;
	}

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(55555);

	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {

		std::cout << "Client connect() failed to connect... " << std::endl;
		WSACleanup();

		return 0;
	}
	else {

		std::cout << "Client connect() is OK " << std::endl;
		std::cout << "Client start send and recive " << std::endl;
	}

	/*std::cout << "Enter a word to send. " << std::endl;
	char inital[300];
	std::cin.getline(inital, 300); 

	int byteCount = send(clientSocket, inital, 300, 0); // sends data

	if (byteCount == SOCKET_ERROR) {
	 
		printf("Server send error %id.\n", WSAGetLastError());
		return 0;
	}
	else {

		printf("Server: Sent %id bytes \n", byteCount);
	} */

	thefucklings fucklingFamily;

	int send_object = send(clientSocket, (char*)&fucklingFamily.fuck, sizeof(thefucklings), 0); // sending objects

	if (send_object == SOCKET_ERROR) {

		printf("Send error %id.\n", WSAGetLastError());
		return 0;
	}
	else {

		printf("Sent %id bytes \n", send_object);
	}

	closesocket(clientSocket); // closes socket
	WSACleanup();

	return 1;
}

/*
	Server Functions UDP

initialize WSA - WSAStartup()
Create a socket - socket()
Bind the socket - bind()
Send and recive data - recv(), send(), recvfrom(), sendto()
Disconnect - closesocket()

*/

/*
	Client Functions UDP

initialize WSA - WSAStartup()
Create a socket - socket()
Send and recive data - recv(), send(), recvfrom(), sendto()
Disconnect - closesocket()

*/

int clientUDP() {

	WSADATA	wsaData; // initialize WSA
	int wsaerr;

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0) {
		std::cout << "Winsock not found!" << std::endl;
	}
	else {
		std::cout << "Found Winsock dll! " << std::endl;
		std::cout << "status: " << wsaData.szSystemStatus << std::endl;
	}

	SOCKET clientSocket = INVALID_SOCKET; // create a socket
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (clientSocket == INVALID_SOCKET) {

		std::cout << "Error at Socket: " << WSAGetLastError() << std::endl;
		WSACleanup();

		return 0;
	}
	else {

		std::cout << "Socket() is OK! " << std::endl;
	}

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(55555);

	char buffer_biddy[10];
	std::cin.getline(buffer_biddy, 10);

	int send_buffer = sendto(clientSocket, (const char*)buffer_biddy, strlen(buffer_biddy), 0, 
		(struct sockaddr*)&clientService, sizeof(clientService));

	if (send_buffer == -1) {

		std::cout << "Error transmitting data." << std::endl;
		WSACleanup();

		return 0;
	}
	else {

		std::cout << "Data sent: " << buffer_biddy << std::endl;
	}

	return 1;
}

int main() {

	// clientTCP();
	clientUDP();

	return 1;
}