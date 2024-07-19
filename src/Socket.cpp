#include "../include/Socket.h"
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>

Socket::Socket(const Address& address) {
    create(address);
}

Socket::Socket(int socketFD)
    : m_SocketFD(socketFD) {

}

Socket::~Socket() {
    close(m_SocketFD);
}

void Socket::create(const Address& address) {
    for(struct addrinfo* p = address.getAddrinfoPtr(); p != nullptr; p = p->ai_next) {
        if((m_SocketFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            printf("socket not created for host: %s", p->ai_canonname);
            continue;
        }
        m_PtrToAddrPtr = &p;
        break;
    }
}

void Socket::bind() {
    if(::bind(m_SocketFD, (*m_PtrToAddrPtr)->ai_addr, (*m_PtrToAddrPtr)->ai_addrlen) == -1) {
        throw SocketException("Bind'ing error");
    }
}

void Socket::connect(const Address& address) {
    if(::connect(m_SocketFD, address.getSockaddr(), address.getAddressLength()) == -1) {
        throw SocketException("Connect'ing error");
    }
}

int Socket::accept(Address& address) {
    address.m_AddrLen = sizeof(*address.getSockaddr());
    return ::accept(m_SocketFD, address.getSockaddr(), &address.m_AddrLen);
}

void Socket::sendData(const std::string& data) {
    if((::send(m_SocketFD, data.c_str(), data.size(), 0)) == -1) {
        throw SocketException("Send'ing error");
    }
}

void* Socket::receiveData(size_t size,
                         void* buffer /* stores result */) {
    if((::recv(m_SocketFD, buffer, size, 0)) == -1) {
        throw SocketException("Receive'ing error");
    }
    return buffer;
}
