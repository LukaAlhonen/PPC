/*
This is the function you need to implement. Quick reference:
- input rows: 0 <= y < ny
- input columns: 0 <= x < nx
- element at row y and column x is stored in data[x + y*nx]
- correlation between rows i and row j has to be stored in result[i + j*ny]
- only parts with 0 <= j <= i < ny need to be filled
*/
#include <cmath>
#include <cstring>
#include <vector>

// Normalize matrix rows before calculating matrix product
void normalizeMatrix(int ny, int nx, const float *data,
                     double *normalized_data) {
  // Normalize rows (mean = 0)
  for (int y = 0; y < ny; ++y) {
    double mean = 0.0;
    // Calculate mean of data array
    for (int x = 0; x < nx; ++x) {
      mean += static_cast<double>(data[x + y * nx]);
    }
    mean /= nx;

    // Subtract mean from each value in row
    for (int x = 0; x < nx; ++x) {
      normalized_data[x + y * nx] =
          static_cast<double>(data[x + y * nx]) - mean;
    }
  }

  // Normalize rows again using L2 normalization (sum of squares of elements =
  // 1)
  for (int y = 0; y < ny; ++y) {
    double l2_norm = 0.0;

    for (int x = 0; x < nx; ++x) {
      l2_norm += normalized_data[x + y * nx] * normalized_data[x + y * nx];
    }

    l2_norm = std::sqrt(l2_norm);

    for (int x = 0; x < nx; ++x) {
      normalized_data[x + y * nx] /= l2_norm;
    }
  }
}

// Calculate matrix product of upper triangle of normalized matrix
void matrixProduct(int ny, int nx, double *normalized_data, float *result) {
  for (int i = 0; i < ny; ++i) {
    for (int j = i; j < ny; ++j) {
      double dot_product = 0.0;
      for (int k = 0; k < nx; ++k) {
        dot_product +=
            normalized_data[k + i * nx] * normalized_data[k + j * nx];
      }
      result[j + i * ny] = static_cast<float>(dot_product);
      result[i + j * ny] = static_cast<float>(dot_product);
    }
  }
}

void correlate(int ny, int nx, const float *data, float *result) {
  std::vector<double> normalized_data(ny * nx);

  normalizeMatrix(ny, nx, data, normalized_data.data());

  matrixProduct(ny, nx, normalized_data.data(), result);
}
