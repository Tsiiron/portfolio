#include "FileLogger.h"

FileLogger :: FileLogger(const std::string& file_name) {
    out_.open(file_name);
    if(!out_.is_open()) {
        throw std::invalid_argument("Не удалось открыть файл: " + file_name);
    } else {
        out_ << "Игра начата!\n";
        out_.flush();
    }
}

void FileLogger :: set_log(MessageInterface* new_log) {
    out_ << *new_log;
    out_.flush();
}

FileLogger :: ~FileLogger() {
    if(out_.is_open()) {
        out_.close();
    }
}