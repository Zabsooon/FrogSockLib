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

/* If address hints are not specified they are set to support IPv4 or IPv6.
 * Also the type of socket is set to TCP stream sockets.
 *
 * Constructors:
 * hostname: can be DNS, IPv4 or IPv6 address
 * service: can be port number or service name eg. "http", "smtp"
 */
class Address {
public:
    Address();
    Address(const std::string& hostname, const std::string& service);
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
    void setPort(const std::string& port);

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
