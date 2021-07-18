#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

struct Config
{
  std::string EditorPath;
  std::string PostsDir;
};

void ReadConfig(Config& config);

int main(int argc, char* argv[])
{
  Config config;
  ReadConfig(config);
  
  std::string post = "../_posts/2021-06-05-my-story.markdown";

  std::string command = "\"" + config.EditorPath + "\" " + post;
  std::cout << command << std::endl;

  return std::system(command.c_str());
}

void ReadConfig(Config& config)
{
  std::fstream file("config.txt", std::ios_base::in);
  if (!file.is_open())
  {
    throw std::runtime_error("Unable to open config.txt");
  }

  std::string line;
  while (std::getline(file, line))
  {
    if (line.length() == 0)
      continue;

    std::size_t pos = line.find('=');

    if (pos == std::string::npos)
      continue;

    std::string key = line.substr(0, pos);
    std::string val = line.substr(pos + 1, line.length() - 1);
    
    if (key == "editor")
      config.EditorPath = val;
    else if (key == "posts_dir")
      config.PostsDir = val;
  }

  file.close();
}
