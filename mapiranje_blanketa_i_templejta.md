# Mapiranje blanketa i template-a

Fokus: samo zadaci gde se trazi funkcija/metoda/pseudokod za stabla i grafove.
Preskoceno: teorija, crtanje reprezentacija, formiranje heap-a/BST-a korak po korak, zadaci iz listi/hash tabela.

Kompletni primeri deklaracija i `main.cpp` testova za postojece tree template-e:
[`main_primeri_za_blankete.md`](main_primeri_za_blankete.md).

Odvojeno mapiranje i `main.cpp` testovi za grafove:
[`mapiranje_grafova_i_templejta.md`](mapiranje_grafova_i_templejta.md) i
[`main_primeri_za_grafove.md`](main_primeri_za_grafove.md).

## Template-i koji postoje

| Template folder | Klasa | Kada ga koristiti |
|---|---|---|
| `CelobrojnoBinarnoStabloPretrage` | `BSTreeInt`, `BSTNodeInt` | Uredjeno binarno stablo / binarno stablo pretrage / BST |
| `CelobrojnaGomilaMinimalna` | `BinaryMinHeapInt` | Min-heap zadaci nad nizom |
| `CelobrojnaGomilaMaksimalna` | `BinaryMaxHeapInt` | Max-heap zadaci nad nizom |
| Nije u folderu kao zaseban projekat | `BTreeInt`, `BTNodeInt` | Obicno/neuredjeno dinamicko binarno stablo |
| `CelobrojniGraf` | `GraphAsListsInt`, `LinkedNodeInt`, `LinkedEdgeInt` | Usmereni i tezinski graf sa listama suseda |

Napomena: fajlovi `BTreeInt.h/.cpp` i `BTNodeInt.h` fizicki se nalaze u
direktorijumu projekta `CelobrojnaGomilaMinimalna`, ali nisu navedeni u
njegovom `.vcxproj` fajlu. Visual Studio projekat sadrzi samo
`BinaryMinHeapInt`, pa se ne racuna kao pravi template binarnog stabla.

## 2024

| Blanket | Zadatak | Trazi se | Template | Recept |
|---|---:|---|---|---|
| Januar 2024 | 3 | `countCloseParents(BSTNode* root, int n)` | `CelobrojnoBinarnoStabloPretrage` | Rekurzija kroz BST; za svaki cvor koji ima decu proveri da li se `key` razlikuje od direktnih potomaka za najvise `n`; vrati zbir iz levog i desnog podstabla. |
| Januar 2024 | 4 | `arePathsPossible(start, goal1, goal2, mid)` | `CelobrojniGraf` / `GraphAsListsInt` | BFS sa `status` i `prev`; proverava se put od `start` preko `mid` do oba cilja, uz uslov da se cvorovi na putu ne ponavljaju. |
| Jun 2024 | 3 | `deleteLeaves()` i `maxLevel()` | Fali zaseban `BTreeInt` template | Neuredjeno binarno stablo. Postojeci `BTreeInt` fajlovi mogu posluziti za vezbu tek kada se rucno dodaju u projekat, ali nisu deo templejta gomile. Za `deleteLeaves` rekurzija koja vraca novi koren podstabla. Za `maxLevel` BFS po nivoima ili rekurzija koja broji cvorove po dubini. |
| Jun 2024 | 4 | `printMaxConnectedComponentNodes()` | `CelobrojniGraf` / `GraphAsListsInt` | Graf je usmeren, ali se za komponentu tretira kao neusmeren. Napraviti obilazak koji prati i izlazne i ulazne veze, izbroji komponente i stampa najvecu. |
| Jun II 2024 | 3 | `Node* minEvenDiff()` | Fali zaseban `BTreeInt` template | Rekurzija vraca sumu parnih potomaka za podstablo; usput azurira najbolji cvor kod kog je razlika suma levog i desnog podstabla najmanja. |
| Jun II 2024 | 4 | `int* defineOrder(int* dep, int n)` | `CelobrojniGraf` / `GraphAsListsInt` | Topolosko sortiranje. Iz parova `(zavisan, preduslov)` napravi usmeren graf `preduslov -> zavisan`, racunaj ulazne stepene, Kahn BFS redom. Ako ciklus, vrati `nullptr`. |
| Jun 2024 - drugo polaganje | 5, samo kod deo | Pseudokod za dodavanje potega u neusmeren graf | `CelobrojniGraf` / `GraphAsListsInt` | Ako `findEdge(u,v)` ne nadje poteg, dodaj `u->v`; zatim isto uradi za `v->u`. |
| Kolokvijum P2 grupa B, Jun 2024 | 1 | `populate(int* arData, int n)` i `sumInterval(min,max)` | `CelobrojnoBinarnoStabloPretrage` | `populate` zove `insert/add` redom. `sumInterval` radi jednu rekurziju; u BST preskaces levo ako je `key < min`, preskaces desno ako je `key > max`. |
| Kolokvijum P2 grupa B, Jun 2024 | 2 | `whichOneIsCloser(a,b,c)` i `ensureEdgeExists(b,c)` | `CelobrojniGraf` / `GraphAsListsInt` | BFS od `a` daje distance do `b` i `c`; manja distanca je blizi cvor. `ensureEdgeExists` poziva `findEdge` i dodaje poteg ako ga nema. |
| Kolokvijum P2 grupa A, Jun 2024 | 1 | `create(int* vec, int n)` i `inorderDistance(a,b)` | `CelobrojnoBinarnoStabloPretrage` | `create` zove `insert`. `inorderDistance` radi jedan inorder obilazak sa brojacem pozicije; kad nadje oba cvora, vrati razliku pozicija + 1; ako neki ne postoji, `-1`. |
| Kolokvijum P2 grupa A, Jun 2024 | 2 | `pathThroughEdgeExists(a,b,c,d)` i `ensureEdgeExists(c,d)` | `CelobrojniGraf` / `GraphAsListsInt` | Proveri `pathExists(a,c)`, `findEdge(c,d)` i `pathExists(d,b)`. Resetovati `status` izmedju obilazaka. |

