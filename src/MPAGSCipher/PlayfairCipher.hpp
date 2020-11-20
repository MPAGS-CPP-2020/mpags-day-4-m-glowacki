#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include <vector>
#include "CipherMode.hpp"
#include <map>

class PlayfairCipher {
    
    public:
    explicit PlayfairCipher(const std::string& key);
    void setKey(const std::string& key);
    std::string getKey();
    std::string applyCipher( const std::string& inputText, const CipherMode cipherMode ) const;
    const std::vector<char> alphabet_ = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    using Str2IntMap = std::map<char, std::tuple<int,int > >;
    using Int2StrMap = std::map<std::tuple<int,int >, char>;
    Str2IntMap letter2coordmap_;
    Int2StrMap coord2lettermap_;


    private:
    std::string key_ {""};
};

#endif