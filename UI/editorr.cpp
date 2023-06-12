//
// Created by Иван Грибанов on 11.06.2023.
//

#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>
#include <sys/stat.h>

// Функция загрузки файла изображения
std::string loadImage(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Получаем размер файла
        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // Создаем буфер для хранения данных файла
        std::string imageData;
        imageData.resize(fileSize);

        // Читаем данные файла в буфер
        file.read(&imageData[0], fileSize);

        // Закрываем файл
        file.close();

        return imageData;
    } else {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

// Функция сохранения файла изображения
void saveImage(const std::string& filename, const std::string& imageData) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Сохраняем данные изображения в файл
        file.write(imageData.data(), imageData.size());

        // Закрываем файл
        file.close();
    } else {
        throw std::runtime_error("Failed to save file: " + filename);
    }
}

// Функция для конфигурации размера окна
void configureWindow(int width, int height, const std::string& windowName, int flags = cv::WINDOW_NORMAL) {
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
    cv::rectangle(image, cv::Rect(0, 0, width, height), cv::Scalar(255, 255, 255), cv::FILLED);

    cv::namedWindow(windowName, flags);
    cv::imshow(windowName, image);
    cv::waitKey(0);
    cv::destroyWindow(windowName);
}

// Функция отрисовки окна (пример)
void drawWindow(int width, int height) {
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
    cv::putText(image, "Drawing window", cv::Point(10, height / 2),
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);

    cv::namedWindow("Window", cv::WINDOW_NORMAL);
    cv::imshow("Window", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

// Функция для вывода сообщения
void displayMessage(const std::string& message) {
    cv::Mat image = cv::Mat::zeros(200, 600, CV_8UC3);
    cv::putText(image, message, cv::Point(10, 100),
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);

    cv::namedWindow("Message", cv::WINDOW_NORMAL);
    cv::imshow("Message", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

// Функция для загрузки окна
void loadWindow(const std::string& windowName) {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

// Функция для выгрузки окна
void unloadWindow(const std::string& windowName) {
    cv::destroyWindow(windowName);
}

// Функция для конфигурации окна с использованием имени окна
void configureWindowByName(const std::string& windowName, int width, int height, int flags = cv::WINDOW_NORMAL) {
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
    cv::rectangle(image, cv::Rect(0, 0, width, height), cv::Scalar(255, 255, 255), cv::FILLED);

    cv::namedWindow(windowName, flags);
    cv::imshow(windowName, image);
    cv::waitKey(0);
    cv::destroyWindow(windowName);
}

// Функция для проверки, является ли файл изображением
bool isImageFile(const std::string& filename) {
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    return (extension == "jpg" || extension == "jpeg" || extension == "png" || extension == "bmp");
}

int main() {
    // Установка рабочей директории в директорию исполняемого файла
    char executablePath[PATH_MAX];
    if (readlink("/proc/self/exe", executablePath, sizeof(executablePath)) != -1) {
        std::string executableDir = std::string(dirname(executablePath));
        chdir(executableDir.c_str());
    }

    std::string folderPath = "/path/to/folder";  // Замените на путь к папке с изображениями
    std::string outputFolderPath = "/path/to/output";  // Замените на путь к папке для сохранения изображений

    DIR* dir;
    struct dirent* entry;
    struct stat fileStat;

    dir = opendir(folderPath.c_str());
    if (dir) {
        while ((entry = readdir(dir)) != nullptr) {
            std::string filename = entry->d_name;
            std::string filePath = folderPath + "/" + filename;

            if (stat(filePath.c_str(), &fileStat) == -1)
                continue;

            if (!S_ISREG(fileStat.st_mode))
                continue;

            if (!isImageFile(filename))
                continue;

            std::string imageData;
            try {
                imageData = loadImage(filePath);
                // Продолжение работы с данными изображения
            } catch (const std::exception& e) {
                // Обработка ошибки загрузки файла
                std::string errorMessage = "Error: " + std::string(e.what());
                displayMessage(errorMessage);
                continue;
            }

            std::string outputFilename = outputFolderPath + "/" + filename;
            try {
                saveImage(outputFilename, imageData);
                // Продолжение работы с сохраненным файлом
            } catch (const std::exception& e) {
                // Обработка ошибки сохранения файла
                std::string errorMessage = "Error: " + std::string(e.what());
                displayMessage(errorMessage);
                continue;
            }

            int windowWidth = 800;
            int windowHeight = 600;
            std::string windowName = "Window";
            try {
                configureWindow(windowWidth, windowHeight, windowName);
                // Продолжение работы с настроенным окном

                loadWindow(windowName);  // Добавлен вызов функции для загрузки окна

                unloadWindow(windowName);  // Добавлен вызов функции для выгрузки окна

                configureWindowByName(windowName, windowWidth, windowHeight);  // Добавлен вызов функции для конфигурации окна по имени
            } catch (const std::exception& e) {
                // Обработка ошибки конфигурации окна
                std::string errorMessage = "Error: " + std::string(e.what());
                displayMessage(errorMessage);
                continue;
            }
        }
        closedir(dir);
    } else {
        std::string errorMessage = "Failed to open folder: " + folderPath;
        displayMessage(errorMessage);
        return 1;
    }

    return 0;
}