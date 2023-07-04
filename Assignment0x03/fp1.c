#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_VERTICES 10001
#define MAX_EDGES 50000001

typedef struct {
  int u, v, weight;
} edge;

int parent[MAX_VERTICES] = {0};
int size[MAX_VERTICES];
int vertex_num = 0;
int mst_cnt = 0;
long long int edge_num = 0;
long long int mst_weight = 0;
edge min_heap[MAX_EDGES];
FILE *input_file, *output_file;

int findroot(int x); // This function is part of the Union-Find algorithm. It is used to find the root of a set containing the element x.
void unionSets(int, int); // This function is also part of the Union-Find algorithm. It merges two sets together.
void checkconnection(); // This function checks if the graph is connected or not.
void initialize();
void kruskal(); // This function implements the Kruskal's algorithm to find the Minimum Spanning Tree (MST) of a graph.
edge delete(); // This function is used to delete the minimum element from the heap.

int main(int argc, char *argv[]) {
  if (argc != 2) {
  fprintf(stderr, "usage: ./fp1 input_filename\n");
  return 1;
}

  input_file = fopen(argv[1], "r");
  output_file = fopen("fp1_result.txt", "w");

  if (input_file == NULL) {
    fprintf(stderr, "The input file does not exist.\n");
    return 2;
  }
  clock_t start = clock();
  initialize();
  kruskal();
  checkconnection();
  clock_t end = clock();

  double duration = ((double)end - (double)start) / CLOCKS_PER_SEC;
  printf("running time: %lf seconds\n", duration);
  fclose(input_file);
  return 0;
}

/* This function is part of the Union-Find algorithm. 
* It is used to find the root of a set containing the element x. */
int findroot(int x) {
  while (1) {
    if (parent[x] < 0) break;
    x = parent[x];
  }
  return x;
}

/* This function merges two sets based on their sizes */ 
void unionSets(int x, int y) {
    int xRoot = findroot(x);
    int yRoot = findroot(y);

    // Ensure that the smaller set is absorbed into the larger set
    if (size[xRoot] < size[yRoot]) {
        parent[xRoot] = yRoot;
        size[yRoot] += size[xRoot];
    } else {
        parent[yRoot] = xRoot;
        size[xRoot] += size[yRoot];
    }
}


/* This function checks if the graph is connected or not. */
void checkconnection() {
  output_file = fopen("fp1_result.txt", "a");

  if(mst_cnt == vertex_num - 1) {
    fprintf(output_file, "CONNECTED\n");
  } else {
    fprintf(output_file, "DISCONNECTED\n");
  }

  fclose(output_file);
  return;
}

void initialize() {
  fscanf(input_file, "%d", &vertex_num);
  fscanf(input_file, "%lld", &edge_num);
  for (long long int i = 0; i < edge_num; i++) {
    int index = i + 1;
    edge new_edge;
    fscanf(input_file, "%d %d %d", &new_edge.u, &new_edge.v, &new_edge.weight);
    while ((new_edge.weight < min_heap[index / 2].weight) && (index != 1)) {
      min_heap[index] = min_heap[index / 2];
      index /= 2;
    }
    min_heap[index] = new_edge;
  }

  for (int i = 0; i < vertex_num; i++) {
    parent[i] = -1;
  }
}

/* This function is used to delete the minimum element from the heap. */
edge delete() {
  long long int heap_num = edge_num;
  edge min, last_edge;
  
  min = min_heap[1];
  last_edge = min_heap[heap_num--];
  
  long long int index = 1;
  while (index * 2 <= heap_num) {
    long long int child = index * 2;
    
    // Find smaller child
    if (child != heap_num && min_heap[child].weight > min_heap[child + 1].weight)
      child++;
    
    // If the child is greater than the last element, we can place the last element in the current index position
    if (last_edge.weight <= min_heap[child].weight)
      break;

    // Move the child up
    min_heap[index] = min_heap[child];
    index = child;
  }
  
  min_heap[index] = last_edge;
  
  return min;
}

/* This function implements the Kruskal's algorithm to find the Minimum Spanning Tree (MST) of a graph. */
void kruskal() {
  for (long long int i = 0; i < edge_num; i++) {
    if (mst_cnt == vertex_num - 1) break;
    edge min_edge = delete();

    if (findroot(min_edge.u) == findroot(min_edge.v))
      continue;
    else {
      unionSets(findroot(min_edge.u), findroot(min_edge.v));
      mst_cnt++;
      mst_weight += min_edge.weight;
      fprintf(output_file, "%d %d %d\n", min_edge.u, min_edge.v, min_edge.weight);
    }
  }
  fprintf(output_file, "%lld\n", mst_weight);
  fclose(output_file);
  printf("output written to fp1_result.txt.\n");
}