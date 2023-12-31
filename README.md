#README
wstęp

Projekt ten ma na celu stworzenie gry polegającej na przeskakiwaniu przeszkód.

w projekcie wykorzystano język programowania C++ oraz bibliotekę SFML.

Instalacja

aby skompilować kod źródłowy potrzebujemy kompilatora C++ oraz skonfigurowanej biblioteki SFML.

w zależności od wybranego środowiska konfiguracja może się różnić poniżej instalacja dla Visual Studio:

1.  Pobierz bibliotekę SFML ze strony oficjalnej: [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php) Wybierz wersję biblioteki, która odpowiada Twojej wersji Visual Studio (na przykład, jeśli używasz Visual Studio 2019, pobierz odpowiednią wersję dla tej wersji)
2.  W projekcie kliknij prawym przyciskiem myszy na nazwę projektu w eksploratorze rozwiązań i wybierz opcję "Właściwości".
3.  W oknie właściwości projektu przejdź do sekcji "Konfiguracje właściwości" i wybierz "Wszystkie konfiguracje" oraz "Wszystkie platformy" (jeśli masz kilka konfiguracji i platform).
4.  Wybierz "C/C++" w lewym panelu i kliknij na "Ogólne".
5.  Edytuj pole "Dodatkowe katalogi zawierające pliki nagłówkowe" (Additional Include Directories) i dodaj ścieżkę do katalogu zawierającego nagłówki SFML, które zostały rozpakowane. Na przykład, jeśli rozpakowałeś SFML do "C:\\SFML", to dodaj "C:\\SFML\\include" jako ścieżkę.
6.  Następnie, wciąż w sekcji "C/C++", wybierz "Kompilator" i kliknij na "Zaawansowane".
7.  W polu "Zestawienie kodowania znaków" (Character Set) wybierz "Unicode".
8.  Wybierz "Linker" w lewym panelu i kliknij na "Ogólne".
9.  Edytuj pole "Dodatkowe katalogi bibliotek" (Additional Library Directories) i dodaj ścieżkę do katalogu zawierającego biblioteki SFML. Na przykład, jeśli rozpakowałeś SFML do "C:\\SFML", to dodaj "C:\\SFML\\lib" jako ścieżkę.
10.  Wciąż w sekcji "Linker", wybierz "Wejście" (Input).
11.  Kliknij na "Dodatkowe zależności" (Additional Dependencies) i dodaj nazwy bibliotek SFML, których potrzebujesz w swoim projekcie. Na przykład, jeśli używasz SFML dla grafiki 2D, dodaj "sfml-graphics.lib", "sfml-window.lib" i "sfml-system.lib".
12.  Teraz możesz użyć funkcji i klas z biblioteki SFML w swoim projekcie. Upewnij się, że dodajesz odpowiednie dyrektywy preprocesora i includujesz nagłówki SFML w swoim kodzie.
13.  Skompiluj i uruchom projekt. Jeśli wszystko zostało poprawnie skonfigurowane, powinieneś móc skompilować i uruchomić aplikację korzystającą z SFML w Visual Studio.

  
  

kompilator C++ jest instalowany w pakiecie z Visual studio które można łatwo zainstalować dzięki graficznemu interfejsowi.

  
  

![](Dokumentacja/1.png)

Funkcja void wczytująca dane z poprzednich sesji pozwala na przechowywanie wyników po zamknięciu aplikacji.

![](Dokumentacja/2.png)

Funkcja void która wczytuje ostatnie 10 zapisanych wyników punktowych do pliku w celu zapisania danych.

![](Dokumentacja/3.png)

Struktura pozwalająca na przełączanie zawartości okna (menu,rozgrywka,oraz tablica wyników) podczas korzystania z aplikacji.

![](Dokumentacja/4.png)

Obsługa zdarzenia naciśnięcia klawisza S powodującego przeniesienie do rozgrywki.

![](Dokumentacja/5.png)

Obsługa klawisza T który przenosi do tablicy wyników z aktualizacją wyników (szczytuje z kolejki oraz zapisuje w tablicy).

![](Dokumentacja/6.png)

Obsługa klawisza M który przenosi do ekranu tytułowego gry.

![](Dokumentacja/7.png)

obsługa restartu przypisanego do klawisza R pozwala na zresetowanie gry po porażce usuwa również wszystkie elementy z kontenera przechowującego przeszkody oraz ustawia wszystkie zmienne wykorzystywane w grze na początkowe wartości.

![](Dokumentacja/8.png)

Usuwanie przeszkód które są poza wyświetlaną częścią ekranu w celu rozwiązania problemu ewentualnego wycieku pamięci.

![](Dokumentacja/10.png)

Obsługa skoku awatara gracza zawiera prostą grawitację oraz warunek sprawdzający czy skok jest dozwolony.

![](Dokumentacja/9.png)

Ten fragment kodu jest odpowiedzialny za generowanie nowych przeszkód w określonym interwale czasowym, jeśli liczba przeszkód nie przekracza maksymalnej wartości. Każda przeszkoda ma losową prędkość, oraz losowo przydzielaną teksture.

![](Dokumentacja/11.png)

fragment kodu odpowiadający za zapisywanie wyniku do pliku tekstowego.

Panda Run

![](Dokumentacja/13.png) ![](Dokumentacja/12.png) ![](Dokumentacja/14.png)

Gra polega na przeskakiwaniu przeszkód które panda napotyka podczas biegu w celu skoku należy nacisnąć spację jeżeli nie uda nam się przeskoczyć elementu możemy zobaczyć swój wyniki oraz rozpocząć gre ponownie naciskająć klawisz R.

gra posiada międzysesyjną tablice wyników która pozwala zobaczyć ile punktów udało się zdobyć w 10 ostatnich podejściach .

linki zewnętrzne

poradnik instalacji sfml https://www.sfml-dev.org/tutorials/2.5/start-vc.php

Github https://github.com/yvv138/PandaRunn.git
