neighbCount <- function(x, y, radius = 0.05)
{
  cnc <- function(x, rd)
  {
    length(x[x <= rd])
  }
  mtr <- distMatr2d(x, y)
  apply(mtr, 1, cnc, radius)
}
