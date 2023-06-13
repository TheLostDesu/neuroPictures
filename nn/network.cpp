#include <vector>
#include "nn/layers/convolution.cpp"
#include "nn/layers/perceptron.cpp"
#include "nn/layers/pooling.cpp"

class CNN 
{
    public:
        CNN(int numberOfLayersC_, int numberOfLayersP_, std::vector<std::pair<int, int>> convolution_params, std::vector<int> pooling_params) {
            numberOfLayersC = numberOfLayersC_;
            numberOfLayersP = numberOfLayersP_;
            prc.resize(numberOfLayersP);
            conv.resize(numberOfLayersC);
            pool.resize(numberOfLayersC);

        }
        
        int recognize() {
            
        }
        void learn() {
            std::vector<double> error = calculate_error(output, target_output);
            error = hidden_error;
            double learning_rate = float m;
            update_weight(error, gradients, learning_rate)

            for (size_t i = 0; i < perceptron_layers.size(); ++i)
            {
                Perceptron& layer = perceptron_layers[i];

                std::vector<double> output = layer.predict(matrix layer_in);

                std::vector<double> hidden_error = layer.calculate_hidden_error(error);

            }


            for (size_t i = 0; i < convolution_layers.size(); ++i)
            {
                Convolution& layer = convolution_layers[i];

                std::vector<double> output = layer.convolve(layerIn);

                std::vector<double> hidden_error = layer.calculate_hidden_error(error);

            }


    matrix weights;
};
        }

        
    private:
        std::vector<double> calculate_error(std::vector<double>& output_res, std::vector<double>& result)
        {
            int result_size = result.size();
            std::vector<double> error(result_size);

            for (int i = 0; i < result_size; ++i)
            {
                error[i] = result[i] - output_res[i];
            }
            return error;
        }

        int numberOfLayersC, numberOfLayersP;
        std::vector<perceptronLayer> prc;
        std::vector<convolutionLayer> conv;
        std::vector<poolingLayer> pool;
};