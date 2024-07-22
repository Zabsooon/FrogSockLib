#ifndef FSL_ADDRESS_H_
#define FSL_ADDRESS_H_

#include <exception>
#include <cstdint>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

class Socket;

class AddressException : public std::exception {
public:

    AddressException(const char* message);
    const char* what() const noexcept;

private:
    std::string m_Message;
};

/*
    TODO:
    - Constructor that instead of hints takes bunch of parameters,
    - Documentation,
*/
class Address {
public:
    /*
    @brief Constructs address with type (AF_UNSPEC) DEFAULT hostname, service and hints.
    */
    Address();
    /*
    @brief Construct address with type AF_INET or AF_INET6 
           depending on hostname and service with DEFAULT hints.
    
    @param hostname DNS, IPv4, IPv6 address.
    @param service Port number or service name, eg. http, smtp.
    */
    Address(const std::string& hostname, const std::string& service);
    /*
    @brief Construct address with type AF_INET or AF_INET6
           depending on hostname, service and hints.
    
    @param hostname DNS, IPv4, IPv6 address.
    @param service Port number or service name, eg. http, smtp.
    @param hints
    */
    Address(const std::string& hostname, const std::string& service, const struct addrinfo& hints);
    ~Address();

    void printAddresses() const;

    struct addrinfo* getAddrinfoPtr() const;
    int getFlags() const;
    int getAddressFamily() const;
    int getSockType() const;
    int getProtocol() const;
    socklen_t getAddressLength() const;

    // For struct sockaddr *ai_addr:
    void setAddress(const std::string& address);
    void setPort(unsigned short port);

    struct sockaddr* getSockaddr() const;
    socklen_t getSockaddrLength() const;
    in_port_t getPort() const;
    struct sockaddr_in* getSockaddrIPv4() const;
    struct sockaddr_in6* getSockaddrIPv6() const;


    friend Socket;
protected:
    socklen_t m_AddrLen; // for accept function in socket
private:
    struct addrinfo m_Hints;
    struct addrinfo* m_AddressInfo;
};
#endif
