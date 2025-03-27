#include <fstream>
#include <string>
#include <sys/mman.h>
#include <fcntl.h>      // Для open()
#include <unistd.h>     // Для close(), read(), write()
#include <sys/types.h>  // Для типов данных
#include <sys/stat.h>
#include <iostream>

#define SEGMENT_SIZE 100000

 class image{
    std::string path;
    uint64_t offset;
 };


// либо через openCV
// структура папки одинаковая всегда, там разные спектры


// разбивку на блоки делать в зависимости от мода  - метео - один спектр в один блок 
// гидро - одинаковые участки в разных спектрах в один блок


// мб и не надо блоки, просто тайлы как объекты хранить
int split_equal_segments(std::string path, int segments){
    int src_file = open(path.c_str(), O_RDONLY);
    std::vector<char> buffer(SEGMENT_SIZE);
    //это сам сегмент хранилища, туда скопируем часть файла
    int dest_file = open("storage.dat", O_RDWR | O_CREAT, SEGMENT_SIZE); // название памяти автогенерировать

    if (ftruncate(dest_file, SEGMENT_SIZE) == -1) {
        std::cerr << "Ошибка ftruncate: " << strerror(errno) << std::endl;
        close(dest_file);
        return 1;
    }
    void *mapped = mmap(NULL, SEGMENT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, dest_file, 0); //смещение разное должно быть
    ssize_t bytes_read = read(src_file, buffer.data(), SEGMENT_SIZE);
    if (bytes_read < 0) {
        std::cout << "Ошибка чтения файла: " << strerror(errno) << std::endl;
        close(src_file);
        return 1;
    }
    // здесь хочу из буфера скопировать в dest_file
    if (mapped == MAP_FAILED) {
        std::cout << "Ошибка mmap: " << strerror(errno) << std::endl;
        close(src_file);
        close(dest_file);
        return 1;
    }

    // Копируем данные из буфера в отображенную область памяти
    memcpy(mapped, buffer.data(), bytes_read);
    return 0;
}

int main() {
    std::string filename = "/Users/elizavetaomelcenko/Downloads/S2B_MSIL1C_20230519T075609_N0509_R035_T38UMU_20230519T085529.SAFE/GRANULE/L1C_T38UMU_A032379_20230519T080227/IMG_DATA/T38UMU_20230519T075609_B10.jp2";  // Задаем путь к файлу
    split_equal_segments(filename, 10);
    return 0;
}