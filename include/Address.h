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

class AddressException : public std::exception {
public:

    AddressException(const char* message);
    const char* what() const noexcept;

private:
    std::string m_Message;
};

/* The Address class can be of different types eg. IPv4 or IPv6.
 * For that reason the Address class is an abstract class and we have
 * specific implementations for IPv4 and IPv6.
 *
 * The Address cannot be used by itself in socket specific functions,
 * it is designed to work with wrapper functions (functions that add
 * functionality on top of the sockets logic).
 *
 * Since while we use 'getaddrinfo()' we can pass hints as a parameter,
 * I have decided to code that logic into constructors.
 * Default hints are implemented in default constructor.
 *
 * Since Address can be IPv4 or IPv6 we can manually check what type is Address.
 * This is done in that way so we can get advantage of polimorphism while,
 * still meeting requirements of sockets implementation (sockaddr_in and sockaddr_in6).
 *
 *
 */
class Address {
public:
    virtual ~Address() = default;

    virtual std::string getAddress() const = 0;
    virtual uint16_t getPort() const = 0;

    virtual void setAddress(const std::string& address) = 0;
    virtual void setPort(uint16_t port) = 0;

    virtual struct sockaddr* getSockaddr() = 0;
    virtual socklen_t getSockaddrLen() const = 0;
};

class IPv4Address : Address {
public:
    IPv4Address();
    IPv4Address(const std::string& address, uint16_t port);
    IPv4Address(const std::string& address, uint16_t port, struct addrinfo& hints);

    std::string getAddress() const override;
    uint16_t getPort() const override;

    void setAddress(const std::string& address) override;
    void setPort(uint16_t port) override;

    struct sockaddr* getSockaddr() override;
    socklen_t getSockaddrLen() const override;

private:
    struct sockaddr_in m_Addr;
};

class IPv6Address : Address {
public:
    IPv6Address();
    IPv6Address(const std::string& address, uint16_t port);
    IPv6Address(const std::string& address, uint16_t port, struct addrinfo& hints);

    std::string getAddress() const override;
    uint16_t getPort() const override;

    void setAddress(const std::string& address) override;
    void setPort(uint16_t port) override;

    struct sockaddr* getSockaddr() override;
    socklen_t getSockaddrLen() const override;

private:
    struct sockaddr_in6 m_Addr;
};

#endif
