#ifndef _HASHMAP_HPP_
#define _HASHMAP_HPP_
#include <stdexcept>
#include <vector>
#define SIXTEEN 16
#define ZERO 0
#define MAX 0.75
#define MIN 0.25


template <class KeyT,class ValueT >
class HashMap{

 protected://object protected for other class that can reach
  typedef std::vector<std::pair<KeyT,ValueT>> my_map;
  my_map *_data;//the gibob tavla
  int  _size;
  int _capacity;
 private:

  //hash func to enter to the data in a place
  int hash_function(const KeyT key)const{
      return std::hash<KeyT>() (key) &(_capacity-1);
  }
  //check if the key is in
  bool check_in_data(const KeyT keys)const
  {
    if(empty()){return false;}//if the map is empty no need
    for ( auto p :_data[hash_function (keys)]){

      if (p.first==keys){
        return true;//beacse the key is in the map
      }

    }
    //not in the map

    return false;
  }
  //dicrease the size
  void dicrease(){
//like te increase but oposite the same work
    if (_size==ZERO){
      _capacity=1;
      delete[]_data;
      _data=new my_map[SIXTEEN];
    }
    else{
      my_map *map;
      while (get_load_factor()<MIN){
        int n_c=_capacity/2;
        _capacity=n_c;
        map=new my_map[n_c];
        for (int i=ZERO;i<_capacity*2;++i){
          for( auto pair:_data[i]){
            map[hash_function (pair.first)].push_back
                (std::make_pair//copy heach element
                     (pair.first,pair.second));
          }
        }
        delete[]_data;//delete
        _data=map;
      }

    }}

  //increase the capacity
  void increase(){
    int n_c=_capacity*2;
    _capacity=n_c;
    my_map *map;
    map=new my_map[n_c];
    for (int i=ZERO;i<_capacity/2;++i){
      for(const auto &pair:_data[i]){
        map[hash_function (pair.first)].push_back
        (std::make_pair (pair
        .first,pair
        .second));//new map to copy
      }
    }
    delete[]_data;//delete the last and make copy
    _data=map;
  }

 public:
  virtual ~HashMap(){//disractor

    delete  _data;
  }
  //inisiliaz new hashmap defult
  HashMap():_size(ZERO),_capacity(SIXTEEN){//defult
    _data=new my_map [SIXTEEN];
    if (!_data){//trhow error bcs allocation did not susceed
      throw std::domain_error("error in the constarctor defult with allocion");
    }
  }
  //constractor for hashmap whan given a hash map
  HashMap(const HashMap &hash_map):_size(ZERO),_capacity(SIXTEEN){
    _data=new my_map [SIXTEEN];//defult

    if (!hash_map._data){//error in allocation
      throw std::domain_error("error in Hashmap constactor");
    }
    _capacity=hash_map._capacity;//new value
    clear();//clear the map to create a new one

    for (int i=ZERO;i<_capacity;i++){
      for (auto pair: hash_map._data[i]){

        insert (pair.first,pair.second);//copy the constarctor with the insert
        //func
      }
    }

  }
  //constarctor with two vector one of key end one of value
  HashMap(const std::vector<KeyT> keys,const std::vector<ValueT> value):_size
  (ZERO),_capacity(SIXTEEN){//defuelt
    if (keys.size() != value.size()){//error in allocation
      throw std::domain_error("error in Hashmap consractor with vec");
    }
    _data=new my_map[SIXTEEN];
    _size=ZERO;
    int e=ZERO;
    for (size_t i=ZERO;i<keys.size();i++){

      if (!contains_key (keys[i])){//
        _size++;
        while(get_load_factor() > MAX)
        {
          increase();//check if the capacity is ok
        }
        _data[hash_function (keys[i])].
        push_back(std::make_pair(keys[i],value[i]));//put the valu ein the
        // new data

      }
      else {
        (*this)[keys[i]] = value[i];//change the value because is already in
        e++;

      }
    }
  }
  //getter return the size
  int size() const {
    return _size;
  }
  // return the capacity
  int capacity()const {
    return _capacity;
  }
  //return if the data id empty
  bool empty() const {
    return _size==ZERO;
  }
  //insert key end value to the map
  bool insert(const KeyT keys,const ValueT &value_t){
    if (!contains_key (keys)){//check if already in

      auto z=hash_function (keys);
      this->_data[z].push_back(std::make_pair (keys, value_t));//put in map
      ++_size;
      if (get_load_factor() > MAX){
        increase();
      }

      return true;
    }
    else {
      return false;//because is already in
    }

  }
  //check if the key is in the map
  bool contains_key(const KeyT keys)const{
    bool v= check_in_data (keys);//private func that help us
    return v;

  }

  ValueT operator [](const KeyT key_t) const {//the operator [] const
    for (const auto pair:_data[hash_function (key_t)])
    {
      if (pair.first == key_t)
      {
        return pair.second;//return the value
      }
    }
    return ValueT();//return garbage value
  }

