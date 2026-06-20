# Mapiranje grafovskih blanketa i template-a

Fokus: samo programski zadaci iz grafova sa pismenih ispita i P2
kolokvijuma iz 2024. i 2025. godine.

Kompletni `main.cpp` primeri i ocekivani rezultati nalaze se u:
[`main_primeri_za_grafove.md`](main_primeri_za_grafove.md).

## Template koji se koristi

Folder: `CelobrojniGraf`

Glavna klasa:

```cpp
GraphAsListsInt
```

Najvazniji clanovi:

| Clan | Namena |
|---|---|
| `LinkedNodeInt* start` | Pocetak liste svih cvorova grafa |
| `long nodeNum` | Broj cvorova i kapacitet reda/steka |
| `LinkedNodeInt::node` | Celobrojni identifikator cvora |
| `LinkedNodeInt::adj` | Pocetak liste izlaznih potega |
| `LinkedNodeInt::next` | Sledeci cvor u listi svih cvorova |
| `LinkedNodeInt::status` | Posecenost, nivo ili ulazni stepen |
| `LinkedNodeInt::prev` | Prethodnik na BFS/DFS putu |
| `LinkedEdgeInt::dest` | Odredisni cvor potega |
| `LinkedEdgeInt::weight` | Tezina potega |
| `LinkedEdgeInt::link` | Sledeci poteg u listi suseda |

Postojece javne metode koje se najcesce koriste:

```cpp
LinkedNodeInt* findNode(const int& data) const;
LinkedEdgeInt* findEdge(const int& dataSrc,
                        const int& dataDest) const;
void insertNode(const int& data);
bool insertEdge(const int& dataSrc, const int& dataDest,
                const double& weight = 0);
bool deleteEdge(const int& dataSrc, const int& dataDest);
void print() const;
```

Pomocne strukture:

- `QueueAsArrayLinkedNodeInt` za BFS i najkrace puteve po broju potega;
- `StackAsArrayLinkedNodeInt` za iterativni DFS;
- rekurzija za DFS kada nije potrebno pamtiti duzinu puta.

## Vazne zamke template-a

1. `insertEdge(a, b)` dodaje samo usmereni poteg `a -> b`.
2. Poteg se dodaje na pocetak liste suseda, pa red obilaska zavisi od obrnutog
   redosleda poziva `insertEdge`.
3. `insertNode` i `insertEdge` ne sprecavaju duplikate. Metode `ensure...`
   moraju prvo pozvati `findNode` ili `findEdge`.
4. Prosledjena tezina se trenutno ignorise u `insertEdge`. Za vezbanje
   `Save/Load` zadatka tezinu postaviti sa
   `findEdge(a, b)->weight = vrednost`.
5. Destruktor nije implementiran i pri zavrsetku programa ispisuje
   `Not implemented!`. To nije rezultat zadatka.
6. Privatni `setStatusForAllNodes` mogu pozivati nove metode clanice klase,
   ali ne i slobodne funkcije.
7. Pre svakog nezavisnog BFS/DFS obilaska treba resetovati `status` i `prev`.

## Zajednicke pomocne metode

Vecina zadataka moze da koristi sledece privatne pomocne metode:

```cpp
bool pathExists(LinkedNodeInt* src, LinkedNodeInt* dest) const;
void resetTraversalState(int statusValue = 0) const;
```

`pathExists` radi BFS ili DFS, a `resetTraversalState` prolazi kroz listu
`start` i postavlja `status` i `prev`. Ne treba pozivati postojece
`breadthFirstTraversal`, jer ono stampa cvorove i ne pamti rastojanja.

## Januar 2024 - `arePathsPossible`

Originalni potpis:

```cpp
bool arePathsPossible(Node* start, Node* goal1,
                      Node* goal2, Node* mid);
```

Potpis za dati template:

```cpp
bool arePathsPossible(LinkedNodeInt* pStart,
                      LinkedNodeInt* goal1,
                      LinkedNodeInt* goal2,
                      LinkedNodeInt* mid) const;
```

Algoritam:

1. BFS od `pStart` do `mid`, uz postavljanje `prev`, nalazi zajednicki put sa
   minimalnim brojem presedanja.
2. Rekonstrukcijom preko `prev` oznaciti sve cvorove zajednickog puta.
3. Iz `mid` posebno proveriti put do `goal1` i `goal2`.
4. U oba obilaska zabraniti cvorove zajednickog puta osim samog `mid`, kako se
   nijedan putnik ne bi vratio na vec posecen aerodrom.

