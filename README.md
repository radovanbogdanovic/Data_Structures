# Strukture podataka - templejti i urađeni zadaci

Ovaj repozitorijum sadrži C++ templejte i urađene zadatke sa blanketa iz
predmeta **Strukture podataka**. Zadaci su raspoređeni u Visual Studio projekte
prema strukturi podataka koju koriste.

Trenutno su uključeni projekti za:

- uređeno celobrojno binarno stablo pretrage;
- usmereni dinamički graf predstavljen listama suseda.

Pored izvornog koda, repozitorijum sadrži mapiranje zadataka na templejte,
gotove `main.cpp` primere i detaljna objašnjenja postojećih rešenja.

## Sadržaj

1. [Brzi početak](#brzi-početak)
2. [Potrebni alati](#potrebni-alati)
3. [Struktura repozitorijuma](#struktura-repozitorijuma)
4. [Kako se pokreće zadatak](#kako-se-pokreće-zadatak)
5. [Kako se dodaje novi zadatak](#kako-se-dodaje-novi-zadatak)
6. [Dokumentacija](#dokumentacija)
7. [Dostupni urađeni zadaci](#dostupni-urađeni-zadaci)
8. [Važne napomene o templejtima](#važne-napomene-o-templejtima)
9. [Rad sa Git-om](#rad-sa-git-om)
10. [Česti problemi](#česti-problemi)

## Brzi početak

Kloniraj repozitorijum:

```bash
git clone git@github.com:radovanbogdanovic/Data_Structures.git
cd Data_Structures
```

Zatim otvori odgovarajući Visual Studio solution:

- za stabla:
  `CelobrojnoBinarnoStabloPretrage/CelobrojnoBinarnoStabloPretrage.sln`;
- za grafove:
  `CelobrojniGraf/CelobrojniGraf.sln`.

U projektu:

1. otvori `main.cpp`;
2. ostavi aktivan samo jedan `main()` test;
3. izaberi konfiguraciju `Debug` i odgovarajuću platformu, na primer `x64`;
4. pokreni **Build > Build Solution**;
5. pokreni program pomoću **Ctrl+F5**.

> U jednom projektu sme postojati samo jedna aktivna `main()` funkcija.
> Većina testova u postojećim `main.cpp` fajlovima je komentarisana upravo
> zato da ne bi došlo do višestruke definicije funkcije `main`.

## Potrebni alati

Projekti su napravljeni za:

- Windows;
- Visual Studio 2019 ili noviji;
- workload **Desktop development with C++**;
- Windows 10 SDK;
- platform toolset `v142`.

Ako koristiš noviji Visual Studio i nemaš `v142`, možeš:

- instalirati **MSVC v142 build tools** kroz Visual Studio Installer; ili
- prihvatiti Visual Studio ponudu za retargetovanje projekta na noviji
  toolset, na primer `v143`.

Za čitanje Markdown dokumentacije možeš koristiti GitHub, Visual Studio Code
ili ugrađeni Markdown pregled u editoru.

## Struktura repozitorijuma

```text
SP_templejti/
|
|-- CelobrojnoBinarnoStabloPretrage/
|   |-- CelobrojnoBinarnoStabloPretrage.sln
|   `-- CelobrojnoBinarnoStabloPretrage/
|       |-- BSTNodeInt.h
|       |-- BSTreeInt.h
|       |-- BSTreeInt.cpp
|       |-- QueueAsArrayInt.h/.cpp
|       |-- StackAsArrayInt.h/.cpp
|       `-- main.cpp
|
|-- CelobrojniGraf/
|   |-- CelobrojniGraf.sln
|   `-- CelobrojniGraf/
|       |-- GraphInt.h
|       |-- GraphInt.cpp
|       |-- LinkedNodeInt.h/.cpp
|       |-- LinkedEdgeInt.h/.cpp
|       |-- QueueAsArrayInt.h/.cpp
|       |-- StackAsArrayInt.h/.cpp
|       `-- main.cpp
|
|-- mapiranje_blanketa_i_templejta.md
|-- mapiranje_grafova_i_templejta.md
|-- main_primeri_za_blankete.md
|-- main_primeri_za_grafove.md
|-- detaljno_objasnjenje_stabla.md
`-- detaljno_objasnjenje_grafovi.md
```

### Projekat za binarno stablo pretrage

Glavna klasa je:

```cpp
BSTreeInt
```

Čvor stabla je:

```cpp
BSTNodeInt
```

Deklaracije metoda nalaze se u `BSTreeInt.h`, implementacije u
`BSTreeInt.cpp`, a primeri korišćenja u `main.cpp`.

### Projekat za graf

Glavna klasa je:

```cpp
GraphAsListsInt
```

Graf koristi:

- `LinkedNodeInt` za čvorove;
- `LinkedEdgeInt` za potegove;
- `QueueAsArrayLinkedNodeInt` za BFS;
- `StackAsArrayLinkedNodeInt` za iterativni DFS.

Deklaracije metoda nalaze se u `GraphInt.h`, implementacije u `GraphInt.cpp`,
a primeri korišćenja u `main.cpp`.

## Kako se pokreće zadatak

### 1. Odredi kojoj strukturi zadatak pripada

Ako zadatak koristi:

- BST, uređeno binarno stablo ili ključeve raspoređene po veličini, koristi
  projekat `CelobrojnoBinarnoStabloPretrage`;
- čvorove, potegove, putanje, BFS, DFS, komponente ili topološko sortiranje,
  koristi projekat `CelobrojniGraf`.

Mapiranje postojećih blanketa nalazi se u:

- [mapiranju svih zadataka](mapiranje_blanketa_i_templejta.md);
- [detaljnom mapiranju grafova](mapiranje_grafova_i_templejta.md).

### 2. Pronađi implementaciju

Za stabla:

```text
deklaracija   -> BSTreeInt.h
implementacija -> BSTreeInt.cpp
test           -> main.cpp
```

Za grafove:

```text
deklaracija   -> GraphInt.h
implementacija -> GraphInt.cpp
test           -> main.cpp
```

### 3. Aktiviraj odgovarajući `main`

Postojeći `main.cpp` fajlovi sadrže više testova. Većina njih je komentarisana.

Da pokreneš drugi test:

1. komentariši trenutno aktivnu `main()` funkciju;
2. pronađi željeni test u istom fajlu ili u dokumentu sa `main` primerima;
3. ukloni komentare sa tog testa;
4. proveri da je samo jedna `main()` funkcija aktivna;
5. ponovo izgradi projekat.

Kompletni test-primeri nalaze se u:

- [primerima za stabla](main_primeri_za_blankete.md);
- [primerima za grafove](main_primeri_za_grafove.md).

### 4. Pokreni i proveri rezultat

U Visual Studio-u:

```text
Build Solution: Ctrl+Shift+B
Run without debugging: Ctrl+F5
```

Uporedi rezultat sa očekivanim ispisom navedenim uz odgovarajući test.

Kod grafovskog projekta se na kraju može pojaviti:

```text
Not implemented!
```

To ispisuje trenutni destruktor klase `GraphAsListsInt`. Ta poruka nije deo
rezultata ispitnog zadatka.

## Kako se dodaje novi zadatak

### Zadatak sa stablima

1. Dodaj deklaraciju javne metode u `BSTreeInt.h`.
2. Ako je potrebna pomoćna rekurzivna metoda, dodaj i njenu deklaraciju.
3. Implementaciju napiši u `BSTreeInt.cpp`.
4. U `main.cpp` napravi mali test sa jasnim očekivanim rezultatom.
5. Proveri prazno stablo, jedan čvor i tipičan primer.

Primer organizacije:

```cpp
// BSTreeInt.h
public:
    int novaMetoda() const;

protected:
    int novaMetoda(BSTNodeInt* ptr) const;
```

```cpp
// BSTreeInt.cpp
int BSTreeInt::novaMetoda(BSTNodeInt* ptr) const
{
    if (ptr == nullptr)
        return 0;

    // Obrada trenutnog čvora i podstabala.
}

int BSTreeInt::novaMetoda() const
{
    return novaMetoda(root);
}
```

Izaberi obilazak prema podatku koji je potreban:

- preorder kada se čvor obrađuje pre potomaka;
- inorder kada je važan sortirani redosled BST ključeva;
- postorder kada rezultat roditelja zavisi od rezultata oba podstabla;
- BFS kada se radi po nivoima ili traži dubina.

### Zadatak sa grafovima

1. Dodaj deklaraciju javne metode u `GraphInt.h`.
2. Dodaj samo neophodne pomoćne metode.
3. Implementaciju napiši u `GraphInt.cpp`.
4. Resetuj `status` pre svakog nezavisnog obilaska.
5. Ako koristiš najkraći put po broju potega, postavi i `prev`.
6. Napravi mali test u `main.cpp`.

Tipična priprema za obilazak:

```cpp
setStatusForAllNodes(1);

LinkedNodeInt* source = findNode(startNode);
if (source == nullptr)
    return false;
```

Izaberi algoritam prema zadatku:

- BFS za najkraći put po broju potega, udaljenost i nivoe;
- DFS za proveru dostupnosti, cikluse i obilazak komponenti;
- Kahn-ov algoritam za topološko sortiranje;
- `findEdge` kada je potreban konkretan direktan poteg.

## Dokumentacija

### Brzo mapiranje zadataka

[mapiranje_blanketa_i_templejta.md](mapiranje_blanketa_i_templejta.md)
sadrži pregled zadataka po rokovima i odgovarajućim projektima.

[mapiranje_grafova_i_templejta.md](mapiranje_grafova_i_templejta.md)
detaljnije opisuje način prilagođavanja grafovskih zadataka klasi
`GraphAsListsInt`.

### Gotovi test-primeri

[main_primeri_za_blankete.md](main_primeri_za_blankete.md) sadrži
`main.cpp` primere za zadatke sa stablima.

[main_primeri_za_grafove.md](main_primeri_za_grafove.md) sadrži
`main.cpp` primere za zadatke sa grafovima.

### Detaljna objašnjenja postojećeg koda

[detaljno_objasnjenje_stabla.md](detaljno_objasnjenje_stabla.md) objašnjava:

- zahtev svakog zadatka;
- korišćene metode;
- tok izvršavanja;
- ulogu promenljivih;
- razlog izbora obilaska;
- prolazak kroz primer;
- vremensku i prostornu složenost;
- stvarno ponašanje u graničnim slučajevima.

[detaljno_objasnjenje_grafovi.md](detaljno_objasnjenje_grafovi.md) daje isti
nivo objašnjenja za implementirane grafovske zadatke.

## Dostupni urađeni zadaci

### Binarno stablo pretrage

| Rok | Metode |
|---|---|
| Januar 2024 | `countCloseParents` |
| Jun 2024 | `deleteLeaves`, `maxLevel` |
| Jun II 2024 | `minEvenDiff` |
| P2 grupa B 2024 | `populate`, `sumInterval` |
| P2 grupa A 2024 | `create`, `inorderDistance` |
| April 2025 | `findDeepestLeaf` |
| Oktobar II 2025 | `getDeepestEvenParent` |
| Oktobar III 2025 | `maxLevelCount` |
| Januar 2026 | `sumUpThePath` |
| Decembarski rok 2026 | `maxDiffOfEvenNodes` |

### Grafovi

| Rok | Metode |
|---|---|
| Januar 2024 | `arePathsPossible` |
| Jun 2024 | `printMaxConnectedComponentNodes` |
| Jun II 2024 | `defineOrder` |
| P2 grupa B 2024 | `whichOneIsCloser`, `ensureEdgeExists` |
| P2 grupa A 2024 | `pathThroughEdgeExists` |
| April 2025 | `FindStation` |
| Oktobar II 2025 | `pathGoesThrough` |
| Januar 2026 | `topologicalOrderTravrsal` |
| Decembarski rok 2026 | `countSafeNodes`, `isSafe` |

Ova tabela prikazuje metode koje trenutno postoje u `.h` i `.cpp` fajlovima.
Mapirani zadaci koji još nemaju implementaciju nisu navedeni kao urađeni.

## Važne napomene o templejtima

### `insert` i `add` nisu isto

U `BSTreeInt` projektu:

- `insert` dozvoljava duplikate i smešta jednaku vrednost ulevo;
- `add` proverava da li ključ već postoji i ne dodaje duplikat.

Zato obrati pažnju koju metodu zahteva tekst zadatka.

### Neki zadaci su za obično binarno stablo

Deo blanketa traži obično, neuređeno binarno stablo. Pošto je aktivni projekat
`BSTreeInt`, takvi zadaci su vežbani u njemu kada algoritam ne zavisi od BST
poretka, na primer:

- brisanje listova;
- brojanje čvorova po nivoima;
- pronalaženje najdubljeg lista;
- poređenje rezultata levog i desnog podstabla.

Kod takvih zadataka nemoj koristiti BST osobinu ako je tekst zadatka ne
garantuje.

### Graf je usmeren

Jedan poziv:

```cpp
graph.insertEdge(a, b);
```

dodaje samo:

```text
a -> b
```

Za neusmerenu vezu potrebna su dva potega:

```cpp
graph.insertEdge(a, b);
graph.insertEdge(b, a);
```

### Redosled obilaska zavisi od umetanja

Novi čvor i novi poteg dodaju se na početak svojih ulančanih lista. Zato
redosled BFS/DFS ispisa može biti obrnut u odnosu na redosled poziva
`insertNode` i `insertEdge`.

Ako zadatak dozvoljava više ispravnih redosleda, proveravaj skup čvorova i
logiku rezultata, a ne samo jedan tačno određen ispis.

### `status` i `prev`

Grafovske metode koriste polja čvora kao privremenu radnu memoriju:

- `status` za posećenost, DFS boju ili ulazni stepen;
- `prev` za prethodnika na BFS putanji.

Pre novog nezavisnog obilaska statusi moraju biti pravilno postavljeni.
Značenje konkretnih vrednosti proveri u metodi koju koristiš.

### Težina potega

Klasa `LinkedEdgeInt` ima polje `weight`, ali trenutni `insertEdge` ne koristi
prosleđeni argument `weight` pri pravljenju potega. Ako zadatak radi sa
težinama, obavezno proveri stvarno ponašanje postojeće implementacije.

### Destruktor grafa

Destruktor klase `GraphAsListsInt` nije implementiran i trenutno samo ispisuje:

```text
Not implemented!
```

Ta poruka se može pojaviti posle očekivanog rezultata testa.

## Rad sa Git-om

### Pre početka rada

Proveri stanje repozitorijuma:

```bash
git status
```

Preuzmi najnovije izmene:

```bash
git pull
```

Ako radiš novi zadatak, preporučeno je da napraviš posebnu granu:

```bash
git switch -c zadatak/naziv-zadatka
```

### Čuvanje izmene

Ponovo proveri šta je promenjeno:

```bash
git status
git diff
```

Dodaj samo fajlove koji pripadaju zadatku:

```bash
git add putanja/do/fajla
```

Napravi jasan commit:

```bash
git commit -m "Dodaj resenje zadatka naziv-zadatka"
```

Pošalji granu na GitHub:

```bash
git push -u origin zadatak/naziv-zadatka
```

### Šta ne treba dodavati u Git

`.gitignore` već isključuje:

- `.vs/`;
- `Debug/`, `Release/`, `x64/` i `x86/`;
- `.obj`, `.pdb`, `.exe` i druge build artefakte;
- Visual Studio korisničke i privremene fajlove.

U commit uglavnom ulaze:

- `.h` deklaracije;
- `.cpp` implementacije;
- relevantni `main.cpp` testovi;
- Markdown dokumentacija.

Pre commita uvek pogledaj `git status` da slučajno ne uključiš tuđe ili
nepovezane izmene.

## Česti problemi

### Greška: više definicija funkcije `main`

Uzrok: u istom projektu je aktivirano više `main()` funkcija.

Rešenje: komentariši sve testove osim jednog.

### Visual Studio ne nalazi `v142`

Uzrok: nije instaliran Visual Studio 2019 C++ toolset.

Rešenje: instaliraj `MSVC v142` ili retargetuj projekat na toolset koji imaš.

### Program ispisuje `Not implemented!`

Uzrok: pozvan je destruktor grafa.

To nije rezultat zadatka, već postojeće ponašanje `GraphAsListsInt`
destruktora.

### Graf daje drugačiji, ali logički ispravan redosled

BFS, DFS i topološko sortiranje mogu imati više ispravnih redosleda. U ovom
templejtu redosled zavisi od toga što se novi čvorovi i potegovi dodaju na
početak ulančanih lista.

### Putanja iz prethodnog testa utiče na sledeći obilazak

Proveri da li su pre novog BFS/DFS obilaska resetovani `status` i, kada je
potrebno, `prev` pokazivači.

### Novi metod je napisan, ali linker javlja grešku

Proveri:

- da li se deklaracija u `.h` i definicija u `.cpp` potpuno poklapaju;
- da li oba potpisa imaju isti `const`;
- da li je naveden prefiks klase, na primer
  `BSTreeInt::imeMetode` ili `GraphAsListsInt::imeMetode`;
- da li je `.cpp` fajl uključen u Visual Studio projekat.

## Preporučeni način učenja

1. Pročitaj originalni zahtev zadatka.
2. Pronađi odgovarajući projekat i metodu.
3. Pre čitanja rešenja pokušaj da odrediš potreban obilazak.
4. Prođi kod ručno nad malim primerom.
5. Pokreni postojeći `main.cpp` test.
6. Promeni test-podatke i proveri granične slučajeve.
7. Tek zatim pročitaj detaljno objašnjenje i složenost.

Repozitorijum je prvenstveno namenjen vežbanju načina razmišljanja nad
strukturama podataka, a ne samo kopiranju gotovih metoda.
