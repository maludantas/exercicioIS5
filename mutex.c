#include <stdio.h>
#include <pthread.h>

void *somation(void *matrix_line);

int number, somation_value = 0, total_somation_value = 0;
int size = 0, j = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
  int i = 0, j = 0;
  scanf("%d", &size);

  int matrix[size][size], matrix_line[size];
  pthread_t threads_array[size];

  for (i=0; i<size; i++){
    for (j=0; j<size; j++){
      scanf(" %d", &number);
      matrix[i][j] = number;
      matrix_line[j] = number;
    }

    pthread_create(&(threads_array[i]), NULL, somation, (void *)matrix_line);
    somation_value = 0;
  }

  for (i=0; i<size; i++){
    pthread_join(threads_array[i], NULL);
  }

  printf("%d\n", total_somation_value);
  return 0;
}

void *somation(void *matrix_line){
  int *matrix_function = (int *)matrix_line;
  somation_value = 0;
  pthread_mutex_lock(&mutex);

  for (j=0; j<size; j++){
   somation_value += matrix_function[j];
   total_somation_value += matrix_function[j];
  }
  j++;

  pthread_mutex_unlock(&mutex);
}
