# Main primeri za mapirane blankete

Ovi primeri su namenjeni proveri metoda posle implementacije. Koriste stvarna
imena klasa iz foldera `SP_templejti`.

Vazna napomena: `BTreeInt.h/.cpp` i `BTNodeInt.h` postoje kao fajlovi unutar
direktorijuma `CelobrojnaGomilaMinimalna`, ali nisu ukljuceni u njegov
Visual Studio projekat. Taj projekat je templejt za `BinaryMinHeapInt`, ne za
binarno stablo. Svi primeri ispod koji koriste `BTreeInt` mogu posluziti tek
kada se ti fajlovi rucno dodaju u zaseban projekat ili kada se skine pravi
template obicnog binarnog stabla.

Pravilo:

- deklaraciju trazene metode dodaj u `public` deo klase;
- deklaracije rekurzivnih pomocnih metoda dodaj u `protected`;
- implementaciju pisi u odgovarajuci `.cpp`;
- u `main.cpp` menjaj samo test-podatke i poziv metode.

## Januar 2024 - `countCloseParents`

Template: `CelobrojnoBinarnoStabloPretrage`.

Deklaracije vec postoje u `BSTreeInt.h`:

```cpp
int countCloseParents(BSTNodeInt* root, int n) const;
int countCloseParents(int n) const;
```

`main.cpp`:

```cpp
#include "BSTreeInt.h"
#include <iostream>
using namespace std;

int main()
{
    BSTreeInt tree;
    int values[] = { 10, 5, 15, 3, 8, 12, 20 };

    for (int value : values)
        tree.insert(value);

    tree.inorder();
    cout << endl;
    cout << "Broj bliskih roditelja za n=5: "
         << tree.countCloseParents(5) << endl;

    return 0;
}
```

Ocekivani ispis:

```text
3 5 8 10 12 15 20
Broj bliskih roditelja za n=5: 3
```

## Jun 2024 - `deleteLeaves` i `maxLevel`

Potreban template: obicno dinamicko binarno stablo, klasa `BTreeInt`.
Trenutno ne postoji kao zaseban Visual Studio projekat.

U `public` deo `BTreeInt.h`:

```cpp
void deleteLeaves();
int maxLevel() const;
```

Za pravljenje neuredjenog stabla u testu koristimo izvedenu klasu. To je samo
za `main`; resenje zadatka i dalje ostaje u `BTreeInt`.

```cpp
#include "BTreeInt.h"
#include <iostream>
using namespace std;

class TestBTreeInt : public BTreeInt
{
public:
    void makeExample()
    {
        root = new BTNodeInt(10);
        root->left = new BTNodeInt(5);
        root->right = new BTNodeInt(15);
        root->left->left = new BTNodeInt(3);
        root->left->right = new BTNodeInt(8);
        root->right->right = new BTNodeInt(20);
        numOfElements = 6;
    }
};

int main()
{
    TestBTreeInt tree;
    tree.makeExample();

    cout << "Pre brisanja: ";
    tree.breadthFirstSearch();
    cout << "\nNivo sa najvise cvorova: " << tree.maxLevel() << endl;

    tree.deleteLeaves();

    cout << "Posle brisanja listova: ";
    tree.breadthFirstSearch();
    cout << "\nNivo sa najvise cvorova: " << tree.maxLevel() << endl;

    return 0;
}
```

Ocekivani ispis, ako se koren nalazi na nivou `0`:

```text
Pre brisanja: 10 5 15 3 8 20
Nivo sa najvise cvorova: 2
Posle brisanja listova: 10 5 15
Nivo sa najvise cvorova: 1
```

Brisu se samo listovi koji su postojali na pocetku poziva: `3`, `8` i `20`.
Zbog toga cvorovi `5` i `15`, iako nakon brisanja postaju listovi, ostaju u
stablu.

## Jun II 2024 - `minEvenDiff`

Potreban template: obicno dinamicko binarno stablo, klasa `BTreeInt`.
Trenutno ne postoji kao zaseban Visual Studio projekat.

U `public` deo `BTreeInt.h`:

```cpp
BTNodeInt* minEvenDiff() const;
```

`main.cpp`:

```cpp
#include "BTreeInt.h"
#include <iostream>
using namespace std;

class TestBTreeInt : public BTreeInt
{
public:
    void makeExample()
    {
        root = new BTNodeInt(10);
        root->left = new BTNodeInt(6);
        root->right = new BTNodeInt(15);
        root->left->left = new BTNodeInt(2);
        root->left->right = new BTNodeInt(8);
        root->right->left = new BTNodeInt(12);
        root->right->right = new BTNodeInt(20);
        numOfElements = 7;
    }
};

int main()
{
    TestBTreeInt tree;
    tree.makeExample();

    BTNodeInt* result = tree.minEvenDiff();

    if (result != nullptr)
        cout << "Najbolji cvor: " << result->key << endl;
    else
        cout << "Stablo je prazno." << endl;

    return 0;
}
```

