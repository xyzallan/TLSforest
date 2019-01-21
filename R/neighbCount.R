# Neighbours count from 2D data

neighbCount2d <- function(x, y, radius = 0.05)
{
  cnc <- function(x, rd)
  {
    length(x[x <= rd])
  }
  apply(distMatr2d(x, y), 1, cnc, radius)
}

# Neighbours count from 3D data
neighbCount3d <- function(x, y, z, radius = 0.05)
{
  cnc <- function(x, rd)
  {
    length(x[x <= rd])
  }
  apply(distMatr3d(x, y, z), 1, cnc, radius)
}
