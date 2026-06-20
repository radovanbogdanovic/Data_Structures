# Main primeri za grafovske blankete

Svi primeri koriste stvarni template:

```cpp
#include "GraphInt.h"
```

Klasa grafa je `GraphAsListsInt`, cvor je `LinkedNodeInt`, a poteg je
`LinkedEdgeInt`.

Deklaraciju trazene javne metode dodaj u `public` deo klase
`GraphAsListsInt`. Deklaracije pomocnih metoda dodaj u `private` deo.

## Napomena o ispisu destruktora

Trenutni destruktor sadrzi:

```cpp
cout << "Not implemented!" << endl;
```

Zato ce se na kraju programa pojaviti po jedna dodatna linija
`Not implemented!` za svaki objekat grafa. Ta linija nije deo ocekivanog
rezultata zadatka i izostavljena je iz ispisa ispod.

## Januar 2024 - `arePathsPossible`

U `public` deo `GraphInt.h`:

```cpp
bool arePathsPossible(LinkedNodeInt* pStart,
                      LinkedNodeInt* goal1,
                      LinkedNodeInt* goal2,
                      LinkedNodeInt* mid) const;
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;

    for (int i = 1; i <= 8; i++)
        graph.insertNode(i);

    graph.insertEdge(1, 2);
    graph.insertEdge(2, 3);
    graph.insertEdge(3, 4);
    graph.insertEdge(4, 5);
    graph.insertEdge(3, 6);
    graph.insertEdge(6, 7);

    cout << boolalpha;
    cout << "Oba putovanja moguca: "
         << graph.arePathsPossible(
                graph.findNode(1),
                graph.findNode(5),
                graph.findNode(7),
                graph.findNode(3))
         << endl;

    cout << "Drugi cilj nedostupan: "
         << graph.arePathsPossible(
                graph.findNode(1),
                graph.findNode(5),
                graph.findNode(8),
                graph.findNode(3))
         << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Oba putovanja moguca: true
Drugi cilj nedostupan: false
```

Zajednicki put je `1 -> 2 -> 3`. Nakon toga prvi putnik ide
`3 -> 4 -> 5`, a drugi `3 -> 6 -> 7`.

## Jun 2024 - `printMaxConnectedComponentNodes`

U `public` deo `GraphInt.h`:

```cpp
int printMaxConnectedComponentNodes() const;
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;

    for (int i = 1; i <= 7; i++)
        graph.insertNode(i);

    graph.insertEdge(1, 2);
    graph.insertEdge(3, 2);
    graph.insertEdge(3, 4);
    graph.insertEdge(5, 6);

    cout << "Cvorovi najvece komponente: ";
    int size = graph.printMaxConnectedComponentNodes();
    cout << "\nVelicina: " << size << endl;

    return 0;
}
```

Najveca slaba komponenta je skup:

```text
{ 1, 2, 3, 4 }
```

Dozvoljen je bilo koji redosled ta cetiri cvora. Povratna vrednost i poslednja
linija moraju biti:

```text
Velicina: 4
```

Komponenta `{5, 6}` je manja, a cvor `7` je izolovan.

## Jun II 2024 - `defineOrder`

U `public` deo `GraphInt.h`:

```cpp
int* defineOrder(const int* dep, int n) const;
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;

    int dep[] = {
        2, 1,
        3, 2,
        4, 3
    };

    int* order = graph.defineOrder(dep, 6);

    cout << "Redosled: ";
    if (order != nullptr) {
        for (int i = 0; i < 4; i++)
            cout << order[i] << " ";
        delete[] order;
    }
    else {
        cout << "nije moguc";
    }
    cout << endl;

    int cycle[] = {
        2, 1,
        1, 2
    };

    int* impossible = graph.defineOrder(cycle, 4);
    cout << "Ciklus: "
         << (impossible == nullptr ? "nullptr" : "greska")
         << endl;
    delete[] impossible;

    return 0;
}
```

Ocekivani ispis:

```text
Redosled: 1 2 3 4
Ciklus: nullptr
```

Prvi primer ima jedinstven topoloski redosled.

## Jun 2024 P2 grupa B - `whichOneIsCloser`

