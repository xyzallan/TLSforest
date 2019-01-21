# Neighbours count from 2D data

neighbCount2d <- function(x, y, radius = 0.05)
{
  apply(
    distMatr2d(x, y), 
    1, 
    function(x, rd){length(x[x <= rd])}, 
    radius)
}

# Neighbours count from 3D data
neighbCount3d <- function(x, y, z, radius = 0.05)
{
  apply(
    distMatr3d(x, y, z), 
    1, 
    function(x, rd){length(x[x <= rd])}, 
    radius)
}
