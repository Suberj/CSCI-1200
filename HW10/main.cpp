#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <utility>
#include <queue>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
	for (int j2 = 0; j2 < h; j2++) {
	  const Color& c = input.GetPixel(i2,j2);
	  // skip all pixels that are not black
	  if (!c.isBlack()) continue;
	  // calculate the distance between the two pixels
	  double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
	  // store the closest distance to a black pixel
	  if (closest < 0 || distance < closest) {
	    closest = distance;
	  }
	}
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}

//copied most of the NaiveDistanceFieldMethod
//compares every pixel to every black pixel instead of comparing every pixel to every other pixel
//I store every black pixel in a vector of pairs (stores coords)
//I then compare the pixels to all the elements in the black_pixel vector
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
    int w = input.Width();
    int h = input.Height();
    double answer = 0;
    //create a vector to store the coordinates of all black pixels
    std::vector<std::pair<int, int>> black_pixels;
    // loop over the pixels in the input image
    for (int i = 0; i < w; i++)  {
        for (int j = 0; j < h; j++) {
            const Color& c = input.GetPixel(i,j);
            //check if the pixel is black
            if (c.isBlack()) {
                black_pixels.emplace_back(i, j);
            }
            DistancePixel& p = distance_image.GetPixel(i,j);
            p.setValue(-1);
        }
    }
    // loop over the pixels in the input image
    for (int i = 0; i < w; i++)  {
        for (int j = 0; j < h; j++) {
            double closest = -1;
            // loops over all black pixels
            for (unsigned int k = 0; k < black_pixels.size(); k++) {
                int i2 = black_pixels[k].first;
                int j2 = black_pixels[k].second;
                double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
                if (closest < 0 || distance < closest) {
                    closest = distance;
                }
            }
            assert (closest >= 0);
            answer = std::max(answer, closest);
            DistancePixel& p = distance_image.GetPixel(i,j);
            p.setValue(closest);
        }
    }
    return answer;
}
//this is the implementation of the FastMarchingMethod that is described in the HW10 handout
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
    int w = input.Width();
    int h = input.Height();
    double max_distance = 0;
    //create a DistancePixel_PriorityQueue object to store the coordinates of all black pixels
    DistancePixel_PriorityQueue black_pixels;
    //loop over the pixels in the input image
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            const Color& c = input.GetPixel(i,j);
            //check if the pixel is black
            //if pixel is black add it to que and make its value 0
            if (c.isBlack()) {
                DistancePixel tmp(i,j,0);
                black_pixels.push(tmp);
                distance_image.SetPixel(i,j, DistancePixel(i, j, 0));
            }
            //if pixel is not black make its value infinity
            else {
                distance_image.SetPixel(i,j, DistancePixel(i, j, 727379969));
            }
        }
    }
    //going through every black pixel
    while (!black_pixels.empty()) {
        DistancePixel current = black_pixels.top_nonptr();
        black_pixels.pop();
        int x = current.getX();
        int y = current.getY();
        //going through all neightbors
        for (int dx = -1; dx <= 1; dx++) {
            //if 0,0 means that it is itself not a neighbor
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                int nx = x + dx;
                int ny = y + dy;
                //make sure in bounds
                if (nx < 0 || ny < 0 || nx >= w || ny >= h) {
                    continue;
                }
                DistancePixel neighbor = distance_image.GetPixel(nx, ny);
                double distance = neighbor.getValue();
                double new_distance = current.getValue() + sqrt(dx * dx + dy * dy);
                if (new_distance < distance) {
                    neighbor.setValue(new_distance);
                    distance_image.SetPixel(nx, ny, neighbor);
                    black_pixels.push(neighbor);
                    max_distance = std::max(max_distance, new_distance);
                }
            }
        }
    }
    return max_distance;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }
  return answer;
}

// ===================================================================================================
