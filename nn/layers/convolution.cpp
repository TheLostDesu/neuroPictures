#include <vector>
#include "utility.cpp"

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
};