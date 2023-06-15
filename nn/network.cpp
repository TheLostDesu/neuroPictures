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

class NN 
{
    public:
        NN(int numberOfLayersC_, int numberOfLayersP_, std::vector<int> p_sizes, int first_in) 
        {
            number_of_layers_prc = numberOfLayersP_;
            prc.resize(number_of_layers_prc);
            for(int i = 0; i < number_of_layers_prc; ++i) 
            {
                if(i != 0) 
                {
                    prc[i].set(p_sizes[i - 1], p_sizes[i]);
                }
                else
                {
                    prc[i].set(first_in, p_sizes[i]);
                }
            }
        }
        
        int recognize(matrix rgb) 
        {
            matrix now = rgb;
            for(int i = 0; i < prc.size(); ++i) 
            {
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


        void learn(matrix rgb, int ans, float learning_rate) {
            matrix target_output({});
            target_output.set_size(1, 10);
            target_output.set(0, ans, 1);

            matrix in = rgb;
            for(int i = 0; i < prc.size(); ++i) {
                in = prc[i].predict(in);
            }
            matrix err = calculate_error(in, target_output);

            for (size_t i = 0; i < prc.size(); ++i)
            {
                prc[i].update_weights(err, 0.1);
                err = prc[i].calculate_hidden_error(err, prc[i].get_weights());
            }
        }

        
    private:
        int number_of_layers_prc;
        int learning_rate;
        std::vector<perceptronLayer> prc;
};


void save_NN() {
    
}