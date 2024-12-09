struct Result {
  float avg[3];
};

/*
This is the function you need to implement. Quick reference:
- x coordinates: 0 <= x < nx
- y coordinates: 0 <= y < ny
- horizontal position: 0 <= x0 < x1 <= nx
- vertical position: 0 <= y0 < y1 <= ny
- color components: 0 <= c < 3
- input: data[c + 3 * x + 3 * nx * y]
- output: avg[c]
*/
Result calculate(int ny, int nx, const float *data, int y0, int x0, int y1,
                 int x1) {
  double r = 0.0;
  double g = 0.0;
  double b = 0.0;

  float r_res = 0.0f;
  float g_res = 0.0f;
  float b_res = 0.0f;

  for (int x = x0; x < x1; ++x) {
    for (int y = y0; y < y1; ++y) {
      r += data[0 + 3 * x + 3 * nx * y];
      g += data[1 + 3 * x + 3 * nx * y];
      b += data[2 + 3 * x + 3 * nx * y];
    }
  }

  double rect_sz = (x1 - x0) * (y1 - y0);
  r_res = r / rect_sz;
  g_res = g / rect_sz;
  b_res = b / rect_sz;

  Result result{{r_res, g_res, b_res}};
  return result;
}
