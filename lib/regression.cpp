#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include "matplotlibcpp.h"

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
        // table.push_back({elem});
        elems.push_back(elem);
      }
      table.push_back(elems);
    }

  }

  CSV(std::string fname): CSV(fname, ','){ }

};

class Regression{
  public:
    long double theta0, theta1;
    Regression(){
      std::random_device rd;
      std::mt19937_64 mt(rd());
      std::uniform_real_distribution<double> theta(0.0, 1.0);
      theta0 = theta(mt);
      theta1 = theta(mt);
    }





};


namespace plt = matplotlibcpp;

int main(){
  CSV csv("./click.csv");
  std::vector<double> x, y;

  for (int i = 1; i < int(csv.table.size()); i++) {
    // std::cout << csv.table[0][i] << std::endl;
    x.push_back(stod(csv.table[i][0]));
    y.push_back(stod(csv.table[i][1]));
  }
  // for (int i = 1; i < int(csv.table[0].size()); i++) {
  //   y.push_back(stod(csv.table[1][i]));
  //   // y[i] = 2 * i;
  // }

  Regression r;

  // plt::scatter<double, double>(x, y, 50);
  // plt::show();
  return 0;
}
