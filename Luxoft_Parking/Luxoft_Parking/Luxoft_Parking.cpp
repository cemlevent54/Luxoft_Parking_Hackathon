#include <iostream>
#include "ParkingManager.h"
#include "ParkingGrid.h" // ParkingGrid sýnýfý
using namespace std;

#if 1

// ANSI renk kodlari
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

// Park alanýný renkli olarak görselleþtirme
void parkAlaniniGorsellestir(ParkingGrid& grid, int hedefX = -1, int hedefY = -1) {
    cout << "\n======= PARK ALANI DURUMU =======" << endl;
    for (int i = 0; i < grid.getSatir(); i++) {
        for (int j = 0; j < grid.getSutun(); j++) {
            if (i == hedefX && j == hedefY) {
                cout << BLUE << "H " << RESET; // Hedef park yeri (mavi)
            }
            else if (grid.getDeger(i, j) == ParkingGrid::ENGEL) {
                cout << YELLOW << "E " << RESET; // Engel alaný (sarý)
            }
            else if (grid.getDeger(i, j) == ParkingGrid::DOLU) {
                cout << RED << "X " << RESET; // Dolu park yeri (kýrmýzý)
            }
            else {
                cout << GREEN << ". " << RESET; // Boþ park yeri (yeþil)
            }
        }
        cout << endl;
    }
    cout << "=================================\n";
}

// Menü arayuzu
void arayuzGoster() {
    cout << "=================================" << endl;
    cout << "1. En yakin bos park yerini bul ve park et" << endl;
    cout << "2. Manuel olarak park yeri doldur" << endl;
    cout << "3. Bos park yerlerini listele" << endl;
    cout << "4. Engel koy" << endl; 
    cout << "5. Cikis" << endl;
    cout << "=================================" << endl;
}

int main() {
    int satir, sutun;
    cout << "Park alani boyutlarini girin (satir ve sutun): ";

    if (!(cin >> satir) || satir <= 0) {
        cout << "Hata: Satir icin pozitif bir sayi girmeniz gerekiyor!" << endl;
        return 1;
    }

    if (!(cin >> sutun) || sutun <= 0) {
        cout << "Hata: Sutun icin pozitif bir sayi girmeniz gerekiyor!" << endl;
        return 1;
    }


    ParkingGrid grid(satir, sutun);
    ParkingManager manager(grid);

    bool cikis = false;

    while (!cikis) {
        parkAlaniniGorsellestir(grid);
        arayuzGoster();
        int secim;
        cout << "Seciminizi yapin: ";

        if (!(cin >> secim)) {
            cout << "Hata: Secim icin bir sayi girmeniz gerekiyor!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (secim) {
        case 1: {
            int baslangicX, baslangicY;
            cout << "Baslangic noktasini girin (x, y): ";
            if (!(cin >> baslangicX >> baslangicY)) {
                cout << "Hata: Gecersiz koordinat girdiniz!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            if (!grid.gecerliKoordinatMi(baslangicX, baslangicY)) {
                cout << "Gecersiz baslangic noktasi!" << endl;
                break;
            }

            auto bosYer = manager.bfsEnYakinBosParkYeri(baslangicX, baslangicY);
            if (bosYer.first.first != -1) {
                cout << "En yakin bos park yeri: (" << bosYer.first.first << ", " << bosYer.first.second << ")" << endl;
                parkAlaniniGorsellestir(grid, bosYer.first.first, bosYer.first.second);
                cout << "Isaretli yere(H) park etmek ister misiniz? (1: Evet, 0: Hayir): ";
                int onay;
                if (!(cin >> onay) || (onay != 1 && onay != 0)) {
                    cout << "Hata: Lutfen 1 veya 0 giriniz!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (onay == 1) {
                    manager.parkYeriDoldur(bosYer.first.first, bosYer.first.second);
                }
            }
            else {
                cout << "Bos park yeri bulunamadi!" << endl;
            }
            break;
        }
        case 2: {
            int x, y;
            cout << "Park yeri secin (x, y): ";
            if (!(cin >> x >> y)) {
                cout << "Hata: Gecersiz koordinat girdiniz!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            if (!grid.gecerliKoordinatMi(x, y)) {
                cout << "Hata: Girdiginiz koordinatlar park alani sinirlari disinda!" << endl;
                break;
            }
            manager.parkYeriDoldur(x, y);
            break;
        }
        case 3:
            manager.bosParkYerleriniListele();
            break;
        case 4: { // Engel koyma iþlemi
            int x, y;
            cout << "Engel koymak istediginiz alanin koordinatlarini girin (x, y): ";
            if (!(cin >> x >> y)) {
                cout << "Hata: Gecersiz koordinat girdiniz!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            if (!grid.gecerliKoordinatMi(x, y)) {
                cout << "Hata: Girdiginiz koordinatlar park alani sinirlari disinda!" << endl;
                break;
            }
            if (!manager.engelKoy(x, y)) {
                cout << "Hata: Engel koyma islemi basarisiz!" << endl;
            }
            break;
        }
        case 5:
            cout << "Cikis yapiliyor..." << endl;
            cikis = true;
            break;
        default:
            cout << "Gecersiz secim!" << endl;
        }
    }

    return 0;
}

#endif

#if 0

#include "Tests.h"

int main() {
    Tests::testParkAlanininTamDoluOlduguDurum();
    cout << endl << endl;
    Tests::testEnYakinBosYerBulma();
    cout << endl << endl;
    Tests::testManuelParkEtme();
    cout << endl << endl;
    Tests::testEngelKoyma();
    cout << endl << endl;
    Tests::testEngelUzerineParkEtme();
    cout << endl << endl;
    Tests::testGecersizKoordinatIleParkEtme();
    cout << endl << endl;
    Tests::testBfsIleBosYerBulmaEngellerle();

    return 0;
}

#endif
