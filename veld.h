// Definitie van klasse Veld.

#ifndef VeldHVar  // voorkom dat dit bestand meerdere keren
#define VeldHVar  // ge-include wordt

#include <vector>
#include "constantes.h"
using namespace std;  // voor pair

//****************************************************************************

class Veld
{ public:
    // Constructor
    Veld ();

    // Lees uit bestand invoernaam een veld in
    // Returned true als gelukt, anders false met cerr
    bool leesInVeld (const char *invoernaam);

    // Druk het veld af op het scherm.
    // Controleer eerst of er al een (geldig) veld is ingelezen.
    void drukAfVeld ();

    // Bepaal rechtstreeks recursief een optimaal boeket
    // op positie (hoogte-1,breedte-1).
    // Controleer eerst of er al een (geldig) veld is ingelezen.
    // Retourneer:
    // * true, als er al een (geldig) veld was ingelezen
    // * false, anders
    // Post:
    // * Als returnwaarde true is,
    //   - representeert parameter optBoeket een optimaal boeket
    //   - bevat optBits het aantal bits 1 in optBoeket
    bool bepaalOptimaalBoeketRec (int &optBoeket, int &optBits);

    // Bepaal met top-down dynamisch programmeren een optimaal boeket
    // op positie (hoogte-1,breedte-1).
    // Controleer eerst of er al een (geldig) veld is ingelezen.
    // Retourneer:
    // * true, als er al een (geldig) veld was ingelezen
    // * false, anders
    // Post:
    // * Als returnwaarde true is,
    //   - representeert parameter optBoeket een optimaal boeket
    //   - bevat optBits het aantal bits 1 in optBoeket
    bool bepaalOptimaalBoeketTD (int &optBoeket, int &optBits);

    // Bepaal met bottom-up dynamisch programmeren een optimaal boeket
    // op positie (hoogte-1,breedte-1). Bepaal tevens een route door
    // het veld die dit optimale boeket oplevert.
    // Controleer eerst of er al een (geldig) veld is ingelezen.
    // Retourneer:
    // * true, als er al een (geldig) veld was ingelezen
    // * false, anders
    // Post:
    // * Als returnwaarde true is,
    //   - representeert parameter optBoeket een optimaal boeket
    //   - bevat optBits het aantal bits 1 in optBoeket
    //   - bevat parameter route een route met aansluitende vakjes van
    //     route[0]=(0,0) tot en met (hoogte-1,breedte-1), dat dit
    //     optimale boeket oplevert.
    bool bepaalOptimaalBoeketBU (int &optBoeket, int &optBits,
                                 vector< pair<int,int> > &route);

    // Druk de route die is opgeslagen in parameter route, af op het scherm,
    // samen met complete boeket (hoeveel bloemen van elke soort) dat
    // op deze route wordt geplukt.
    // Pre:
    // * Er is een (geldig) veld ingelezen.
    // * Alle vakjes in parameter route liggen in dit veld.
    void drukAfRoute (vector< pair<int,int> > &route);

  private:
    int hoogte, breedte,   // hoogte en breedte van veld (h en b dus)
    veld[MaxDim][MaxDim];  // coordinaten van vakken in het veld lopen
                               // van 0 t/m h-1 en van 0 t/m b-1
    bool mogelijk[MaxDim][MaxDim][MaxBoeket+1];
      // [i][j][k]: is het mogelijk om vanaf vakje (0,0) op vakje (i,j)
      //   te arriveren met een boeket overeenkomend met getal (bitstring) k

    // TODO: uw eigen private memberfuncties en -variabelen
    bool bepaalOptimaalBoeketRecursief(int i, int j, int bits, int & optBoeket, int & optBits, vector<pair<int,int>> currRoute, vector<pair<int,int>> &optRoute);
    int gevonden = 0;

    bool isOptimaalBoeket(int boeket);


};  // class Veld

#endif

