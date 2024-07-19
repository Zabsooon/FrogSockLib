#ifndef FSL_SOCKET_H_
#define FSL_SOCKET_H_

#include <exception>
#include <sstream>
#include <string>
#include <vector>

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
public:
    Socket(const Address& address);
    Socket(int socketFD);
    ~Socket();

    void bind();
    void connect(const Address& address);
    /* accept(Address& address)
     * parameters: (socketFD, struct sockaddr_storage their_address, size of their_address)
     * returns: **NEW** socketFD
     * (and sets m_AddrLen in Address)
     */
    int accept(Address& address);
    void sendData(const std::string& data);
    void* receiveData(size_t size, void* buffer);
private:
    void create(const Address& address);
protected:
    int m_SocketFD; // the top node
    struct addrinfo** m_PtrToAddrPtr;
};

#endif
