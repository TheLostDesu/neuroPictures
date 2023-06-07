#include <vector>
#include "utility.cpp"

class convolutionLayer
{   
    public:
        std::vector<matrix> convolve(std::vector<matrix> layerIn) {
            std::vector<matrix> layerOut;

            
        }
    private:
        std::vector<matrix> convolutionMatrixes;
};

double calculate_error(double output_result, double result){
    return (result-output_result)*(result-output_result)
}

void update_weights(vector<double>& link_weights, vector<double>& delta, double learning_rate, vector<double>& activations){
    for (size_t i = 0; i < link_weights.size(); ++i){
        for (size_t j = 0; j < link_weights[0].size(); ++j){
            weight[i][j] += learning_rate * delta[i] * activations[i];
        }
    }
}

vector<double> calculate_hidden_error(vector<double>& delta, vector<double>>& link_weights) {
    vector<double> hidden_error(link_weights[0].size(), 0.0);

    for (int i = 0; i < link_weights[0].size(); ++i) {
        double error = 0.0;
        for (int j = 0; j < link_weights.size(); ++j) {
            sum += delta[j] * link_weights[j][i];
        }
        hidden_error[i] = error;
    }

    return hidden_error;
}