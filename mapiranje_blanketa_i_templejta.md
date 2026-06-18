# Mapiranje blanketa i template-a

Fokus: samo zadaci gde se trazi funkcija/metoda/pseudokod za stabla i grafove.
Preskoceno: teorija, crtanje reprezentacija, formiranje heap-a/BST-a korak po korak, zadaci iz listi/hash tabela.

Kompletni primeri deklaracija i `main.cpp` testova za postojece tree template-e:
[`main_primeri_za_blankete.md`](main_primeri_za_blankete.md).

## Template-i koji postoje

| Template folder | Klasa | Kada ga koristiti |
|---|---|---|
| `CelobrojnoBinarnoStabloPretrage` | `BSTreeInt`, `BSTNodeInt` | Uredjeno binarno stablo / binarno stablo pretrage / BST |
| `CelobrojnaGomilaMinimalna` | `BinaryMinHeapInt` | Min-heap zadaci nad nizom |
| `CelobrojnaGomilaMaksimalna` | `BinaryMaxHeapInt` | Max-heap zadaci nad nizom |
| Nije u folderu kao zaseban projekat | `BTreeInt`, `BTNodeInt` | Obicno/neuredjeno dinamicko binarno stablo |
| Nije u folderu | `GraphAsLists` ili slicno | Svi zadaci iz grafova sa listom suseda |

Napomena: fajlovi `BTreeInt.h/.cpp` i `BTNodeInt.h` fizicki se nalaze u
direktorijumu projekta `CelobrojnaGomilaMinimalna`, ali nisu navedeni u
njegovom `.vcxproj` fajlu. Visual Studio projekat sadrzi samo
`BinaryMinHeapInt`, pa se ne racuna kao pravi template binarnog stabla.

## 2024

| Blanket | Zadatak | Trazi se | Template | Recept |
|---|---:|---|---|---|
| Januar 2024 | 3 | `countCloseParents(BSTNode* root, int n)` | `CelobrojnoBinarnoStabloPretrage` | Rekurzija kroz BST; za svaki cvor koji ima decu proveri da li se `key` razlikuje od direktnih potomaka za najvise `n`; vrati zbir iz levog i desnog podstabla. |
| Januar 2024 | 4 | `arePathsPossible(start, goal1, goal2, mid)` | Fali graph template | Ovo je graf sa listom suseda. Treba DFS/BFS sa `visited` i `prev`; proverava se put od `start` preko `mid` do oba cilja, uz uslov da se cvorovi na putu ne ponavljaju. |
| Jun 2024 | 3 | `deleteLeaves()` i `maxLevel()` | Fali zaseban `BTreeInt` template | Neuredjeno binarno stablo. Postojeci `BTreeInt` fajlovi mogu posluziti za vezbu tek kada se rucno dodaju u projekat, ali nisu deo templejta gomile. Za `deleteLeaves` rekurzija koja vraca novi koren podstabla. Za `maxLevel` BFS po nivoima ili rekurzija koja broji cvorove po dubini. |
| Jun 2024 | 4 | `printMaxConnectedComponentNodes()` | Fali graph template | Graf je usmeren, ali se za komponentu tretira kao neusmeren. Napraviti obilazak koji prati i izlazne i ulazne veze, izbroji komponente i stampa najvecu. |
| Jun II 2024 | 3 | `Node* minEvenDiff()` | Fali zaseban `BTreeInt` template | Rekurzija vraca sumu parnih potomaka za podstablo; usput azurira najbolji cvor kod kog je razlika suma levog i desnog podstabla najmanja. |
| Jun II 2024 | 4 | `int* defineOrder(int* dep, int n)` | Fali graph template, moze i bez klase | Topolosko sortiranje. Iz parova `(zavisan, preduslov)` napravi usmeren graf `preduslov -> zavisan`, racunaj ulazne stepene, Kahn BFS redom. Ako ciklus, vrati `nullptr`. |
| Jun 2024 - drugo polaganje | 5, samo kod deo | Pseudokod za dodavanje potega u neusmeren graf | Fali graph template | `edgeExists(u,v)`, ako ne postoji dodaj `u->v` i `v->u` u liste suseda. Ostatak zadatka je reprezentacija i nije prioritet. |
| Kolokvijum P2 grupa B, Jun 2024 | 1 | `populate(int* arData, int n)` i `sumInterval(min,max)` | `CelobrojnoBinarnoStabloPretrage` | `populate` zove `insert/add` redom. `sumInterval` radi jednu rekurziju; u BST preskaces levo ako je `key < min`, preskaces desno ako je `key > max`. |
| Kolokvijum P2 grupa B, Jun 2024 | 2 | `whichOneIsCloser(a,b,c)` i `ensureEdgeExists(b,c)` | Fali graph template | BFS od `a` daje distance do `b` i `c`; manja distanca je blizi cvor. `ensureEdgeExists` proveri listu suseda i doda poteg ako ga nema. |
| Kolokvijum P2 grupa A, Jun 2024 | 1 | `create(int* vec, int n)` i `inorderDistance(a,b)` | `CelobrojnoBinarnoStabloPretrage` | `create` zove `insert`. `inorderDistance` radi jedan inorder obilazak sa brojacem pozicije; kad nadje oba cvora, vrati razliku pozicija + 1; ako neki ne postoji, `-1`. |
| Kolokvijum P2 grupa A, Jun 2024 | 2 | `pathThroughEdgeExists(a,b,c,d)` i `ensureEdgeExists(c,d)` | Fali graph template | Put kroz poteg `c->d`: proveri `pathExists(a,c)`, `edgeExists(c,d)`, `pathExists(d,b)`. Za neusmeren poteg proveriti oba smera ako tekst/template tako trazi. |

