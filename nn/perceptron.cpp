#include "utility.cpp"
#include <vector>
#include <random>

float activation_funct(float x) 
{
    return x * (1 - x);
}

float calculate_gradient(float x) 
{
    return (1.0 / (1.0 + exp(-x)));
}

class perceptronLayer 
{
    public:
        void set(int in_, int out_) 
        {
            in = in_;
            out = out_;
            weights.set_size(in, out);
            for(int i = 0; i < in; ++i) {
                for(int j = 0; j < out; ++j) {
                    weights.set(i, j, (float(rand())/RAND_MAX));
                }
            }
        }
        
        matrix predict(matrix data) 
        {
            matrix ans = data * weights;
            for(int i = 0; i < in; ++i) {
                for(int j = 0; j < out; ++j) {
                    ans.set(i, j, activation_funct(ans.get(i, j)));
                }
            }
            return ans;
        }

        matrix calculate_hidden_error(matrix error, matrix pweights)
        {
            std::vector<float> hidden_error(in);
            for (int i = 0; i < in; ++i) 
            {
                float error = 0.0;
                for (int j = 0; j < out; ++j) 
                {
                    error += gradients[j] * pweights.get(i, j);
                }
                hidden_error[i] = error;
            }

            return hidden_error;
        }
        
        
        void update_weights(matrix error, float learning_rate)
        {
            for (int i = 0; i < in; ++i)
            {
                for (int j = 0; j < out; ++j)
                {
                    weights.add(i, j, learning_rate * error.get(0, i) * gradients[i]);
                }
            }
        }

    private:
        int in;
        int out;
        matrix weights;
};
