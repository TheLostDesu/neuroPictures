#include <vector>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "GPU_stuff/matrix_mul.cpp"
#include "GPU_stuff/detect_device.cpp"


class matrix
{
    public:
        matrix(std::vector<std::vector<float>> data_) {
            data = data_;
            size_x = data.size();
            size_y = data[0].size();
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
        matrix operator *(matrix& other) const {
            if(is_cuda()) {
                return matrix(multiplyMatrices(data, other.get_data()));
            }
            else {
                std::vector<std::vector<float>> ans; 
                for(int i = 0; i < size_x; ++i) {
                    for(int j = 0; j < size_y; ++j) {
                        for(int k = 0; k < size_y; ++k) {
                            ans[i][k] += data[i][j] * other.get(j, k);
                        }
                    }
                }
            }
        }
        void relu(){
            for (i = 0; i < size_x(); ++i){
                for (j = 0; j < size_y(); ++j){
                    if (data[i][j] < 0){
                        data[i][j] = 0;
                    }
                }
            }
        }

        void calculate_gradient(){

        }

    private:
        int size_x, size_y;
        std::vector<std::vector<float>> data;
};


int max(int a, int b, int c, int d) 
{
    return std::max(std::max(a, b), std::max(c, d)); 
}


std::vector<std::vector<std::vector<int>>> getRGBMatrix(const std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath);
    int height = image.rows;
    int width = image.cols;
    std::vector<std::vector<std::vector<int>>> rgbMatrix(height, std::vector<std::vector<int>>(width, std::vector<int>(3)));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            rgbMatrix[i][j][0] = pixel[0]; 
            rgbMatrix[i][j][1] = pixel[1];  
            rgbMatrix[i][j][2] = pixel[2]; 
        }
    }

    return rgbMatrix;
}

