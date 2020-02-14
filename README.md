# mrover-artag
This repository is meant for AR Tag detection for the University of Michigan Mars Rover Team

## Branches
`master` - the most up-to-date, working detection.

`secondary-detection` - meant for developing the fallback detection - the detector that runs if ARUCO fails to find the tags.

## Building
To build, simply run the following command:
```g++ main.cpp -o main `pkg-config --cflags --libs opencv` -std=c++11```
