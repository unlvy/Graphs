#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <array>
#include <algorithm>
#include <fstream>
#include <time.h>

#include "Graph.h"

typedef std::vector<int> Vector;
typedef std::vector< Vector > Matrix;
typedef std::array<int, 3> Connection;

void printMatrix( Matrix mat );
void printVector( Vector vec );
Vector range_vec(int from, int to);
void printConnection( Connection con );
bool conEquals( Connection c1, Connection c2 );
bool containsConnection( std::vector<Connection> vec, Connection con );
std::vector<Connection> createMinConnections( Vector given_layer_left, Vector given_layer_right );
Graph createRandomGraphFlow(int N);

Matrix fordFulkerson( Matrix mat );
Vector bfs( Matrix mat );




//--------------------------------------------------
int main() {

bool input = true;
char key;
while( input == true ) {

    int layers;

    std::cout << "// Amount of layers: ";
    std::cin >> layers; 
    srand( time( NULL ) );

    Graph graph = createRandomGraphFlow( layers );
    Matrix mat = graph._mat;

    std::cout << "\n\n\n\n-------------Created Random Graph ------------\n\n";
    printMatrix(mat);

    bfs(mat);
    Matrix mat_new = fordFulkerson( mat );

    std::cout << "\n\n\n\n-------------Computed max flow Graph ------------\n\n";
    printMatrix(mat_new);

    graph.saveMatrixToDotFile("mat.dot");

    std::cout << "// \n\nPress q to quit or sth else to continue\n";
    std::cin >> key;
    if( key == 'q' ) {
        input = false;
        std::cout << std::endl;
    }
}  
  
  return 0;
}
//------------------------------------------main end




Vector bfs( Matrix mat ) {
  Vector s_path;
  Vector visited;
  Vector queue = { 0 };
  Vector parents;

  int target_index = mat.size() - 1;
  visited.resize( mat.size(), 0 );
  parents.resize( mat.size(), -1 );

  while( !queue.empty() && std::find(queue.begin(), queue.end(), target_index) == queue.end() ) {
    
    int node = queue.front();
    visited[node] = true;
    
    for(int i = 1 ; i < mat.size(); i++) {
      if( mat[node][i] > 0 && visited[i] == false ) {
        visited[i] = true;
        parents[i] = node;
        queue.push_back(i);
      }
    }

    queue.erase( queue.begin() );
  }
  
  if( !queue.empty() ) {
    int parent = target_index;
    while( parent != -1 ) {
      s_path.insert(s_path.begin(), parent);
      parent = parents[parent];
    }
  }
  
  return s_path;
}



Matrix fordFulkerson( Matrix mat ) {

  int gathered_flow = 0;
  int path_min_flow;
  Vector shortest_path = bfs(mat);
  
  while( !shortest_path.empty() ) {

    path_min_flow = 1000000;
    for(int i = 0; i < shortest_path.size() - 1; i++) {
      if( path_min_flow > mat[ shortest_path[i] ][ shortest_path[i+1] ])
        path_min_flow = mat[ shortest_path[i] ][ shortest_path[i+1] ];
    }

    gathered_flow += path_min_flow;

    // adjusting flow in matrix
    for(int i = 0; i < shortest_path.size() - 1; i++) {
        mat[ shortest_path[i] ][ shortest_path[i+1] ] -= path_min_flow;
        mat[ shortest_path[i+1] ] [shortest_path[i] ] += path_min_flow;
    }

    shortest_path = bfs(mat);
  }
  std::cout << "\n\nMaximum flow in this network is : " << gathered_flow << " \n\n";
  return mat;
}



