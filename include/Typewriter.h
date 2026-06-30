#ifndef TYPEWRITER_H
#define TYPEWRITER_H

#include <iostream>
#include <streambuf>
#include <windows.h>

class TypewriterBuf : public std::streambuf {
    std::streambuf* oldBuf;
    int sync() override {
        return oldBuf->pubsync();
    }
    int overflow(int c) override {
        if (c != EOF) {
            oldBuf->sputc(c);
            oldBuf->pubsync();
            if (c == '\n')
                Sleep(30);
            else
                Sleep(15);
        }
        return c;
    }
public:
    TypewriterBuf() : oldBuf(std::cout.rdbuf()) {
        std::cout.rdbuf(this);
    }
    ~TypewriterBuf() {
        std::cout.rdbuf(oldBuf);
    }
};

#endif
