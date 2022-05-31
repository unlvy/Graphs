#pragma once

typedef std::vector<int> Vector;
typedef std::vector< Vector > Matrix;
typedef std::array<int, 3> Connection;

class Graph {
    public:
        Matrix _mat;
        Vector _layers;

        Graph( Matrix mat, Vector layers) : _mat(mat), _layers(layers) { }
        void saveMatrixToDotFile( std::string name ) {
            std::ofstream file( name );
            int base = 0;
            int num_cluster = 0;
            file << "digraph {\n";
            for( int layer : _layers ) {
                file << "subgraph cluster_" << num_cluster << " {\n";
                for(int i = base; i < layer + base; i++) {
                    file << "   N" << i << "\n";
                }
                file << "}\n";
                base += layer;
                num_cluster++;
            }
            for(int i = 0; i < _mat.size(); i++) {
                for( int j = 0; j < _mat.size(); j++) {
                    if( _mat[i][j] > 0 )
                        file << "   N" << i << " -> " << "N" << j << "[label=\"0/" << _mat[i][j] << "\"]\n";
                }
            }
            file << "}\n";
            file.close();
        }
};