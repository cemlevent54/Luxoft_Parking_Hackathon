#include "ParkingManager.h"
#include <iostream>
#include <queue>
#include <limits>
using namespace std;

// Constructor
ParkingManager::ParkingManager(ParkingGrid& gridRef) : grid(gridRef), doluYerSayisi(0) {}

// Park yerini doldur
bool ParkingManager::parkYeriDoldur(int x, int y) {
    if (!grid.gecerliKoordinatMi(x, y)) {
        cout << "Hata: Ge�ersiz koordinat!" << endl;
        return false;
    }
    if (grid.doluMu(x, y)) {
        cout << "Hata: Park yeri dolu veya engelli!" << endl;
        return false;
    }
    grid.setDeger(x, y, ParkingGrid::DOLU);
    doluYerSayisi++;
    cout << "Park yeri (" << x << ", " << y << ") dolu olarak ayarlandi." << endl;
    return true;
}

// En yak�n bo� park yerini bul
pair<pair<int, int>, int> ParkingManager::enYakinBosParkYeri(int baslangicX, int baslangicY) {
    int minMesafe = numeric_limits<int>::max();
    pair<int, int> enYakinYer = { -1, -1 };

    for (int i = 0; i < grid.getSatir(); i++) {
        for (int j = 0; j < grid.getSutun(); j++) {
            if (grid.getDeger(i, j) == ParkingGrid::BOS) { // E�er h�cre bo�sa
                int mesafe = abs(baslangicX - i) + abs(baslangicY - j); // Manhattan mesafesi
                if (mesafe < minMesafe) {
                    minMesafe = mesafe;
                    enYakinYer = { i, j };
                }
            }
        }
    }

    return { enYakinYer, minMesafe };
}

// Park alan�n� yazd�r
void ParkingManager::parkAlaniniYazdir() const {
    cout << "======= PARK ALANI DURUMU =======" << endl;
    for (int i = 0; i < grid.getSatir(); i++) {
        for (int j = 0; j < grid.getSutun(); j++) {
            if (grid.getDeger(i, j) == ParkingGrid::BOS) {
                cout << ". ";
            }
            else if (grid.getDeger(i, j) == ParkingGrid::DOLU) {
                cout << "X ";
            }
            else if (grid.getDeger(i, j) == ParkingGrid::ENGEL) {
                cout << "E "; // Engel alan�
            }
        }
        cout << endl;
    }
    cout << "=================================" << endl;
}

// T�m bo� park yerlerini listele
void ParkingManager::bosParkYerleriniListele() const {
    cout << "Bo� Park Yerleri:" << endl;
    for (int i = 0; i < grid.getSatir(); i++) {
        for (int j = 0; j < grid.getSutun(); j++) {
            if (grid.getDeger(i, j) == ParkingGrid::BOS) {
                cout << "(" << i << ", " << j << ") ";
            }
        }
    }
    cout << endl;
}

// Engel koyma
bool ParkingManager::engelKoy(int x, int y) {
    if (!grid.gecerliKoordinatMi(x, y)) {
        cout << "Hata: Ge�ersiz koordinat!" << endl;
        return false;
    }
    if (grid.getDeger(x, y) != ParkingGrid::BOS) {
        cout << "Hata: Bu alana engel koyulamaz, zaten dolu!" << endl;
        return false;
    }
    grid.setDeger(x, y, ParkingGrid::ENGEL);
    cout << "Engel (" << x << ", " << y << ") noktas�na koyuldu." << endl;
    return true;
}

// BFS ile en yak�n bo� park yerini bul
pair<pair<int, int>, int> ParkingManager::bfsEnYakinBosParkYeri(int baslangicX, int baslangicY) {
    vector<vector<bool>> ziyaretEdildi(grid.getSatir(), vector<bool>(grid.getSutun(), false));
    queue<pair<pair<int, int>, int>> q; // S�ra: Koordinatlar ve mesafe

    q.push({ {baslangicX, baslangicY}, 0 });
    ziyaretEdildi[baslangicX][baslangicY] = true;

    vector<pair<int, int>> yonler = {
        {1, 0},  // A�a��
        {0, -1}, // Sol
        {-1, 0}, // Yukar�
        {0, 1}   // Sa�
    };

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        int x = current.first.first;
        int y = current.first.second;
        int mesafe = current.second;

        if (grid.getDeger(x, y) == ParkingGrid::BOS) {
            return { {x, y}, mesafe };
        }

        for (auto yon : yonler) {
            int yeniX = x + yon.first;
            int yeniY = y + yon.second;

            if (grid.gecerliKoordinatMi(yeniX, yeniY) && !ziyaretEdildi[yeniX][yeniY] && grid.getDeger(yeniX, yeniY) != ParkingGrid::ENGEL) {
                q.push({ {yeniX, yeniY}, mesafe + 1 });
                ziyaretEdildi[yeniX][yeniY] = true;
            }
        }
    }

    return { {-1, -1}, -1 }; // Bo� park yeri bulunamad�
}
