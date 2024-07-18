#include "../include/Address.h"
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>

#define DEFAULT_PORT 42069

AddressException::AddressException(const char* message)
    : m_Message(message) {
}

const char* AddressException::what() const noexcept {
    return this->m_Message.c_str();
}

// ---------- IPv4 ----------
IPv4Address::IPv4Address() {
    struct addrinfo hints, *servinfo;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    setPort(DEFAULT_PORT);

    int result;
    if((result = getaddrinfo(NULL, "42069", &hints, &servinfo)) != 0) {
        throw AddressException(gai_strerror(result));
    }
}

IPv4Address::IPv4Address(const std::string& address, uint16_t port) {
    struct addrinfo hints, *servinfo;
}

IPv4Address::IPv4Address(const std::string& address, uint16_t port, struct addrinfo& hints) {

}

std::string IPv4Address::getAddress() const {
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(m_Addr.sin_addr), str, INET_ADDRSTRLEN);
    return std::string(str);
}

uint16_t IPv4Address::getPort() const {
    return ntohs(m_Addr.sin_port);
}

void IPv4Address::setAddress(const std::string& address) {
    inet_pton(AF_INET, address.c_str(), &(m_Addr.sin_addr));
}

void IPv4Address::setPort(uint16_t port) {
    m_Addr.sin_port = htons(port);
}

struct sockaddr* IPv4Address::getSockaddr() {
    return reinterpret_cast<struct sockaddr*>(&m_Addr);
}

socklen_t IPv4Address::getSockaddrLen() const {
    return sizeof(m_Addr);
}

// ---------- IPv6 ----------

IPv6Address::IPv6Address() {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
}

IPv6Address::IPv6Address(const std::string& address, uint16_t port) {

}

IPv6Address::IPv6Address(const std::string& address, uint16_t port, struct addrinfo& hints) {

}

std::string IPv6Address::getAddress() const {
    char str[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &(m_Addr.sin6_addr), str, INET6_ADDRSTRLEN);
    return std::string(str);
}

uint16_t IPv6Address::getPort() const {
    return ntohs(m_Addr.sin6_port);
}

void IPv6Address::setAddress(const std::string& address) {
    inet_pton(AF_INET6, address.c_str(), &(m_Addr.sin6_addr));
}

void IPv6Address::setPort(uint16_t port) {
    m_Addr.sin6_port = htons(port);
}

struct sockaddr* IPv6Address::getSockaddr() {
    return reinterpret_cast<struct sockaddr*>(&m_Addr);
}

socklen_t IPv6Address::getSockaddrLen() const {
    return sizeof(m_Addr);
}
