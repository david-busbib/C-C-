
#include "Movie.h"

#include <utility>
#define HASH_START 17
#define RES_MULT 31

/**
 * hash function used for a unordered_map (implemented for you)
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */

std::size_t sp_movie_hash(const sp_movie& movie){
    std::  res = HASH_START;
    res = res * RES_MULT + std::hash<std::string>()(movie->get_name());
    res = res * RES_MULT + std::hash<int>()(movie->get_year());
    return res;
}

/**
 * equal function used for an unordered_map (implemented for you)
 * @param m1
 * @param m2
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2){
    return !(*m1 < *m2) && !(*m2 < *m1);
}
Movie::Movie(std::string  name, double year) :name(std::move(name)),year(year)
{

}
std::string Movie::get_name() const{
  return (name);
}
double Movie ::get_year () const
{
  return year;
}
// Overloads the less than operator for the Movie class
bool Movie:: operator<(const Movie &movie_2)
{
  // If the year of movie_2 is the same as the current movie object's year
  if (movie_2.get_year() == year)
  {
    // Return true if movie_2's name is
    // greater than the current movie object's name, false otherwise
    return movie_2.name > name;
  }
    // If the year of movie_2 is greater than the current movie object's year
  else
  {
    // Return true if movie_2's year is greater than the
    // current movie object's year, false otherwise
    return movie_2.get_year() > year;
  }
}

// Overloads the less than operator for the Movie class
bool operator<(const Movie &movie_1, const Movie &movie_2)
{
  // If the year of movie_2 is the same as movie_1's year
  if (movie_2.get_year() == movie_1.year)
  {
    // Return true if movie_2's name is  greater than movie_1's name,
    // false otherwise
    return movie_2.name > movie_1.name;
  }
    // If the year of movie_2 is greater than movie_1's year
  else
  {
    // Return true if movie_2's year is greater than movie_1's year,
    // false otherwise
    return movie_2.get_year() > movie_1.year;
  }
}

// Overloads the output stream operator for the Movie class
std::ostream &operator<<(std::ostream &ostream, const Movie &movie)
{
  // Output the movie's name and year to the output stream
  ostream << movie.name << " " << "(" << movie.get_year() << ")" << std::endl;
  // Return the output stream
  return ostream;
}

