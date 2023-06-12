#include <vector>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>


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



void read_mnist_cv(const char* image_filename, const char* label_filename){
    std::ifstream image_file(image_filename, std::ios::in | std::ios::binary);
    std::ifstream label_file(label_filename, std::ios::in | std::ios::binary);
    uint32_t magic;
    uint32_t num_items;
    uint32_t num_labels;
    uint32_t rows;
    uint32_t cols;
    image_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);

    image_file.read(reinterpret_cast<char*>(&num_items), 4);
    num_items = swap_endian(num_items);
    label_file.read(reinterpret_cast<char*>(&num_labels), 4);
    num_labels = swap_endian(num_labels);

    image_file.read(reinterpret_cast<char*>(&rows), 4);
    rows = swap_endian(rows);
    image_file.read(reinterpret_cast<char*>(&cols), 4);
    cols = swap_endian(cols);

    char label;
    char* pixels = new char[rows * cols];

    for (int item_id = 0; item_id < num_items; ++item_id) {
        image_file.read(pixels, rows * cols);
        label_file.read(&label, 1);

        std::string sLabel = std::to_string(int(label));
        cv::Mat image_tmp(rows,cols,CV_8UC1,pixels);
        cv::resize(image_tmp, image_tmp, cv::Size(100, 100));
        cv::imshow(sLabel, image_tmp);
        cv::waitKey(0);
    }

    delete[] pixels;
}