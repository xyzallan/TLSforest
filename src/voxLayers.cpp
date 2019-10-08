#include <Rcpp.h>
using namespace Rcpp;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

struct point2d
{
  int x, y;
};

bool operator< ( point2d a, point2d b ) { return (std::make_pair(a.x,a.y) < std::make_pair(b.x,b.y)); }

typedef std::map<point2d, int> innerXYN;
typedef std::map<int, innerXYN> mainMapZXY;


// [[Rcpp::export]]
DataFrame voxLayers(NumericVector x, NumericVector y, NumericVector z, double res = 0.01) {
  mainMapZXY vox;
  std::vector<double> tulX;
  std::vector<double> tulY;
  std::vector<double> tulZ;
  std::vector<int> tulN;
  
  double zStep = 0.05;
  
  for(int i = 0; i < x.length(); i++)
  {
    point2d pnt;
    int iX = (x(i)) / res;
    int iY = (y(i)) / res;
    int iZ = (z(i) / zStep);
    pnt.x = iX;
    pnt.y = iY;
    vox[iZ][pnt]++;
  }
  
  for (mainMapZXY::iterator mmIt = vox.begin(); mmIt != vox.end(); ++mmIt)
  {
    for (innerXYN::iterator imIt = mmIt->second.begin(); imIt != mmIt->second.end(); ++imIt)
    {
      tulZ.push_back(((double)mmIt->first) * zStep);
      
      tulX.push_back(((double)imIt->first.x) * res);
      tulY.push_back(((double)imIt->first.y) * res);
      
      tulN.push_back(imIt->second);
    }
  }  

  return DataFrame::create(
    _["x"] = tulX,
    _["y"] = tulY,
    _["z"] = tulZ,
    _["n"] = tulN
  );
}


typedef std::map<int, int> innerZN;
typedef std::map<point2d, innerZN> mainMapXYZ;

// [[Rcpp::export]]
DataFrame mapLevels(NumericVector x, NumericVector y, NumericVector z, double res = 0.01) {
  mainMapXYZ vox;
  
  for(int i = 0; i < x.length(); i++)
  {
    point2d pnt;
    int iX = (x(i)) / res;
    int iY = (y(i)) / res;
    int iZ = (z(i)) / res;
    pnt.x = iX;
    pnt.y = iY;
    vox[pnt][iZ]++;
  }
  
  std::vector<double> tulX;
  std::vector<double> tulY;
  std::vector<double> tulZ;
  std::vector<int> tulN;
  for (mainMapXYZ::iterator mmIt = vox.begin(); mmIt != vox.end(); ++mmIt)
  {
    for (innerZN::iterator imIt = mmIt->second.begin(); imIt != mmIt->second.end(); ++imIt)
    {
      tulX.push_back(((double)mmIt->first.x) * res);
      tulY.push_back(((double)mmIt->first.y) * res);
      tulZ.push_back(((double)imIt->first) * res);
      tulN.push_back(imIt->second);
    }
  }  
  
  return DataFrame::create(
    _["x"] = tulX,
    _["y"] = tulY,
    _["z"] = tulZ,
    _["n"] = tulN
  );
}


