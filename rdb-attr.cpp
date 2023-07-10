#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include "rdb.h"
using namespace std;


//methods and operatirs for IntAttr
int IntAttr::getVal() const {
    return val;
}
void IntAttr::setVal(int v) {
    val = v;
}

Attr * IntAttr::clone() const {
    return new IntAttr(val);
}

string IntAttr::toString() const {
    return to_string(val);
}

bool IntAttr::operator== (const Attr & right) {
    return val == ((IntAttr &)right).getVal();
}

bool IntAttr::operator!= (const Attr & right) {
    return val != ((IntAttr &)right).getVal();
}

bool IntAttr::operator< (const Attr & right) {
    return val < ((IntAttr &)right).getVal();
}

bool IntAttr::operator> (const Attr & right) {
    return val > ((IntAttr &)right).getVal();
}

bool IntAttr::operator<= (const Attr & right) {
    return val <= ((IntAttr &)right).getVal();
}

bool IntAttr::operator>= (const Attr & right) {
    return val >= ((IntAttr &)right).getVal();
}


//methods and operators for floatAttr
float floatAttr::getVal() const {
    return val;
}

void floatAttr::setVal(float v) {
    val = v;
}

Attr * floatAttr::clone() const {
    return new floatAttr(val);
}

string floatAttr::toString() const {
    return to_string(val);
}

bool floatAttr::operator== (const Attr & right) {
    return val == ((floatAttr &)right).getVal();
}

bool floatAttr::operator!= (const Attr & right) {
    return val != ((floatAttr &)right).getVal();
}

bool floatAttr::operator< (const Attr & right) {
    return val < ((floatAttr &)right).getVal();
}

bool floatAttr::operator> (const Attr & right) {
    return val > ((floatAttr &)right).getVal();
}

bool floatAttr::operator<= (const Attr & right) {
    return val <= ((floatAttr &)right).getVal();
}

bool floatAttr::operator>= (const Attr & right) {
    return val >= ((floatAttr &)right).getVal();
}


//methods and operators for stringAttr
string stringAttr::getVal() const {
    return val;
}

void stringAttr::setVal(string v) {
    val = v;
}

Attr * stringAttr::clone() const {
    return new stringAttr(val);
}

string stringAttr::toString() const {
    return val;
}

bool stringAttr::operator== (const Attr & right) {
    return val == ((stringAttr &)right).getVal();
}

bool stringAttr::operator!= (const Attr & right) {
    return val != ((stringAttr &)right).getVal();
}

bool stringAttr::operator< (const Attr & right) {
    return val < ((stringAttr &)right).getVal();
}

bool stringAttr::operator> (const Attr & right) {
    return val > ((stringAttr &)right).getVal();
}

bool stringAttr::operator<= (const Attr & right) {
    return val <= ((stringAttr &)right).getVal();
}

bool stringAttr::operator>= (const Attr & right) {
    return val >= ((stringAttr &)right).getVal();
}
