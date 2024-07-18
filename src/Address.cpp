#include "../include/Address.h"
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>

#define DEFAULT_PORT "42069"

AddressException::AddressException(const char* message)
    : m_Message(message) {
}

const char* AddressException::what() const noexcept {
    return this->m_Message.c_str();
}

// ---------- Address ----------
Address::Address() {
    memset(&m_Hints, 0, sizeof(m_Hints));
    m_Hints.ai_family = AF_UNSPEC;
    m_Hints.ai_socktype = SOCK_STREAM;
    m_Hints.ai_flags = AI_PASSIVE;

    int result;
    if((result = getaddrinfo(NULL, DEFAULT_PORT, &m_Hints, &m_AddressInfo)) != 0) {
        throw AddressException(gai_strerror(result));
    }
}

Address::Address(const std::string& hostname, const std::string& service) {
    memset(&m_Hints, 0, sizeof(m_Hints));
    m_Hints.ai_family = AF_UNSPEC;
    m_Hints.ai_socktype = SOCK_STREAM;
    m_Hints.ai_flags = AI_PASSIVE;

    int result;
    if((result = getaddrinfo(hostname.c_str(), service.c_str(), &m_Hints, &m_AddressInfo)) != 0) {
        throw AddressException(gai_strerror(result));
    }
}

Address::Address(const std::string& hostname, const std::string& service, const struct addrinfo& hints)
    : m_Hints(hints) {
    int result;
    if((result = getaddrinfo(hostname.c_str(), service.c_str(), &m_Hints, &m_AddressInfo)) != 0) {
        throw AddressException(gai_strerror(result));
    }
}

void Address::printAddresses() const {
    for(struct addrinfo* p = m_AddressInfo; p != nullptr; p = p->ai_next) {
        void* address;
        char ipstr[INET6_ADDRSTRLEN];

        if(p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            address = &(ipv4->sin_addr);
        } else if(p->ai_family == AF_INET6) {
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            address = &(ipv6->sin6_addr);
        }

        inet_ntop(p->ai_family, address, ipstr, sizeof(ipstr));
        std::cout << "IP Address: " << ipstr << std::endl;
    }
}

int Address::getFlags() const {
    return m_AddressInfo->ai_flags;
}

int Address::getAddressFamily() const {
    return m_AddressInfo->ai_family;
}

int Address::getSockType() const {
    return m_AddressInfo->ai_socktype;
}

int Address::getProtocol() const {
    return m_AddressInfo->ai_protocol;
}

socklen_t Address::getAddressLength() const {
    return m_AddressInfo->ai_addrlen;
}

void Address::setAddress(const std::string& address) {

}

void Address::setPort(const std::string& port) {

}

struct sockaddr* Address::getSockaddr() const {
    return m_AddressInfo->ai_addr;
}

socklen_t Address::getSockaddrLength() const {
    return sizeof(&m_AddressInfo->ai_addr);
}

in_port_t Address::getPort() const {
    if(m_AddressInfo->ai_addr->sa_family == AF_INET) {
        return ((struct sockaddr_in*)m_AddressInfo->ai_addr)->sin_port;
    } else if(m_AddressInfo->ai_addr->sa_family == AF_INET6) {
        return ((struct sockaddr_in6*)m_AddressInfo->ai_addr)->sin6_port;
    } else {
        return 42069; // DEFAULT_PORT
    }
}

struct sockaddr_in* Address::getSockaddrIPv4() const {
    return (struct sockaddr_in*)m_AddressInfo->ai_addr;
}

struct sockaddr_in6* Address::getSockaddrIPv6() const {
    return (struct sockaddr_in6*)m_AddressInfo->ai_addr;
}
