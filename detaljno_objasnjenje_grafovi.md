# Detaljno objašnjenje urađenih zadataka - grafovi

Ovaj vodič objašnjava postojeće implementacije iz projekta `CelobrojniGraf`.
Kod nije menjan niti prepravljan. Opisuje se stvarno ponašanje trenutnih
metoda, uključujući njihove promene stanja grafa i ponašanje u graničnim
slučajevima.

Glavni fajlovi:

- [`GraphInt.h`](CelobrojniGraf/CelobrojniGraf/GraphInt.h)
- [`GraphInt.cpp`](CelobrojniGraf/CelobrojniGraf/GraphInt.cpp)
- [`LinkedNodeInt.h`](CelobrojniGraf/CelobrojniGraf/LinkedNodeInt.h)
- [`LinkedEdgeInt.h`](CelobrojniGraf/CelobrojniGraf/LinkedEdgeInt.h)
- [`main.cpp`](CelobrojniGraf/CelobrojniGraf/main.cpp)
- [`main_primeri_za_grafove.md`](main_primeri_za_grafove.md)

## Sadržaj

1. [Osnova templejta](#osnova-templejta)
2. [Januar 2024 - `arePathsPossible`](#1-januar-2024---arepathspossible)
3. [Jun 2024 - `printMaxConnectedComponentNodes`](#2-jun-2024---printmaxconnectedcomponentnodes)
4. [Jun II 2024 - `defineOrder`](#3-jun-ii-2024---defineorder)
5. [P2 grupa B 2024 - `whichOneIsCloser` i `ensureEdgeExists`](#4-p2-grupa-b-2024---whichoneiscloser-i-ensureedgeexists)
6. [P2 grupa A 2024 - `pathThroughEdgeExists`](#5-p2-grupa-a-2024---paththroughedgeexists)
7. [April 2025 - `FindStation`](#6-april-2025---findstation)
8. [Oktobar II 2025 - `pathGoesThrough`](#7-oktobar-ii-2025---pathgoesthrough)
9. [Januar 2026 - topološki redosled sklapanja](#8-januar-2026---topološki-redosled-sklapanja)
10. [Decembarski rok 2026 - `countSafeNodes`](#9-decembarski-rok-2026---countsafenodes)

## Osnova templejta

Klasa `GraphAsListsInt` predstavlja usmereni graf pomoću ulančanih lista
suseda.

```cpp
LinkedNodeInt* start;
long nodeNum;
```

- `start` je početak ulančane liste svih čvorova.
- `nodeNum` je broj čvorova i koristi se kao kapacitet reda ili steka.

Jedan čvor sadrži:

```cpp
int node;
LinkedEdgeInt* adj;
LinkedNodeInt* next;
int status;
LinkedNodeInt* prev;
```

- `node` je celobrojni identifikator;
- `adj` je početak liste izlaznih potega;
- `next` vodi do sledećeg čvora grafa;
- `status` se privremeno koristi za posećenost, stanje DFS-a ili ulazni
  stepen;
- `prev` čuva prethodnika u BFS stablu.

Jedan poteg sadrži:

```cpp
LinkedNodeInt* dest;
double weight;
LinkedEdgeInt* link;
```

`dest` je odredišni čvor, a `link` sledeći poteg u listi suseda.

### Bitno ponašanje osnovnog templejta

`insertNode` dodaje čvor na početak liste:

```cpp
start = new LinkedNodeInt(data, nullptr, start);
nodeNum++;
```

Zato je redosled čvorova u listi obrnut od redosleda umetanja.

`insertEdge` dodaje novi izlazni poteg na početak liste suseda:

```cpp
pSrc->adj = new LinkedEdgeInt(pDest, pSrc->adj);
```

Argument `weight` se u ovoj implementaciji ne prosleđuje konstruktoru potega.

Destruktor trenutno sadrži:

```cpp
cout << "Not implemented!" << endl;
```

Zato se po završetku programa ispisuje dodatna linija `Not implemented!`.
Ona nije rezultat nijednog ispitnog zadatka.

Najčešća značenja polja `status` u BFS/DFS metodama su:

```text
0 - zabranjen ili neposećen, zavisno od metode
1 - neobrađen
2 - dodat u red ili stek
3 - obrađen ili nebezbedan
```

Svaka metoda u nastavku određuje sopstveno značenje statusa.

Za složenost se koristi:

- `V` - broj čvorova;
- `E` - broj usmerenih potega.

---

## 1. Januar 2024 - `arePathsPossible`

### Zahtev zadatka

Potrebno je proveriti da li se od početnog čvora može stići do zajedničkog
čvora `mid`, a zatim od `mid` do oba cilja, bez vraćanja na čvorove zajedničke
početne putanje.

### Korišćena metoda

```cpp
bool arePathsPossible(LinkedNodeInt* start,
                      LinkedNodeInt* goal1,
                      LinkedNodeInt* goal2,
                      LinkedNodeInt* mid) const;
```

### Ključni postojeći kod

Prvi BFS traži `mid`:

```cpp
setStatusForAllNodes(1);
QueueAsArrayLinkedNodeInt queue(nodeNum);
queue.enqueue(start);
start->status = 2;
start->prev = nullptr;

while (!queue.isEmpty()) {
    ptr = queue.dequeue();
    adj = ptr->adj;

    if (ptr == mid) {
        firstP = true;
        setStatusForAllNodes(1);
        while (ptr->prev) {
            ptr->prev->status = 0;
            ptr = ptr->prev;
        }
        break;
    }

    ptr->status = 3;
    while (adj) {
        if (adj->dest->status == 1) {
            queue.enqueue(adj->dest);
            adj->dest->prev = ptr;
            adj->dest->status = 2;
        }
        adj = adj->link;
    }
}
```

Drugi BFS kreće od `mid`:

```cpp
queue1.enqueue(mid);
mid->status = 2;

while (!queue1.isEmpty()) {
    ptr = queue1.dequeue();
    adj = ptr->adj;

    if (ptr == goal1) {
        secondP1 = true;
    }
    if (ptr == goal2) {
        secondP2 = true;
    }

    ptr->status = 3;
    while (adj) {
        if (adj->dest->status == 1) {
            adj->dest->prev = ptr;
            adj->dest->status = 2;
            queue1.enqueue(adj->dest);
        }
        adj = adj->link;
    }
}
```

### Tok izvršavanja

1. Svi čvorovi dobijaju status `1`, odnosno neobrađen.
2. Prvi BFS kreće od prosleđenog `start`.
3. Kada se sused prvi put pronađe, njegov `prev` pokazuje na čvor iz kog je
   otkriven. Tako se formira BFS stablo prethodnika.
4. Kada se `mid` skine iz reda:
   - potvrđuje se da prva deonica postoji;
   - svi statusi se ponovo postavljaju na `1`;
   - praćenjem `prev` unazad svi prethodnici na putu do `mid` dobijaju status
     `0`.
5. Status `0` ih zabranjuje za drugi BFS. Sam `mid` se ne zabranjuje.
6. Drugi BFS kreće iz `mid` i proverava dostupnost oba cilja.
7. Rezultat je `true` samo ako je pronađen `mid` i oba cilja.

### Uloga promenljivih

- `firstP` označava da je pronađen put od početka do `mid`.
- `secondP1` i `secondP2` označavaju dostupnost dva cilja.
- `prev` rekonstruiše jednu putanju koju je izabrao BFS.
- `status == 0` u drugoj fazi znači da se čvor sa zajedničke početne putanje
  ne sme ponovo koristiti.
- `queue` i `queue1` razdvajaju dve BFS faze.

### Zašto BFS

BFS prvi pronalazi `mid` preko najmanjeg broja potega i postavlja
prethodnike bez ponavljanja čvorova. Ista struktura zatim efikasno proverava
koji su čvorovi dostupni iz `mid`.

### Prolazak kroz primer

Za potegove:

```text
1 -> 2 -> 3 -> 4 -> 5
          \
           -> 6 -> 7
```

poziv koristi:

```text
start = 1
mid   = 3
goal1 = 5
goal2 = 7
```

Prvi BFS pamti put `1 -> 2 -> 3`. Posle dolaska do `3`, čvorovi `1` i `2`
postaju zabranjeni. Drugi BFS iz `3` nalazi i `5` i `7`, pa metoda vraća
`true`.

Kada je drugi cilj izolovani čvor `8`, `secondP2` ostaje `false` i rezultat je
`false`.

### Složenost

- vreme: `O(V + E)`, jer se izvršavaju najviše dva BFS obilaska;
- dodatni prostor: `O(V)` za redove i prethodnike.

### Granični slučajevi trenutnog koda

- ako prvi BFS ne može da dođe do `mid`, odmah se vraća `false`;
- drugi BFS u jednom obilasku traži oba cilja;
- zabranjuju se prethodnici iz jedne BFS putanje do `mid`, ne sve moguće
  putanje do njega;
- grane od `mid` ka `goal1` i `goal2` nisu međusobno označene kao odvojene:
  kod proverava dostupnost oba cilja u istom BFS-u;
- metoda ne proverava da li su prosleđeni pokazivači `nullptr`; nepostojeći
  početni pokazivač bi bio dereferenciran pri postavljanju statusa.

---

## 2. Jun 2024 - `printMaxConnectedComponentNodes`

### Zahtev zadatka

Za usmereni graf treba pronaći i ispisati čvorove najveće slabe komponente
povezanosti. „Slaba“ znači da se pri određivanju komponente smer potega
zanemaruje.

### Korišćene metode

```cpp
void deorientation();
int printMaxConnectedComponentNodes();
```

### Pretvaranje potega u oba smera

```cpp
void GraphAsListsInt::deorientation()
{
    LinkedNodeInt* ptr = start;
    while (ptr) {
        LinkedEdgeInt* adj = ptr->adj;
        while (adj) {
            if (!findEdge(adj->dest->node,
                          ptr->node)) {
                insertEdge(adj->dest->node,
                           ptr->node);
            }
            adj = adj->link;
        }
        ptr = ptr->next;
    }
}
```

Za svaki postojeći `u -> v`, metoda proverava da li postoji `v -> u` i dodaje
ga ako nedostaje. Time se usmereni graf trajno dopunjava obrnutim potegovima.

### Ključni BFS kod

```cpp
deorientation();
setStatusForAllNodes(1);

for (int i = 0; i < nodeNum; i++) {
    if (ptr->status == 1) {
        q.enqueue(ptr);
        ptr->status = 2;

        while (!q.isEmpty()) {
            ptr2 = q.dequeue();
            adj = ptr2->adj;
            counter++;

            if (counter > max_count) {
                max_count = counter;
                max_start = ptr;
            }

            ptr2->status = 3;
            while (adj) {
                if (adj->dest->status == 1) {
                    q.enqueue(adj->dest);
                    adj->dest->status = 2;
                    adj->dest->prev = ptr2;
                }
                adj = adj->link;
            }
        }
        counter = 0;
    }
    ptr = ptr->next;
}
```

Nakon pronalaženja `max_start`, statusi se resetuju i drugi BFS iz tog čvora
poziva `visit()` za svaki čvor komponente.

### Tok izvršavanja

1. `deorientation` obezbeđuje da se svaka veza može pratiti u oba smera.
2. Svi čvorovi dobijaju status `1`.
3. Spoljašnja petlja prolazi kroz listu svih čvorova.
4. Za svaki još neobrađen čvor pokreće se BFS njegove komponente.
5. `counter` se uvećava za svaki skinuti čvor.
6. Kad god trenutna komponenta postane veća od svih ranije viđenih,
   `max_count` i `max_start` se ažuriraju.
7. Posle obilaska svih komponenti, statusi se resetuju.
8. Novi BFS od `max_start` štampa sve čvorove pobedničke komponente.
9. Metoda vraća `max_count`.

### Uloga promenljivih

- `ptr` prolazi kroz sve čvorove i u trenutku pokretanja BFS-a predstavlja
  početak komponente.
- `ptr2` je čvor trenutno skinut iz reda.
- `counter` je veličina tekuće komponente.
- `max_count` je najveća do sada pronađena veličina.
- `max_start` pamti čvor iz najveće komponente za kasniji ispis.
- `max_end` se postavlja u kodu, ali se aktivni deo metode ne oslanja na
  njega.

### Zašto BFS

Nakon dodavanja obrnutih potega, svi čvorovi jedne slabe komponente dostupni
su običnim obilaskom. BFS osigurava da se svaki od njih doda u red najviše
jednom.

### Prolazak kroz primer

Za potegove:

```text
1 -> 2
3 -> 2
3 -> 4
5 -> 6
7 je izolovan
```

posle `deorientation` prva komponenta sadrži `{1, 2, 3, 4}`, druga `{5, 6}`,
a treća `{7}`. Metoda štampa čvorove prve komponente i vraća `4`.

Redosled ispisa zavisi od redosleda čvorova u listi i potega u listama
suseda.

### Složenost

BFS deo je `O(V + E)` i koristi `O(V)` dodatnog prostora.

U trenutnoj realizaciji `deorientation` za svaki poteg poziva `findEdge`.
`findEdge` prvo linearno traži početni čvor, a zatim njegov poteg, pa ukupno
vreme dopunjavanja može biti do `O(E(V + E))` u nepovoljnom rasporedu.

### Granični slučajevi trenutnog koda

- graf se trajno menja dodavanjem obrnutih potega;
- ako više komponenti ima istu najveću veličinu, ostaje ona koja je prva
  dostigla `max_count`, jer se koristi strogo `>`;
- izolovani čvor predstavlja komponentu veličine `1`;
- na početku se pristupa `ptr->adj` pre posebne provere praznog grafa, pa
  prazan graf nije bezbedno obrađen;
- metoda nije deklarisana kao `const`, jer `deorientation` menja graf.

---

## 3. Jun II 2024 - `defineOrder`

### Zahtev zadatka

Niz `dep` sadrži parove:

```text
zavisan proces, proces od kog zavisi
```

Potrebno je vratiti niz sa jednim mogućim redosledom aktiviranja procesa. Ako
zavisnosti sadrže ciklus, vraća se `nullptr`.

### Korišćena metoda

```cpp
int* defineOrder(int* dep, int n);
```

### Formiranje grafa zavisnosti

```cpp
while (start != nullptr) {
    deleteNode(start->node);
}

for (int i = 0; i < n; i += 2) {
    dependent = findNode(dep[i]);
    dependency = findNode(dep[i + 1]);

    if (!dependent) {
        insertNode(dep[i]);
        dependent = findNode(dep[i]);
        dependent->status = 0;
    }

    if (!dependency) {
        insertNode(dep[i + 1]);
        dependency = findNode(dep[i + 1]);
        dependency->status = 0;
    }

    if (!findEdge(dep[i + 1], dep[i])) {
        insertEdge(dep[i + 1], dep[i]);
        dependent->status++;
    }
}
```

Poteg se dodaje u smeru:

```text
preduslov -> zavisan proces
```

`status` zavisnog procesa se uvećava i predstavlja njegov ulazni stepen.

### Kahn-ov deo algoritma

```cpp
int* rezultat = new int[nodeNum]();
QueueAsArrayLinkedNodeInt q(nodeNum);

while (ptr) {
    if (ptr->status == 0) {
        q.enqueue(ptr);
    }
    ptr = ptr->next;
}

while (!q.isEmpty()) {
    ptr = q.dequeue();
    rezultat[i] = ptr->node;
    i++;

    adj = ptr->adj;
    while (adj) {
        adj->dest->status--;
        if (adj->dest->status == 0) {
            q.enqueue(adj->dest);
        }
        adj = adj->link;
    }
}

if (i == nodeNum) {
    return rezultat;
}
return nullptr;
```

### Tok izvršavanja

1. Metoda najpre briše sve čvorove koji su ranije postojali u objektu grafa.
2. Iz svakog para pravi potrebne čvorove.
3. Dodaje poteg od preduslova ka zavisnom procesu.
4. Duplikat istog potega se ne dodaje i zato se ulazni stepen ne uvećava dva
   puta.
5. Svi čvorovi sa ulaznim stepenom nula stavljaju se u red.
6. Skidanjem takvog čvora smatra se da je proces aktiviran.
7. Njegovi izlazni potegovi vode ka procesima kojima je on bio preduslov, pa
   se njihov ulazni stepen smanjuje.
8. Kada nekom procesu stepen postane nula, svi njegovi preduslovi su obrađeni
   i on ulazi u red.
9. Ako je obrađeno tačno `nodeNum` čvorova, niz je topološki redosled.
10. Ako je obrađeno manje, deo grafa je ostao zaključan ciklusom i vraća se
    `nullptr`.

### Uloga promenljivih

- `dependent` je proces zapisan kao prvi član para.
- `dependency` je njegov preduslov, drugi član para.
- `status` predstavlja trenutni ulazni stepen.
- `rezultat` je dinamički alociran izlazni niz.
- `i` je broj upisanih, odnosno obrađenih procesa.

### Zašto topološko sortiranje

Uslov „proces tek nakon svih preduslova“ upravo je parcijalni poredak u
usmerenom acikličnom grafu. Kahn-ov algoritam direktno obrađuje čvorove kojima
više ništa ne prethodi i istovremeno otkriva ciklus.

### Prolazak kroz primer

Za:

```cpp
int dep[] = {
    2, 1,
    3, 2,
    4, 3
};
```

nastaju potegovi:

```text
1 -> 2 -> 3 -> 4
```

Jedini početni ulazni stepen nula ima čvor `1`. Obrada zatim redom oslobađa
`2`, `3` i `4`, pa rezultat glasi:

```text
1 2 3 4
```

Za parove `(2, 1)` i `(1, 2)` oba čvora imaju ulazni stepen jedan. Početni red
je prazan, `i` ostaje nula i metoda vraća `nullptr`.

### Složenost

- sama Kahn-ova faza: `O(V + E)`;
- dodatni prostor: `O(V)` za red i rezultat;
- kompletna trenutna metoda koristi linearne `findNode`, `findEdge` i
  `deleteNode`, pa konstrukcija i prethodno pražnjenje objekta mogu biti
  skuplji od same topološke faze.

### Granični slučajevi trenutnog koda

- prethodni sadržaj objekta grafa se briše;
- `n` se tumači kao broj elemenata niza, ne broj parova;
- za neparno `n` petlja pristupa `dep[i + 1]`, pa ulaz mora imati kompletne
  parove;
- ako postoji više čvorova ulaznog stepena nula, njihov redosled zavisi od
  ulančane liste čvorova;
- kod ciklusa se vraća `nullptr`, ali prethodno alocirani `rezultat` se u toj
  grani ne oslobađa;
- nakon uspeha statusi obrađenih čvorova su smanjeni na nulu; nakon ciklusa
  deo statusa ostaje pozitivan do sledećeg resetovanja ili brisanja.

---

## 4. P2 grupa B 2024 - `whichOneIsCloser` i `ensureEdgeExists`

### Zahtev zadatka

Od početnog čvora `a` treba utvrditi da li je po broju potega bliži čvor `b`
ili `c`. Zatim treba obezbediti poteg od bližeg ka daljem čvoru.

### Korišćene metode

```cpp
int whichOneIsCloser(int a, int b, int c) const;
void ensureEdgeExists(int b, int c);
```

### Ključni BFS kod

```cpp
setStatusForAllNodes(1);
q.enqueue(ptr);
ptr->prev = nullptr;
ptr->status = 2;

while (!q.isEmpty()) {
    ptr = q.dequeue();
    adj = ptr->adj;
    ptr->status = 3;

    while (adj) {
        if (adj->dest->status == 1) {
            q.enqueue(adj->dest);
            adj->dest->status = 2;
            adj->dest->prev = ptr;
        }
        if (adj->dest->node == b && !foundb) {
            ptrb = adj->dest;
            foundb = true;
        }
        else if (adj->dest->node == c && !foundc) {
            ptrc = adj->dest;
            foundc = true;
        }
        adj = adj->link;
    }
}
```

Posle BFS-a dužine se određuju praćenjem `prev`:

```cpp
while (ptrb) {
    pathb++;
    ptrb = ptrb->prev;
}
while (ptrc) {
    pathc++;
    ptrc = ptrc->prev;
}

if (pathb < pathc) {
    return b;
}
else if (pathb > pathc) {
    return c;
}
return b;
```

### Kako se određuje blizina

BFS svakom prvi put pronađenom čvoru postavlja prethodnika na najkraćoj
putanji po broju potega. Nakon obilaska:

- `ptrb` i `ptrc` pokazuju na pronađene ciljeve;
- praćenje `prev` broji čvorove na putanji, uključujući početni i krajnji;
- obe putanje imaju isti dodatak od jednog čvora u odnosu na broj potega, pa
  poređenje ostaje isto kao poređenje udaljenosti.

Kod jednakih dužina metoda vraća `b`.

### Postojeći kod za dodavanje potega

```cpp
void GraphAsListsInt::ensureEdgeExists(int b, int c)
{
    if (findNode(b) && findNode(c)) {
        if (!findEdge(b, c) &&
            !findEdge(c, b)) {
            insertEdge(b, c);
        }
    }
}
```

Poteg `b -> c` dodaje se samo ako postoje oba čvora i ako ne postoji ni
`b -> c` ni obrnuti `c -> b`.

### Prolazak kroz primer

Graf ima:

```text
1 -> 2 -> 4
1 -> 3 -> 5 -> 6
```

Od `1` do `4` postoje dva potega, a do `6` tri. Metoda vraća `4`.

`ensureEdgeExists(4, 6)` zatim proverava oba smera. Pošto nema ni `4 -> 6` ni
`6 -> 4`, dodaje `4 -> 6`.

### Zašto BFS

Svi potegovi imaju isti značaj za meru udaljenosti. BFS u takvom grafu prvi
put pronalazi svaki čvor najkraćom putanjom po broju potega.

### Složenost

- `whichOneIsCloser`: `O(V + E)` za BFS i do `O(V)` za praćenje obe putanje;
- dodatni prostor: `O(V)`;
- `ensureEdgeExists`: linearne pretrage čvorova i potega, najgore
  `O(V + E)`.

### Granični slučajevi trenutnog koda

- ako čvor `a` ne postoji, vraća `-1`;
- početni čvor se ne proverava direktno kao `b` ili `c`; ciljevi se registruju
  kada se vide kao odredišta potega;
- ako cilj nije dostupan, njegov pokazivač ostaje `nullptr`, a izračunata
  dužina ostaje `0`;
- zbog toga nedostupan cilj može biti ocenjen kao „bliži“ od dostupnog cilja
  sa pozitivnom dužinom;
- ako su dužine jednake, vraća se `b`;
- `ensureEdgeExists` neće dodati `b -> c` ako već postoji samo obrnuti
  `c -> b`, iako je graf usmeren.

---

## 5. P2 grupa A 2024 - `pathThroughEdgeExists`

### Zahtev zadatka

Treba proveriti da li postoji put od `a` do `b` koji obavezno prolazi kroz
usmereni poteg `c -> d`.

### Korišćene metode

```cpp
bool pathThroughEdgeExists(int a,
                           int b,
                           int c,
                           int d);
void ensureEdgeExists(int b, int c);
```

### Ključni postojeći kod

Metoda prvo poziva:

```cpp
ensureEdgeExists(d, b);
```

Zatim iterativnim DFS-om traži `c` iz `a`:

```cpp
s.push(start);
start->status = 2;

while (!s.isEmpty()) {
    ptr = s.pop();
    if (ptr->node == c) {
        mozec = true;
        start = ptr;
    }

    adj = ptr->adj;
    ptr->status = 3;
    while (adj) {
        if (adj->dest->status == 1) {
            s.push(adj->dest);
            adj->dest->status = 2;
        }
        adj = adj->link;
    }
}
```

Potom direktno proverava izlazni poteg iz `c`:

```cpp
adj = start->adj;
while (adj) {
    if (adj->dest->node == d) {
        mozecd = true;
        start = adj->dest;
    }
    adj = adj->link;
}
```

Na kraju resetuje statuse i DFS-om proverava dostupnost `b` iz `d`.

### Tok izvršavanja

1. `ensureEdgeExists(d, b)` proverava ili dodaje vezu od `d` ka krajnjem
   čvoru `b`, u skladu sa ponašanjem te pomoćne metode.
2. Svi statusi se postavljaju na `1`.
3. Prvi DFS polazi od `a` i proverava da li je `c` dostupan.
4. Kada se pronađe `c`, pokazivač `start` se preusmerava na taj čvor.
5. Posle završetka DFS-a pregleda se lista suseda čvora `c` i traži se tačno
   odredište `d`.
6. Ako poteg postoji, `start` postaje `d`.
7. Statusi se resetuju i drugi DFS proverava može li se od `d` stići do `b`.
8. Rezultat je konjunkcija:

```text
dostupan c && postoji c->d && dostupan b iz d
```

### Uloga promenljivih

- `mozec` označava dostupnost čvora `c` iz `a`.
- `mozecd` označava postojanje direktnog potega `c -> d`.
- `mozedb` označava dostupnost `b` iz `d`.
- `start` se tokom metode koristi za tri različite tačke: početno `a`,
  pronađeno `c` i zatim `d`.
- `s` je stek za iterativni DFS.

### Zašto DFS

Za segmente `a -> c` i `d -> b` potrebno je samo utvrditi da li put postoji,
ne i da li je najkraći. DFS zato daje dovoljan odgovor uz linearno obilaženje
dostupnog dela grafa.

### Prolazak kroz primer

Za:

```text
1 -> 2 -> 3 -> 4
 \
  -> 5
```

poziv `pathThroughEdgeExists(1, 4, 2, 3)`:

- nalazi `2` iz `1`;
- nalazi direktan poteg `2 -> 3`;
- iz `3` nalazi `4`;
- vraća `true`.

Za traženi poteg `5 -> 2`, prvi poziv vraća `false` jer taj poteg ne postoji.
Posle spoljnog poziva `ensureEdgeExists(5, 2)`, put
`1 -> 5 -> 2 -> 3 -> 4` postaje moguć i sledeći poziv vraća `true`.

### Složenost

- dva DFS obilaska: `O(V + E)`;
- direktna provera liste suseda čvora `c`: do `O(E)`;
- pomoćni poziv `ensureEdgeExists`: do `O(V + E)`;
- dodatni prostor: `O(V)` zbog steka i statusa.

### Granični slučajevi trenutnog koda

- metoda na početku može promeniti graf pozivom `ensureEdgeExists(d, b)`;
- zbog tog poziva veza potrebna za poslednju deonicu može biti dodata pre
  same provere;
- ako između `d` i `b` postoji obrnuti poteg `b -> d`, `ensureEdgeExists`
  neće dodati `d -> b`;
- početni čvor `a` se ne proverava na `nullptr` pre stavljanja na stek i
  pristupa statusu;
- direktni poteg `c -> d` se proverava pregledom liste suseda pronađenog
  čvora `c`;
- prvi DFS se ne prekida odmah kada pronađe `c`, već nastavlja obilazak.

---

## 6. April 2025 - `FindStation`

### Zahtev zadatka

Od početne stanice `s` treba izabrati bližu od stanica `g1` i `g2` prema
broju potega i kroz referencu vratiti broj međustanica.

### Korišćena metoda

```cpp
LinkedNodeInt* FindStation(int s,
                           int g1,
                           int g2,
                           int& noInter);
```

### Ključni postojeći kod

```cpp
setStatusForAllNodes(1);
LinkedNodeInt* start1 = findNode(s);

q.enqueue(start1);
start1->status = 2;
start1->prev = nullptr;

while (!q.isEmpty()) {
    ptr = q.dequeue();

    if (ptr->node == g1) {
        pg1 = ptr;
    }
    if (ptr->node == g2) {
        pg2 = ptr;
    }

    adj = ptr->adj;
    ptr->status = 3;
    while (adj) {
        if (adj->dest->status == 1) {
            q.enqueue(adj->dest);
            adj->dest->status = 2;
            adj->dest->prev = ptr;
        }
        adj = adj->link;
    }
}
```

Poređenje pronađenih putanja:

```cpp
if (pg1 && pg2) {
    ptr = pg1;
    while (ptr->prev != nullptr) {
        nointer1++;
        ptr = ptr->prev;
    }

    ptr = pg2;
    while (ptr->prev != nullptr) {
        nointer2++;
        ptr = ptr->prev;
    }

    if (nointer2 < nointer1) {
        noInter = nointer2 - 1;
        return pg2;
    }
    else {
        noInter = nointer1 - 1;
        return pg1;
    }
}

noInter = -1;
return nullptr;
```

### Tok izvršavanja

1. BFS kreće od stanice `s`.
2. Svakom prvi put otkrivenom čvoru postavlja se `prev`.
3. Kada se iz reda izvadi `g1` ili `g2`, čuva se pokazivač na odgovarajuću
   stanicu.
4. BFS obilazi ceo dostupan deo grafa.
5. Ako su pronađene obe stanice, praćenjem `prev` broji se broj potega do
   svake.
6. Bira se stanica sa manjim brojem potega.
7. Broj međustanica je broj potega umanjen za jedan.
8. Ako uslov `pg1 && pg2` nije ispunjen, metoda vraća `nullptr` i postavlja
   `noInter = -1`.

### Uloga promenljivih

- `start1` je početna stanica.
- `pg1` i `pg2` su pokazivači na pronađene ciljeve.
- `nointer1` i `nointer2` u toku brojanja zapravo predstavljaju broj potega,
  a ne još broj međustanica.
- `noInter` je izlazni referentni parametar.

### Zašto BFS

Broj potega je mera udaljenosti, pa BFS daje najkraće putanje i odgovarajuće
`prev` pokazivače.

### Prolazak kroz primer

Graf sadrži:

```text
1 -> 2 -> 3 -> 4
 \
  -> 5 -> 6
```

Od `1` do `4` postoje tri potega, a do `6` dva. Metoda bira čvor `6`.

Put `1 -> 5 -> 6` ima jednu međustanicu, pa postavlja:

```text
noInter = 2 - 1 = 1
```

Za početnu stanicu `7`, koja je izolovana, nijedan cilj nije pronađen.
Rezultat je `nullptr`, a `noInter` je `-1`.

### Složenost

- vreme: `O(V + E)` za BFS i do `O(V)` za dve rekonstrukcije;
- dodatni prostor: `O(V)`.

### Granični slučajevi trenutnog koda

- početna stanica mora da postoji; `nullptr` se ne proverava pre
  `q.enqueue(start1)` i `start1->status`;
- metoda bira stanicu samo kada su pronađene obe;
- ako je dostupna samo jedna ciljna stanica, ipak vraća `nullptr` i `-1`;
- kod jednake udaljenosti bira `g1`, jer `else` grana vraća `pg1`;
- ako je cilj jednak početnom čvoru, broj potega je nula, pa se pri izboru
  postavlja `noInter = -1`;
- BFS se ne prekida nakon pronalaska oba cilja.

---

## 7. Oktobar II 2025 - `pathGoesThrough`

### Zahtev zadatka

Treba proveriti da li postoji put od `a` do `c` koji prolazi kroz čvor `b`.

### Korišćena metoda

```cpp
bool pathGoesThrough(int a, int b, int c);
```

### Ključni postojeći kod

Prvi DFS:

```cpp
StackAsArrayLinkedNodeInt q(nodeNum);
LinkedNodeInt* start = findNode(a);
if (!start) {
    return false;
}

q.push(start);
setStatusForAllNodes(1);
start->status = 2;

while (!q.isEmpty()) {
    ptr = q.pop();
    if (ptr->node == b) {
        existsb = true;
        start = ptr;
    }

    adj = ptr->adj;
    ptr->status = 3;
    while (adj) {
        if (adj->dest->status == 1) {
            q.push(adj->dest);
            adj->dest->status = 2;
        }
        adj = adj->link;
    }
}
```

Drugi DFS resetuje statuse, kreće od pronađenog `b` i traži `c`.

### Tok izvršavanja

1. Pronalazi se čvor `a`. Ako ne postoji, rezultat je odmah `false`.
2. Iterativni DFS iz `a` proverava da li je `b` dostupan.
3. Kada pronađe `b`, postavlja `existsb = true` i čuva taj čvor u promenljivoj
   `start`.
4. Prvi DFS nastavlja do kraja dostupnog dela grafa.
5. Ako `b` nije pronađen, vraća se `false`.
6. Statusi se resetuju.
7. Drugi DFS počinje od `b` i traži `c`.
8. Rezultat je `existsb && existsc`.

### Šta tačno metoda dokazuje

Metoda odvojeno dokazuje:

```text
postoji put a -> b
postoji put b -> c
```

Te dve deonice mogu da se nadovežu u prolaz od `a` do `c` kroz `b`. Kod ne
rekonstruiše jednu prostu putanju i ne proverava da li se čvorovi dve deonice
ponavljaju.

### Uloga promenljivih

- `q` je, uprkos imenu, stek tipa `StackAsArrayLinkedNodeInt`.
- `start` prvo pokazuje na `a`, a nakon pronalaska na `b`.
- `existsb` i `existsc` pamte rezultate dve faze.
- status `2` znači da je čvor stavljen na stek, a `3` da je obrađen.

### Zašto DFS

Traži se samo postojanje putanje. DFS ne mora da računa udaljenost i može da
obradi dostupan deo grafa uz jedan stek.

### Prolazak kroz primer

Za:

```text
1 -> 2 -> 3 -> 4
 \
  -> 5 -> 4
6 je izolovan
```

`pathGoesThrough(1, 2, 4)`:

- prvi DFS nalazi `2` iz `1`;
- drugi DFS nalazi `4` iz `2`;
- vraća `true`.

`pathGoesThrough(1, 6, 4)` ne nalazi `6` iz `1` i vraća `false`.

### Složenost

- vreme: `O(V + E)`, uz najviše dva DFS obilaska;
- dodatni prostor: `O(V)`.

### Granični slučajevi trenutnog koda

- ako `a` ne postoji, vraća `false`;
- `b` i `c` se ne traže unapred pomoću `findNode`, već se porede
  identifikatori tokom obilaska;
- ako je `b == a`, prvi DFS prepoznaje početni čvor pri prvom skidanju sa
  steka;
- ako je `c == b`, drugi DFS ga prepoznaje odmah;
- prvi DFS nastavlja i nakon što pronađe `b`;
- metoda menja `status` polja čvorova, ali ih resetuje pre druge faze.

---

## 8. Januar 2026 - topološki redosled sklapanja

Rok je održan 3. marta 2026.

### Zahtev zadatka

Poteg `u -> v` označava da deo `u` mora biti spreman pre dela `v`. Potrebno je
ispisati jedan dozvoljen redosled sklapanja ili utvrditi da ciklus sprečava
obradu svih delova.

### Korišćena metoda

```cpp
long topologicalOrderTravrsal() const;
```

Metoda već postoji u osnovnom templejtu.

### Ključni postojeći kod

Računanje ulaznih stepena:

```cpp
setStatusForAllNodes(0);
while (ptr) {
    adj = ptr->adj;
    while (adj) {
        adj->dest->status++;
        adj = adj->link;
    }
    ptr = ptr->next;
}
```

Kahn-ov obilazak:

```cpp
while (ptr) {
    if (ptr->status == 0) {
        q.enqueue(ptr);
    }
    ptr = ptr->next;
}

while (!q.isEmpty()) {
    ptr = q.dequeue();
    adj = ptr->adj;
    ptr->visit();
    rez++;

    while (adj) {
        adj->dest->status--;
        if (adj->dest->status == 0) {
            q.enqueue(adj->dest);
        }
        adj = adj->link;
    }
}

return rez;
```

### Tok izvršavanja

1. `status` svakog čvora postavlja se na nulu.
2. Prolaskom kroz sve potegove uvećava se status njihovog odredišta. Status
   tada predstavlja ulazni stepen.
3. Svi čvorovi stepena nula stavljaju se u red.
4. Čvor skinut iz reda se štampa i broji kao obrađen.
5. Za svaki njegov izlazni poteg smanjuje se stepen odredišta.
6. Čim odredište dobije stepen nula, stavlja se u red.
7. Metoda vraća broj obrađenih čvorova.

Ako je povratna vrednost jednaka `nodeNum`, svi čvorovi su deo topološkog
redosleda. Manja vrednost znači da su neki čvorovi ostali u ciklusu ili iza
ciklusa.

### Uloga promenljivih

- `status` je ulazni stepen koji se tokom algoritma smanjuje.
- `q` sadrži trenutno dostupne delove bez neobrađenih preduslova.
- `rez` je broj odštampanih čvorova.
- `adj` prolazi kroz zavisne delove trenutnog čvora.

### Zašto Kahn-ov algoritam

Čvor ulaznog stepena nula nema neobrađen preduslov i može odmah biti sklopljen.
Uklanjanje njegovog uticaja može osloboditi sledeće čvorove. Ako red postane
prazan pre obrade svih čvorova, preostali preduslovi se kružno zavise.

### Prolazak kroz primer

Za:

```text
1 -> 2 -> 3 -> 4
```

početni stepen nula ima samo `1`. Obrada redom oslobađa `2`, `3` i `4`.
Metoda štampa:

```text
1 2 3 4
```

i vraća `4`.

Nakon dodavanja `4 -> 1`, svaki čvor ima ulazni stepen jedan. Red je od
početka prazan, ništa se ne štampa i metoda vraća `0`.

### Složenost

- vreme: `O(V + E)`;
- dodatni prostor: `O(V)`.

### Granični slučajevi trenutnog koda

- prazan graf vraća `0`;
- ciklus se ne prijavljuje posebnom vrednošću, već brojem manjim od
  `nodeNum`;
- ako postoji aciklični deo i odvojeni ciklus, metoda štampa aciklični deo i
  vraća njegov broj čvorova;
- kada postoji više čvorova ulaznog stepena nula, redosled zavisi od
  ulančane liste čvorova;
- metoda menja `status`, ali ga na početku svakog poziva ponovo izračunava.

---

## 9. Decembarski rok 2026 - `countSafeNodes`

Rok nazvan „Decembarski“ održan je 16. januara 2026.

### Zahtev zadatka

Čvor je bezbedan ako se iz njega ne može stići do ciklusa. Potrebno je
prebrojati sve takve čvorove.

### Korišćene metode

```cpp
int countSafeNodes() const;
bool isSafe(LinkedNodeInt* ptr) const;
```

### Značenje statusa

U ovoj implementaciji:

```text
0 - još nije obrađen
1 - trenutno je na aktivnoj DFS putanji
2 - dokazano bezbedan
3 - dokazano nebezbedan
```

### Postojeći kod za brojanje

```cpp
int GraphAsListsInt::countSafeNodes() const
{
    setStatusForAllNodes(0);
    int count = 0;
    LinkedNodeInt* ptr = start;

    while (ptr) {
        if (isSafe(ptr)) {
            count++;
        }
        ptr = ptr->next;
    }

    return count;
}
```

### Rekurzivni DFS

```cpp
if (ptr->status == 1) {
    return false;
}
if (ptr->status == 2) {
    return true;
}
if (ptr->status == 3) {
    return false;
}

ptr->status = 1;
LinkedEdgeInt* adj = ptr->adj;

while (adj) {
    if (!isSafe(adj->dest)) {
        ptr->status = 3;
        return false;
    }
    adj = adj->link;
}

ptr->status = 2;
return true;
```

### Tok izvršavanja

1. Svi čvorovi počinju sa statusom `0`.
2. `countSafeNodes` poziva `isSafe` za svaki čvor.
3. Pri prvom ulasku u čvor, njegov status postaje `1`, što znači da je na
   trenutnoj rekurzivnoj putanji.
4. Rekurzivno se proveravaju sva odredišta njegovih izlaznih potega.
5. Ako se tokom te putanje ponovo dođe do čvora statusa `1`, pronađen je
   povratni poteg i ciklus.
6. Čvor iz kog se stiže do nebezbednog suseda dobija status `3` i vraća
   `false`.
7. Ako su svi izlazni susedi bezbedni, čvor dobija status `2`.
8. Već određeni statusi `2` i `3` kasnije se koriste kao zapamćeni rezultat,
   pa se isto podstablo grafa ne analizira iznova.

### Zašto DFS bojenje

Samo „posećen/neposećen“ nije dovoljno, jer je potrebno razlikovati:

- čvor koji je završen u ranijem obilasku;
- čvor koji je još na trenutnoj putanji.

Ponovni susret sa aktivnim čvorom dokazuje ciklus. Konačni status zatim
propagira nebezbednost svim prethodnicima koji mogu da stignu do tog ciklusa.

### Prolazak kroz primer

Graf sadrži:

```text
1 -> 2 -> 3
     ^    |
     |____|

4 -> 5 -> 6
8 -> 4
7 je izolovan
```

- `2` i `3` su u ciklusu;
- `1` vodi do tog ciklusa;
- zato su `{1, 2, 3}` nebezbedni.

Put `8 -> 4 -> 5 -> 6` se završava u čvoru bez izlaznih potega, pa su svi ti
čvorovi bezbedni. Izolovani `7` je takođe bezbedan.

Metoda zato broji `{4, 5, 6, 7, 8}` i vraća `5`.

### Uloga promenljivih

- `ptr` je trenutni DFS čvor.
- `adj` prolazi kroz njegove izlazne potegove.
- `count` je broj poziva `isSafe` koji su vratili `true`.
- `status` istovremeno služi kao boja DFS-a i keš konačnog rezultata.

### Složenost

- vreme: `O(V + E)`, jer svaki čvor konačno dobija status `2` ili `3`, a
  njegovi potegovi se analiziraju u okviru tog određivanja;
- dodatni prostor: `O(V)` u najdubljoj rekurziji.

### Granični slučajevi trenutnog koda

- prazan graf vraća `0`;
- čvor bez izlaznih potega postaje bezbedan;
- samopetlja odmah dovodi do ponovnog susreta sa statusom `1`, pa je čvor
  nebezbedan;
- čvor koji nije u ciklusu, ali ima put do ciklusa, dobija status `3`;
- čim se pronađe jedan nebezbedan sused, metoda se odmah vraća i ne proverava
  preostale susede tog čvora;
- neprovereni susedi biće obrađeni kasnije kada do njih dođe spoljašnja petlja
  ili neki drugi DFS.

---

## Završna napomena

Ovaj dokument obuhvata samo metode koje postoje i u deklaracijama i u
implementaciji trenutnog `GraphAsListsInt` projekta. Mapirani, ali
neimplementirani zadaci `numNeighbours`, `Save`/`Load` i
`pathGoesThroughEdge` nisu uključeni.

Za detaljna objašnjenja implementiranih zadataka sa stablima pogledati
[`detaljno_objasnjenje_stabla.md`](detaljno_objasnjenje_stabla.md).
