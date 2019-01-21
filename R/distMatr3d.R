distMatr3d <- function(x, y, z)
{
  sqrt(outer(x, x,"-")^2 + outer(y, y,"-")^2 + outer(z, z,"-")^2)
}
