#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <numeric>
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

    std::vector<double> standardization(std::vector<double> xs){
      double mean = accumulate(xs.begin(), xs.end(), 0) / double(xs.size());
      double stdv = 0;
      for(auto a : xs) stdv += (a - mean) * (a - mean);
      stdv /= double(xs.size());
      stdv = sqrt(stdv);
      for (int i = 0; i < int(xs.size()); i++) {
        xs[i] = (xs[i] - mean) / stdv;
      }
      return xs;
    }

    // predict function
    double f(long double x){
      return theta0 + theta1 * x;
    }

    // objective function
    double e(std::vector<double> xs, std::vector<double> ys){
      double result = 0;
      for (int i = 0; i < int(xs.size()); i++) {
        result += (ys[i] - f(xs[i])) * (ys[i] - f(xs[i]));
      }
      result /= 2.0;
      return result;
    }

    void fit(std::vector<double> xs, std::vector<double> ys){
      xs = standardization(xs);
      const double ETA = 1e-3;
      double diff = 1;
      int count = 0;
      double error = e(xs, ys);

      while(diff > 1e-2){
        double tmp0 = 0, tmp1 = 0;
        for(int i = 0; i < int(xs.size()); i++){
          tmp0 += f(xs[i]) - ys[i];
          tmp1 += (f(xs[i]) - ys[i]) * xs[i];
        }
        std::cout << tmp0 << std::endl;
        std::cout << tmp1 << std::endl;
        tmp0 *= ETA;
        tmp1 *= ETA;
        tmp0 = theta0 - tmp0;
        tmp1 = theta1 - tmp1;
        theta0 = tmp0;
        theta1 = tmp1;
        puts("===");

        double current_err = e(xs, ys);
        diff = error - current_err;
        error = current_err;
        count++;
        std::cout << "count: " << count << std::endl;
        std::cout << "theta0: " << theta0 << std::endl;
        std::cout << "theta1: " << theta1 << std::endl;
        std::cout << "diff: " << diff << std::endl;
      }
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

  Regression r;
  r.fit(x, y);
  std::vector<double> tmp;
  x = r.standardization(x);
  for(auto a : x){
    tmp.push_back(r.f(a));
  }


  plt::scatter<double, double>(x, y, 50);
  plt::named_plot("theta0 + theta1 * x", x, tmp);
  plt::title("click.csv");
  plt::legend();
  plt::show();

  return 0;
}
