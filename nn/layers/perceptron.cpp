#include "../utility.cpp"
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

        std::vector<float> calculate_hidden_error(std::vector<float>& error,
                                                  std::vector<float>& gradients, matrix& next_layer_weights)
        {
            int input_size = weights.get_size_x();
            int output_size = gradients.size();
            std::vector<float> hidden_error(input_size);
            for (int i = 0; i < input_size; ++i) 
            {
                float error = 0.0;
                for (int j = 0; j < output_size; ++j) 
                {
                    error += gradients[j] * next_layer_weights.get(i, j);
                }
                hidden_error[i] = error;
            }

            return hidden_error;
        }
        void update_weights(std::vector<float>& error, std::vector<float>& gradients, float learning_rate)
        {
            int error_size = error.size();
            int gradients_size = gradients.size();

            for (int i = 0; i < error_size; ++i)
            {
                for (int j = 0; j < gradients_size; ++j)
                {
                    weights.add(i, j, learning_rate * error[i] * gradients[i]);
                }
            }
        }
    private:
        matrix weights;
};
