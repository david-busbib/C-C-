#include <iostream>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
  std::ifstream file ("C:\\Users\\busbib\\CLionProjects\\ex5\\RSUsersLoader_input.txt");
  if (!file.is_open ())
  {
    std::cout << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  std::string token;
  std::string name;
  double year;
  int t = 0;
  while (std::getline (file, line))
  {
    std::istringstream iss (line);
    std::string token;
    for (int i = 0; i < line.size (); i++)
    {
      if (line[i] != ' ' && line[i] != '-')
      {
        token += line[i];

      }
      else {
        std::cout << token << '\n';
        token.erase ();
      }
    }
    }
    file.close ();
    return 0;

}
