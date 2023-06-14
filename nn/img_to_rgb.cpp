#include <opencv2/opencv.hpp>
#include "utility.cpp"

/**Разбивает изображение на три матрицы R, G, B и возвращает их в виде вектора.
         * @param imagePath Путь к изображению.
         */
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
