#include <vector>

class matrix
{
    public:
        int get_size_x() {
            return size_x;
        }
        int get_size_y() {
            return size_y;
        }
        std::vector<std::vector<int>> get_data() {
            return data;
        }


    private:
        int size_x, size_y;
        std::vector<std::vector<int>> data;
};