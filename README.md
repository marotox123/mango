# mango

A nano like editor for Windows console.

Prosty edytor tekstu na konsolę Windows napisany w czystym C. Rysuje interfejs
przy pomocy sekwencji ANSI (`\033[...`) i obsługuje klawiaturę przez WinAPI
(`conio.h`, `GetAsyncKeyState`).

## Build

Wymaga MinGW (`x86_64-w64-mingw32-gcc`) lub natywnego `gcc` na Windows.

```sh
make          # buduje mango.exe
make run      # buduje i uruchamia
make clean    # sprząta
```

## Użycie

```
mango.exe <plik>
```

Otwiera `<plik>` w trybie edycji na cały ekran konsoli.

### Skróty klawiszowe

- `Ctrl+S` — zapisz
- `ESC` — wyjście
- strzałki — nawigacja

`Ctrl+Z / C / V / X / A` (undo/copy/paste/cut/select all) są w pasku
skrótów, ale w kodzie tylko przerywają pętlę menu — nie są jeszcze
zaimplementowane (patrz `to do.txt`).

## Struktura kodu

Program był pierwotnie jednym plikiem (`main.c`, ~370 linii). Podzielony na
moduły:

| Plik | Zawartość |
|---|---|
| `common.h` | wspólne include'y i stałe `CTRL_*` |
| `terminal.h/.c` | niskopoziomowe rzeczy konsolowe: `gotoxy`, `ctrl_held` |
| `display.h/.c` | rysowanie: pasek góra/dół, obszar tekstu, pełne i częściowe odświeżanie ekranu |
| `fileio.h/.c` | wczytywanie i zapisywanie pliku (`odczytaj`, `save_file`) |
| `cursor.h/.c` | konwersja pozycji kursora bufor ↔ współrzędne (x, y) na ekranie |
| `editor.h/.c` | pętla edycji (`editmode`), menu Ctrl (`quick_menu`), ekran startowy (`start`) |
| `main.c` | wejście programu — parsowanie argumentów, rozmiar konsoli, uruchomienie |

Bufor tekstu to jeden `char*` alokowany z zapasem 64 KB na edycję, bez
struktury linii — pozycje liczone są przeliczeniem znaków `\n` przy każdym
odwołaniu (`cursor_pos_to_xy` / `xy_to_cursor_pos`). Odświeżanie ekranu ma
dwa tryby: pełne (`wyswietl_tekst_silent`, używane przy zmianach układu np.
Enter/Backspace na `\n`) i częściowe od bieżącej linii w dół
(`refresh_from_line`, przy zwykłym pisaniu) — dla wydajności.

## Znane ograniczenia / TODO

Z `to do.txt`:
- brak limitu długości nazwy pliku
- program się zawiesza po Ctrl — trzeba to naprawić Ctrl-em (sic)

Poza tym: undo/copy/paste/cut/select all są tylko w pasku podpowiedzi,
kod ich jeszcze nie realizuje.
