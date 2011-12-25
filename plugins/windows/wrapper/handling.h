#ifndef HANDLING_H
#define HANDLING_H

#include <windows.h>
#include <string>

typedef void (*HandlerCallback)(const char*);

class Handler
{
public:
	static const int port = 42042;

	inline void setCallback(HandlerCallback cb)
	{
		m_callback = cb;
	}
	static Handler *instance()
	{
		static Handler h;
		return &h;
	}

private:
	HandlerCallback m_callback;
	UINT_PTR m_listenTread;

	Handler();
	~Handler();
	static SOCKET makeSocket();
	static void listenner(void *);
};

#endif // HANDLING_H
