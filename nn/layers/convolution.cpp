#include <vector>
#include "../utility.cpp"

class convolutionLayer
{   
    public:
        std::vector<matrix> convolve(std::vector<matrix> layerIn) {
            std::vector<matrix> layerOut(layerIn.size() * convolutionMatrixes.size());
            int size_x = layerIn[0].get_size_x(), size_y = layerIn[0].get_size_y();
            for(int i = 0; i < layerIn.size(); ++i) {
                for(int j = 0; j < convolutionMatrixes.size(); ++j) {
                    layerOut[i * layerIn.size() + j].set_size(
                                           size_x - convolutionMatrixes[j].get_size_x() + 1,
                                           size_y - convolutionMatrixes[j].get_size_y() + 1);
                }
            }
            
        }


    private:
    
        std::vector<matrix> convolutionMatrixes;


        void update_weights(std::vector<double>& link_weights, std::vector<double>& error, double learning_rate, std::vector<double>& activations)
        {
            int link_weights_size = link_weights.size();
            int gradients_size = gradients.size();

            for (int i = 0; i < link_weights_size; ++i)
            {
                for (int j = 0; j < gradients_size; ++j)
                {
                    weights.add(i, j, learning_rate * delta[i] * activations[i]);
                }
            }
        }

        /**Подсчитывает ошибки для нейронов на скрытом слое.
         * @param delta Ошибка на следующем слое.
         * @param link_weights Веса связи между слоями.
         * @return Вычисленные ошибки для каждого нейрона на скрытом слое.
         */
        std::vector<double> calculate_hidden_error(std::vector<double>& delta, std::vector<double>> & link_weights) {
            std::vector<double> hidden_error(link_weights[0].size(), 0.0);

            for (int i = 0; i < link_weights[0].size(); ++i) {
                double error = 0.0;
                for (int j = 0; j < link_weights.size(); ++j) {
                    error += delta[j] * link_weights[j][i];
                }
                hidden_error[i] = error;
            }

            return hidden_error;
        }
};

         /**Находит ошибку между значениями векторов.
         * @param output_res Выходное значение нейронной сети.
         * @param result Ожидаемое(истинное) значение.
         * @return Ошибка.
         */
double calculate_error(double output_result, double result){
    return (result-output_result)*(result-output_result);
}

