//
// Created on 2/20/2022.
//
#include <map>
#ifndef RECOMMENDERSYSTEM_H
#define RECOMMENDERSYSTEM_H
#include "RSUser.h"
struct sp_movie_equals{
    bool operator()(const sp_movie &movie,const sp_movie &movie_1)const{
      return *movie<*movie_1;

    }
};

struct btr_equals{
    bool operator()(double v_1,double v_2)const{
      return v_1>v_2;

    }
};
typedef std::map<sp_movie, std::vector<double>,sp_movie_equals> comp_map;
class RecommenderSystem
{
 private:
  comp_map map;
  sp_movie find_preference(const std::vector<double>& n,const RSUser&
      user);
   double multi_and_get_sum(std::vector<double> n,
                                               std::vector<double> vector);
  std::vector<double> get_multiply(double num,std::vector<double> vector_1);
  double norm_of_two_vec(std::vector<double> n,std::vector<double> vector);
  std::vector<double> get_sum_and_multply_vector(
      std::vector<double> vector_1, std::vector<double> vector_2 );
public:

	explicit RecommenderSystem();
    /**
     * adds a new movie to the system
     * @param name name of movie
     * @param year year it was made
     * @param features features for movie
     * @return shared pointer for movie in system
     */
	sp_movie add_movie(
        const std::string& name,double year,const std::vector<double>& features
        );


    /**
     * a function that calculates the movie with highest score
     * based on movie features
     * @param ranks user ranking to use for algorithm
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_content(const RSUser& user);

    /**
     * a function that calculates the movie with highest predicted
     * score based on ranking of other movies
     * @param ranks user ranking to use for algorithm
     * @param k
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_cf(const RSUser& user, int k);


    /**
     * Predict a user rating for a movie given argument using
     * item cf procedure with k most similar movies.
     * @param user_rankings: ranking to use
     * @param movie: movie to predict
     * @param k:
     * @return score based on algorithm as described in pdf
     */
	double predict_movie_score
    (const RSUser &user, const sp_movie &movie,int k);

	/**
	 * gets a shared pointer to movie in system
	 * @param name name of movie
	 * @param year year movie was made
	 * @return shared pointer to movie in system
	 */
	sp_movie get_movie(const std::string &name, double year) const;


  friend std::ostream& operator<<(std::ostream& ostream,const
  RecommenderSystem
  &recommender_system);
};


#endif //RECOMMENDERSYSTEM_H
