//
//  Buffer.cpp
//  zip
//
//  Created by chunquedong on 15/6/26.
//  Copyright (c) 2015年 chunquedong. All rights reserved.
//

#include "Buffer.h"
#include <iostream>
#include <stdlib.h>

CF_USING_NAMESPACE

Buffer::Buffer() :
    data(nullptr), _size(0), _pos(0), owner(false) {
}

Buffer::Buffer(size_t size) : _size(size), _pos(0), owner(false) {
  data = (uint8_t*)cf_malloc(size);
}

Buffer::Buffer(uint8_t* data, size_t size, bool owner) :
    data(data), _size(size), _pos(0), owner(owner) {
}

Buffer::~Buffer() {
  if (owner) {
    cf_free(data);
  }
}

ssize_t Buffer::write(const char *buf, size_t size) {
  if (size > remaining()) {
    size = remaining();
  }
  memcpy(data + _pos, buf, size);
  return size;
}

ssize_t Buffer::read(char *buf, size_t size) {
  if (size > remaining()) {
    size = remaining();
  }
  memcpy(buf, data + _pos, size);
  return size;
}

unsigned char * Buffer::readDirect(int len) {
  unsigned char *p = data+_pos;
  if (_pos <= _size - len) {
    _pos += len;
    return p;
  }
  else {
    _pos = _size;
    return p;
  }
}

void Buffer::readSlice(Buffer &out, bool copy) {
    out._pos = 0;
    size_t size = readUInt16();
    out._size = size;
    if (_pos + size >= _size) {
        return;
    }
    uint8_t *data = readDirect((int)size);
    if (copy) {
        out.data = (uint8_t*)malloc(size);
        memcpy(out.data, data, size);
        out.owner = true;
    } else {
        out.data = data;
        out.owner = false;
    }
}

void Buffer::seek(int pos) {
    if (pos <= _size) {
        this->_pos = pos;
    }
}