## 2025

| Blanket | Zadatak | Trazi se | Template | Recept |
|---|---:|---|---|---|
| April 2025 | 3 | `BSTNode* findDeepestLeaf(BSTNode* root)` | `CelobrojnoBinarnoStabloPretrage` ako je zadato BST; inace fali obican `BTreeInt` template | Obican obilazak stabla. Rekurzija sa `level`; najbolji je list sa najvecom dubinom. Ako je izjednaceno, zadrzi prvi nadjen osim ako zadatak kaze drugacije. |
| April 2025 | 4 | `FindStation(int s, int g1, int g2, int& noInter)` | `CelobrojniGraf` / `GraphAsListsInt` | BFS od `s`; `status` cuva udaljenost, a `prev` prethodnika. Vraca se bliza stanica i broj medjustanica. |
| Septembar 2025 | 3 | `int deleteNodes(int key, Node* p)` | Fali zaseban `BTreeInt` template | Neuredjeno binarno stablo. Brisu se cvorovi sa zadatim `key` koji imaju 0 ili 1 potomka; cvorovi sa 2 potomka ostaju. Rekurzija vraca novi koren podstabla i broj obrisanih. |
| Septembar 2025 | 4 | `int numNeighbours(Node host, int n)` | `CelobrojniGraf` / `GraphAsListsInt` | BFS od `host` do dubine najvise `n`; `status` cuva nivo. Broje se razliciti cvorovi, bez pocetnog cvora. |
| Oktobar 2025 | 3 | `int DegreeOfKinship(Osoba* osoba1, Osoba* osoba2)` | Fali porodicno stablo sa cvorom `Osoba*` | Ovo je najkraci put izmedju dva cvora u binarnom stablu. Nadji najnizeg zajednickog pretka ili napravi put od korena do oba cvora, pa izracunaj rastojanje. |
| Oktobar 2025 | 4 | `Save(fileName)` i `Load(fileName)` za tezinski usmeren graf | `CelobrojniGraf` / `GraphAsListsInt` | Sacuvati cvorove i potegove sa `weight`, pa rekonstruisati prazan graf. Postojeci `insertEdge` ignorise tezinu, pa je postaviti preko `findEdge`. |
| Oktobar 2 2025 | 3 | `BSTNode* getDeepestEvenParent(BSTNode* root)` | `CelobrojnoBinarnoStabloPretrage` | Rekurzija kroz BST; kandidat je paran cvor koji nije list. Prati `level` i najbolji cvor na najvecoj dubini. |
| Oktobar 2 2025 | 4 | `pathGoesThrough(int a, int b, int c)` | `CelobrojniGraf` / `GraphAsListsInt` | `pathExists(a,b) && pathExists(b,c)`, uz reset `status` izmedju poziva. |
| Oktobar 3 2025 | 3 | `int maxLevelCount()` | Fali zaseban `BTreeInt` template | BFS po nivoima je najdirektniji: za svaki nivo izbroj cvorove, zapamti maksimum. Moze i rekurzija koja puni niz brojaca po dubini. |
| Oktobar 3 2025 | 4 | `pathGoesThroughEdge(int a, int b, int c, int d)` | `CelobrojniGraf` / `GraphAsListsInt` | `pathExists(a,b) && findEdge(b,c) && pathExists(c,d)`. Ako poteg ne postoji, odmah `false`. |

