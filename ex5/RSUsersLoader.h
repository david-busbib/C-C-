//
// Created on 2/21/2022.
//




#ifndef USERFACTORY_H
#define USERFACTORY_H
#include "RecommenderSystemLoader.h"
class RSUsersLoader
{
private:
  static std::string return_name(std::string &token);
  static double return_year(std::string &token);
  static rank_map return_map(std::string token, rank_map my_map,
                             std::vector<std::shared_ptr<Movie>>
                             m_vec, int num_line);
  static std::vector<RSUser> users_rank(const std::string &users_file_path,
                                  std::string
  line,std::vector<std::shared_ptr<Movie>> m_vec,std::vector<RSUser> user_vec,
   int k,const std::shared_ptr<RecommenderSystem>& r_system,rank_map my_map);


public:
    RSUsersLoader() = delete;
    /**
     *
     * loads users by the given format with their movie's ranks
     * @param users_file_path a path to the file of the users
     * and their movie ranks
     * @param rs RecommendingSystem for the Users
     * @return vector of the users created according to the file
     */
    static std::vector<RSUser> create_users_from_file(const std::string&
    users_file_path, rc rs) noexcept(false);

};


#endif //USERFACTORY_H
