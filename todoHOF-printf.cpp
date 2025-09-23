#include <cstdio> // for printf
#include <fstream>
#include <iostream> // for cerr

#define RESET "[0m"
#define BRIGHT_MAGENTA "[95m"

using namespace std;
int main(int argc, char *argv[]) {
  // print string with format specifiers:
  // %[flags][width][.precision][length]specifier
  //
  // specifier	Output	Example
  // d or i	Signed decimal integer	392
  // u	Unsigned decimal integher	7235
  // f	Decimal floating point, lowercase	392.65
  // e	Scientific notation (mantissa/exponent), lowercase	3.9265e+2
  // g	Use the shortest representation: %e or %f	392.65
  // c	Character	a
  // s	String of characters	sample
  // p	Pointer address	b8000000
  // n	Nothing printed - outputs # of chars printed so farm to *int
  // The corresponding argument must be a pointer to a signed int.
  // The number of characters written so far is stored in the pointed location.
  // %	A % followed by another % character will write a single % to the stream.
  puts("puts"); // if you dont need format

  char str[] = "HELLO";
  int goo;

  printf("The humble printf statement.%n\n", &goo);
  printf("Last statement had %i chars.\n", goo);
  printf("The %10s humble %-10s printf  statement\n", str, str); // justifying
  printf("printf" BRIGHT_MAGENTA "concatenates\n" RESET);

  printf("some variables: %i %c %s ");
  fprintf(stderr, "The humble fprintf statement: print to stream\n");

  FILE *file = fopen("asdf.txt", "w+");
  // if (!file)// handle
  fprintf(file, "fprintf: print to file.");
  fclose(file);

  float f;
  FILE *pFile;

  pFile = fopen("myfile.txt", "w+");
  fprintf(pFile, "%f %s", 3.1416, "PI");
  rewind(pFile);
  fscanf(pFile, "%f", &f);
  fscanf(pFile, "%s", str);
  fclose(pFile);
  printf("I have read: %f and %s \n", f, str);

  return 0;
}