Originalni tekst zadatka ne iskljucuje listove iz skupa kandidata. Kod svakog
lista su oba zbira `0`, pa je najmanja razlika `0` i postoji vise jednako
dobrih rezultata.

Ako obilazis stablo sleva nadesno i najboljeg kandidata menjas samo kada
pronadjes strogo manju razliku, ocekivani ispis je:

```text
Najbolji cvor: 2
```

Ako nastavnik podrazumeva da se posmatraju samo cvorovi koji imaju potomke,
onda je za isti primer rezultat:

```text
Najbolji cvor: 6
```

Za unutrasnje cvorove razlike su: cvor `10` ima `16`, cvor `6` ima `6`, a
cvor `15` ima `8`.

## Kolokvijum P2 grupa B 2024 - `populate` i `sumInterval`

Template: `CelobrojnoBinarnoStabloPretrage`.

U `public` deo `BSTreeInt.h`:

```cpp
void populate(int* arData, int n);
int sumInterval(int min, int max) const;
```

`main.cpp`:

```cpp
#include "BSTreeInt.h"
#include <iostream>
using namespace std;

int main()
{
    BSTreeInt tree;
    int values[] = { 10, 5, 15, 3, 8, 12, 20, 8 };
    int n = sizeof(values) / sizeof(values[0]);

    tree.populate(values, n);

    cout << "Inorder: ";
    tree.inorder();
    cout << "\nSuma intervala [6, 16]: "
         << tree.sumInterval(6, 16) << endl;

    return 0;
}
```

Poslednja osmica namerno proverava zahtev da nema duplikata.

Ocekivani ispis:

```text
Inorder: 3 5 8 10 12 15 20
Suma intervala [6, 16]: 45
```

U zbir ulaze `8 + 10 + 12 + 15`.

## Kolokvijum P2 grupa A 2024 - `create` i `inorderDistance`

Template: `CelobrojnoBinarnoStabloPretrage`.

U `public` deo `BSTreeInt.h`:

```cpp
void create(int* vec, int n);
int inorderDistance(int a, int b) const;
```

`main.cpp`:

```cpp
#include "BSTreeInt.h"
#include <iostream>
using namespace std;

int main()
{
    BSTreeInt tree;
    int values[] = { 10, 5, 15, 3, 8, 12, 20 };
    int n = sizeof(values) / sizeof(values[0]);

    tree.create(values, n);

    cout << "Inorder: ";
    tree.inorder();
    cout << "\nRastojanje 5-15: "
         << tree.inorderDistance(5, 15) << endl;
    cout << "Rastojanje 5-99: "
         << tree.inorderDistance(5, 99) << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Inorder: 3 5 8 10 12 15 20
Rastojanje 5-15: 4
Rastojanje 5-99: -1
```

Izmedju `5` i `15` obilaze se cvorovi `8`, `10` i `12`, pa je rezultat
`3 + 1 = 4`. Drugi poziv vraca `-1`, jer cvor `99` ne postoji.

## April 2025 - `findDeepestLeaf`

Za test mozemo koristiti `BSTreeInt`, jer dubina lista ne zavisi od toga sto je
stablo uredjeno.

U `public` deo `BSTreeInt.h`:

```cpp
BSTNodeInt* findDeepestLeaf(BSTNodeInt* root) const;
```

`main.cpp`:

```cpp
#include "BSTreeInt.h"
#include <iostream>
using namespace std;

int main()
{
    BSTreeInt tree;
    int values[] = { 10, 5, 15, 3, 8, 2, 1 };

    for (int value : values)
        tree.insert(value);

    BSTNodeInt* result = tree.findDeepestLeaf(tree.search(10));

    if (result != nullptr)
        cout << "Najdublji list: " << result->key << endl;
    else
        cout << "Stablo je prazno." << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Najdublji list: 1
```

## Septembar 2025 - `deleteNodes`

Potreban template: obicno dinamicko binarno stablo, klasa `BTreeInt`.
Trenutno ne postoji kao zaseban Visual Studio projekat.

U `public` deo `BTreeInt.h`:

```cpp
int deleteNodes(int key, BTNodeInt* p);
```

Ukoliko metoda menja i sam koren stabla, prakticnija deklaracija je:

```cpp
int deleteNodes(int key);
```

Javna metoda bez pokazivaca tada poziva rekurzivni pomocni metod nad `root`.
Sledeci `main` koristi deklaraciju iz teksta zadatka.

