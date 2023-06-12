#include <vector>

class CNN 
{
    public:
        CNN(int numberOfLayersC_, int numberOfLayersP_) {
            numberOfLayersC = numberOfLayersC_;
            numberOfLayersP = numberOfLayersP_;
        }
        ~CNN() {
            a.~vector();
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
        std::vector<int> a;
};