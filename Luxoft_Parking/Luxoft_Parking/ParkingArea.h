#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <queue>
#include <tuple>
using namespace std;

class ParkingArea {
private:
    vector<vector<int>> grid; // Park alanýný temsil eden 2D matris
    int satir, sutun;         // Matris boyutlarý
    int doluParkYeriSayisi;   // Dolu park yeri sayýsý

public:
    // Constructor: Matris boyutlarýný alýr ve baþlangýç deðerlerini 0 olarak ayarlar
    ParkingArea(int s, int t) : satir(s), sutun(t), doluParkYeriSayisi(0) {
        grid.resize(satir, vector<int>(sutun, 0)); // Baþlangýçta tüm hücreler boþ (0)
    }

    // Getter ve Setter
    int getSatir() const { return satir; }
    void setSatir(int _satir) { satir = _satir; }

    int getSutun() const { return sutun; }
    void setSutun(int _sutun) { sutun = _sutun; }

    int getDoluParkYeriSayisi() const { return doluParkYeriSayisi; }
    void setDoluParkYeriSayisi(int _doluParkYeriSayisi) { doluParkYeriSayisi = _doluParkYeriSayisi; }

    int getGridValue(int x, int y) const { return grid[x][y]; }

    // Park alanýný ekrana yazdýrýr
    void parkAlaniniYazdir() {
        cout << "======= PARK ALANI DURUMU =======" << endl;
        for (int i = 0; i < satir; i++) {
            for (int j = 0; j < sutun; j++) {
                cout << (grid[i][j] == 0 ? "." : "X") << " ";
            }
            cout << endl;
        }
        cout << "Dolu Park Yeri Sayisi: " << doluParkYeriSayisi << endl; // Dolu park yeri sayýsýný göster
        cout << "=================================" << endl;
    }

    // Belirli bir hücreyi dolu (1) yapar
    bool parkYeriDoldur(int x, int y) {
        if (doluParkYeriSayisi == satir * sutun) {
            cout << "Hata: Tum park yerleri dolu! Yeni arac park edilemez." << endl;
            return false;
        }

        if (x >= 0 && x < satir && y >= 0 && y < sutun) {
            if (grid[x][y] == 1) {
                cout << "Hata: Park yeri (" << x << ", " << y << ") zaten dolu!" << endl;
                return false;
            }
            else {
                grid[x][y] = 1;
                doluParkYeriSayisi++; // Dolu park yeri sayýsýný artýr
                cout << "Park yeri (" << x << ", " << y << ") dolu olarak ayarlandi." << endl;
                return true;
            }
        }
        else {
            cout << "Hata: Gecersiz koordinat!" << endl;
            return false;
        }
    }

    // Manhattan mesafesi kullanarak en yakýn boþ park yerini bulur
    pair<pair<int, int>, int> enYakinBosParkYeri(int baslangicX, int baslangicY) {
        int minMesafe = numeric_limits<int>::max();
        pair<int, int> enYakinYer = { -1, -1 };

        for (int i = 0; i < satir; i++) {
            for (int j = 0; j < sutun; j++) {
                if (grid[i][j] == 0) { // Eðer hücre boþsa
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

    // Tüm boþ park yerlerini ekrana yazdýrýr
    void bosParkYerleriniListele() {
        cout << "Bos Park Yerleri:" << endl;
        for (int i = 0; i < satir; i++) {
            for (int j = 0; j < sutun; j++) {
                if (grid[i][j] == 0) {
                    cout << "(" << i << ", " << j << ")" << " , ";
                }
            }
        }
        cout << endl;
    }

    // BFS ile en yakýn boþ park yerini bulur
    pair<pair<int, int>, int> bfsEnYakinBosParkYeri(int baslangicX, int baslangicY) {
        vector<vector<bool>> ziyaretEdildi(satir, vector<bool>(sutun, false));
        queue<pair<pair<int, int>, int>> q; // Sýra: Koordinatlar ve mesafe

        q.push({ {baslangicX, baslangicY}, 0 }); // Baþlangýç noktasýný sýraya ekle
        ziyaretEdildi[baslangicX][baslangicY] = true;

        // 4 yönlü hareket
        //vector<pair<int, int>> yonler = {
        //    {-1, 0}, // Yukarý
        //    {1, 0},  // Aþaðý
        //    {0, -1}, // Sol
        //    {0, 1}   // Sað
        //};


        // my suggestion
        vector<pair<int, int>> yonler = {
        {1, 0},  // Aþaðý
        {0, -1}, // Sol
        {0, 1},  // Sað
        {-1, 0}  // Yukarý
        };

        while (!q.empty()) {
            auto current = q.front(); // Þu anki hücreyi sýradan al
            int x = current.first.first;
            int y = current.first.second;
            int mesafe = current.second;
            q.pop();

            // Eðer boþ park yeri bulunduysa döndür
            if (grid[x][y] == 0) {
                return { {x, y}, mesafe };
            }

            // Komþu hücreleri kontrol et
            for (pair<int, int> yon : yonler) {
                int yeniX = x + yon.first;
                int yeniY = y + yon.second;

                if (yeniX >= 0 && yeniX < satir && yeniY >= 0 && yeniY < sutun && !ziyaretEdildi[yeniX][yeniY]) {
                    q.push({ {yeniX, yeniY}, mesafe + 1 }); // Mesafeyi bir artýrarak sýraya ekle
                    ziyaretEdildi[yeniX][yeniY] = true;
                }
            }
        }

        return { {-1, -1}, -1 }; // Boþ park yeri bulunamadý
    }

    
};
