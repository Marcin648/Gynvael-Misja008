![](http://i.imgur.com/7AAKTjq.png)
# misja008_drone_io
CTF challenge http://gynvael.coldwind.pl/misja008_drone_io/

# Sterowanie
`↑` - Dron w górę
`←` - Dron w lewo
`→` - Dron w prawo
`↓` - Dron w dół
`e` - Autopilot (tylko przy ścianie)
`s` - Zrzut ekranu

# Misja
http://gynvael.vexillium.org/ext/70809d8a8c51f6963a882f906dd21c18bd37428b_misja008.txt
Zadanie wydaje się proste, napisać interfejs i przejść tunele.
Wybrałem do tego celu c++ wraz z SFML, ponieważ chciałem lepiej poznać tę bibliotekę. SFML nadał się idealnie ;)

# Cache
Jedna pozycja odpowiadała jednemu odpytaniu serwera, co niekoniecznie sprzyja wydajności.
Zaimplementowałem prosty cache na plikach tak, aby odpytywać serwer, tylko gdy nie byliśmy nigdy na danej pozycji.
Sprzyjały temu nazwy plików, które były unikalne.

# Matematyka
Posiadamy dane ze skanera przedstawiające odległość do ścian o rozdzielczości 10° oraz pozycję drona.
Przydała się zwykła trygonometria.

```
for(unsigned int i = 0; i < distance.size(); i++){
if(distance.at(i) == INFINITY){
continue;
}
float a = (i*10.f)* M_PI / 180.0f ;
float y = cosf(a) * distance.at(i);
float x = sinf(a) * distance.at(i);

sf::Vertex point;
point.color = sf::Color(255, 255, 255);
point.position = sf::Vector2f(position.x + x, position.y - y);

points.push_back(point);
}
```

Teraz starczy tylko to narysować.

# Rysowanie
Na początku próbowałem rysować za pomocą linii, co dało dość słaby efekt.
![](http://i.imgur.com/seUrZiJ.png)

Następna próba z kropkami wypadła o wiele lepiej.
![](http://i.imgur.com/e7zJSra.png)

# Strategia
Proste sprawdzenie każdej pozycji trwałoby zbyt długo, trzeba było wymyślić lepsze podejście.
Postanowiłem, że dron będzie się trzymać ścian. Pozwoli to zeskanować tunel dość efektywnie.

# Mapa
Mapa 8K
https://raw.githubusercontent.com/Marcin648/misja008_drone_io/master/misja008_drone_io/map.png

# Film
https://www.youtube.com/watch?v=s1PquOqELIc
