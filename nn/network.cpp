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