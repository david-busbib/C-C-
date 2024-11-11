#include <numeric>
#include "RecommenderSystem.h"

// Adds a movie to the system and returns a shared pointer to the movie object
sp_movie RecommenderSystem::add_movie(
    const std::string& name,double year,const std::vector<double>& features){
  // Add the movie and its features to the map
  map[std::make_shared<Movie>(Movie (name,year))]=features;
  // Create a shared pointer to the movie object
  sp_movie new_movie =std::make_shared<Movie>(Movie (name,year));
  // Return the shared pointer to the movie object
  return get_movie (name,year);
}

// Returns a new vector that is the result of multiplying each element in the
// input vector by the input number
std::vector<double> RecommenderSystem:: get_multiply(double num,
                                                    std::vector<double>
                                                        vector_1){
  std::vector<double> n_vector_1(vector_1.begin(),vector_1.end());
  // Multiply each element in n_vector_1 by num
  std::transform(
      n_vector_1.begin(),
      n_vector_1.end(),
      n_vector_1.begin(),
      std::bind1st(std::multiplies<double>(),
                   num));
  return n_vector_1;
}

// Returns the product of the norms of the two input vectors
double RecommenderSystem:: norm_of_two_vec(std::vector<double> n,
                                          std::vector<double> vector){
  return
      (std::sqrt(std::inner_product(
          n.begin(), n.end(),n.begin(),0))
       *
       std::sqrt(std::inner_product
                     (vector.begin(),
                      vector.end(),vector.begin(),0)));
}

// Returns the sum of the element-wise product of the two input vectors
// divided by the product of their norms
double RecommenderSystem::multi_and_get_sum(std::vector<double> n,
                                            std::vector<double> vector){
  // Calculate the element-wise product of the two input vectors
  double element_wise_product = std::inner_product(n.begin(),
                                                   n.end(),
                                                   vector.begin(),0);
  // Calculate the product of the norms of the two input vectors
  double norms_product = norm_of_two_vec (n,vector);
  // Return the element-wise product divided by the product of the norms
  return element_wise_product / norms_product;
}
// Returns a new vector that is the element-wise sum of two input vectors
std::vector<double> RecommenderSystem:: get_sum_and_multply_vector(
    std::vector<double> vector_1, std::vector<double> vector_2 ){

  std::vector<double> n_vector_1(vector_1.begin(), vector_1.end());
  std::vector<double> n_vector_2(vector_2.begin(), vector_2.end());
  std::transform (n_vector_2.begin (),
                  n_vector_2.end (),
                  n_vector_1.begin (),
                  n_vector_1.begin (),
                  std::plus<double> ());
  return n_vector_1;
}

// Returns a shared pointer to the movie object with the
// highest predicted rating based on the input preference vector
// and user object
sp_movie RecommenderSystem::find_preference(
    const std::vector<double> &n,const RSUser&user){
  // Initialize variables for storing the current highest prediction
  // and movie object
  double nurm =0;

  sp_movie sp_movie_1;
  bool first=true;
  // Iterate through the map of movies and their feature vectors
  for (auto &vector: map)
  {
    // Check if the user has ranked the current movie
    if (std::isnan (user.get_ranks ()[vector.first]))
    {
      // If the user has not ranked the current movie,
      // calculate the predicted rating using the preference vector and feature
      // vector
      auto cur = multi_and_get_sum (n,vector.second);
      // If this is the first movie being considered
      // , set the current highest prediction to the current prediction and
      // store
      // the movie object
      if (first){
        nurm=cur;
        sp_movie_1 =vector.first;
        first=false;
      }
      // If the current prediction is higher than
      // the current highest prediction, update the
      // current highest prediction and store the movie object
      if(cur>nurm){
        nurm= cur;
        sp_movie_1 =vector.first;
      }
    }
  }
  // Return the shared pointer to the movie object with
  // the highest predicted rating
  return sp_movie_1;
}



// Returns a shared pointer to the movie object with
// the highest predicted rating based on the content-based recommendation
// algorithm
sp_movie RecommenderSystem::recommend_by_content(const RSUser& user)
{
  // Initialize variables for calculating the average rating given by the user
  double cur = 0;
  auto num_of_iteration = 0;
  // Get the user's movie rankings
  auto new_r = user.get_ranks ();
  // Iterate through the user's movie rankings
  for (auto &movie: user.get_ranks ())
  {
    // Check if the user has ranked the current movie
    if (movie.second == movie.second)
    {
      // If the user has ranked the current movie, add the rating to the
      //  running       // total and increment the number of iterations
      cur += movie.second;
      num_of_iteration += 1;
    }
  }
  // Calculate the average rating given by the user
  double avg = cur / num_of_iteration;
  // Subtract the average rating from each of the user's movie rankings
  for (auto &movie:new_r){
    if (movie.second == movie.second)
    {
      movie.second-=avg;
    }
  }
  // Initialize variables for storing the preference vector and movie count
  std::vector<double> n;
  int count =0;
  for (auto &vector: map)
  {
    // Check if the user has ranked the current movie
    if (!(std::isnan(new_r[vector.first])))
    {
      // If this is the first movie being considered, set the preference vector
      if (!count)
      {
        n = get_multiply (new_r[vector.first], map[vector.first]);
        count += 1;
      }
        //If this is not the first movie being considered,update the preference
        //vector by adding the product of the user's rating and the movie's
        // feature vector
      else{
        auto scalar = get_multiply (
            new_r[vector.first], map[vector.first]);
        n= get_sum_and_multply_vector (n, scalar);
      }
    }
  }
// Return the movie object with the highest predicted
// rating based on the preference vector and user object
  return find_preference(n,user);
}


