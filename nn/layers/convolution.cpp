#include <vector>
#include "../utility.cpp"

class convolutionLayer {
public:
    std::vector <matrix> convolve(std::vector <matrix> layerIn) {
        std::vector <matrix> layerOut(layerIn.size() * convolutionMatrixes.size());
        int size_x = layerIn[0].get_size_x(), size_y = layerIn[0].get_size_y();
        for (int i = 0; i < layerIn.size(); ++i) {
            for (int j = 0; j < convolutionMatrixes.size(); ++j) {
                layerOut[i * layerIn.size() + j].set_size(
                        size_x - convolutionMatrixes[j].get_size_x() + 1,
                        size_y - convolutionMatrixes[j].get_size_y() + 1);
            }
        }

    }


private:

    std::vector <matrix> convolutionMatrixes;


    void update_weights(std::vector<matrix>& convolutionMatrixes, std::vector<matrix>& gradient, std::vector<float>& error, std::vector<float>& activations){

    std::vector<float> hidden_errors(convolutionMatrixes[0].size(),0.0);

    for (size_t i = 0;i<convolutionMatrixes[0].size();++i) {
        for (size_t j = 0; j < error.size(); ++j) {
            for (size_t k = 0; k < gradient.size(); ++k) {
                hidden_errors[i] += convolutionMatrixes[j][i] * error[j] * gradient[k][j];
            }
        }
    }


    for (size_t i = 0;i<hidden_errors.size();++i) {
        hidden_errors[i] *= activations[i];
    }
}


        /**Подсчитывает ошибки для нейронов на скрытом слое.
         * @param delta Ошибка на следующем слое.
         * @param link_weights Веса связи между слоями.
         * @return Вычисленные ошибки для каждого нейрона на скрытом слое.
         */
        std::vector<double> calculate_hidden_error(std::vector<double>& error, std::vector<double>> & link_weights) {
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