```cpp
#include "BTreeInt.h"
#include <iostream>
using namespace std;

class TestBTreeInt : public BTreeInt
{
public:
    void makeExample()
    {
        root = new BTNodeInt(5);
        root->left = new BTNodeInt(5);
        root->right = new BTNodeInt(8);
        root->left->left = new BTNodeInt(3);
        root->right->left = new BTNodeInt(5);
        numOfElements = 5;
    }

    BTNodeInt* getRoot() const
    {
        return root;
    }
};

int main()
{
    TestBTreeInt tree;
    tree.makeExample();

    cout << "Pre: ";
    tree.breadthFirstSearch();

    int deleted = tree.deleteNodes(5, tree.getRoot());

    cout << "\nObrisano: " << deleted << endl;
    cout << "Posle: ";
    tree.breadthFirstSearch();
    cout << endl;

    return 0;
}
```

Obavezno testiraj posebno slucajeve kada trazeni cvor ima nula, jedan i dva
potomka.

Ocekivani ispis za dati `main`:

```text
Pre: 5 5 8 3 5
Obrisano: 2
Posle: 5 3 8
```

Koren `5` ostaje jer ima dva potomka. Levi cvor `5`, koji ima jednog potomka,
zamenjuje se cvorom `3`, dok se poslednji cvor `5`, koji je list, brise.

## Oktobar 2025 - `DegreeOfKinship`

Blanket koristi klase za porodicno stablo i `Osoba`, kojih nema u trenutnom
folderu sa template-ima. Zato se poziv moze zapisati samo ovako:

```cpp
int main()
{
    PorodicnoStablo tree;

    // Ovde se stablo formira metodama koje postoje u dobijenom template-u.
    Osoba* osoba1 = tree.find("Ana");
    Osoba* osoba2 = tree.find("Marko");

    cout << tree.DegreeOfKinship(osoba1, osoba2) << endl;
    return 0;
}
```

Ovaj `main` treba prilagoditi stvarnim imenima klase i metode za pretragu kada
se doda odgovarajuci template.

Za ovaj kostur ne postoji odredjen ocekivani ispis, jer stablo nije formirano i
ne znamo gde se osobe `Ana` i `Marko` nalaze. Na primer, ako je put u stablu
`Ana -> Petar -> Marko`, ocekivani rezultat metode bio bi:

```text
2
```

## Oktobar 2 2025 - `getDeepestEvenParent`

Template: `CelobrojnoBinarnoStabloPretrage`.

U `public` deo `BSTreeInt.h`:

```cpp
BSTNodeInt* getDeepestEvenParent(BSTNodeInt* root) const;
```

`main.cpp`:

```cpp
#include "BSTreeInt.h"
#include <iostream>
using namespace std;

int main()
{
    BSTreeInt tree;
    int values[] = { 10, 5, 16, 3, 8, 14, 20, 7 };

    for (int value : values)
        tree.insert(value);

    BSTNodeInt* result =
        tree.getDeepestEvenParent(tree.search(10));

    if (result != nullptr)
        cout << "Najdublji paran roditelj: " << result->key << endl;
    else
        cout << "Takav cvor ne postoji." << endl;

    return 0;
}
```

Ocekivani ispis:

```text
Najdublji paran roditelj: 8
```

## Oktobar 3 2025 - `maxLevelCount`

Potreban template: obicno dinamicko binarno stablo, klasa `BTreeInt`.
Trenutno ne postoji kao zaseban Visual Studio projekat.

U `public` deo `BTreeInt.h`:

```cpp
int maxLevelCount() const;
```

`main.cpp`:

```cpp
#include "BTreeInt.h"
#include <iostream>
using namespace std;

class TestBTreeInt : public BTreeInt
{
public:
    void makeExample()
    {
        root = new BTNodeInt(10);
        root->left = new BTNodeInt(5);
        root->right = new BTNodeInt(15);
        root->left->left = new BTNodeInt(3);
        root->left->right = new BTNodeInt(8);
        root->right->left = new BTNodeInt(12);
        root->right->right = new BTNodeInt(20);
        numOfElements = 7;
    }
};

int main()
{
    TestBTreeInt tree;
    tree.makeExample();

    tree.breadthFirstSearch();
    cout << "\nNivo sa najvise cvorova: "
         << tree.maxLevelCount() << endl;

    return 0;
}
```

Ocekivani ispis, ako se koren nalazi na nivou `0`:

```text
10 5 15 3 8 12 20
Nivo sa najvise cvorova: 2
```

## Grafovi

Za grafovske zadatke jos ne treba uciti napamet izmisljeni `main`, jer u
folderu nema grafovskog template-a. Konstrukcija grafa zavisi od stvarnih
metoda kao sto su `insertNode`, `insertEdge`, `findNode` i od toga da li je graf
usmeren ili tezinski.

Kada se doda graph template, za svaki mapirani grafovski zadatak treba dopisati:

1. tacnu deklaraciju u klasi;
2. formiranje malog grafa od 5-7 cvorova;
3. pozitivan test gde put postoji;
4. negativan test gde put ne postoji;
5. ispis povratne vrednosti ili pronadjenog puta.
