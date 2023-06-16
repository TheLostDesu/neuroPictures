#include "utility.cpp"
#include <vector>
#include <random>
#pragma once

float calculate_grad(float x) 
{
    return x * (1 - x);
}

float activation_funct(float x) 
{
    return (1.0 / (1.0 + exp(-x)));
}

class perceptronLayer 
{
    public:    
        perceptronLayer() 
        {
            weights = matrix(std::vector<std::vector<float>>(0));

            ans = matrix(std::vector<std::vector<float>>(0));
            in = 0;
            out = 0;
        }
        void set(int in_, int out_) 
        {
            in = in_;
            out = out_;
            weights.set_size(in, out);
            for(int i = 0; i < in; ++i) {
                for(int j = 0; j < out; ++j) {
                    weights.set(i, j, (float(rand())/RAND_MAX - 0.5)* pow(out,-0.5));
                }
            }
        }

        void set_values(matrix values) 
        {
            in = values.get_size_x();
            out = values.get_size_y();
            weights = values;
        }
        
        matrix predict(matrix data) 
        {
            ans = data * weights;
            for(int j = 0; j < out; ++j) {
                if(activation_funct(ans.get(0, j)) != activation_funct(ans.get(0, j))) {
                    std::cout << ans.get(0, j) << "WARNING";
                    system("pause");
                }
                ans.set(0, j, activation_funct(ans.get(0, j)));
            }
            return ans;
        }

        matrix calculate_hidden_error(matrix error, matrix pweights)
        {
            matrix hidden_error;
            hidden_error.set_size(1, in);
            for (int i = 0; i < in; ++i) 
            {   
                float err = 0.0;
                for (int j = 0; j < out; ++j) 
                {
                    err += error.get(0, j) * pweights.get(i, j) * calculate_grad(ans.get(0, j));
                    if(err != err) 
                    {
                        std::cout << error.get(0, j) << ' ' << pweights.get(i, j) << ' ' << ans.get(0, j);
                        system("pause");
                    }
                }
                hidden_error.set(0, i, err);
            }

            return hidden_error;
        }
        
        
        void update_weights(matrix error, float learning_rate)
        {
            
            for (int i = 0; i < in; ++i)
            {
                for (int j = 0; j < out; ++j)
                {
                    weights.add(i, j, learning_rate * error.get(0, j) * calculate_grad(ans.get(0, j)));
                    if(weights.get(i, j) != weights.get(i, j)) {
                        std::cout << "NAN_WEIGHTS_WARNING";
                        std::cout << error.get(0, i) << ' ' << ans.get(0, j);
                        system("pause");
                    }
                }
            }
        }
        matrix get_weights() {
            return weights;
        }
        int get_size_x() 
        {
            return weights.get_size_x();
        }
        int get_size_y() 
        {
            return weights.get_size_y();
        }

    private:
        int in;
        int out;
        matrix weights;
        matrix ans;
};
