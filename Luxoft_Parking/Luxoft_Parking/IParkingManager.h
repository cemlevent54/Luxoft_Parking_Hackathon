#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <memory>
using namespace std;

class IParkingManager {
public:
    virtual bool parkYeriDoldur(int x, int y) = 0;
    virtual pair<pair<int, int>, int> enYakinBosParkYeri(int baslangicX, int baslangicY) = 0;
    virtual void parkAlaniniYazdir() const = 0;
    virtual void bosParkYerleriniListele() const = 0;
    virtual ~IParkingManager() = default;
};
