#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include "ParkingGrid.h"
#include "IParkingManager.h"
using namespace std;

class ParkingManager : public IParkingManager {
private:
    ParkingGrid& grid;  
    int doluYerSayisi;  

public:
    static const int BOS = 0;   // Bo� alan
    static const int DOLU = 1;  // Park edilmi� alan
    static const int ENGEL = 2; // Engel alan�
    // Constructor
    ParkingManager(ParkingGrid& grid);

    
    bool parkYeriDoldur(int x, int y) override;
    pair<pair<int, int>, int> enYakinBosParkYeri(int baslangicX, int baslangicY) override;
    void parkAlaniniYazdir() const override;
    void bosParkYerleriniListele() const override;

    bool engelKoy(int x, int y);

    pair<pair<int, int>, int> bfsEnYakinBosParkYeri(int baslangicX, int baslangicY);
};
