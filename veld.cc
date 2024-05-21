// Implementatie van klasse Veld.
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include "standaard.h"
#include "veld.h"
using namespace std;

Veld::Veld () {
} // constructor

bool Veld::leesInVeld(const char *invoernaam) {
  // Bestand openen
  ifstream bestand(invoernaam);
  // Is bestandsnaam geldig
  if (!bestand.is_open()) {
    cerr << "Ongeldige bestandsnaam \n";
    return false;
  }

  // Eerste regel: hoogte en breedte
  bestand >> hoogte >> breedte;
  if (hoogte <= 0 || breedte <= 0 || hoogte > MaxDim || breedte > MaxDim) {
    cerr << "Ongeldige hoogte of breedte in bestand \n";
    return false;
  }

  // Volgende regels: vakken van het bloemenveld
  for (int i = 0; i < hoogte; ++i) {
    for (int j = 0; j < breedte; ++j) {
      bestand >> veld[i][j];
      if (veld[i][j] < 0 || veld[i][j] > MaxBloem) {
        cerr << "Ongeldig getal in bestand \n";
        return false;
      }
    }
  }

  // Bestand sluiten
  bestand.close();

  // Alles is goed gegaan
  return true;
} // leesInVeld

void Veld::drukAfVeld() {
  // Controleer of er een geldig veld is ingelezen
  if (hoogte <= 0 || breedte <= 0) {
    cerr << "Er is nog geen veld ingelezen \n";
    return;
  }

  cout << "==| Bloemenveld |== \n";

  // Print elke rij van het veld
  for (int i = 0; i < hoogte; ++i) {
    for (int j = 0; j < breedte; ++j) {
      cout << veld[i][j] << " ";
    }
    cout << '\n';
  }
} // drukAfVeld


bool Veld::bepaalOptimaalBoeketRec(int &optBoeket, int &optBits) {
  // Controleer of er een geldig veld is ingelezen
  if (hoogte <= 0 || breedte <= 0) {
    cerr << "Er is nog geen veld ingelezen \n";
    return false;
  }

  // init vars
  optBoeket = 0;
  optBits = 0;

  // curr(ent)Route houdt de huidige node bij,
  // als die optimaal is gaat die samen bij opt(imal)Route
  vector<pair<int, int>> currRoute;
  vector<pair<int, int>> optRoute;


  // start recursie op vakje 0,0 : i,j
  bool gelukt = bepaalOptimaalBoeketRecursief(0, 0, 0, optBoeket, optBits, currRoute, optRoute);

  // Als recursie gelukt, log de optimale route
  if (gelukt) {
    drukAfRoute(optRoute);
  }

  return gelukt;
}


bool Veld::bepaalOptimaalBoeketRecursief(int i, int j, int bits, int &optBoeket, int &optBits, vector<pair<int,int>> currRoute, vector<pair<int,int>> &optRoute) {
    // Push node in temp route
    currRoute.push_back({i,j});

    // Stopgeval ( base case), vakje rechtsonder bereikt
    if (i == hoogte - 1 && j == breedte - 1) {
        // Update opt(imal)Boeket en opt(imal)Bits
        int count = 0;
        for (int k = 0; k < 8; k++) {
            if (getBit(bits, k)) {
                count++;
            }
        }
        if (count > optBoeket) {
            optBoeket = count;
            optBits = bits;
            // Update opt(imal) route
            optRoute = currRoute;
        }
        return true;
    }

    // recursief geval, probeer vakje rechts of onder van huidig vakje
    bool right = false, down = false;
    if (i + 1 < hoogte) {
        switchBit(bits, veld[i + 1][j]);
        right = bepaalOptimaalBoeketRecursief(i + 1, j, bits, optBoeket, optBits, currRoute, optRoute);
        switchBit(bits, veld[i + 1][j]);  // backtrack
    }
    if (j + 1 < breedte) {
        switchBit(bits, veld[i][j + 1]);
        down = bepaalOptimaalBoeketRecursief(i, j + 1, bits, optBoeket, optBits, currRoute, optRoute);
        switchBit(bits, veld[i][j + 1]);  // backtrack
    }

    // Pop node weg aangezien onoptimale route
    currRoute.pop_back();

    return right || down;
}



//****************************************************************************

bool Veld::bepaalOptimaalBoeketTD (int &optBoeket, int &optBits)
{
  // TODO: implementeer deze memberfunctie
  return false;

}  // bepaalOptimaalBoeketTD

//****************************************************************************

bool Veld::bepaalOptimaalBoeketBU (int &optBoeket, int &optBits,
                                 vector< pair<int,int> > &route)
{
  // TODO: implementeer deze memberfunctie
  return false;

}  // bepaalOptimaalBoeketBU

//****************************************************************************

void Veld::drukAfRoute(vector < pair < int, int > > & route) {
  // Maak een kopie van het veld
  vector < vector < string >> veldKopie(hoogte, vector < string > (breedte));

  // Kopieer de waarden van het veld naar de kopie
  for (int i = 0; i < hoogte; ++i) {
    for (int j = 0; j < breedte; ++j) {
      veldKopie[i][j] = to_string(veld[i][j]);
    }
  }

  // Markeer de route op het veld
  for (size_t k = 0; k < route.size() - 1; ++k) {
    auto &vakje = route[k];
    auto &nextVakje = route[k + 1];

    if (nextVakje.first > vakje.first) {
      veldKopie[vakje.first][vakje.second] = "↓";
    } else if (nextVakje.second > vakje.second) {
      veldKopie[vakje.first][vakje.second] = "→";
    }
  }
  veldKopie[route.back().first][route.back().second] = "X";

  // Druk het veld af
  cout << "==| Optimale Route |== \n";
  for (int i = 0; i < hoogte; ++i) {
    for (int j = 0; j < breedte; ++j) {
      cout << setw(1) << veldKopie[i][j] << " ";
    }
    cout << '\n';
  }
} // drukAfRoute