#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

class matrix
{
    public:
        matrix(float *data_, int x, int y) {
            data.resize(x, std::vector<float>(y));
            size_x = x;
            size_y = y;
        }

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
        void add(int x, int y, float val) {
            data[x][y] += val;
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
//Для красного цвета
std::vector<int> red PixelsToVector(std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath);

    std::vector<int> pixelVector;

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            int redValue = pixel[2];
            pixelVector.push_back(redValue);
        }
    }

    return pixelVector;
}
//Для синего цвета
std::vector<int> bluePixelsToVector(std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath);

    std::vector<int> pixelVector;


    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            int blueValue = pixel[2]; // Значение синего канала (BGR формат)
            pixelVector.push_back(blueValue);
        }
    }

    return pixelVector;
}
//Для зеленого цвета
std::vector<int> greenPixelsToVector(std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath);

    std::vector<int> pixelVector;


    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            int blueValue = pixel[1]; // Значение синего канала (BGR формат)
            pixelVector.push_back(blueValue);
        }
    }

    return pixelVector;
}