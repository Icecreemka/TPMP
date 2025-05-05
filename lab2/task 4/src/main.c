#include <stdio.h>

void processPatients(const char *inputPath, const char *outputPath);

int main(int argc, char *argv[]) {
  const char *input = argc > 1 ? argv[1] : "data/input.txt";
  processPatients(input, "output/result.txt");
  return 0;
}
