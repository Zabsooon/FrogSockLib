#ifndef FSL_SOCKET_H_
#define FSL_SOCKET_H_

#include <exception>
#include <string>

#include "Address.h"

class SocketException : std::exception {
public:
    SocketException(const char* msg)
        : m_Message(msg) {

    }

    SocketException(int sockFD, const char* msg)
        : m_SockFD(sockFD), m_Message(msg) {

    }

    const char* what() const noexcept {
        return m_Message.c_str();
    }

private:
    std::string m_Message;
    int m_SockFD;
};

class Socket {
    Socket();
    virtual ~Socket();

private:
    void create();
    void close();
    void bind(const Address& address);
    void connect(const Address& address);
    void send(const std::string& data);
    std::string receive(size_t size);
protected:
    int m_socketFD;
};

#endif
