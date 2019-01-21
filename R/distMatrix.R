# Matrix of distances from 2D data
distMatr2d <- function(x, y)
{
  sqrt(outer(x, x,"-")^2 + outer(y, y,"-")^2)
}

# Matrix of distances from 3D data
distMatr3d <- function(x, y, z)
{
  sqrt(outer(x, x,"-")^2 + outer(y, y,"-")^2 + outer(z, z,"-")^2)
}