Koriste se `status`, `prev`, `adj`, `QueueAsArrayLinkedNodeInt`.

Upozorenje: ako postoji vise najkracih puteva od `start` do `mid`, potpuno
opste resenje treba da proveri sve najkrace varijante. Za tipican kolokvijumski
template ocekuje se rekonstrukcija jednog BFS puta preko `prev`.

## Jun 2024 - `printMaxConnectedComponentNodes`

Originalni potpis:

```cpp
int printMaxConnectedComponentNodes();
```

Potpis za dati template:

```cpp
int printMaxConnectedComponentNodes() const;
```

Trazi se slaba komponenta povezanosti: usmereni graf se posmatra kao
neusmeren.

Najjednostavniji pristup bez trajnog menjanja grafa:

1. Za svaki neposecen cvor pokrenuti DFS/BFS komponente.
2. Iz cvora pratiti njegove izlazne potegove.
3. Prolaskom kroz sve cvorove pronaci i ulazne potegove ka tekucem cvoru.
4. Sacuvati cvorove trenutno najvece komponente.
5. Odstampati njihove identifikatore i vratiti broj cvorova.

Koriste se `start`, `adj`, `status`, `nodeNum`.

Slozenost direktnog resenja moze biti `O(V * (V + E))`. Efikasnija varijanta
prvo napravi privremene obrnute liste potega, pa radi u `O(V + E)`.

## Jun II 2024 - `defineOrder`

Originalni potpis:

```cpp
int* defineOrder(int* dep, int n);
```

Potpis prilagodjen za dokumentaciju:

```cpp
int* defineOrder(const int* dep, int n) const;
```

Polje sadrzi parove:

```text
zavisan_proces, njegov_preduslov
```

Za svaki par dodaje se poteg:

```text
preduslov -> zavisan_proces
```

Zatim se primenjuje Kahn-ov algoritam:

1. `status` svakog cvora predstavlja ulazni stepen.
2. U red se stavljaju svi cvorovi sa ulaznim stepenom `0`.
3. Pri skidanju cvora smanjuju se ulazni stepeni njegovih suseda.
4. Ako broj obradjenih cvorova nije jednak broju procesa, postoji ciklus i
   vraca se `nullptr`.

Postojeci `topologicalOrderTravrsal` vec sadrzi osnovu algoritma, ali samo
stampa redosled. Nova metoda mora da ga upise u dinamicki alociran niz.

## Jun 2024 P2 grupa B - `whichOneIsCloser`

Originalni potpisi:

```cpp
int whichOneIsCloser(int a, int b, int c);
void ensureEdgeExists(int b, int c);
```

Potpisi za dati template ostaju isti:

```cpp
int whichOneIsCloser(int a, int b, int c) const;
void ensureEdgeExists(int b, int c);
```

`whichOneIsCloser` radi jedan BFS od cvora `a`. Polje `status` moze da cuva
udaljenost:

```text
status(a) = 0
status(sused) = status(tekuceg) + 1
```

Vraca identifikator cvora sa manjom udaljenoscu. Testovi treba da izbegavaju
izjednacenje, jer tekst zadatka ne definise sta se tada vraca.

`ensureEdgeExists(b, c)` poziva `findEdge(b, c)` i dodaje `b -> c` samo ako
poteg ne postoji.

## Jun 2024 P2 grupa A - `pathThroughEdgeExists`

Originalni potpisi:

```cpp
bool pathThroughEdgeExists(int a, int b, int c, int d);
void ensureEdgeExists(int c, int d);
```

Potpisi za dati template ostaju isti:

```cpp
bool pathThroughEdgeExists(int a, int b,
                           int c, int d) const;
void ensureEdgeExists(int c, int d);
```

Provera:

```cpp
pathExists(findNode(a), findNode(c)) &&
findEdge(c, d) != nullptr &&
pathExists(findNode(d), findNode(b))
```

Statusi moraju biti resetovani izmedju dva poziva `pathExists`.

## Pseudokod - dodavanje neusmerenog potega

Prilagodjeni potpis:

```cpp
void ensureUndirectedEdge(int u, int v);
```

Pseudokod:

