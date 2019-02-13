# Matrix of distances from 2D data
distMatr2d <- function(x, y)
{
  sqrt(outer(x, x,"-")^2 + outer(y, y,"-")^2)
}

cppFunction('
NumericMatrix cppDistMatr2d(NumericVector x, NumericVector y) {
  NumericMatrix retValue(x.size(), x.size());

  for(int i = 0; i < x.size(); i++)
    {
      retValue(_,i) = sqrt(pow(x - x[i], 2) + pow(y - y[i], 2));
    }
    return retValue;
}')

# Matrix of distances from 3D data
distMatr3d <- function(x, y, z)
{
  sqrt(outer(x, x,"-")^2 + outer(y, y,"-")^2 + outer(z, z,"-")^2)
}

cppFunction('
NumericMatrix cppDistMatr3d(NumericVector x, NumericVector y, NumericVector z) {
  NumericMatrix retValue(x.size(), x.size());

  for(int i = 0; i < x.size(); i++)
    {
      retValue(_,i) = sqrt(pow(x - x[i], 2) + pow(y - y[i], 2) + pow(z - z[i], 2));
    }
    return retValue;
}')
