#ifndef PAFE_PAFE_H
#define PAFE_PAFE_H

#include <nan.h>
#include <node.h>
#include <stdio.h>

extern "C"{
#include <libpafe/libpafe.h>
}

NAN_METHOD(readIDm);

#endif
