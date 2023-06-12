#include <vector>
#include "nn/utility.cpp"

class poolingLayer
{
    public:
        std::vector<matrix> max_pool(std::vector<matrix> layer_in) {
            std::vector<matrix> layer_out(layer_in.size());
            
            for(int l = 0; l < layer_in.size(); ++l) {
                for(int i = 0; i < layer_in[l].get_size_x(); i += 2) {
                    for(int j = 0; j < layer_in[l].get_size_y(); j += 2) {
                        layer_out[l].set(i / 2, j / 2, max(
                            layer_in[l].get(i, j),
                            layer_in[l].get(i + 1, j),
                            layer_in[l].get(i, j + 1),
                            layer_in[l].get(i + 1, j + 1)
                            ));
                    }
                }
            }
        }
};