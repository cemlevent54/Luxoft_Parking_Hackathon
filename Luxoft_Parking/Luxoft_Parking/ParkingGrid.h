#pragma once
#include <vector>
using namespace std;

class ParkingGrid {
private:
    vector<vector<int>> alan; 
    int satir, sutun;        

public:
    static const int BOS = 0;   
    static const int DOLU = 1;  
    static const int ENGEL = 2; 

    ParkingGrid(int s, int t) : satir(s), sutun(t) {
        alan.resize(satir, vector<int>(sutun, BOS)); 
    }

    int getSatir() const { return satir; }
    int getSutun() const { return sutun; }
    int getDeger(int x, int y) const { return alan[x][y]; }
    void setDeger(int x, int y, int deger) { alan[x][y] = deger; }

    bool doluMu(int x, int y) const { return alan[x][y] == DOLU || alan[x][y] == ENGEL; }
    bool gecerliKoordinatMi(int x, int y) const { return x >= 0 && x < satir && y >= 0 && y < sutun; }
};