  ValueT &operator [](const KeyT &key_t){//same as bellow but no const
    insert (key_t,ValueT());//first insert to the data
    for (auto &pair:_data[hash_function (key_t)])
    {
      if (pair.first == key_t)
      {
        return pair.second;//return the value
      }
    }
    return _data[0][0].second;//garbage value
  }
  ValueT at(const KeyT &keys)const//return const
  {//check if in the map
    if (!contains_key (keys))
    {//no so return error
      throw std::domain_error ("THE KEY IS NOT VALID");
    }
    return (*this)[keys];//use operator to give as the value
  }
  ValueT &at(const KeyT keys){//same as bellow but no const
  if (contains_key (keys))//check if in
  {
    for ( auto &pair:_data[hash_function (keys)])
    {
      if (pair.first == keys)
      {
        return pair.second;//return value
      }
  }
  }
  throw std::domain_error ("PROBELM WITH THE KEY");//not in so error
  }
  virtual bool erase(const KeyT key_t){//erase method to erase key
    if(!contains_key (key_t)){
      return false;//not in so do nothing
    }
    else {
      int i=ZERO;
      for (auto &cur:_data[hash_function (key_t)]){
        if (cur.first==key_t){
          _data[hash_function (key_t)].erase
          (_data[hash_function (key_t)]             .begin()+i);//find the
          // value to erase and erase
          --_size;
          if(get_load_factor()<MIN){
            dicrease();//decrease in case of demade
          }
          return true ;//sucseed
        }
        else {
          i++;
        }
      }

    }
    return false;//not sucseed
  }

  double get_load_factor()const {//get the load factor
    return (double )_size/(double )_capacity;
  }
  int bucket_index(const KeyT &keys) const  {//return the index of the bucket
    if (contains_key (keys)){
      for (int i=ZERO;i<_capacity;i++){
        for (auto &pair:_data[i]){
          if (pair.first==keys)
          {
            return (int) i;//is the index
          }
          else
          {
          }
        }
      }
    }
    else{//no in the bucket so retru error
      throw std::invalid_argument ("ERROR WHEN CALL TO BUCKET INDEX");
    }
    return ZERO;
  }
  int bucket_size(const KeyT &keys){//return the bucket size
    if (contains_key (keys)){
     return  _data[hash_function(keys)].size();
  }
    else{//not sucseed so retrun error
      throw std::invalid_argument ("ERROR WHEN CALL TO BUCKET SIZE");
    }
    return ZERO;
  }
  void clear(){//clear the protecded argument
    delete[] _data;
    _data =new my_map [_capacity];
    _size=ZERO;
  }
  class ConstIterator{//the const iterator
    friend class HashMap;//makefriend
   private:
    const HashMap<KeyT,ValueT> *_hash_map;//the type if hashmap
    size_t _cur_buk;//the current buk
    size_t _cur_ind;//the current ind

   public:
    typedef const std::pair<KeyT,ValueT> pair_1;
    typedef  const pair_1 &reference;
    typedef  const pair_1 *pointer;
    typedef int diferent_type;
    typedef   std::forward_iterator_tag forward_iterator;
   private:
    //consractor with all the given alement to inisiliaz
    ConstIterator(const HashMap<KeyT,ValueT>
        *hash_map_1, size_t cur_buk, size_t
    cur_ind):
    _hash_map(hash_map_1),_cur_buk(cur_buk),_cur_ind(cur_ind){}
   public:
    //make some operator
    reference operator*()const {
      return _hash_map->_data[_cur_buk][_cur_ind];
    }
    //pointer
    pointer operator->()const{
      return &(operator*());
    }
    //check if eqaul
    bool operator ==(const ConstIterator &constiterator)const {
      return (_cur_ind == constiterator._cur_ind && _cur_buk ==
      constiterator._cur_buk &&
              _hash_map == constiterator._hash_map);
    }
    //check if not eqaul
    bool operator !=(const ConstIterator &iterator)const {
      return !operator== (iterator);
    }
    //arrive to the not empty next cell
    ConstIterator& operator++() {
      auto  map_1=_hash_map->_data[_cur_buk];
      if (_cur_ind==map_1.size()-1){
        _cur_buk++;
        _cur_ind=ZERO;
        for (int i = _cur_buk; i < _hash_map->capacity() ; ++i)
        {
          if (!_hash_map->_data[i].empty ())
          {
            _cur_buk = i;//the not empty next cell
            return *this;
          }
        }
        _cur_buk=_hash_map->capacity();//all of them are empty so do this
        return *this;
      }
        ++_cur_ind;
        return *this;
    }
    //using the last operator from the other side
    ConstIterator operator++(int){
      ConstIterator it(*this);
      this->operator++();
      return it;
    }
  };
  typedef ConstIterator const_iterator;//typedef
  const_iterator cbegin()const {//cbrgin method return the first not empty cell
    for (int i=ZERO;i<_capacity;i++){
      if(_data[i].empty()){ }
      else{
        return ConstIterator(this, i, ZERO);
      }
    }
    return ConstIterator (this, _capacity, ZERO);//return the ast
  }
  const_iterator cend()const {//return the end
    return ConstIterator(this, _capacity, ZERO);

  }
  const_iterator begin()const{//call the cbegin method
    return cbegin();
  }
  const_iterator end()const { //call the cend method
    return cend();
  }
  //operator = of hash map make a copy of the map
  HashMap &operator=(const HashMap hash_map){
    if (*this==hash_map){
      return *this;//no need of the next line
    }
    _capacity=hash_map.capacity();
    delete []_data;
    _data=new my_map[_capacity];
    for (size_t i=ZERO;i<_capacity;i++){
      for(size_t j=ZERO;j<hash_map._data[i].size();j++){
      insert (hash_map._data[i][j].
      first,hash_map._data[i][j].second);//copy heach element
      }
    }
    return *this ;
//return this with modufaction
  }
//chack if two hashmap are eqaul return true if yes else not
  bool operator ==(const HashMap &hash_map)const {
    if (_size!=hash_map._size){
      return false;//not eqaul
    }
    for(int i=ZERO;i<_capacity;i++){
      for ( const auto pair:_data[i]){
        if (contains_key (pair.first) && hash_map[pair.first]
        != pair.second){//check heach element
          return false;//not eqaul
        }
      }
    }
    return true;//eqaul
  }
  //check the oposite of ==
  bool operator !=(const HashMap &hash_map)const{
    return !(this->operator== (hash_map));
  }
};
#endif
