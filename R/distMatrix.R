distMatr2d <- function(x, y)
{
  sqrt(outer(x, x,"-")^2 + outer(y, y,"-")^2)
}
