# Detaljno objašnjenje urađenih zadataka - stabla

Ovaj vodič objašnjava postojeće implementacije iz projekta
`CelobrojnoBinarnoStabloPretrage`. Kod nije menjan niti prepravljan. Kada se
ponašanje trenutne implementacije razlikuje od formulacije zadatka ili od
ranije zapisanog očekivanog rezultata, ovde je opisano ono što kod zaista radi.

Glavni fajlovi:

- [`BSTreeInt.h`](CelobrojnoBinarnoStabloPretrage/CelobrojnoBinarnoStabloPretrage/BSTreeInt.h)
- [`BSTreeInt.cpp`](CelobrojnoBinarnoStabloPretrage/CelobrojnoBinarnoStabloPretrage/BSTreeInt.cpp)
- [`BSTNodeInt.h`](CelobrojnoBinarnoStabloPretrage/CelobrojnoBinarnoStabloPretrage/BSTNodeInt.h)
- [`main.cpp`](CelobrojnoBinarnoStabloPretrage/CelobrojnoBinarnoStabloPretrage/main.cpp)
- [`main_primeri_za_blankete.md`](main_primeri_za_blankete.md)

## Sadržaj

1. [Osnova templejta](#osnova-templejta)
2. [Januar 2024 - `countCloseParents`](#1-januar-2024---countcloseparents)
3. [Jun 2024 - `deleteLeaves` i `maxLevel`](#2-jun-2024---deleteleaves-i-maxlevel)
4. [Jun II 2024 - `minEvenDiff`](#3-jun-ii-2024---minevendiff)
5. [P2 grupa B 2024 - `populate` i `sumInterval`](#4-p2-grupa-b-2024---populate-i-suminterval)
6. [P2 grupa A 2024 - `create` i `inorderDistance`](#5-p2-grupa-a-2024---create-i-inorderdistance)
7. [April 2025 - `findDeepestLeaf`](#6-april-2025---finddeepestleaf)
8. [Oktobar II 2025 - `getDeepestEvenParent`](#7-oktobar-ii-2025---getdeepestevenparent)
9. [Oktobar III 2025 - `maxLevelCount`](#8-oktobar-iii-2025---maxlevelcount)
10. [Januar 2026 - `sumUpThePath`](#9-januar-2026---sumupthepath)
11. [Decembarski rok 2026 - `maxDiffOfEvenNodes`](#10-decembarski-rok-2026---maxdiffofevennodes)

## Osnova templejta

Klasa `BSTreeInt` predstavlja dinamičko celobrojno binarno stablo pretrage.
Svaki čvor je objekat klase `BSTNodeInt` i sadrži:

```cpp
int key;
BSTNodeInt* left, * right;
```

Za svaki čvor važi standardno BST pravilo: manje vrednosti nalaze se levo, a
veće vrednosti desno. Metoda `insert` u ovoj implementaciji dozvoljava
duplikate i smešta ih ulevo, dok metoda `add` prvo poziva `isInTree` i zato
duplikat ne dodaje.

Bitni članovi klase su:

```cpp
BSTNodeInt* root;
long numOfElements;
```

- `root` pokazuje na koren stabla.
- `numOfElements` čuva broj čvorova i koristi se i kao kapacitet pomoćnog reda.
- visina stabla se u nastavku označava sa `h`;
- broj čvorova obrađenog stabla ili podstabla označava se sa `n`;
- najveći broj čvorova na jednom nivou označava se sa `w`.

Neki blanketi traže obično, neuređeno binarno stablo. Pošto zaseban
`BTreeInt` projekat nije uključen u solution, odgovarajuće metode su u
postojećem radu implementirane u `BSTreeInt`. Njihov algoritam uglavnom ne
koristi uređenost stabla, pa isti obilazak radi i nad ručno formiranim običnim
binarnim stablom.

---

## 1. Januar 2024 - `countCloseParents`

### Zahtev zadatka

Potrebno je prebrojati roditeljske čvorove kod kojih se ključ roditelja od
ključa svakog neposrednog potomka razlikuje najviše za zadato `n`.

### Korišćene metode

```cpp
int countCloseParents(BSTNodeInt* root, int n) const;
int countCloseParents(int n) const;
```

Druga metoda je javni omotač: poziva prvu metodu nad korenom celog stabla.

### Ključni postojeći kod

```cpp
if (ptr == nullptr) {
    return 0;
}
if (ptr->right and ptr->left) {
    if (n >= (ptr->getKey() - ptr->left->getKey()) &&
        n >= (ptr->right->getKey() - ptr->getKey())) {
        count += 1;
    }
    levi = root->left;
    desni = root->right;
    return count
        + countCloseParents(levi, n)
        + countCloseParents(desni, n);
}
```

Za čvor sa samo desnim ili samo levim detetom kod proverava samo postojeće
dete, a list vraća `0`.

### Tok izvršavanja

1. Ako je pokazivač `root` jednak `nullptr`, podstablo je prazno i doprinos
   rezultatu je nula.
2. Ako čvor ima oba deteta, računaju se dve razlike:
   - `roditelj - levo dete`;
   - `desno dete - roditelj`.
3. Ovakav smer oduzimanja koristi BST osobinu: levo dete ima manji, a desno
   dete veći ključ.
4. Ako su obe razlike najviše `n`, lokalni `count` postaje `1`.
5. Metoda se rekurzivno poziva za levo i desno podstablo i sabira njihove
   rezultate.
6. Kada postoji samo jedno dete, proverava se samo ta veza i nastavlja se kroz
   to podstablo.
7. List nije roditelj, pa vraća `0`.

### Uloga promenljivih

- `ptr` je lokalni pokazivač na trenutno obrađeni čvor.
- `levi` i `desni` pamte korene podstabala za sledeće rekurzivne pozive.
- `count` je lokalni rezultat za trenutni čvor: `0` ili `1`.
- `n` je najveća dozvoljena razlika između roditelja i neposrednog deteta.

### Zašto rekurzija

Uslov se proverava nezavisno za svaki čvor, a ukupan rezultat je zbir rezultata
levog i desnog podstabla. To direktno prati rekurzivnu strukturu stabla:

```text
rezultat podstabla =
rezultat korena + rezultat levog + rezultat desnog
```

### Prolazak kroz primer

Za umetanje:

```cpp
int values[] = { 10, 5, 15, 3, 8, 12, 20 };
```

dobija se:

```text
        10
       /  \
      5    15
     / \   / \
    3   8 12 20
```

Za `n = 5`:

- čvor `10`: razlike su `10 - 5 = 5` i `15 - 10 = 5`;
- čvor `5`: razlike su `5 - 3 = 2` i `8 - 5 = 3`;
- čvor `15`: razlike su `15 - 12 = 3` i `20 - 15 = 5`.

Sva tri roditelja ispunjavaju uslov, pa metoda vraća `3`.

### Složenost

- vreme: `O(n)`, jer se svaki čvor posećuje jednom;
- dodatni prostor: `O(h)` zbog steka rekurzivnih poziva.

### Granični slučajevi trenutnog koda

- prazno stablo vraća `0`;
- stablo sa samo jednim čvorom vraća `0`;
- čvor sa jednim detetom može biti prebrojan;
- za negativno `n` nijedna pozitivna BST razlika neće zadovoljiti uslov;
- računanje razlika se oslanja na BST poredak ključeva.

---

## 2. Jun 2024 - `deleteLeaves` i `maxLevel`

### Prilagođavanje templejtu

Blanket traži metode nad običnim dinamičkim binarnim stablom. U postojećem
kodu metode su dodate u `BSTreeInt`, ali sam postupak brisanja listova i BFS
brojanje nivoa ne koriste BST pretragu niti poređenje ključeva.

### Korišćene metode

```cpp
void deleteLeaves();
void deleteLeaves(BSTNodeInt* ptr,
                  BSTNodeInt* ptr_parent,
                  bool isright);
int maxLevel() const;
```

### `deleteLeaves` - ključni postojeći kod

```cpp
else if (!ptr->right && !ptr->left) {
    delete ptr;
    if (isright) {
        ptr_parent->right = nullptr;
    }
    else {
        ptr_parent->left = nullptr;
    }
    numOfElements--;
    return;
}
```

Javna metoda posebno obrađuje koren:

```cpp
if (ptr != nullptr && (!ptr->right && !ptr->left)) {
    delete ptr;
    root = nullptr;
    numOfElements--;
    return;
}

deleteLeaves(ptr->right, ptr, true);
deleteLeaves(ptr->left, ptr, false);
```

### Kako radi brisanje

1. Javna metoda proverava da li je stablo prazno.
2. Ako je sam koren list, briše ga i postavlja `root = nullptr`.
3. U ostalim slučajevima pomoćna metoda dobija:
   - trenutni čvor;
   - njegovog roditelja;
   - informaciju da li je trenutni čvor desno dete.
4. Kada naiđe na list, oslobađa ga pomoću `delete`.
5. Roditeljski pokazivač se postavlja na `nullptr`, čime se prekida veza ka
   obrisanom objektu.
6. `numOfElements` se smanjuje za jedan.
7. Za unutrašnji čvor rekurzija se nastavlja ka njegovoj deci.

Kod prvo poziva desno, pa levo podstablo. Taj redosled ne utiče na skup
obrisanih listova.

### Zašto se prosleđuje roditelj

Posle `delete ptr` mora se promeniti pokazivač koji je ranije pokazivao na
obrisani čvor. Pošto čvor nema pokazivač na roditelja, pomoćna metoda eksplicitno
prima `ptr_parent`. Parametar `isright` govori da li treba postaviti
`ptr_parent->right` ili `ptr_parent->left` na `nullptr`.

### Koji listovi se brišu

Metoda briše listove koji postoje kada rekurzija dođe do njih. Unutrašnji čvor
se ne proverava ponovo nakon obrade svoje dece. Zato čvor koji tokom poziva
ostane bez dece ne biva obrisan u istom pozivu.

### `maxLevel` - ključni postojeći kod

```cpp
int currentlevel = 0;
int nodesincurrentlevel = 1;
int maxlevel = 0;
int nodesinmaxlevel = 0;

QueueAsArrayBSTNodeInt queue(numOfElements);
queue.enqueue(root);

while (!queue.isEmpty()) {
    int nodesinnextlevel = 0;
    for (int i = 0; i < nodesincurrentlevel; i++) {
        ptr = queue.dequeue();

        if (ptr->right) {
            queue.enqueue(ptr->right);
            nodesinnextlevel++;
        }
        if (ptr->left) {
            queue.enqueue(ptr->left);
            nodesinnextlevel++;
        }
    }

    if (nodesinmaxlevel < nodesincurrentlevel) {
        nodesinmaxlevel = nodesincurrentlevel;
        maxlevel = currentlevel;
    }

    nodesincurrentlevel = nodesinnextlevel;
    currentlevel++;
}
```

### Kako se određuje nivo sa najviše čvorova

Red sadrži čvorove koji tek treba da se obrade. Promenljiva
`nodesincurrentlevel` govori koliko čvorova pripada trenutnom nivou, pa `for`
petlja skida tačno toliko elemenata. Njihova deca se dodaju u red i broje kroz
`nodesinnextlevel`.

Posle obrade nivoa:

- trenutni broj se poredi sa do sada najvećim;
- ako je strogo veći, pamti se indeks trenutnog nivoa;
- broj čvorova sledećeg nivoa postaje novi `nodesincurrentlevel`.

Koren je na nivou `0`.

### Prolazak kroz primer

Početno stablo:

```text
        10
       /  \
      5    15
     / \     \
    3   8     20
```

Brojevi čvorova po nivoima su `1`, `2`, `3`, pa `maxLevel()` vraća `2`.

`deleteLeaves()` briše `3`, `8` i `20`. Čvorovi `5` i `15` postaju listovi,
ali ostaju u stablu. Posle brisanja nivoi sadrže `1` i `2` čvora, pa
`maxLevel()` vraća `1`.

### Složenost

Za obe metode:

- vreme: `O(n)`;
- `deleteLeaves`: dodatni prostor `O(h)` zbog rekurzije;
- `maxLevel`: dodatni prostor `O(w)` zbog reda.

### Granični slučajevi trenutnog koda

- `deleteLeaves()` nad praznim stablom ne radi ništa;
- ako je koren jedini čvor, briše se i stablo postaje prazno;
- `maxLevel()` nad praznim stablom vraća `-1`;
- kod izjednačenja broja čvorova ostaje ranije pronađen, plići nivo, jer se
  maksimum menja samo kada je novi broj strogo veći.

---

## 3. Jun II 2024 - `minEvenDiff`

### Zahtev zadatka

Traži se čvor kod kog se zbir parnih ključeva u levom podstablu i zbir parnih
ključeva u desnom podstablu najmanje razlikuju.

### Prilagođavanje templejtu

Originalni zadatak govori o običnom binarnom stablu. Postojeća implementacija
je u `BSTreeInt`, ali algoritam ne koristi poredak ključeva. Kao kandidati se u
trenutnom kodu posmatraju samo čvorovi koji imaju i levo i desno dete.

### Korišćene metode

```cpp
BSTNodeInt* minEvenDiff() const;
int minEvenDiff(BSTNodeInt* ptr,
                BSTNodeInt*& best,
                int& minDiff,
                bool& found) const;
```

### Ključni postojeći kod

```cpp
zbirulevom = minEvenDiff(ptr->left, best, minDiff, found);
zbirudesnom = minEvenDiff(ptr->right, best, minDiff, found);

diff = abs(zbirudesnom - zbirulevom);

if (ptr->right && ptr->left && !found) {
    minDiff = diff;
    best = ptr;
    found = true;
}

if (ptr->right && ptr->left && diff < minDiff) {
    minDiff = diff;
    best = ptr;
}

if (ptr->getKey() % 2 == 0) {
    return ptr->getKey() + zbirulevom + zbirudesnom;
}
return zbirudesnom + zbirulevom;
```

### Zašto je korišćen postorder

Da bi se za trenutni čvor izračunala razlika, prvo moraju biti poznati zbirovi
parnih ključeva oba njegova podstabla. Zato se prvo obrađuju levo i desno
podstablo, a tek zatim trenutni čvor. To je postorder obrazac.

Povratna vrednost pomoćne metode ima dvostruku ulogu:

- roditelju vraća zbir svih parnih ključeva trenutnog podstabla;
- usput preko referenci `best`, `minDiff` i `found` ažurira globalno najbolji
  rezultat za taj jedan poziv.

### Uloga promenljivih

- `zbirulevom` je zbir parnih ključeva u levom podstablu.
- `zbirudesnom` je zbir parnih ključeva u desnom podstablu.
- `diff` je apsolutna razlika ova dva zbira.
- `best` pokazuje na trenutno najbolji čvor.
- `minDiff` čuva njegovu razliku.
- `found` označava da je pronađen prvi kandidat sa oba deteta.

`found` je potreban zato što je početna vrednost `minDiff` jednaka nuli. Bez
posebne oznake prvi stvarni kandidat sa pozitivnom razlikom ne bi mogao da
postane minimum.

### Prolazak kroz dokumentovani primer

Za stablo:

```text
          10
        /    \
       6      15
      / \    /  \
     2   8  12  20
```

unutrašnji kandidati imaju:

- čvor `6`: levo `2`, desno `8`, razlika `6`;
- čvor `15`: levo `12`, desno `20`, razlika `8`;
- čvor `10`: levo `6 + 2 + 8 = 16`, desno `12 + 20 = 32`, razlika `16`.

Najmanju razliku ima čvor `6`.

### Složenost

- vreme: `O(n)`, jer se svaki čvor obrađuje jednom;
- dodatni prostor: `O(h)` zbog rekurzivnog steka.

### Granični slučajevi trenutnog koda

- prazno stablo vraća `nullptr`;
- ako nijedan čvor nema oba deteta, `best` ostaje `nullptr`;
- listovi i čvorovi sa samo jednim detetom doprinose zbiru, ali nisu kandidati;
- kod jednake razlike zadržava se ranije pronađen kandidat, jer se `best`
  menja samo za `diff < minDiff`;
- zbog postorder obilaska ranije se razmatraju dublji čvorovi, prvo u levom
  podstablu.

---

## 4. P2 grupa B 2024 - `populate` i `sumInterval`

### Zahtev zadatka

`populate` treba redom da umetne elemente niza u prazno uređeno stablo bez
duplikata. `sumInterval` treba da vrati zbir ključeva koji pripadaju zatvorenom
intervalu `[min, max]`.

### Korišćene metode

```cpp
void populate(int* arData, int n);
int sumInterval(int min, int max) const;
void sumInterval(BSTNodeInt* ptr,
                 int min,
                 int max,
                 int& sum) const;
```

### Postojeći kod za `populate`

```cpp
void BSTreeInt::populate(int* arData, int n)
{
    for (int i = 0; i < n; i++) {
        add(arData[i]);
    }
}
```

Metoda `add` najpre proverava `isInTree(el)`. Ako ključ već postoji, odmah se
vraća, pa `populate` ne dodaje duplikate.

### Postojeći kod za `sumInterval`

```cpp
void BSTreeInt::sumInterval(BSTNodeInt* ptr,
                            int min,
                            int max,
                            int& sum) const
{
    if (ptr != nullptr) {
        if (ptr->getKey() <= max &&
            ptr->getKey() >= min) {
            sum += ptr->getKey();
        }
        sumInterval(ptr->left, min, max, sum);
        sumInterval(ptr->right, min, max, sum);
    }
}

int BSTreeInt::sumInterval(int min, int max) const
{
    int sum = 0;
    sumInterval(root, min, max, sum);
    return sum;
}
```

### Tok izvršavanja

`populate` prolazi kroz niz sleva nadesno. Redosled elemenata je bitan jer on
određuje oblik BST-a. Za svaki element poziva `add`, pa se element ili umeće
na odgovarajuće mesto ili preskače kao duplikat.

`sumInterval`:

1. pravi akumulator `sum = 0`;
2. obilazi trenutno podstablo;
3. ako je ključ između granica, uključujući granice, dodaje ga zbiru;
4. u svakom slučaju poziva sebe za levo i desno dete;
5. po završetku javna metoda vraća akumulirani zbir.

### Zašto rekurzija

Svaki čvor mora da se proveri, a ista operacija se primenjuje nad oba
podstabla. Referenca `int& sum` omogućava da svi rekurzivni pozivi ažuriraju
isti akumulator.

### Prolazak kroz primer

Za:

```cpp
int values[] = { 10, 5, 15, 3, 8, 12, 20, 8 };
tree.populate(values, 8);
```

druga vrednost `8` se ne dodaje. Inorder ispis je:

```text
3 5 8 10 12 15 20
```

Za interval `[6, 16]` u zbir ulaze `8`, `10`, `12` i `15`, pa je rezultat:

```text
8 + 10 + 12 + 15 = 45
```

### Složenost

`populate`:

- svaki `add` prvo pretražuje, a zatim po potrebi ponovo prolazi putanju za
  umetanje;
- prosečno vreme za `n` elemenata u približno uravnoteženom stablu je
  `O(n log n)`;
- najgore vreme za degenerisano stablo je `O(n^2)`;
- dodatni prostor same metode je `O(1)`, ne računajući nove čvorove.

`sumInterval`:

- vreme: `O(n)`, jer trenutni kod obilazi oba podstabla bez BST skraćivanja;
- dodatni prostor: `O(h)`.

### Granični slučajevi trenutnog koda

- `n <= 0` znači da `populate` ne umeće nijedan element;
- `arData` se ne proverava na `nullptr`;
- prazan intervalski zbir nad praznim stablom je `0`;
- ako je `min > max`, nijedan ključ ne ispunjava oba uslova i rezultat je `0`;
- ključevi jednaki granicama ulaze u zbir.

---

## 5. P2 grupa A 2024 - `create` i `inorderDistance`

### Zahtev zadatka

`create` formira stablo dodavanjem elemenata vektora zadatim redom.
`inorderDistance` jednim inorder obilaskom određuje rastojanje između dva
ključa.

### Korišćene metode

```cpp
void create(int* vec, int n);
int inorderDistance(int a, int b) const;
void inorderDistance(BSTNodeInt* ptr,
                     bool& foundA,
                     bool& foundB,
                     int a,
                     int b,
                     int& length) const;
```

### Postojeći kod za `create`

```cpp
void BSTreeInt::create(int* vec, int n)
{
    for (int i = 0; i < n; i++) {
        insert(vec[i]);
    }
}
```

Za razliku od `populate`, ova metoda koristi `insert`, koji ne proverava
postojanje ključa. Jednaki ključevi se u `insert` spuštaju ulevo.

### Postojeći kod za `inorderDistance`

```cpp
if (a > b) {
    int pom = a;
    a = b;
    b = pom;
}

inorderDistance(root, foundA, foundB, a, b, length);

if (foundA && foundB) {
    return length + 1;
}
return -1;
```

Pomoćna metoda:

```cpp
inorderDistance(ptr->left, foundA, foundB,
                a, b, length);

if (ptr->getKey() == a) {
    foundA = true;
}
if (ptr->getKey() == b) {
    foundB = true;
}
if (foundA && !foundB) {
    length++;
}

inorderDistance(ptr->right, foundA, foundB,
                a, b, length);
```

### Tok izvršavanja

1. Pošto inorder obilazak BST-a daje ključeve u neopadajućem redosledu, javna
   metoda obezbeđuje da je `a <= b`.
2. Pomoćna metoda radi standardni inorder: levo, čvor, desno.
3. Kada naiđe na `a`, postavlja `foundA = true`.
4. Kada naiđe na `b`, postavlja `foundB = true`.
5. Dok je `a` već pronađen, a `b` još nije, uvećava `length`.
6. Ako su na kraju pronađena oba ključa, vraća `length + 1`.
7. Ako bar jedan nedostaje, vraća `-1`.

### Uloga promenljivih

- `foundA` označava da je inorder stigao do manjeg traženog ključa.
- `foundB` označava da je stigao do većeg ključa.
- `length` broji čvorove u delu obilaska nakon pronalaska `a`, dok `b` još
  nije pronađen.
- `pom` služi za zamenu argumenata ako su prosleđeni obrnutim redom.

### Prolazak kroz postojeći `main.cpp` primer

Stablo napravljeno od:

```cpp
{ 10, 5, 15, 3, 8, 12, 20 }
```

ima inorder:

```text
3 5 8 10 12 15 20
```

Za poziv `inorderDistance(5, 15)` trenutni kod uvećava `length` kod ključeva
`5`, `8`, `10` i `12`. Zato `length` postaje `4`, a javna metoda vraća
`length + 1`, odnosno `5`.

Raniji pomoćni dokument navodi očekivanje `4`, ali trenutna implementacija za
ovaj konkretan poziv vraća `5`. Ovde se ne menja algoritam; beleži se njegovo
stvarno ponašanje.

Poziv `inorderDistance(5, 99)` vraća `-1`, jer `foundB` ostaje `false`.

### Zašto inorder

Zadatak rastojanje definiše upravo redosledom inorder obilaska. U BST-u je taj
redosled sortiran, pa se nakon numeričkog uređivanja `a` i `b` prvi traženi
ključ očekuje pre drugog.

### Složenost

- `create`: prosečno `O(n log n)`, najgore `O(n^2)`;
- `inorderDistance`: vreme `O(n)`, jer kod ne prekida obilazak nakon drugog
  ključa;
- dodatni prostor za inorder: `O(h)`.

### Granični slučajevi trenutnog koda

- ako jedan ili oba ključa ne postoje, rezultat je `-1`;
- ako je `a > b`, vrednosti se zamene;
- ako je `a == b` i ključ postoji, oba indikatora se postave u istom čvoru,
  `length` ostaje `0`, pa rezultat iznosi `1`;
- duplikati su mogući zato što `create` koristi `insert`; indikatori ostaju
  postavljeni nakon prvih odgovarajućih pojavljivanja.

---

## 6. April 2025 - `findDeepestLeaf`

### Zahtev zadatka

Potrebno je vratiti pokazivač na najdublji list u podstablu čiji je koren
prosleđen metodi.

### Prilagođavanje templejtu

Pronalaženje najdubljeg lista ne zavisi od BST poretka, pa je zadatak za
binarno stablo implementiran i testiran kroz `BSTreeInt`.

### Korišćene metode

```cpp
BSTNodeInt* findDeepestLeaf(BSTNodeInt* root) const;
void findDeepestLeaf(BSTNodeInt* ptr,
                     BSTNodeInt*& rez,
                     int& depth,
                     int& maxdepth) const;
```

Iako je pomoćna metoda deklarisana u obliku koji liči na rekurzivnu pomoćnu
funkciju, njena trenutna implementacija koristi BFS i ne poziva samu sebe.

### Ključni postojeći kod

```cpp
QueueAsArrayBSTNodeInt q(numOfElements);
q.enqueue(ptr);
int elincurrent = 1;
int elinnext = 0;

while (!q.isEmpty()) {
    for (int i = 0; i < elincurrent; i++) {
        a = q.dequeue();

        if (a->left) {
            elinnext++;
            q.enqueue(a->left);
        }
        if (a->right) {
            elinnext++;
            q.enqueue(a->right);
        }
        if (!a->right && !a->left &&
            depth >= maxdepth) {
            maxdepth = depth;
            rez = a;
        }
    }
    elincurrent = elinnext;
    elinnext = 0;
    depth++;
}
```

### Tok izvršavanja

1. Javna metoda za `nullptr` odmah vraća `nullptr`.
2. `depth` i `maxdepth` počinju od nule.
3. U red se stavlja prosleđeni koren podstabla.
4. `elincurrent` čuva broj čvorova trenutnog nivoa.
5. Deca tih čvorova se dodaju u red i broje kroz `elinnext`.
6. Čvor bez dece je list.
7. Ako je njegova dubina veća ili jednaka do sada najvećoj, `rez` se postavlja
   na taj list.
8. Kada se obradi ceo nivo, prelazi se na sledeći i `depth` se uvećava.

### Zašto BFS

BFS prirodno obrađuje stablo nivo po nivo. Poslednji nivo na kom se pronađe
list predstavlja najveću dubinu. Nema potrebe posebno računati visinu svakog
podstabla.

### Prolazak kroz primer

Za umetanje:

```cpp
{ 10, 5, 15, 3, 8, 2, 1 }
```

putanja `10 -> 5 -> 3 -> 2 -> 1` sadrži najdublji list `1`. Metoda pozvana sa
`tree.search(10)` vraća pokazivač na taj čvor.

### Složenost

- vreme: `O(n)` za broj čvorova prosleđenog podstabla;
- dodatni prostor: `O(w)` zbog BFS reda.

### Granični slučajevi trenutnog koda

- za `nullptr` vraća `nullptr`;
- ako je prosleđeni čvor list, vraća taj isti čvor;
- uslov je `depth >= maxdepth`, pa kod više listova na istoj najvećoj dubini
  rezultat postaje poslednji takav list u BFS redosledu;
- deca se u red dodaju prvo levo, pa desno, pa će na istom nivou kasnije
  obrađeni desni list zameniti raniji levi list.

---

## 7. Oktobar II 2025 - `getDeepestEvenParent`

### Zahtev zadatka

Traži se najdublji čvor sa parnim ključem koji je roditelj, odnosno ima bar
jedno dete.

### Korišćene metode

```cpp
BSTNodeInt* getDeepestEvenParent(BSTNodeInt* root);
void getDeepestEvenParent(BSTNodeInt* root,
                          BSTNodeInt*& rez);
```

### Ključni postojeći kod

```cpp
if (root == nullptr ||
    (root->right == nullptr &&
     root->left == nullptr)) {
    return nullptr;
}

getDeepestEvenParent(root, rez);
```

BFS deo:

```cpp
if (ptr->getKey() % 2 == 0 &&
    (ptr->right != nullptr ||
     ptr->left != nullptr) &&
    depth >= maxdepth) {
    maxdepth = depth;
    rez = ptr;
}

if (ptr->right) {
    q.enqueue(ptr->right);
    nodesinnextlevel++;
}
if (ptr->left) {
    q.enqueue(ptr->left);
    nodesinnextlevel++;
}
```

### Tok izvršavanja

1. Prazno podstablo i podstablo koje se sastoji samo od lista odmah vraćaju
   `nullptr`.
2. Koren podstabla se stavlja u red.
3. Čvor je kandidat ako:
   - ključ je paran;
   - ima levo ili desno dete.
4. `depth` označava nivo koji se trenutno obrađuje.
5. Ako je kandidat na dubini većoj ili jednakoj od zapamćene, upisuje se u
   `rez`.
6. Deca se dodaju u red i obrađuju na sledećem nivou.

### Uloga promenljivih

- `rez` je pokazivač na trenutno izabrani paran roditeljski čvor.
- `depth` je indeks trenutnog nivoa.
- `maxdepth` je dubina trenutno izabranog kandidata.
- `nodesincurrentlevel` i `nodesinnextlevel` odvajaju nivoe u BFS-u.

### Prolazak kroz primer

Za:

```cpp
{ 10, 5, 16, 3, 8, 14, 20, 7 }
```

parni roditelji su:

- `10` na nivou `0`;
- `16` na nivou `1`;
- `8` na nivou `2`, jer ima dete `7`.

Najdublji je `8`, pa metoda vraća pokazivač na taj čvor.

### Složenost

- vreme: `O(n)`;
- dodatni prostor: `O(w)`.

### Granični slučajevi trenutnog koda

- prazan koren vraća `nullptr`;
- prosleđeni koren koji je list vraća `nullptr`, čak i ako je paran;
- ako nijedan roditeljski čvor nije paran, rezultat ostaje `nullptr`;
- kod izjednačene dubine kandidat se menja zbog uslova `>=`;
- deca se dodaju prvo desno, pa levo, zato će među kandidatima na istom nivou
  kasnije obrađen levi kandidat zameniti raniji desni.

---

## 8. Oktobar III 2025 - `maxLevelCount`

### Zahtev zadatka

Potrebno je odrediti nivo koji sadrži najveći broj čvorova.

### Prilagođavanje templejtu

Zadatak je namenjen običnom binarnom stablu, ali je implementiran u
`BSTreeInt`. BFS ne koristi uređenost stabla.

### Korišćena metoda

```cpp
int maxLevelCount();
```

Iako naziv može da sugeriše vraćanje broja čvorova, trenutna implementacija
vraća indeks nivoa sa najvećim brojem čvorova.

### Ključni postojeći kod

```cpp
QueueAsArrayBSTNodeInt q(numOfElements);
q.enqueue(root);
int nodesincurrent = 1;
int nodesinnext = 0;
int level = 0;
int maxlevel = 0;
int maxnodes = 0;

while (!q.isEmpty()) {
    for (int i = 0; i < nodesincurrent; i++) {
        ptr = q.dequeue();

        if (nodesincurrent > maxnodes) {
            maxlevel = level;
            maxnodes = nodesincurrent;
        }

        if (ptr->left) {
            q.enqueue(ptr->left);
            nodesinnext++;
        }
        if (ptr->right) {
            q.enqueue(ptr->right);
            nodesinnext++;
        }
    }

    nodesincurrent = nodesinnext;
    nodesinnext = 0;
    level++;
}
```

### Tok izvršavanja

`nodesincurrent` unapred govori koliko puta treba skinuti čvor iz reda da bi
se završio trenutni nivo. Sva pronađena deca čine sledeći nivo i broje se u
`nodesinnext`.

Poređenje `nodesincurrent > maxnodes` nalazi se unutar `for` petlje, ali je
`nodesincurrent` konstantan tokom obrade tog nivoa. Prvi čvor nivoa zato
obavlja stvarno ažuriranje, a ostala ponavljanja proveravaju isti uslov.

### Prolazak kroz primer

Za potpuno stablo sa nivoima:

```text
nivo 0: 10
nivo 1: 5 15
nivo 2: 3 8 12 20
```

brojevi čvorova su `1`, `2` i `4`. Najveći broj je na nivou `2`, pa metoda
vraća `2`.

### Zašto BFS

Tražena veličina pripada celom nivou, a BFS već grupiše čvorove prema
udaljenosti od korena. Brojači omogućavaju da se nivo odredi bez posebnih
oznaka u redu.

### Složenost

- vreme: `O(n)`;
- dodatni prostor: `O(w)`.

### Granični slučajevi trenutnog koda

- kod izjednačenja ostaje raniji, plići nivo, jer se koristi strogo `>`;
- za stablo sa jednim čvorom vraća `0`;
- metoda nema proveru `root == nullptr` pre `q.enqueue(root)`;
- nad praznim stablom trenutni kod može iz reda dobiti `nullptr` i zatim
  pristupiti `ptr->left`, pa taj slučaj nije bezbedno obrađen.

---

## 9. Januar 2026 - `sumUpThePath`

### Zahtev zadatka

Od prosleđenog čvora BST-a treba pratiti putanju do ključa `destKey` i sabrati
ključeve svih posećenih čvorova. Ako ključ nije u tom podstablu, rezultat je
`-1`.

### Korišćene metode

```cpp
int sumUpThePath(BSTNodeInt* root, int destKey);
int sumUpThePath(BSTNodeInt* ptr1,
                 int destKey,
                 int& sum);
```

### Ključni postojeći kod

```cpp
int sum = 0;
if (!ptr) {
    return -1;
}
sumUpThePath(root, destKey, sum);
return sum;
```

Pomoćna metoda:

```cpp
sum += ptr->getKey();

if (destKey == ptr->getKey()) {
    return sum;
}
if (ptr->right && destKey > ptr->getKey()) {
    sumUpThePath(ptr->right, destKey, sum);
}
if (ptr->left && destKey < ptr->getKey()) {
    sumUpThePath(ptr->left, destKey, sum);
}
if (destKey > ptr->getKey() && !ptr->right) {
    sum = -1;
}
if (destKey < ptr->getKey() && !ptr->left) {
    sum = -1;
}
```

### Tok izvršavanja

1. Ako početni pokazivač ne postoji, odmah se vraća `-1`.
2. Ključ trenutnog čvora dodaje se u `sum`.
3. Ako je to traženi ključ, pomoćna metoda završava.
4. Ako je `destKey` veći, prati se samo desno dete.
5. Ako je `destKey` manji, prati se samo levo dete.
6. Ako potrebno dete ne postoji, `sum` se postavlja na `-1`.
7. Javna metoda ne koristi povratnu vrednost pomoćne metode, već vraća
   promenljivu `sum` prosleđenu referencom.

### Zašto se prati samo jedna grana

BST poredak jednoznačno određuje smer u kom traženi ključ može da se nalazi.
Za razliku od opšteg obilaska stabla, nema potrebe proveravati obe grane.

### Prolazak kroz primer

Za:

```text
        50
       /  \
      30   70
     / \   / \
    20 40 60 80
```

poziv:

```cpp
tree.sumUpThePath(tree.search(50), 40)
```

prati `50 -> 30 -> 40`, pa je:

```text
50 + 30 + 40 = 120
```

Za `destKey = 99` put ide `50 -> 70 -> 80`. Pošto `80` nema desno dete,
`sum` postaje `-1`.

### Složenost

- vreme: `O(h)`;
- dodatni prostor: `O(h)` zbog rekurzije.

### Granični slučajevi trenutnog koda

- početni `nullptr` vraća `-1`;
- početni čvor može biti koren bilo kog BST podstabla;
- ako je početni ključ jednak `destKey`, vraća upravo taj ključ;
- ako tražena grana prestane pre pronalaska ključa, rezultat postaje `-1`;
- pomoćna metoda ima povratni tip `int`, ali javna metoda koristi isključivo
  referencu `sum`; na granama koje nastavljaju rekurziju njena povratna
  vrednost nije prosleđena javnoj metodi.

---

## 10. Decembarski rok 2026 - `maxDiffOfEvenNodes`

Rok nazvan „Decembarski“ održan je 16. januara 2026.

### Zahtev zadatka

Za svaki čvor treba izračunati razliku između broja parnih čvorova u levom i
desnom podstablu i vratiti čvor sa najvećom apsolutnom razlikom.

### Korišćene metode

```cpp
BSTNodeInt* maxDiffOfEvenNodes() const;
int maxDiffOfEvenNodes(BSTNodeInt* ptr,
                       int& max,
                       BSTNodeInt*& rezultat) const;
```

### Ključni postojeći kod

```cpp
ul = maxDiffOfEvenNodes(ptr->left,
                        max, rezultat);
ud = maxDiffOfEvenNodes(ptr->right,
                        max, rezultat);

diff = abs(ul - ud);

if (max <= diff) {
    max = diff;
    rezultat = ptr;
}

if (ptr->getKey() % 2 == 0) {
    return 1 + ul + ud;
}
return ul + ud;
```

Javna metoda:

```cpp
BSTNodeInt* rezultat = nullptr;
int max = 0;
maxDiffOfEvenNodes(root, max, rezultat);
return rezultat;
```

### Zašto postorder

Razlika za trenutni čvor može da se izračuna tek kada su poznati brojevi
parnih čvorova u oba podstabla. Zbog toga se prvo obrađuju levo i desno dete.

Povratna vrednost pomoćne metode je broj parnih čvorova u podstablu:

```text
broj = parnost trenutnog čvora
     + broj u levom podstablu
     + broj u desnom podstablu
```

Istovremeno se preko referenci održavaju najveća razlika i pokazivač na čvor
koji je ima.

### Uloga promenljivih

- `ul` je broj parnih čvorova u levom podstablu.
- `ud` je broj parnih čvorova u desnom podstablu.
- `diff` je `abs(ul - ud)`.
- `max` je najveća do sada pronađena razlika.
- `rezultat` pokazuje na čvor vezan za trenutni `max`.

### Prolazak kroz primer

Za vrednosti:

```cpp
{
    10, 5, 20, 2, 7, 15, 30,
    12, 18, 25, 40, 22, 27
}
```

levo podstablo korena `10` ima jedan paran čvor, `2`. Desno podstablo ima
šest parnih čvorova: `20`, `30`, `12`, `18`, `40` i `22`.

Za koren je zato:

```text
abs(1 - 6) = 5
```

U dokumentovanom testu to je jedinstvena najveća razlika, pa metoda vraća
čvor `10`.

Za prazno stablo pomoćna metoda odmah vraća `0`, a `rezultat` ostaje
`nullptr`.

### Složenost

- vreme: `O(n)`;
- dodatni prostor: `O(h)`.

### Granični slučajevi trenutnog koda

- prazno stablo vraća `nullptr`;
- list ima `ul = 0` i `ud = 0`, pa je i on kandidat sa razlikom `0`;
- koristi se uslov `max <= diff`, pa novi čvor zamenjuje stari i kada je
  razlika jednaka;
- zbog postorder redosleda konačan rezultat kod izjednačenja postaje kandidat
  koji je obrađen kasnije;
- parnost trenutnog čvora ne utiče direktno na njegov `diff`, već na broj koji
  se vraća njegovom roditelju.

---

## Završna napomena

Ovaj dokument obuhvata samo metode koje postoje i u deklaracijama i u
implementaciji trenutnog `BSTreeInt` projekta. Mapirani, ali neimplementirani
zadaci `deleteNodes` i `DegreeOfKinship` nisu uključeni.

Za detaljna objašnjenja implementiranih grafovskih zadataka pogledati
[`detaljno_objasnjenje_grafovi.md`](detaljno_objasnjenje_grafovi.md).
