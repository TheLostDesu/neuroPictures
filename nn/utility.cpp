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
            for (int i = 0; i < size_x; ++i){
                for (int j = 0; j < size_y; ++j){
                    if (data[i][j] < 0){
                        data[i][j] = 0;
                    }
                }
            }
        }



    private:
        int size_x, size_y;
        std::vector<std::vector<float>> data;
};

std::vector<int> calculate_gradient(std::vector<int> values){
    std::vector<int> gradients(values.size());
    for (int i = 0; i < values.size(); ++i){
        if(values[i] > 0) 
        {
            gradients[i] = 1;
        }
        else 
        {
            gradients[i] = 0;
        }
    }
    return gradients;
}

int max(int a, int b, int c, int d) 
{
    return std::max(std::max(a, b), std::max(c, d)); 
}


matrix conv_to_perc(std::vector<matrix> conv_out) {
    std::vector<std::vector<float>> ans(0);

    for(int i = 0; i < conv_out.size(); ++i) {
        for(int j = 0; j < conv_out[i].get_size_x(); ++j) {
            for(int k = 0; k < conv_out[i].get_size_y(); ++k) {
                ans[0].push_back(conv_out[i].get(j, k));
            }
        }
    }
    return matrix(ans);
}

std::vector<matrix> getrgbmatrix(const std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath);
    int height = image.rows;
    int width = image.cols;
    std::vector<matrix> rgbMatrix(3);
    rgbMatrix[0].set_size(height, width);
    rgbMatrix[1].set_size(height, width);
    rgbMatrix[2].set_size(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            rgbMatrix[0].set(i, j, pixel[0]); 
            rgbMatrix[1].set(i, j, pixel[1]); 
            rgbMatrix[2].set(i, j, pixel[2]); 
        }
    }

    return rgbMatrix;
}
