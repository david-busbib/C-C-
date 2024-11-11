

#include "RSUser.h"

#include <utility>
#include "RecommenderSystem.h"

// implement your cpp code here
RSUser::RSUser (std::string string, rank_map &map,
                std::shared_ptr<RecommenderSystem>  _recommender_system) :
                name (std::move(string)),rank_map_1 (map)
                ,
                _recommender_system(std::move (_recommender_system))
{

}
std::string RSUser::get_name () const
{
  return name;
}
void RSUser::add_movie_to_rs (const std::string &name, int year,
                              const std::vector<double> &features,
                              double rate)
{
  rank_map_1[_recommender_system->add_movie (name, year, features)] = rate;

}
rank_map RSUser::get_ranks () const
{
  return rank_map_1;
}
sp_movie RSUser::get_recommendation_by_content () const
{
  return _recommender_system->recommend_by_content ((*this));
}
sp_movie RSUser::get_recommendation_by_cf (int k) const
{
  return _recommender_system->recommend_by_cf ((*this), k);
}
double RSUser::get_prediction_score_for_movie (const std::string &name, int
year, int k) const
{
  sp_movie sp_movie_1 = _recommender_system->get_movie (name, year);
  return _recommender_system->predict_movie_score ((*this),
                                                   sp_movie_1, k);
}
std::ostream &operator<< (std::ostream &ostream, const RSUser
&rs_user)
{
  ostream << "name : " << rs_user.get_name () << std::endl;
  ostream << *rs_user._recommender_system;
  return ostream;
}
