#include <vector>
#include "perceptron.cpp"
#include "utility.cpp"


/**Находит ошибку между значениями векторов.
* @param output_res Выходное значение нейронной сети.
* @param result Ожидаемое(истинное) значение.
* @return Ошибка.
*/
matrix calculate_error(matrix output_res, matrix result)
{
    matrix err({});
    err.set_size(0, output_res.get_size_y());
    for (int i = 0; i < result.get_size_x(); ++i)
    {
        err.set(0, i, (result.get(0, i) - output_res.get(0, i)) * (result.get(0, i) - output_res.get(0, i)));
    }
    return err;
}

class CNN 
{
    public:
        CNN(int numberOfLayersC_, int numberOfLayersP_, std::vector<int> p_sizes) {
            number_of_layers_prc = numberOfLayersP_;
            prc.resize(number_of_layers_prc);
            for(int i = 0; i < number_of_layers_prc; ++i) {
                prc[i].set_size(p_sizes[i]);
            }
        }
        
        int recognize(matrix rgb) {
            matrix now = rgb;
            for(int i = 0; i < prc.size(); ++i) {
                now = prc[i].predict(now);
            }
            int ans = 0;
            for(int i = 0; i < 10; ++i) 
            {
                if(now.get(0, i) > now.get(0, ans)) 
                {
                    ans = i;
                }
            }
            return ans;
        }


        void learn(std::vector<matrix> rgb, int ans, float learning_rate) {
            std::vector<float> target_output(10, 0);
            target_output[ans] = 1;

            std::vector <matrix> ins_perc;
            ins_perc.push_back(conv_to_perc(ins_conv[conv.size()]));
            for(int i = 0; i < prc.size(); ++i) {
                ins_perc.push_back(prc[i].predict(ins_perc[i]));
            }
            std::vector<float> out(10);
            for(int i = 0; i < 10; ++i) {
                out[i] = ins_perc[i].get(0, i);
            }

            std::vector<float> error = calculate_error(out, target_output);
            
            for (size_t i = 0; i < prc.size(); ++i)
            {
                std::vector<double> output = ins_perc[i + 1];
                error = prc[i].calculate_hidden_error(error);

            }

            for (size_t i = 0; i < conv.size(); ++i)
            {
                std::vector<double> output = ins_conv[i + 1];
                std::vector<double> hidden_error = conv[i].calculate_hidden_error(error);
            }
        }

        
    private:
        int number_of_layers_prc;
        int learning_rate;
        std::vector<perceptronLayer> prc;
};