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
    vector<vector<int>> grid; // Park alan�n� temsil eden 2D matris
    int satir, sutun;         // Matris boyutlar�
    int doluParkYeriSayisi;   // Dolu park yeri say�s�

public:
    // Constructor: Matris boyutlar�n� al�r ve ba�lang�� de�erlerini 0 olarak ayarlar
    ParkingArea(int s, int t) : satir(s), sutun(t), doluParkYeriSayisi(0) {
        grid.resize(satir, vector<int>(sutun, 0)); // Ba�lang��ta t�m h�creler bo� (0)
    }

    // Getter ve Setter
    int getSatir() const { return satir; }
    void setSatir(int _satir) { satir = _satir; }

    int getSutun() const { return sutun; }
    void setSutun(int _sutun) { sutun = _sutun; }

    int getDoluParkYeriSayisi() const { return doluParkYeriSayisi; }
    void setDoluParkYeriSayisi(int _doluParkYeriSayisi) { doluParkYeriSayisi = _doluParkYeriSayisi; }

    int getGridValue(int x, int y) const { return grid[x][y]; }

    // Park alan�n� ekrana yazd�r�r
    void parkAlaniniYazdir() {
        cout << "======= PARK ALANI DURUMU =======" << endl;
        for (int i = 0; i < satir; i++) {
            for (int j = 0; j < sutun; j++) {
                cout << (grid[i][j] == 0 ? "." : "X") << " ";
            }
            cout << endl;
        }
        cout << "Dolu Park Yeri Sayisi: " << doluParkYeriSayisi << endl; // Dolu park yeri say�s�n� g�ster
        cout << "=================================" << endl;
    }

    // Belirli bir h�creyi dolu (1) yapar
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
                doluParkYeriSayisi++; // Dolu park yeri say�s�n� art�r
                cout << "Park yeri (" << x << ", " << y << ") dolu olarak ayarlandi." << endl;
                return true;
            }
        }
        else {
            cout << "Hata: Gecersiz koordinat!" << endl;
            return false;
        }
    }

    // Manhattan mesafesi kullanarak en yak�n bo� park yerini bulur
    pair<pair<int, int>, int> enYakinBosParkYeri(int baslangicX, int baslangicY) {
        int minMesafe = numeric_limits<int>::max();
        pair<int, int> enYakinYer = { -1, -1 };

        for (int i = 0; i < satir; i++) {
            for (int j = 0; j < sutun; j++) {
                if (grid[i][j] == 0) { // E�er h�cre bo�sa
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

    // T�m bo� park yerlerini ekrana yazd�r�r
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

    // BFS ile en yak�n bo� park yerini bulur
    pair<pair<int, int>, int> bfsEnYakinBosParkYeri(int baslangicX, int baslangicY) {
        vector<vector<bool>> ziyaretEdildi(satir, vector<bool>(sutun, false));
        queue<pair<pair<int, int>, int>> q; // S�ra: Koordinatlar ve mesafe

        q.push({ {baslangicX, baslangicY}, 0 }); // Ba�lang�� noktas�n� s�raya ekle
        ziyaretEdildi[baslangicX][baslangicY] = true;

        // 4 y�nl� hareket
        //vector<pair<int, int>> yonler = {
        //    {-1, 0}, // Yukar�
        //    {1, 0},  // A�a��
        //    {0, -1}, // Sol
        //    {0, 1}   // Sa�
        //};


        // my suggestion
        vector<pair<int, int>> yonler = {
        {1, 0},  // A�a��
        {0, -1}, // Sol
        {0, 1},  // Sa�
        {-1, 0}  // Yukar�
        };

        while (!q.empty()) {
            auto current = q.front(); // �u anki h�creyi s�radan al
            int x = current.first.first;
            int y = current.first.second;
            int mesafe = current.second;
            q.pop();

            // E�er bo� park yeri bulunduysa d�nd�r
            if (grid[x][y] == 0) {
                return { {x, y}, mesafe };
            }

            // Kom�u h�creleri kontrol et
            for (pair<int, int> yon : yonler) {
                int yeniX = x + yon.first;
                int yeniY = y + yon.second;

                if (yeniX >= 0 && yeniX < satir && yeniY >= 0 && yeniY < sutun && !ziyaretEdildi[yeniX][yeniY]) {
                    q.push({ {yeniX, yeniY}, mesafe + 1 }); // Mesafeyi bir art�rarak s�raya ekle
                    ziyaretEdildi[yeniX][yeniY] = true;
                }
            }
        }

        return { {-1, -1}, -1 }; // Bo� park yeri bulunamad�
    }

    
};
