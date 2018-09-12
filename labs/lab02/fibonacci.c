#include <stdio.h>
#include <stdlib.h>

int fib_recursive(int n) {
  if (n == 2 || n == 1) return 1;
  return fib_recursive(n-1) + fib_recursive(n-2);
}

int fib_memoization(int n, int *arr) {
  if (arr[n] != 0) return arr[n];
  
  int result;
  if (n == 1 || n == 2) {
    result = 1;
  } else {
    result = fib_memoization(n-1, arr) + fib_memoization(n-2, arr);
  }
  arr[n] = result;
  return result;
}

int fib_bottom_up(int n) {
  if (n == 1 || n == 2) return 1;
  int arr[n+1];
  arr[0] = arr[1] = arr[2] = 1;
  int i;
  for (i = 3; i <= n; i++) {
    arr[i] = arr[i-1] + arr[i-2];
  }
  return arr[n];
}

int main(int argc, char *argv[]) {
  if (argc > 10) {
    printf("ERROR: Too many inputs!\n");
    return EXIT_FAILURE;
  }

  int i, num, fib;
  int arr[100];

  // Initializa the int array
  for (i = 0; i < 100; i++) arr[i] = 0;

  for (i = 1; i < argc; i++) {
    num = atoi(argv[i]);
    // fib = fib_recursive(num);
    fib = fib_bottom_up(num);
    // fib = fib_memoization(num, arr);
    printf("fib(%d) is %d\n", num, fib);
  }
  
  return EXIT_SUCCESS;
}
