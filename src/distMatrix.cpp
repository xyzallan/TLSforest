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

// [[Rcpp::export]]
NumericMatrix cppDistMatr2d(NumericVector x, NumericVector y) {
  NumericMatrix retValue(x.size(), x.size());
  for(int i = 0; i < x.size(); i++)
  {
    retValue(_,i) = sqrt(pow(x - x[i], 2) + pow(y - y[i], 2));
  }
  return retValue;
}


// [[Rcpp::export]]
NumericMatrix cppDistMatr3d(NumericVector x, NumericVector y, NumericVector z) {
  NumericMatrix retValue(x.size(), x.size());
  for(int i = 0; i < x.size(); i++)
  {
    retValue(_,i) = sqrt(pow(x - x[i], 2) + pow(y - y[i], 2) + pow(z - z[i], 2));
  }
  return retValue;
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//


