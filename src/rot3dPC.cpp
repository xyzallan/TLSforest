#include <Rcpp.h>
#include <math.h>

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

// [[Rcpp::export]]
DataFrame rot3dPC(NumericVector x, NumericVector y, NumericVector z,
                  double degx = 0.0, double degy = 0.0, double degz = 0.0,
                  double pivotx = 0.0, double pivoty = 0.0, double pivotz = 0.0
                  ) {
  int num = x.length();
  double radx = (degx*M_PI)/180;
  double rady = (degy*M_PI)/180;
  double radz = (degz*M_PI)/180;
  
  
  NumericMatrix res(num, 3);
  for (int p1 = 0; p1 < num; p1++) {
    double xi = x(p1);
    double yi = y(p1);
    double zi = z(p1);
    
    
    double xii = xi * cos(radz) - yi * sin(radz);
    double yii = xi * sin(radz) + yi * cos(radz);
    double zii = zi;
    
    // rotation along y
    double xiii = xii * cos(rady) - zii * sin(rady);
    double yiii = yii;
    double ziii = xii * sin(rady) + zii * cos(rady);
    
    // rotation along x
    double xiiii = xiii;
    double yiiii = yiii * cos(radx) - ziii * sin(radx);
    double ziiii = yiii * sin(radx) + ziii * cos(radx);
    
    res(p1, 0) = xiiii + pivotx;
    res(p1, 1) = yiiii + pivoty;
    res(p1, 2) = ziiii + pivotz;
    
    
  }
  
  return DataFrame::create(_["x"] = res(_,0), _["y"] = res(_,1), _["z"] = res(_,2));
}
