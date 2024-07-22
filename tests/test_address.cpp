#include <gtest/gtest.h>
#include "Address.h"

TEST(AddressTest, AddressExceptionThrow) {
    ASSERT_THROW(Address("invalid hostname", "invalid port"), AddressException);
}

TEST(AddressTest, DefualtConstruction) {
    /* Constructor defaults */
    Address adrs{};
    EXPECT_EQ(adrs.getFlags(), AI_PASSIVE);
    // DON'T CHECK THAT IN THIS SCENARIO, BECAUSE HINTS != ADDRESS
    // EXPECT_EQ(adrs.getAddressFamily(), AF_INET);
    EXPECT_EQ(adrs.getSockType(), SOCK_STREAM);

    /* Port */
    EXPECT_EQ(adrs.getPort(), 42069);
    adrs.setPort(2137);
    EXPECT_EQ(adrs.getPort(), 2137);
}

TEST(AddressTest, ConstuctionWithHints) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    Address adrs("192.168.0.10", "80", hints);
    EXPECT_EQ(adrs.getFlags(), AI_PASSIVE);
    EXPECT_EQ(adrs.getAddressFamily(), AF_INET);
    EXPECT_EQ(adrs.getSockType(), SOCK_STREAM);

    /* Address */
    /* TODO: Some other way for gathering sin_addr (IP_ADDRESS)
             maybe in presentation form (stored additionally in class) 
    */
    std::string address = "120.120.240.240";
    adrs.setAddress(address);
    struct in_addr temp;
    inet_pton(AF_INET, address.c_str(), &temp);
    EXPECT_EQ(adrs.getSockaddrIPv4()->sin_addr.s_addr, temp.s_addr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}