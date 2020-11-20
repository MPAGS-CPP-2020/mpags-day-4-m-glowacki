#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
// Out project headers
#include "PlayfairCipher.hpp"


PlayfairCipher::PlayfairCipher(const std::string& key)
   
   :key_{key}

   {
   }

void PlayfairCipher::setKey(const std::string& key)
{
    // store the original key
    key_ = key;

 // Append the alphabet
 //const std::vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
 for(size_t i{0}; i < alphabet_.size(); i++) {
     key_.push_back(alphabet_[i]);
 }
 
 // Make sure the key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper); //range, end, starting postion

 // Remove non-alpha characters
    key_.erase( std::remove_if( key_.begin(), key_.end(), [](char c) {return !std::isalpha(c); } ),
              std::end(key_) );

 // Change J -> I
    std::replace(key_.begin(), key_.end(), 'J', 'I');

 
 // Remove duplicated letters
    std::vector<char>  encountered;
    key_.erase( std::remove_if(key_.begin(), key_.end(), [&encountered](char c) {
        
       int count = std::count(encountered.begin(), encountered.end(), c);
       
       if ( count!= 0 ){
        return true;
       }
       else{
       encountered.push_back(c);
        return false;
       }

    } ), 
    std::end(key_) ); 


 // Store the coords of each letter and create map
  
int row{0};
int col{0};
    
for (size_t idx{0}; idx < key_.size(); idx ++){
while ((col <= 5) & (row <=5)){
    if (col + 1 != 6) {
       auto coords =  std::make_pair(row, col);
       letter2coordmap_.insert(std::make_pair(key_[idx], coords));
       coord2lettermap_.insert(std::make_pair(coords, key_[idx]));
       col ++;
       idx  ++;
    }
    else{
        row  ++;
        col = 0;
        continue;
    }
 }
}

}

std::string PlayfairCipher::getKey(){
    return key_;
    }


std::string PlayfairCipher::applyCipher( \
 const std::string& inputText, \
 const CipherMode cipherMode ) const
{
  switch ( cipherMode ) {
	  case CipherMode::Encrypt :
	    std::cout << "Encypt" << std::endl;
	    break;
	  case CipherMode::Decrypt :
	    std::cout << "decrypt" << std::endl;
 break;
  }
	    
 // Change J → I
 std::replace(key_.begin(), key_.end(), 'J', 'I');

 // If repeated chars in a digraph add an X or Q if XX

for (size_t idx{1}; idx < inputText.size(); i ++){
   if (inputText[idx] == inputText[(idx-1)]){
      inputText{idx} = 'X';
   }
}


 // if the size of input is odd, add a trailing Z

 if (inputText.size() % 2 != 0){
    inputText.append("Z");
 }

 // Loop over the input in Digraphs

 for(size_t idx{0}; inputText.size(); idx +=2 ){

    auto iter_first = letter2coordmap_.find(inputText[idx]);
    int row_1 = std::get<0>(*iter_first.second);
    int col_1 std::get<1>(*iter_first.second);
    
    auto iter_second = letter2coordmap_.find(inputText[(idx + 1)]);
    int row_2 = std::get<0>(*iter_second.second);
    int col_2 = std::get<1>(*iter_second.second);
    
    if row_1 == row_2{
        
       col_1 = col_1 + 1;
       col_2 = col_2 + 1;
    }

    if col_1 == col_2 {
       row_1 = row_1 + 1;
       row_2 = row_2 + 1;
    }

    if (row_1 != row_2 & col_1 != col_2){
       row_1 = row_2;
       col_1 = col_2;
    }

 }

 // - Find the coords in the grid for each digraph
 // - Apply the rules to these coords to get 'new' coords
 // - Find the letter associated with the new coords
 // return the text
 return inputText; 
}
