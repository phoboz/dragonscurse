#ifndef _StoreRestore_H
#define _StoreRestore_H

#include <fstream>
#include <string.h>

class StoreRestore {
public:
    static void write_boolean(std::ofstream &f, bool value) {
        f.write((char *) &value, sizeof(value));
    }

    static void write_integer(std::ofstream &f, int value) {
        f.write((char *) &value, sizeof(value));
    }

    static void write_varchar(std::ofstream &f, const char *s) {
        int len = strlen(s);
        f.write((char *) &len, sizeof(len));
        f.write(s, len);
    }

    static bool read_boolean(std::ifstream &f) {
        bool value;
        f.read((char *) &value, sizeof(value));

        return value;
    }

    static int read_integer(std::ifstream &f) {
        int value;
        f.read((char *) &value, sizeof(value));

        return value;
    }

    static char* read_varchar(std::ifstream &f) {
        int len = 0;
        f.read((char *) &len, sizeof(len));

        char *s = new char[len + 1];
        f.read(s, len);
        s[len] = '\0';

        return s;
    }

};

#endif

