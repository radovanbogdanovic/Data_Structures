//#include <iostream>
//using namespace std;
//
//#include "GraphInt.h"
//
//int main()
//{
//    cout << boolalpha;
//
//    GraphAsListsInt graph;
//
//    for (int i = 1; i <= 10; i++)
//        graph.insertNode(i);
//
//    /*
//        Graf:
//
//        1 -> 2 -> 3 -> 4 -> 5
//                  |
//                  v
//                  6 -> 7
//
//        8 je izolovan
//        9 -> 10 je odvojena komponenta
//    */
//
//    graph.insertEdge(1, 2);
//    graph.insertEdge(2, 3);
//    graph.insertEdge(3, 4);
//    graph.insertEdge(4, 5);
//    graph.insertEdge(3, 6);
//    graph.insertEdge(6, 7);
//
//    graph.insertEdge(9, 10);
//
//    cout << "Test 1: oba cilja dostupna preko mid, ocekuje se true: ";
//    cout << graph.arePathsPossible(
//        graph.findNode(1),
//        graph.findNode(5),
//        graph.findNode(7),
//        graph.findNode(3)
//    ) << endl;
//
//    cout << "Test 2: goal2 je izolovan, ocekuje se false: ";
//    cout << graph.arePathsPossible(
//        graph.findNode(1),
//        graph.findNode(5),
//        graph.findNode(8),
//        graph.findNode(3)
//    ) << endl;
//
//    cout << "Test 3: mid nije dostupan iz start, ocekuje se false: ";
//    cout << graph.arePathsPossible(
//        graph.findNode(1),
//        graph.findNode(10),
//        graph.findNode(7),
//        graph.findNode(9)
//    ) << endl;
//
//    cout << "Test 4: goal1 nije dostupan iz mid, ocekuje se false: ";
//    cout << graph.arePathsPossible(
//        graph.findNode(1),
//        graph.findNode(10),
//        graph.findNode(7),
//        graph.findNode(3)
//    ) << endl;
//
//    cout << "Test 5: start je vec mid, ciljevi dostupni, zavisi od tvoje logike ali najcesce true: ";
//    cout << graph.arePathsPossible(
//        graph.findNode(3),
//        graph.findNode(5),
//        graph.findNode(7),
//        graph.findNode(3)
//    ) << endl;
//
//    return 0;
//} JANUAR 2024
//#include <iostream>
//using namespace std;
//
//#include "GraphInt.h"
//
//int main()
//{
//    cout << "===== TEST 1: jedna komponenta lanac =====" << endl;
//    {
//        GraphAsListsInt g;
//
//        for (int i = 1; i <= 5; i++)
//            g.insertNode(i);
//
//        // Orijentisano: 1 -> 2 -> 3 -> 4 -> 5
//        // Posle deorientation: 1 -- 2 -- 3 -- 4 -- 5
//        g.insertEdge(1, 2);
//        g.insertEdge(2, 3);
//        g.insertEdge(3, 4);
//        g.insertEdge(4, 5);
//
//        cout << "Cvorovi najvece komponente: ";
//        int result = g.printMaxConnectedComponentNodes();
//
//        cout << endl;
//        cout << "Broj cvorova najvece komponente: " << result << endl;
//        cout << "Ocekivano: 5" << endl;
//    }
//
//    cout << endl;
//
//    cout << "===== TEST 2: dve komponente, prva veca =====" << endl;
//    {
//        GraphAsListsInt g;
//
//        for (int i = 1; i <= 8; i++)
//            g.insertNode(i);
//
//        /*
//            Komponenta 1:
//            1 -> 2 -> 3 -> 4 -> 5
//
//            Komponenta 2:
//            6 -> 7
//
//            8 izolovan
//        */
//
//        g.insertEdge(1, 2);
//        g.insertEdge(2, 3);
//        g.insertEdge(3, 4);
//        g.insertEdge(4, 5);
//
//        g.insertEdge(6, 7);
//
//        cout << "Cvorovi najvece komponente: ";
//        int result = g.printMaxConnectedComponentNodes();
//
//        cout << endl;
//        cout << "Broj cvorova najvece komponente: " << result << endl;
//        cout << "Ocekivano: 5" << endl;
//    }
//
//    cout << endl;
//
//    cout << "===== TEST 3: razgranata komponenta =====" << endl;
//    {
//        GraphAsListsInt g;
//
//        for (int i = 1; i <= 7; i++)
//            g.insertNode(i);
//
//        /*
//            Komponenta:
//                    1
//                  / | \
//                 2  3  4
//                       |
//                       5
//
//            Druga komponenta:
//                6 -> 7
//
//            Najveca komponenta ima 5 cvorova: 1,2,3,4,5
//        */
//
//        g.insertEdge(1, 2);
//        g.insertEdge(1, 3);
//        g.insertEdge(1, 4);
//        g.insertEdge(4, 5);
//
//        g.insertEdge(6, 7);
//
//        cout << "Cvorovi najvece komponente: ";
//        int result = g.printMaxConnectedComponentNodes();
//
//        cout << endl;
//        cout << "Broj cvorova najvece komponente: " << result << endl;
//        cout << "Ocekivano: 5" << endl;
//    }
//
//    cout << endl;
//
//    cout << "===== TEST 4: najveća komponenta nije prva =====" << endl;
//    {
//        GraphAsListsInt g;
//
//        for (int i = 1; i <= 9; i++)
//            g.insertNode(i);
//
//        /*
//            Komponenta 1:
//            1 -> 2
//
//            Komponenta 2:
//            3 -> 4 -> 5 -> 6 -> 7
//
//            Komponenta 3:
//            8 izolovan
//            9 izolovan
//
//            Najveca komponenta treba da bude 3,4,5,6,7
//        */
//
//        g.insertEdge(1, 2);
//
//        g.insertEdge(3, 4);
//        g.insertEdge(4, 5);
//        g.insertEdge(5, 6);
//        g.insertEdge(6, 7);
//
//        cout << "Cvorovi najvece komponente: ";
//        int result = g.printMaxConnectedComponentNodes();
//
//        cout << endl;
//        cout << "Broj cvorova najvece komponente: " << result << endl;
//        cout << "Ocekivano: 5" << endl;
//    }
//
//    cout << endl;
//
//    cout << "===== TEST 5: sve izolovani cvorovi =====" << endl;
//    {
//        GraphAsListsInt g;
//
//        for (int i = 1; i <= 4; i++)
//            g.insertNode(i);
//
//        /*
//            Nema grana.
//            Svaki cvor je posebna komponenta velicine 1.
//        */
//
//        cout << "Cvorovi najvece komponente: ";
//        int result = g.printMaxConnectedComponentNodes();
//
//        cout << endl;
//        cout << "Broj cvorova najvece komponente: " << result << endl;
//        cout << "Ocekivano: 1" << endl;
//    }
//
//    cout << endl;
//
//    cout << "===== TEST 6: smerovi su obrnuti, deorientation mora da pomogne =====" << endl;
//    {
//        GraphAsListsInt g;
//
//        for (int i = 1; i <= 6; i++)
//            g.insertNode(i);
//
//        /*
//            Orijentisano:
//            2 -> 1
//            3 -> 2
//            4 -> 3
//
//            Ako se ignorise smer, to je komponenta:
//            1 -- 2 -- 3 -- 4
//
//            Druga komponenta:
//            5 -> 6
//
//            Najveca ima 4 cvora.
//        */
//
//        g.insertEdge(2, 1);
//        g.insertEdge(3, 2);
//        g.insertEdge(4, 3);
//
//        g.insertEdge(5, 6);
//
//        cout << "Cvorovi najvece komponente: ";
//        int result = g.printMaxConnectedComponentNodes();
//
//        cout << endl;
//        cout << "Broj cvorova najvece komponente: " << result << endl;
//        cout << "Ocekivano: 4" << endl;
//    }
//
//    return 0;
//} Jun 2024
//#include <iostream>
//using namespace std;
//
//#include "GraphInt.h"
//
//void printOrder(const char* testName, int* order, int expectedSize, bool shouldBePossible)
//{
//    cout << "===== " << testName << " =====" << endl;
//
//    if (order == nullptr) {
//        cout << "Rezultat: nullptr" << endl;
//
//        if (shouldBePossible)
//            cout << "Ocekivano: moguc redosled -> GRESKA" << endl;
//        else
//            cout << "Ocekivano: nullptr -> OK" << endl;
//
//        cout << endl;
//        return;
//    }
//
//    cout << "Redosled: ";
//    for (int i = 0; i < expectedSize; i++) {
//        cout << order[i] << " ";
//    }
//    cout << endl;
//
//    if (shouldBePossible)
//        cout << "Ocekivano: moguc redosled" << endl;
//    else
//        cout << "Ocekivano: nullptr -> GRESKA" << endl;
//
//    delete[] order;
//
//    cout << endl;
//}
//
//int main()
//{
//    {
//        GraphAsListsInt graph;
//
//        /*
//            2 zavisi od 1
//            3 zavisi od 2
//            4 zavisi od 3
//
//            Redosled mora biti:
//            1 2 3 4
//        */
//        int dep[] = {
//            2, 1,
//            3, 2,
//            4, 3
//        };
//
//        int* order = graph.defineOrder(dep, 6);
//        printOrder("TEST 1: prost lanac", order, 4, true);
//    }
//
//    {
//        GraphAsListsInt graph;
//
//        /*
//            1 zavisi od 2
//            1 zavisi od 4
//
//            Validno:
//            2 4 1
//            ili
//            4 2 1
//        */
//        int dep[] = {
//            1, 2,
//            1, 4
//        };
//
//        int* order = graph.defineOrder(dep, 4);
//        printOrder("TEST 2: jedan cvor ima dve zavisnosti", order, 3, true);
//    }
//
//    {
//        GraphAsListsInt graph;
//
//        /*
//            2 zavisi od 1
//            3 zavisi od 1
//            4 zavisi od 2
//            4 zavisi od 3
//
//            Znaci:
//            1 mora pre 2 i 3
//            2 i 3 moraju pre 4
//
//            Validno:
//            1 2 3 4
//            ili
//            1 3 2 4
//        */
//        int dep[] = {
//            2, 1,
//            3, 1,
//            4, 2,
//            4, 3
//        };
//
//        int* order = graph.defineOrder(dep, 8);
//        printOrder("TEST 3: razgranate zavisnosti", order, 4, true);
//    }
//
//    {
//        GraphAsListsInt graph;
//
//        /*
//            2 zavisi od 1
//            4 zavisi od 3
//
//            Dve odvojene grupe:
//            1 pre 2
//            3 pre 4
//
//            Validno:
//            1 3 2 4
//            3 1 4 2
//            itd.
//        */
//        int dep[] = {
//            2, 1,
//            4, 3
//        };
//
//        int* order = graph.defineOrder(dep, 4);
//        printOrder("TEST 4: dve nezavisne komponente", order, 4, true);
//    }
//
//    {
//        GraphAsListsInt graph;
//
//        /*
//            Duplirana zavisnost:
//            2 zavisi od 1
//            2 zavisi od 1 opet
//
//            Ako findEdge radi dobro, indegree za 2 se povecava samo jednom.
//
//            Plus:
//            3 zavisi od 2
//
//            Redosled:
//            1 2 3
//        */
//        int dep[] = {
//            2, 1,
//            2, 1,
//            3, 2
//        };
//
//        int* order = graph.defineOrder(dep, 6);
//        printOrder("TEST 5: duplirana grana", order, 3, true);
//    }
//
//    {
//        GraphAsListsInt graph;
//
//        /*
//            2 zavisi od 1
//            1 zavisi od 2
//
//            Ciklus:
//            1 <-> 2
//
//            Nije moguce.
//        */
//        int dep[] = {
//            2, 1,
//            1, 2
//        };
//
//        int* order = graph.defineOrder(dep, 4);
//        printOrder("TEST 6: prost ciklus", order, 2, false);
//    }
//
//    {
//        GraphAsListsInt graph;
//
//        /*
//            2 zavisi od 1
//            3 zavisi od 2
//            1 zavisi od 3
//
//            Ciklus:
//            1 -> 2 -> 3 -> 1
//
//            Nije moguce.
//        */
//        int dep[] = {
//            2, 1,
//            3, 2,
//            1, 3
//        };
//
//        int* order = graph.defineOrder(dep, 6);
//        printOrder("TEST 7: duzi ciklus", order, 3, false);
//    }
//
//    {
//        GraphAsListsInt graph;
//
//        /*
//            1 zavisi od 1
//
//            Sam od sebe zavisi, to je ciklus.
//        */
//        int dep[] = {
//            1, 1
//        };
//
//        int* order = graph.defineOrder(dep, 2);
//        printOrder("TEST 8: samociklus", order, 1, false);
//    }
//
//    return 0;
//} Jun2 2024
//#include <iostream>
//using namespace std;
//
//#include "GraphInt.h"
//
//int main()
//{
//    GraphAsListsInt graph;
//
//    for (int i = 1; i <= 8; i++)
//        graph.insertNode(i);
//
//    graph.insertEdge(1, 2);
//    graph.insertEdge(2, 3);
//    graph.insertEdge(3, 2);
//
//    graph.insertEdge(4, 5);
//    graph.insertEdge(5, 6);
//
//    graph.insertEdge(8, 4);
//
//    cout << "Broj bezbednih cvorova: "
//        << graph.countSafeNodes()
//        << endl;
//
//    return 0;
//} decembar 2026
//#include <iostream>
//using namespace std;
//
//#include "GraphInt.h"
//
//int main()
//{
//    GraphAsListsInt graph;
//
//    for (int i = 1; i <= 4; i++)
//        graph.insertNode(i);
//
//    graph.insertEdge(1, 2);
//    graph.insertEdge(2, 3);
//    graph.insertEdge(3, 4);
//
//    cout << "Redosled: ";
//    long processed = graph.topologicalOrderTravrsal();
//    cout << "Broj obradjenih: " << processed << endl;
//
//    graph.insertEdge(4, 1);
//
//    cout << "Redosled sa ciklusom: ";
//    processed = graph.topologicalOrderTravrsal();
//    cout << "Broj obradjenih: " << processed << endl;
//
//    return 0;
//} januar 2026
//#include <iostream>
//using namespace std;
//
//#include "GraphInt.h"
//
//int main()
//{
//    GraphAsListsInt graph;
//
//    for (int i = 1; i <= 6; i++)
//        graph.insertNode(i);
//
//    graph.insertEdge(1, 2);
//    graph.insertEdge(2, 4);
//    graph.insertEdge(1, 3);
//    graph.insertEdge(3, 5);
//    graph.insertEdge(5, 6);
//
//    int closer = graph.whichOneIsCloser(1, 4, 6);
//    int farther = closer == 4 ? 6 : 4;
//
//    cout << "Blizi cvor: " << closer << endl;
//    cout << boolalpha;
//    cout << "Poteg pre: "
//        << (graph.findEdge(closer, farther) != nullptr)
//        << endl;
//
//    graph.ensureEdgeExists(closer, farther);
//
//    cout << "Poteg posle: "
//        << (graph.findEdge(closer, farther) != nullptr)
//        << endl;
//
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//#include "GraphInt.h"
//
//int main()
//{
//    GraphAsListsInt graph;
//
//    for (int i = 1; i <= 7; i++)
//        graph.insertNode(i);
//
//    graph.insertEdge(1, 2);
//    graph.insertEdge(2, 3);
//    graph.insertEdge(3, 4);
//    graph.insertEdge(1, 5);
//    graph.insertEdge(5, 6);
//
//    int noInter = -1;
//    LinkedNodeInt* station =
//        graph.FindStation(1, 4, 6, noInter);
//
//    cout << "Bliza stanica: "
//        << (station != nullptr ? station->node : -1)
//        << endl;
//    cout << "Broj medjustanica: " << noInter << endl;
//
//    station = graph.FindStation(7, 4, 6, noInter);
//    cout << boolalpha;
//    cout << "Nedostupan cilj: "
//        << (station == nullptr) << endl;
//    cout << "Broj medjustanica: " << noInter << endl;
//
//    return 0;
//
//} april 2025
//#include <iostream>
//using namespace std;
//
//#include "GraphInt.h"
//
//int main()
//{
//    GraphAsListsInt graph;
//
//    for (int i = 1; i <= 6; i++)
//        graph.insertNode(i);
//
//    graph.insertEdge(1, 2);
//    graph.insertEdge(2, 3);
//    graph.insertEdge(3, 4);
//    graph.insertEdge(1, 5);
//    graph.insertEdge(5, 4);
//
//    cout << boolalpha;
//    cout << "Put 1->4 kroz 2: "
//        << graph.pathGoesThrough(1, 2, 4)
//        << endl;
//    cout << "Put 1->4 kroz 6: "
//        << graph.pathGoesThrough(1, 6, 4)
//        << endl;
//
//    return 0;
//} oktobar 2 2025
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;

    for (int i = 1; i <= 5; i++)
        graph.insertNode(i);

    graph.insertEdge(1, 2);
    graph.insertEdge(2, 3);
    graph.insertEdge(3, 5);
    graph.insertEdge(1, 4);
    graph.insertEdge(4, 5);

    cout << boolalpha;
    cout << "Put 1->5 kroz 2->3: "
        << graph.pathThroughEdgeExists(1, 2, 3, 5)
        << endl;
    cout << "Put 1->5 kroz 2->4: "
        << graph.pathThroughEdgeExists(1, 2, 4, 5)
        << endl;

    return 0;
}