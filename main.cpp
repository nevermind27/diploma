#include <opencv2/opencv.hpp>
#include <iostream>

void splitImageIntoTiles(const cv::Mat& image, int tileWidth, int tileHeight) {
    int rows = image.rows / tileHeight;
    int cols = image.cols / tileWidth;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Определяем регион интереса (ROI)
            cv::Rect roi(j * tileWidth, i * tileHeight, tileWidth, tileHeight);
            cv::Mat tile = image(roi);

            // Сохраняем тайл
            std::string filename = "tile_" + std::to_string(i) + "_" + std::to_string(j) + ".png";
            cv::imwrite(filename, tile);

            std::cout << "Saved: " << filename << std::endl;
        }
    }
}

int main() {
    std::string imagePath = "/Users/elizavetaomelcenko/Downloads/S2B_MSIL1C_20230519T075609_N0509_R035_T38UMU_20230519T085529.SAFE/GRANULE/L1C_T38UMU_A032379_20230519T080227/IMG_DATA/T38UMU_20230519T075609_B10.jp2"; // Укажите путь к изображению
    cv::Mat image = cv::imread(imagePath);

    if (image.empty()) {
        std::cerr << "Ошибка: не удалось загрузить изображение!" << std::endl;
        return -1;
    }
    else {
        std::cerr << "загружено" << std::endl;
    }

    int tileWidth = 100;  // Ширина тайла
    int tileHeight = 100; // Высота тайла

    splitImageIntoTiles(image, tileWidth, tileHeight);

    return 0;
}