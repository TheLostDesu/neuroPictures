#include <vector>
#include <cmath>

class matrix
{
    public:
        int get_size_x() {
            return size_x;
        }
        int get_size_y() {
            return size_y;
        }
        std::vector<std::vector<float>> get_data() {
            return data;
        }
        float get(int x, int y) {
            return data[x][y];
        }
        void set(int x, int y, float val) {
            data[x][y] = val;
        }
        void set_size(int x, int y) {
            data.resize(x, std::vector<float>(y));
        }
        
        float * convert() {
            float * ans = new float[size_x * size_y];
            for(int i = 0; i < size_x;++i) {
                for(int j = 0; j < size_y;++i) {
                    ans[i * size_x + j] = data[i][j];
                }
            }
            return ans;
        }


    private:
        int size_x, size_y;
        std::vector<std::vector<float>> data;
};


int max(int a, int b, int c, int d) 
{
    return std::max(std::max(a, b), std::max(c, d)); 
}