double RecommenderSystem:: predict_movie_score
(const RSUser &user, const sp_movie &movie, int k)
{
  // Initialize a variable for storing the running total of the product
  double cur = 0;
  // Initialize a map for storing the similarities between the movie
  // being predicted and other movies and the movies themselves
  std::map<double, sp_movie, btr_equals> rank_map_1;
  // Iterate through the map of movies and their feature vectors
  for (auto &vector: map)
  {
    // Check if the user has ranked the current movie
    if (!std::isnan (user.get_ranks ()[vector.first]))
    {
      // Calculate the similarity between the movie being predicted
      rank_map_1[multi_and_get_sum (map[movie],vector.second)] =
          vector.first;
    }
  }
  double divide = 0;
  // Set the number of iterations equal to the value of the k parameter
  auto num_of_iteration = k;
  for (auto &m:rank_map_1)
  {
    if (num_of_iteration)    // Check if there are still iterations left
    {
      // If there are still iterations left, add the product of the similarity
      // between the movie being predicted and the current movie and the user's
      // rating for the current movie to the running total and decrement the
      //  number of iterations
      cur += m.first * user.get_ranks()[m.second];
      num_of_iteration -= 1;
      // Add the similarity between the movie being predicted and the
      // current movie to the running total
      divide += m.first;
    }
    else { break; } // If there are no iterations left, break out of the loop
  }
  // Return the predicted rating by dividing the running total by the sum
  // of the similarities between the movie being predicted and the other movies
  return cur / divide;
}
sp_movie RecommenderSystem::recommend_by_cf (const RSUser &user, int k)
{
  // Initialize a variable for storing the current highest predicted rating
  double cur = 0;
  // Initialize a variable for storing the movie
  sp_movie movies;
  // Initialize a counter variable
  int count = 0;
  // Initialize a map for storing predicted ratings and movie objects
  rank_map rank_map_1;
  // Initialize a variable for storing the predicted rating for a movie
  double num_of_iteration = 0;
  // Iterate through the map of movies and their feature vectors
  for (auto &vector: map)
  {
    // Check if the user has not ranked the current movie
    if (std::isnan (user.get_ranks ()[vector.first]))
    {
      // If this is the first iteration, set the current highest predicted
      // rating to the predicted rating for the current movie and store the
      // movie object
      if (!count)
      {
        cur = predict_movie_score (user,vector.first,k);
        movies = vector.first;
        // Increment the counter variable
        count += 1;
      }
        // If this is not the first iteration, check if the predicted rating
        // for the current movie is higher than the current highest predicted
        // rating
      else
      {
        num_of_iteration = predict_movie_score (user,vector.first,k);
        //If the predicted rating for the current movie is higher than the
        // current
        //highest predicted rating, set the current highest predicted rating to
        // the
        // predicted rating for the current movie and store the movie object
        if (num_of_iteration > cur)
        {
          cur = num_of_iteration;
          movies = vector.first;
        }
      }
    }
  }
  // Return the movie object with the highest predicted rating
  return movies;
}
//Returns a shared pointer to the movie object with the specified name and year
sp_movie RecommenderSystem::get_movie
(const std::string &name, double year) const
{
  sp_movie movie =std::make_shared<Movie>(Movie (name,year));
  // Iterate through the map of movies and their feature vectors
  auto m=map.find(movie);
  return m==map.end() ? nullptr :m->first;


    // Check if the current movie has the specified name and year
      // If the current movie has the specified name and year set the
      // shared pointer to the current movie object and break out of the loop
  // Return the shared pointer to the movie object

}

// Overloads the output stream operator for the RecommenderSystem class
std::ostream& operator<<
(std::ostream& ostream, const RecommenderSystem& recommender_system)
{
  // Iterate through the map of movies and their feature vectors
  for (const auto &film : recommender_system.map)
  {
    // Output the movie object to the output stream
    ostream << *film.first;
  }
  // Return the output stream
  return ostream;
}

RecommenderSystem::RecommenderSystem ()
{

}