```text
ako cvor u ili cvor v ne postoji:
    prekini

ako poteg u -> v ne postoji:
    insertEdge(u, v)

ako poteg v -> u ne postoji:
    insertEdge(v, u)
```

Neusmereni poteg se u ovom template-u predstavlja sa dva usmerena potega.

## April 2025 - `FindStation`

Originalni potpis:

```cpp
Node* FindStation(int s, int g1, int g2, int& noInter);
```

Potpis za dati template:

```cpp
LinkedNodeInt* FindStation(int s, int g1, int g2,
                           int& noInter) const;
```

Jedan BFS od `s` racuna udaljenosti do svih dostupnih stanica. Vraca se
`findNode(g1)` ili `findNode(g2)`, zavisno od manje udaljenosti.

Ako je broj potega do cilja `distance`, broj medjustanica je:

```cpp
noInter = distance > 0 ? distance - 1 : 0;
```

Ako nijedan cilj nije dostupan, vraca se `nullptr`, a `noInter` se postavlja
na `-1`. Test treba da izbegne jednake udaljenosti.

Koriste se `status`, `prev`, `QueueAsArrayLinkedNodeInt`.

## Septembar 2025 - `numNeighbours`

Originalni potpis:

```cpp
int numNeighbours(Node host, int n);
```

Potpis za dati template:

```cpp
int numNeighbours(LinkedNodeInt* host, int n) const;
```

BFS po nivoima:

1. `status` se inicijalizuje na `-1`.
2. `host->status = 0`.
3. Sused dobija nivo `tekuci->status + 1`.
4. Cvor se broji i dodaje u red samo ako mu je nivo najvise `n`.
5. Pocetni cvor se ne broji.

U ovoj dokumentaciji `n` oznacava najvise `n` potega od pocetnog cvora.
Za `n <= 0` rezultat je `0`.

## Oktobar 2025 - `Save` i `Load`

Originalni potpisi:

```cpp
void Save(char* fileName);
void Load(char* fileName);
```

Potpisi za dati template:

```cpp
void Save(const char* fileName) const;
void Load(const char* fileName);
```

Predlozeni tekstualni format:

```text
broj_cvorova
id_1 id_2 ... id_V
broj_potega
src_1 dest_1 weight_1
src_2 dest_2 weight_2
...
```

`Save` prvo prolazi kroz sve cvorove da ih sacuva, zatim kroz sve liste
suseda da prebroji i zapise potegove.

`Load` pretpostavlja prazan graf:

1. procita i umetne sve cvorove;
2. procita svaki poteg;
3. pozove `insertEdge(src, dest)`;
4. postavi `findEdge(src, dest)->weight` na ucitanu tezinu.

Poslednji korak je potreban zato sto trenutni `insertEdge` ignorise argument
`weight`.

## Oktobar 2 2025 - `pathGoesThrough`

Originalni potpis:

```cpp
bool pathGoesThrough(int a, int b, int c);
```

Potpis za dati template:

```cpp
bool pathGoesThrough(int a, int b, int c) const;
```

Provera:

```cpp
pathExists(findNode(a), findNode(b)) &&
pathExists(findNode(b), findNode(c))
```

Statusi se resetuju izmedju dva obilaska. Ako bilo koji od tri cvora ne
postoji, rezultat je `false`.

## Oktobar 3 2025 - `pathGoesThroughEdge`

Originalni potpis:

```cpp
bool pathGoesThroughEdge(int a, int b, int c, int d);
```

Potpis za dati template:

```cpp
bool pathGoesThroughEdge(int a, int b,
                         int c, int d) const;
```

Trazi se put `a -> d` koji prolazi kroz usmereni poteg `b -> c`:

```cpp
pathExists(findNode(a), findNode(b)) &&
findEdge(b, c) != nullptr &&
pathExists(findNode(c), findNode(d))
```

Ako poteg `b -> c` ne postoji, odmah se vraca `false`. Statusi se resetuju
izmedju dva obilaska.

## Redosled za vezbanje

1. `ensureEdgeExists`, `ensureUndirectedEdge`, `pathExists`.
2. `pathGoesThrough`, `pathGoesThroughEdge`, `pathThroughEdgeExists`.
3. `whichOneIsCloser`, `FindStation`, `numNeighbours`.
4. `defineOrder`.
5. `printMaxConnectedComponentNodes`.
6. `arePathsPossible`.
7. `Save` i `Load`.
