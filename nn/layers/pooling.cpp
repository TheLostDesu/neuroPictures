#include <vector>
#include "utility.cpp"

class poolingLayer
{
    public:
        std::vector<matrix> pool(std::vector<matrix> layer_in) {
            
            for(int l = 0; l < layer_in.size(); ++l) {
                for(int i = 0; i < layer_in[l].get_size_x(); i += 2) {
                    for(int j = 0; j < layer_in[l].get_size_y(); j += 2) {
                        

                    }
                }
            }
        }
};