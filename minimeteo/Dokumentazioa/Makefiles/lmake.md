# LMAKE


Lmake, Makefileak bezala funtzionatzen du. Desberdintasun babariena, lmake-n *"Makefile"* izeneko fitxategi bat egin beharrean **lua** lengoaian idatzita dagoen *"lmake.lua"* fitxategia sortu behar da. Bertan, hiru funtzio nagusi sortuko dira, *build, upload* eta *clean*. Makefile batean bezala aldagaiak sor daitezke, parametroen erazagupena dinamikoagoa izateko.
Lmake lagungarria izan daiteke, fitxategi bat baino gehiago konpilatu nahi direnean, *"lmake.lua"* fitxategia idaztea, Makefilea egitea baino sinpleagoa suertatu daiteke kasu honetan.


## Azalpena
##### build

Build prozesuaren barruan hainbat pauso desberdin daude:

1) **konpiladorearen konfigurazioa:** konpiladorea konfiguratzeko *lmake_set_compiler* komando sorta erabiliko dugu.
    - *lmake_set_compiler*: konpiladorea zehaztu.
    - *lmake_set_compilar_flags*: konpiladorearen flag-ak zehazteko
    - *lmake_set_compiler_out*:
2) **Fitxategiak eskuratu eta konpilatu:** Fitxategiak bilatzeko *lmake_find("./\*.c")* erabiliko da eta konpilatzeko *lmake_compile*.

3) **Linkerra konfiguratu:** Konpiladorearen antzera, *lmake_set_linker* komando sorta erabiliko da kasu honetan.
    - *lmake_set_linker*: Linkerra zehaztu.
    - *lmake_set_linker_flags*: Linkerraren flag-ak zehaztu.
    - *lmake_set_linker_out*: Emaitza fitxategiaren izena
4) **objektu fitxategiak eskuratu eta elkartu:** Objektu fitxategiak bilatzeko *lmake_find("./\*.o")* erabiliko da. eta elkartzeko *lmake_link*. 
5) **Mikrokontrolagailuak uler dezan fitxategia eraldatu:** *lmake_exec* erabilta barruan komandoa zehaztuz, exekutatu egingo da.
##### upload

Kodea Mikrora igotzeko, lehen bezala *lmake_exec* erabiliko da, barruan *avrdude*-ren komandoa daukalarik.
##### clean

Sobera dauden fitxategiak garbitzeko ere *lmake_exec* komandoaz baliatuko gara, barruan rm exekutatzeko.

## Erabilera

Kodea konpilatzeko:

    lmake build

Kodea mikrora igotzeko:
    
    lmake upload

Fitxategiak garbitzeko:

    lmake clean


## Instalazioa

Lmake instalatzeko github-eko repositorio bat klonatu egin behar da.

    git clone https://github.com/IkerGalardi/LMake.git

Honek beharrezke fitxategiak deskargatuko ditu, gure sisteman instalatzeko *install.sh* fitxategia exekutatu beharko dugu administradore baimenekin.

    sudo ./install.sh

Instalazioak errorea eman dezake, nire kasuan c++ eko konpiladorea ez zegoelako intalatuta. Konpontzeko *g++* paketea instalatu behar da.

Debianen oinarritutako banaketak (Debian, Ubuntu...)
    
    sudo apt install g++
