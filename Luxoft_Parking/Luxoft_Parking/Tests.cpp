#include "Tests.h"
#include <iostream>
using namespace std;

void Tests::testParkAlanininTamDoluOlduguDurum() {
    cout << "### Test: Park Alanýnýn Tamamen Dolu Olduðu Durum ###" << endl;

    ParkingGrid grid(5, 5);
    ParkingManager manager(grid);

    for (int i = 0; i < grid.getSatir(); i++) {
        for (int j = 0; j < grid.getSutun(); j++) {
            manager.parkYeriDoldur(i, j);
        }
    }

    bool sonuc = manager.parkYeriDoldur(0, 0);

    if (!sonuc) {
        cout << "Durum: Alan tamamen dolu, park yapýlamaz. [GECTI]" << endl;
    }
    else {
        cout << "Durum: Hata, dolu alana park edildi! [KALDI]" << endl;
    }
    cout << endl;
}

void Tests::testEnYakinBosYerBulma() {
    cout << "### Test: En Yakýn Boþ Park Yerini Bulma ###" << endl;

    ParkingGrid grid(5, 5);
    ParkingManager manager(grid);

    manager.parkYeriDoldur(0, 0);
    manager.parkYeriDoldur(0, 1);

    auto sonuc = manager.enYakinBosParkYeri(0, 0);

    cout << "Durum: ";
    if (sonuc.first.first == 1 && sonuc.first.second == 0) {
        cout << "En yakýn boþ yer doðru bulundu: (1, 0). [GECTI]" << endl;
    }
    else {
        cout << "Hata, en yakýn boþ yer yanlýþ hesaplandý! [KALDI]" << endl;
    }
    cout << endl;
}

void Tests::testManuelParkEtme() {
    cout << "### Test: Manuel Park Etme ###" << endl;

    ParkingGrid grid(5, 5);
    ParkingManager manager(grid);

    bool sonuc = manager.parkYeriDoldur(4, 4);

    cout << "Durum: ";
    if (sonuc && grid.getDeger(4, 4) == ParkingGrid::DOLU) {
        cout << "Park iþlemi baþarýyla gerçekleþtirildi: (4, 4). [GECTI]" << endl;
    }
    else {
        cout << "Hata, park iþlemi gerçekleþtirilemedi! [KALDI]" << endl;
    }
    cout << endl;
}

void Tests::testEngelKoyma() {
    cout << "### Test: Engel Koyma ###" << endl;

    ParkingGrid grid(5, 5);
    ParkingManager manager(grid);

    bool sonuc = manager.engelKoy(2, 2);

    cout << "Durum: ";
    if (sonuc && grid.getDeger(2, 2) == ParkingGrid::ENGEL) {
        cout << "Engel baþarýyla eklendi: (2, 2). [GECTI]" << endl;
    }
    else {
        cout << "Hata, engel eklenemedi! [KALDI]" << endl;
    }
    cout << endl;
}

// Test: Engel üzerine park etme
void Tests::testEngelUzerineParkEtme() {
    cout << "### Test: Engel Üzerine Park Etme ###" << endl;

    ParkingGrid grid(5, 5);
    ParkingManager manager(grid);

    manager.engelKoy(2, 2);
    bool sonuc = manager.parkYeriDoldur(2, 2);

    cout << "Durum: ";
    if (!sonuc) {
        cout << "Engel üzerine park edilemedi, beklenen davranýþ. [GECTI]" << endl;
    }
    else {
        cout << "Hata, engel üzerine park edildi! [KALDI]" << endl;
    }
    cout << endl;
}

void Tests::testGecersizKoordinatIleParkEtme() {
    cout << "### Test: Geçersiz Koordinat ile Park Etme ###" << endl;

    ParkingGrid grid(5, 5);
    ParkingManager manager(grid);

    bool sonuc = manager.parkYeriDoldur(6, 6);

    cout << "Durum: ";
    if (!sonuc) {
        cout << "Geçersiz koordinata park edilemedi, beklenen davranýþ. [GECTI]" << endl;
    }
    else {
        cout << "Hata, geçersiz koordinata park edildi! [KALDI]" << endl;
    }
    cout << endl;
}

void Tests::testBfsIleBosYerBulmaEngellerle() {
    cout << "### Test: BFS ile Boþ Yer Bulma (Engellerle) ###" << endl;

    ParkingGrid grid(5, 5);
    ParkingManager manager(grid);

    manager.engelKoy(0, 1);
    manager.engelKoy(1, 0);
    manager.engelKoy(1, 1);

    auto sonuc = manager.bfsEnYakinBosParkYeri(0, 0);

    cout << "Durum: ";
    if (sonuc.first.first == 0 && sonuc.first.second == 0) {
        cout << "BFS algoritmasý doðru þekilde çalýþtý. [GECTI]" << endl;
    }
    else {
        cout << "Hata, BFS algoritmasý doðru çalýþmadý! [KALDI]" << endl;
    }
    cout << endl;
}