U `public` deo `GraphInt.h`:

```cpp
int whichOneIsCloser(int a, int b, int c) const;
void ensureEdgeExists(int b, int c);
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;

    for (int i = 1; i <= 6; i++)
        graph.insertNode(i);

    graph.insertEdge(1, 2);
    graph.insertEdge(2, 4);
    graph.insertEdge(1, 3);
    graph.insertEdge(3, 5);
    graph.insertEdge(5, 6);

    int closer = graph.whichOneIsCloser(1, 4, 6);
    int farther = closer == 4 ? 6 : 4;

    cout << "Blizi cvor: " << closer << endl;
    cout << boolalpha;
    cout << "Poteg pre: "
         << (graph.findEdge(closer, farther) != nullptr)
         << endl;

    graph.ensureEdgeExists(closer, farther);

    cout << "Poteg posle: "
         << (graph.findEdge(closer, farther) != nullptr)
         << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Blizi cvor: 4
Poteg pre: false
Poteg posle: true
```

Udaljenost od `1` do `4` je `2`, a do `6` je `3`.

## Jun 2024 P2 grupa A - `pathThroughEdgeExists`

U `public` deo `GraphInt.h`:

```cpp
bool pathThroughEdgeExists(int a, int b,
                           int c, int d) const;
void ensureEdgeExists(int c, int d);
```

`main.cpp`:

```cpp
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
    graph.insertEdge(3, 4);
    graph.insertEdge(1, 5);

    cout << boolalpha;
    cout << "Kroz 2->3: "
         << graph.pathThroughEdgeExists(1, 4, 2, 3)
         << endl;

    cout << "Kroz 5->2 pre dodavanja: "
         << graph.pathThroughEdgeExists(1, 4, 5, 2)
         << endl;

    graph.ensureEdgeExists(5, 2);

    cout << "Kroz 5->2 posle dodavanja: "
         << graph.pathThroughEdgeExists(1, 4, 5, 2)
         << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Kroz 2->3: true
Kroz 5->2 pre dodavanja: false
Kroz 5->2 posle dodavanja: true
```

## Pseudokod - neusmereni poteg

U `public` deo `GraphInt.h`:

```cpp
void ensureUndirectedEdge(int u, int v);
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;
    graph.insertNode(1);
    graph.insertNode(2);

    cout << boolalpha;
    cout << "Pre 1->2: "
         << (graph.findEdge(1, 2) != nullptr) << endl;
    cout << "Pre 2->1: "
         << (graph.findEdge(2, 1) != nullptr) << endl;

    graph.ensureUndirectedEdge(1, 2);

    cout << "Posle 1->2: "
         << (graph.findEdge(1, 2) != nullptr) << endl;
    cout << "Posle 2->1: "
         << (graph.findEdge(2, 1) != nullptr) << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Pre 1->2: false
Pre 2->1: false
Posle 1->2: true
Posle 2->1: true
```

## April 2025 - `FindStation`

U `public` deo `GraphInt.h`:

```cpp
LinkedNodeInt* FindStation(int s, int g1, int g2,
                           int& noInter) const;
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;

    for (int i = 1; i <= 7; i++)
        graph.insertNode(i);

    graph.insertEdge(1, 2);
    graph.insertEdge(2, 3);
    graph.insertEdge(3, 4);
    graph.insertEdge(1, 5);
    graph.insertEdge(5, 6);

    int noInter = -1;
    LinkedNodeInt* station =
        graph.FindStation(1, 4, 6, noInter);

    cout << "Bliza stanica: "
         << (station != nullptr ? station->node : -1)
         << endl;
    cout << "Broj medjustanica: " << noInter << endl;

    station = graph.FindStation(7, 4, 6, noInter);
    cout << boolalpha;
    cout << "Nedostupan cilj: "
         << (station == nullptr) << endl;
    cout << "Broj medjustanica: " << noInter << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Bliza stanica: 6
Broj medjustanica: 1
Nedostupan cilj: true
Broj medjustanica: -1
```

Do stanice `6` postoje dva potega (`1 -> 5 -> 6`), pa postoji jedna
medjustanica.

## Septembar 2025 - `numNeighbours`

