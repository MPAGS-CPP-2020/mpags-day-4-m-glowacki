#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"
#include "PlayfairCipher.hpp"

TEST_CASE("coorect encryption", "[playfair]") {
std::string cipher_key {"test"};
PlayfairCipher pc(cipher_key);
std::string inputText {"ab"};
std::string outputText {pc.applyCipher(inputText,CipherMode::Encrypt )};
REQUIRE(outputText == "BC");

}