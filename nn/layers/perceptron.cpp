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

vector<double> calculate_error(vector<double>& output_res,vector<double>& result)){
    int result_size = result.size();
    vector<double> error(output_size);

    for (int i = 0; i < result_size; ++i){
        error[i] = result[i] - output_res[i];}
    }
    return error;
}

void update_weights(vector<double>& input, vector<double>& gradients, double learning_rate){
    int input_size = input.size();
    int gradients_size = gradients.size();

    for (int i = 0; i < input_size; ++i){
        for (int j = 0; j < gradients_size; ++j){
            weights[i][j] += learning_rate * input[i] * gradients[i]
        }
    }
}