#ifndef FSL_CLIENT_H_
#define FSL_CLIENT_H_

#include "Socket.h"

class Client : public Socket {
public:
    Client();
    ~Client() override;

};

#endif
