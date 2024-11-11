#ifndef _DICTIONARY_HPP
#define _DICTIONARY_HPP
#include <iostream>
#include "HashMap.hpp"
#include <vector>
#define INVALID "invalid_argument pleease do something "

//thro< the invalid key
class InvalidKey : public std::invalid_argument {
 public:
//defult constarctor
  InvalidKey():std::invalid_argument ("error of non valid argm"){}
  //not defulat constractor with string to put
  explicit InvalidKey(const std::string &st): std::invalid_argument
  (st){}
};
 class Dictionary:public HashMap<std::string,std::string > {
  public:
   Dictionary()=default;//defult
   //not default constarctor
   Dictionary(const std::vector<std::string> &k,const
   std::vector<std::string> &v): HashMap<std::string,
   std::string> (k,v){}
   //call the erase method of the hashmap
   bool erase(const std::string key_t) override{
     if(HashMap::erase(key_t)){
       return true;
     }
     throw InvalidKey(INVALID);//thorw error
   }
   template<class FowardIr>//new template
   void update(const FowardIr &begin,const FowardIr &end ){//apdate heach
     // element in the hashmap
     for(auto i=begin;i!=end;++i){
       this->operator[] (i->first)=i->second;//call the operator []
       //to update
     }

   }


 };
#endif