#include <vector>
#include "utility.cpp"
#include "GPU_stuff/matrix_mul.cpp"

class perceptronLayer 
{
    public:
        matrix predict(matrix layer_in) {
            if(layer_in.get_size_x() > 1) {
                return matrix_mul(layer_in, weights);
            }
            else {
                return matrix_mul(weights, layer_in); 
            }
        }
    private:
        matrix weights;
};