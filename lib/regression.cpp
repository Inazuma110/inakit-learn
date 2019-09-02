#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class CSV{
  public:
    std::vector<std::vector<std::string>> table;
    std::string fname;
    char spliter;

  CSV(std::string fname, char spliter): fname(fname), spliter(spliter){
    std::ifstream ifs(fname);
    std::string line;
    while(getline(ifs, line)){
      std::string elem;
      std::istringstream stream(line);
      std::vector<std::string> elems;
      while(getline(stream, elem, spliter)){
        elems.push_back(elem);
      }
      table.push_back(elems);
    }

  }

  CSV(std::string fname): CSV(fname, ','){ }

};

int main(){
  CSV csv("./click.csv");
  return 0;
}