## 2026

Napomena o datumima:

- Januarski rok je odrzan 3. marta 2026.
- Decembarski rok je odrzan 16. januara 2026. i na sajtu je svrstan pod 2026.

| Blanket | Zadatak | Trazi se | Template | Recept |
|---|---:|---|---|---|
| Januar 2026 | 3 | `int BSTree::sumUpThePath(BSTNode* root, int destKey)` | `CelobrojnoBinarnoStabloPretrage` / `BSTreeInt` | Iterativno prati jedinu BST putanju od prosledjenog cvora do `destKey` i sabira kljuceve posecenih cvorova. Ako kljuc ne postoji, vraca `-1`. |
| Januar 2026 | 4 | Jedan moguci redosled sklapanja delova | `CelobrojniGraf` / `GraphAsListsInt` | Poteg ide od manjeg dela ka vecem delu u koji se ugradjuje. Kahn-ovo topolosko sortiranje vec postoji kao `topologicalOrderTravrsal()`. Ako broj obradjenih cvorova nije `nodeNum`, graf sadrzi ciklus i redosled nije moguc. |
| Decembarski rok, 16. januar 2026 | 3 | `BSTNodeInt* maxDiffOfEvenNodes()` | `CelobrojnoBinarnoStabloPretrage` / `BSTreeInt` | Postorder rekurzija za svako podstablo vraca broj parnih cvorova. Za tekuci cvor racuna `abs(brojParnihLevo - brojParnihDesno)` i pamti cvor sa najvecom razlikom. |
| Decembarski rok, 16. januar 2026 | 4 | `int countSafeNodes()` | `CelobrojniGraf` / `GraphAsListsInt` | DFS bojenje: neposecen, aktivan, bezbedan, nebezbedan. Aktivni cvor ponovo dostignut u DFS-u oznacava ciklus; nebezbedni su i svi cvorovi iz kojih se moze stici do ciklusa. |

## Sta jos treba da skines

Za mapirane grafovske zadatke vise ne fali template. Projekat `CelobrojniGraf`
sadrzi usmereni tezinski graf sa listama suseda, `status`, `prev`, red i stek.

Trenutni `insertEdge` ne cuva prosledjenu tezinu, a destruktor nije
implementiran. To ne sprecava vezbanje, ali utice na `Save/Load` test.

## Kako da vezbas po template-ima

1. Skini pravi template obicnog dinamickog binarnog stabla. Do tada za vezbu mozes rucno napraviti projekat od pronadjenih `BTreeInt` fajlova: `findDeepestLeaf`, `maxLevelCount`, `deleteLeaves`, `deleteNodes`, `minEvenDiff`.
2. Zatim `BSTreeInt`: `populate/create`, `sumInterval`, `inorderDistance`, `getDeepestEvenParent`, `countCloseParents`.
3. U `CelobrojniGraf` vezbaj `pathExists`, BFS udaljenost, `findEdge`, `ensureEdgeExists`, puteve kroz cvor/poteg i topolosko sortiranje.
4. Heap template je nizak prioritet za ove 3/4 zadatke, osim ako dobijes bas gomilu na kolokvijumu.