## 2025

| Blanket | Zadatak | Trazi se | Template | Recept |
|---|---:|---|---|---|
| April 2025 | 3 | `BSTNode* findDeepestLeaf(BSTNode* root)` | `CelobrojnoBinarnoStabloPretrage` ako je zadato BST; inace fali obican `BTreeInt` template | Obican obilazak stabla. Rekurzija sa `level`; najbolji je list sa najvecom dubinom. Ako je izjednaceno, zadrzi prvi nadjen osim ako zadatak kaze drugacije. |
| April 2025 | 4 | `FindStation(int s, int g1, int g2, int& noInter)` | Fali graph template | BFS od `s`; cilj je vratiti do koje od stanica `g1/g2` se stize sa najmanje medjustanica. `noInter` je broj medjustanica/distanca prilagodjena tekstu. |
| Septembar 2025 | 3 | `int deleteNodes(int key, Node* p)` | Fali zaseban `BTreeInt` template | Neuredjeno binarno stablo. Brisu se cvorovi sa zadatim `key` koji imaju 0 ili 1 potomka; cvorovi sa 2 potomka ostaju. Rekurzija vraca novi koren podstabla i broj obrisanih. |
| Septembar 2025 | 4 | `int numNeighbours(Node host, int n)` | Fali graph template | BFS od `host` do dubine najvise `n`; brojis razlicite cvorove do kojih se moze doci. Pazi na `visited` da se cvor ne broji vise puta. |
| Oktobar 2025 | 3 | `int DegreeOfKinship(Osoba* osoba1, Osoba* osoba2)` | Fali porodicno stablo sa cvorom `Osoba*` | Ovo je najkraci put izmedju dva cvora u binarnom stablu. Nadji najnizeg zajednickog pretka ili napravi put od korena do oba cvora, pa izracunaj rastojanje. |
| Oktobar 2025 | 4 | `Save(fileName)` i `Load(fileName)` za tezinski usmeren graf | Fali graph template | Treba serijalizacija grafa: sacuvati cvorove i potegove sa tezinama, a `Load` prvo isprazni graf pa rekonstruise iz fajla. Ovo vezbati tek posle BFS/DFS zadataka. |
| Oktobar 2 2025 | 3 | `BSTNode* getDeepestEvenParent(BSTNode* root)` | `CelobrojnoBinarnoStabloPretrage` | Rekurzija kroz BST; kandidat je paran cvor koji nije list. Prati `level` i najbolji cvor na najvecoj dubini. |
| Oktobar 2 2025 | 4 | `pathGoesThrough(int a, int b, int c)` | Fali graph template | Provera da li postoji put `a -> c` koji prolazi kroz `b`: dovoljno je `pathExists(a,b) && pathExists(b,c)`, uz reset `visited` izmedju poziva. |
| Oktobar 3 2025 | 3 | `int maxLevelCount()` | Fali zaseban `BTreeInt` template | BFS po nivoima je najdirektniji: za svaki nivo izbroj cvorove, zapamti maksimum. Moze i rekurzija koja puni niz brojaca po dubini. |
| Oktobar 3 2025 | 4 | `pathGoesThroughEdge(int a, int b, int c, int d)` | Fali graph template | Put od `a` do `d` kroz poteg `b->c`: `pathExists(a,b) && edgeExists(b,c) && pathExists(c,d)`. Ako poteg ne postoji, odmah `false`. |

## Sta jos treba da skines

Najvise fali template za graf, verovatno projekat sa klasom slicnom `GraphAsLists`.
Ako postoji vise varijanti, najbitnije su:

- usmeren graf sa listom suseda
- neorijentisan graf sa listom suseda
- tezinski graf sa listom suseda
- cvor sa poljima `status/visited`, `prev`, `next`, `adj`

Bez tog template-a moze da se uci algoritam, ali na kolokvijumu je mnogo bolje znati tacna imena polja i metoda.

## Kako da vezbas po template-ima

1. Skini pravi template obicnog dinamickog binarnog stabla. Do tada za vezbu mozes rucno napraviti projekat od pronadjenih `BTreeInt` fajlova: `findDeepestLeaf`, `maxLevelCount`, `deleteLeaves`, `deleteNodes`, `minEvenDiff`.
2. Zatim `BSTreeInt`: `populate/create`, `sumInterval`, `inorderDistance`, `getDeepestEvenParent`, `countCloseParents`.
3. Grafove ostavi kao algoritme dok ne dodas graph template: `pathExists`, BFS distance, `edgeExists`, `ensureEdgeExists`, topolosko sortiranje.
4. Heap template je nizak prioritet za ove 3/4 zadatke, osim ako dobijes bas gomilu na kolokvijumu.