std::vector<Connection> createLayersConnections( Vector given_layer_left, Vector given_layer_right ) {
  std::vector<Connection> c_vec;

  Vector layer_left = given_layer_left;
  Vector layer_right = given_layer_right;
  int amount_min = std::min( layer_left.size(), layer_right.size() );
  int amount_max = std::max( layer_left.size(), layer_right.size() );

  // connecting all nodes for smaller layer
  for(int i = 0; i < amount_min; i++) {
    int i_left = std::rand() % layer_left.size();
    int i_right = std::rand() % layer_right.size();
    int flow = std::rand() % 9 + 1;
    
    c_vec.push_back( { layer_left[i_left], layer_right[i_right], flow } );
    
    layer_left.erase( layer_left.begin() + i_left );
    layer_right.erase( layer_right.begin() + i_right );
  }

  // connecting rest of nodes from bigger layer
  bool erase_left = true;
  Vector layer_left_rest = layer_left.empty() ? erase_left = false, given_layer_left : layer_left;
  Vector layer_right_rest = layer_right.empty() ? given_layer_right : layer_right;

  for(int i = 0; i < amount_max - amount_min; i++) {
    
    int i_left = std::rand() % layer_left_rest.size();
    int i_right = std::rand() % layer_right_rest.size();
    int flow = std::rand() % 9 + 1;

    c_vec.push_back( { layer_left_rest[i_left], layer_right_rest[i_right], flow } );
    
    if( erase_left )
        layer_left_rest.erase( layer_left_rest.begin() + i_left );
    else
        layer_right_rest.erase( layer_right_rest.begin() + i_right );
  }

  return c_vec;
}


Graph createRandomGraphFlow(int N) {

  // draw amount of nodes in each layer
  Vector layers = { 1 }; // source
  for(int i = 0; i < N; i++)
    layers.push_back( std::rand() % (N - 1) + 2 );
  layers.push_back(1); // target

  std::cout<< "Layers: ";
  printVector( layers );

  // creating empty graph
  int Mat_size = std::accumulate(layers.begin(), layers.end(), 0);
  Vector vec;
  Matrix mat;
  vec.resize(Mat_size, 0);
  mat.resize(Mat_size, vec);

  // creating connections in graph
  int node_index_base = 0;
  std::vector<Connection> conn_vec;
  std::vector<Connection> all_connections;

  for(int i = 0; i < layers.size() - 1; i++) {
    node_index_base = std::accumulate(layers.begin(), layers.begin() + i, 0);
    
    Vector l_left = range_vec(node_index_base, node_index_base + layers[i]);
    node_index_base += layers[i];
    Vector l_right = range_vec(node_index_base, node_index_base + layers[i+1]);

    conn_vec = createLayersConnections(l_left, l_right);
    all_connections.insert(all_connections.end(), conn_vec.begin(), conn_vec.end());
  }

  // Additional 2N completly random connections
  Vector left_nodes = range_vec(0, Mat_size - 1);
  Vector right_nodes = range_vec(1, Mat_size);
  std::vector<Connection> add_vec;

  for( int i = 0; i < 2 * N; i++ ) { 

    int i_left = std::rand() % left_nodes.size();
    int i_right = std::rand() % right_nodes.size();
    int flow = std::rand() % 9 + 1;

    Connection con = { left_nodes[i_left], right_nodes[i_right], flow };

    if( containsConnection(all_connections, con) || left_nodes[i_left] == right_nodes[i_right] )
      i--;
    else 
      all_connections.push_back( con );
  }

  //Adding connections to graph matrix
  for( Connection c : all_connections ) {
    mat[ c[0] ][ c[1] ] = c[2];
  }

  return  Graph(mat, layers);
}



void printMatrix( Matrix mat ) {
  
  printf("   |");
  for(int i = 0; i < mat.size(); i++ )
    printf("%2d ", i);
  printf("\n");

  printf("----");
    for(int i = 0; i < mat.size(); i++ )
    printf("---");
  printf("\n");

  int k = 0;
  for( Vector vec : mat ) {
    printf("%2d |",k);
    for( int el : vec )
      printf("%2d ", el);
    printf("\n");
    k++;
    }
}



void printVector( Vector vec ) {
  
  if(vec.size() > 0) printf("[ %2d", vec[0]);
  else printf("[");
  
  for(int i = 1; i < vec.size(); i++)
    printf(", %2d", vec[i]);
  printf(" ]\n");
}



Vector range_vec(int from, int to) {
  Vector vec;
  for( int i = from; i < to; i++) 
    vec.push_back(i);

  return vec;
}



void printConnection( Connection con ) {
  printf("[%d, %d] -> %d\n", con[0], con[1], con[2]);
}



bool conEquals( Connection c1, Connection c2 ) {
  return c1[0] == c2[0] && c1[1] == c2[1] || c1[0] == c2[1] && c1[1] == c2[0];
}



bool containsConnection( std::vector<Connection> vec, Connection con ) {
  for( Connection c : vec)
    if( conEquals(c, con) ) return true;
  return false;
}