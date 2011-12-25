#include <process.h>
#include "handling.h"
#include "taskbar.h"

EXPORT void CALLBACK
RundllCallback(HWND hwnd, HINSTANCE hinst, LPSTR cmdLine, int cmdShow);

void CALLBACK RundllCallback(HWND, HINSTANCE, LPSTR cmdLine, int)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sk;
	sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sk == INVALID_SOCKET) {
		WSACleanup();
		return;
	}

	sockaddr_in sai;
	sai.sin_family      = AF_INET;
	sai.sin_addr.s_addr = inet_addr("127.0.0.1");
	sai.sin_port        = htons(Handler::port);

	if (connect(sk, reinterpret_cast<SOCKADDR*>(&sai), sizeof(sai)) == SOCKET_ERROR) {
		WSACleanup();
		return;
	}

	std::string cmd = cmdLine;
	send(sk, cmd.c_str(), cmd.size(), 0);
	closesocket(sk);
	WSACleanup();
}

Handler::Handler()
	: m_callback(0),
	  m_listenTread(0)
{
	m_listenTread = _beginthread(&Handler::listenner, 0, 0);
}

Handler::~Handler()
{
	CloseHandle(reinterpret_cast<HANDLE>(m_listenTread));
}

SOCKET Handler::makeSocket()
{
	WSADATA wsaData;
	SOCKET sock = 0;
	sockaddr_in sin;

	int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != NO_ERROR) {
		return INVALID_SOCKET;
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		return INVALID_SOCKET;
	}

	sin.sin_family      = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port        = htons(Handler::port);

	res = bind(sock, (SOCKADDR *) &sin, sizeof(sin));
	if (res == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return INVALID_SOCKET;
	}

	if (listen(sock, 2) == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return INVALID_SOCKET;
	}
	return sock;
}

void Handler::listenner(void *)
{
	SOCKET connection, sock = makeSocket();
	if (INVALID_SOCKET == sock)
		return;

	const int buffLen = 512;
	char *buffer = new char[buffLen];
	int datalen = 0;
	while ((connection = accept(sock, 0, 0)) != INVALID_SOCKET) {
		int len = 0;
		while ((len = recv(connection, &buffer[datalen], buffLen-datalen, 0)) > 0) {
			datalen += len;
			Sleep(1);
		}
		buffer[datalen] = 0;
		if (instance()->m_callback)
			instance()->m_callback(buffer);
		datalen = 0;
	}
	delete[] buffer;
}
