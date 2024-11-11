
#include "RecommenderSystemLoader.h"
rc RecommenderSystemLoader:: create_rs_from_movies_file(const std::string
&movies_file_path) noexcept
(false){
  std::ifstream file(movies_file_path);
  if (!file.is_open()) {//check if the file is ok
    throw std::runtime_error( "Error opening file!");
  }
  int count ;
  std::string line;
  comp_map comp_map_1;

  while (std::getline(file, line)) {
    std::string name;
    double year;
    std::istringstream iss(line);
    std::string token;
    std::vector<double> my_vec;
    while ( std::getline(iss, token, '-')){//stopin after the movie
      name= token;
      count=0;
      sp_movie movie_1;
      while (std::getline(iss, token, ' ')){//stoping to get the N
        if (!count){

           year= double (std::stod (token));
           movie_1=std::make_shared<Movie>(name,year);//make him shared


          count=1;
        }
        else{
          if (stod (token)>TEN || stod (token)<=ZERO){
            throw std::domain_error("erorr one");//check for error
          }
          my_vec.push_back (std::stod (token));//insert to the vector
        }
      }
      comp_map_1[movie_1]=my_vec;
    }
  }
  RecommenderSystem comp_1;//create object of RS
  for(auto &v: comp_map_1){
    comp_1.add_movie (v.first->get_name(),
                      v.first->get_year(),v.second);
  }//apedate the object
  file.close();
  return std::make_unique<RecommenderSystem>(comp_1);//return unique o the
  // object
}