U `public` deo `GraphInt.h`:

```cpp
int numNeighbours(LinkedNodeInt* host, int n) const;
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;

    for (int i = 1; i <= 6; i++)
        graph.insertNode(i);

    graph.insertEdge(1, 2);
    graph.insertEdge(1, 3);
    graph.insertEdge(2, 4);
    graph.insertEdge(3, 4);
    graph.insertEdge(4, 5);
    graph.insertEdge(2, 6);

    cout << "Najvise 2 potega: "
         << graph.numNeighbours(graph.findNode(1), 2)
         << endl;

    cout << "Najvise 0 potega: "
         << graph.numNeighbours(graph.findNode(1), 0)
         << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Najvise 2 potega: 4
Najvise 0 potega: 0
```

Na udaljenosti najvise `2` nalaze se cvorovi `{2, 3, 4, 6}`. Cvor `4` se
broji samo jednom iako do njega vode dva puta.

## Oktobar 2025 - `Save` i `Load`

U `public` deo `GraphInt.h`:

```cpp
void Save(const char* fileName) const;
void Load(const char* fileName);
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt source;

    source.insertNode(1);
    source.insertNode(2);
    source.insertNode(3);

    source.insertEdge(1, 2);
    source.insertEdge(2, 3);

    source.findEdge(1, 2)->weight = 2.5;
    source.findEdge(2, 3)->weight = 7.0;

    const char* fileName = "graf_test.txt";
    source.Save(fileName);

    GraphAsListsInt loaded;
    loaded.Load(fileName);

    cout << boolalpha;
    cout << "Cvor 1 postoji: "
         << (loaded.findNode(1) != nullptr) << endl;
    cout << "Poteg 1->2: "
         << (loaded.findEdge(1, 2) != nullptr) << endl;
    cout << "Tezina 1->2: "
         << loaded.findEdge(1, 2)->weight << endl;
    cout << "Poteg 2->3: "
         << (loaded.findEdge(2, 3) != nullptr) << endl;
    cout << "Tezina 2->3: "
         << loaded.findEdge(2, 3)->weight << endl;
    cout << "Poteg 3->1: "
         << (loaded.findEdge(3, 1) != nullptr) << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Cvor 1 postoji: true
Poteg 1->2: true
Tezina 1->2: 2.5
Poteg 2->3: true
Tezina 2->3: 7
Poteg 3->1: false
```

Na samom kraju trenutni destruktor ispisace `Not implemented!` dva puta, po
jednom za `source` i `loaded`.

## Oktobar 2 2025 - `pathGoesThrough`

U `public` deo `GraphInt.h`:

```cpp
bool pathGoesThrough(int a, int b, int c) const;
```

`main.cpp`:

```cpp
#include <iostream>
using namespace std;

#include "GraphInt.h"

int main()
{
    GraphAsListsInt graph;

    for (int i = 1; i <= 6; i++)
        graph.insertNode(i);

    graph.insertEdge(1, 2);
    graph.insertEdge(2, 3);
    graph.insertEdge(3, 4);
    graph.insertEdge(1, 5);
    graph.insertEdge(5, 4);

    cout << boolalpha;
    cout << "Put 1->4 kroz 2: "
         << graph.pathGoesThrough(1, 2, 4)
         << endl;
    cout << "Put 1->4 kroz 6: "
         << graph.pathGoesThrough(1, 6, 4)
         << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Put 1->4 kroz 2: true
Put 1->4 kroz 6: false
```

## Oktobar 3 2025 - `pathGoesThroughEdge`

U `public` deo `GraphInt.h`:

```cpp
bool pathGoesThroughEdge(int a, int b,
                         int c, int d) const;
```

`main.cpp`:

```cpp
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
         << graph.pathGoesThroughEdge(1, 2, 3, 5)
         << endl;
    cout << "Put 1->5 kroz 2->4: "
         << graph.pathGoesThroughEdge(1, 2, 4, 5)
         << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Put 1->5 kroz 2->3: true
Put 1->5 kroz 2->4: false
```

Drugi rezultat je `false` iako put `1 -> 4 -> 5` postoji, zato sto trazeni
poteg `2 -> 4` ne postoji.
