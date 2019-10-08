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

double nurk(double difX, double difY)
{
  return atan2(difX, difY)/PI*180;
}

// [[Rcpp::export]]
DataFrame regTreePos(NumericVector x1, NumericVector y1, NumericVector x2, NumericVector y2) {
  
  mainMapZXY rotPos;
  std::vector<double> tulX;
  std::vector<double> tulY;
  std::vector<double> tulZ;
  std::vector<int> tulN;
  const double res = 0.01;
  const double zStep = 0.2;

  for(int m1p1 = 0; m1p1 < (x1.length()-1); m1p1++)
  {
    
    for(int m1p2 = 1; m1p2 < x1.length(); m1p2++)
    {
      double xd1 = x1(m1p2) - x1(m1p1);
      double yd1 = y1(m1p2) - y1(m1p1);
      double distI = sqrt(xd1 * xd1 + yd1 * yd1);

      for(int m2p1 = 0; m2p1 < (x2.length()-1); m2p1++)
      {
        
        for(int m2p2 = 1; m2p2 < x2.length(); m2p2++)
        {
          double xd2 = x2(m2p2) - x2(m2p1);
          double yd2 = y2(m2p2) - y2(m2p1);

          double distJ = sqrt(xd2 * xd2 + yd2 * yd2);
          
          if((fabs(distJ - distI) < 0.1) & (m1p1 != m1p2) & (distJ > 5))
          {
            // 1) Leida I ja J nurkade erinevus
            double N1 = nurk(xd1, yd1);
            double N2 = nurk(xd2, yd2);
            
            double angDif = N1 - N2 + 360;
            //if(angDif > 360) angDif -= 360;

            // 2) Arvutada m2p1 punkti kaugus keskkohast
            double distJ1 = sqrt(x2(m2p1)*x2(m2p1) + y2(m2p1)*y2(m2p1));

            // 4) Arvutada uus J tsenter
            double asim2 = nurk(x2(m2p1), y2(m2p1));

            double uRotX = sin((asim2 + angDif)/180*PI) * distJ1;
            double uRotY = cos((asim2 + angDif)/180*PI) * distJ1;

            
            double uX = uRotX - x1(m1p1);
            double uY = uRotY - y1(m1p1);

            point2d pnt;
            int iX = uX / res;
            int iY = uY / res;
            int iZ = angDif / zStep;
            pnt.x = iX;
            pnt.y = iY;
            rotPos[iZ][pnt]++;
          }
        }
      }
    }
  }
  
  for (mainMapZXY::iterator mmIt = rotPos.begin(); mmIt != rotPos.end(); ++mmIt)
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
    _["dX"] = tulX,
    _["dY"] = tulY,
    _["rZ"] = tulZ,
    _["n"] = tulN
  );
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

