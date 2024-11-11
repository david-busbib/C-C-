#include "RSUsersLoader.h"
std::string RSUsersLoader:: return_name(std::string &token){
  std::string name = token;
  token.erase ();
  return name ;
}
double RSUsersLoader:: return_year(std::string &token){
  double year = std::stod(token);
  token.erase ();
  return year ;
}
rank_map RSUsersLoader:: return_map(std::string token,rank_map my_map,
                    std::vector<std::shared_ptr<Movie>> m_vec,int num_line){
  if (token != "NA")// check what is the value so we ca enter something
  {
    if ( std::stod (token)>TEN ||  std::stod (token)<=ZERO){
      throw std::domain_error ("error_3");//return eror if error
    }
    my_map[m_vec[num_line++]] = std::stod (token);//apdate the map
    token.erase ();
  }
  else
  {
    my_map[m_vec[num_line++]] =NAN;//apdate the map
    token.erase ();
  }
  return my_map;
}

std::vector<RSUser>RSUsersLoader::users_rank(const std::string &users_file_path
,std::string line,std::vector<std::shared_ptr<Movie>> m_vec,std::vector<RSUser>
user_vec,int k,const std::shared_ptr<RecommenderSystem>& r_system,rank_map
my_map){
  std::ifstream file (users_file_path);
  while (std::getline (file, line)){
    int num_line = -1;//new value
    std::string name;
    double year;
    std::istringstream iss (line);
    std::string token;
    for (int i = 0; i <= int(line.size ()); i++)
    {
      if (line[i] != ' ' && line[i] != '-' &&line[i] != '\0' )
      {
        token += line[i];
      }
      else if (!k)
      {
        if (line[i] == ' ' || line[i] == '\0')
        {
          year = return_year (token);//insert to the vector
          m_vec.push_back (r_system->get_movie (name, year));
        }
        else if (line[i] == '-')
        {
          name = return_name (token);
        }
        token.erase ();//erase the tken
      }
      else
      {
        if (-1 == num_line)
        {
          name = return_name (token);//return the name
          token.erase ();
          num_line = 0;
        }
        else
        {
          my_map= return_map (token,my_map,m_vec,num_line);//return object
          num_line++;//of map
          token.erase ();
        }
      }
    }
    if(k){//apdate the user vector so we can create the user
      user_vec.emplace_back (name,my_map,r_system);
    }
    k = 1;
    token.erase ();
  }
  return user_vec;//return the user vec
}

std::vector<RSUser> RSUsersLoader:: create_users_from_file (const std::string &
users_file_path, rc rs) noexcept (false)
{
  std::shared_ptr<RecommenderSystem> r_system (std::move (rs));
  std::ifstream file (users_file_path);
  if (!file.is_open ())
  {//TROW rror if false
    throw std::domain_error ("error_2");
  }
  rank_map my_map=rank_map(0, sp_movie_hash, sp_movie_equal);
  std::vector<std::shared_ptr<Movie>> m_vec;//make shard pointer to Movie type
  std::string line;
  std::vector<RSUser> user_vec;
  int k = 0;//call the func that will create thevector we want
  user_vec= users_rank (users_file_path,line,m_vec,user_vec,k,r_system,my_map);
  file.close();
  return user_vec;
}
