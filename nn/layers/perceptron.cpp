#include "nn/utility.cpp"
#include <vector>

class perceptronLayer 
{
    public:
        matrix predict(matrix layer_in) {
            if(layer_in.get_size_x() > 1) {
                return layer_in * weights;
            }
            else {
                return weights * layer_in; 
            }
        }
        
    private:
        void update_weights(std::vector<double>& error, std::vector<double>& gradients, double learning_rate)
        {
            int error_size = error.size();
            int gradients_size = gradients.size();

            for (int i = 0; i < error_size; ++i)
            {
                for (int j = 0; j < gradients_size; ++j)
                {
                    weights.add(i, j, learning_rate * error_size[i] * gradients[i]);
                }
            }
        }


        matrix weights;
};




std::vector<double> calculate_hidden_error(std::vector<double>& gradients, matrix& next_layer_weights) 
{
    int input_size = weights.size();
    int output_size = gradients.size();

    vector<double> hidden_error(input_size);

    for (int i = 0; i < input_size; ++i) 
    {
        double error = 0.0;
        for (int j = 0; j < output_size; ++j) 
        {
            error += gradients[j] * next_layer_weights[i][j];
        }
        hidden_error[i] = error;
    }

    return hidden_error;
}