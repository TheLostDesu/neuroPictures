#include <vector>
#include "layers/convolution.cpp"
#include "layers/perceptron.cpp"
#include "layers/pooling.cpp"
#include "utility.cpp"

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
        
        int recognize(std::vector<matrix> rgb) {
            std::vector<matrix> now = rgb;
            for(int i = 0; i < conv.size(); ++i) {
                now = pool[i].max_pool(conv[i].convolve(now));
            }
            matrix nw = conv_to_perc(now);
            for(int i = 0; i < prc.size(); ++i) {
                nw = prc[i].predict(nw);
            }
            int ans = 0;
            for(int i = 0; i < 10; ++i) 
            {
                if(nw.get(0, i) > nw.get(0, ans)) 
                {
                    ans = i;
                }
            }
            return ans;
        }

        void learn(std::vector<matrix> rgb, int ans, float learning_rate) {

            std::vector<float> target_output(10, 0);
            target_output[ans] = 1;

            std::vector <std::vector<matrix>> ins_conv;
            std::vector <matrix> ins_perc;
            ins_conv.push_back(rgb);

            for(int i = 0; i < conv.size(); ++i) {
                ins_conv.push_back(pool[i].max_pool(conv[i].convolve(ins_conv[i])));
            }
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

        /**Находит ошибку между значениями векторов.
         * @param output_res Выходное значение нейронной сети.
         * @param result Ожидаемое(истинное) значение.
         * @return Ошибка.
         */
        std::vector<float> calculate_error(std::vector<float>& output_res, std::vector<float>& result)

        {
            int result_size = result.size();
            std::vector<float> error(result_size);

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