# Algo
a bit of everything
    
  
### Contents

Source here: [profs.info.uaic.ro/~vcosmin/dsfum](http://profs.info.uaic.ro/~vcosmin/dsfum)
```
1. Afişaţi numerele de la 0 la 9999 pe display (la 1 nu se afişeaza 0001 ci doar 1). - 1pt
2. Aceeasi problema a mai sus dar tinand shiledul invers (180 de grade). Evident, cifrele trebuie sa fie afisate corect - 4pt
3. Cantat iepuras dragalas (sau alta melodie cu cel putin 4-5 note diferite) la buzzer. - 3pt fara tempo, 5pt cu tempo (cele doua se exclud dar daca o faceti pe prima si o imbunatatiti, capatati si cele doua puncte ramase). Pentru utilizarea potentiometrului in controlul volumului - inca 2pt.
4. Numarati in binar pana la 15 pe cele 4 leduri disponibile. - 2pt
5. Prin intermediul potentiometrului faceti ca ledul conectat la pinul 11 sa faca fade in/out in functie de pozitia potentiometrului. - 2pt
6. Aceeasi problema ca la punctul 5 dar pentru ledul de la pinul 12. - 3pt
7. Stopwatch cu butoanele (start / pause si lap furnizat pe serial) si cu afisorul de cifre. - 4pt
8. Afisati temperatura procesorului (sau alte informatii numerice de nivel hardware ale PC) pe displayul de leduri. - 9pt
9. Faceti o telecomanda pentru calculator folosind cele 3 butoane. - 7pt
10. Afisati valoarea potentiometrului pe displayul numeric. - 1pt
11. Cele trei linii orizontale a fiecarei cifre indica o pozitie a unui obstacol. La cifra unintatilor se afla o masina (reprezentata tot ca o linie orizontala). Creati o animatie (obstacolele se vor indrepta catre masina) si prin intermediul a doua din cele 3 butoane disponibile ghidati masina printre obstacole. Generati labirintul in asa fel incat masina mereu sa aiba o portita de scapare si construiti un efect sonor atunci cand aceasta se ciocneste de un obstacol - utilizati buzzerul pentru a-l reda. - 7pt
12. In cele trei gaurele dinspre buzzer se poate pune un senzor IR cu fata (X-ul) spre butoane. Detectati prin intermediul lui codurile generate de o telecomanda (scrieti-le in consola seriala) - 3pt
13. Combinati punctele 12 si 9 pentru a face o telecomanda wireless pentru PC. - 4pt
14. Privind afisajul numeric la 90 de grade, pe el se poate afisa o singura cifra (mare). Afisati pe rand cifrele de la 0 la F (in hexazecimal) incrementand sau decrementand la apasarea butoanelor. - 5pt
15. O aplicatie casa de marcat folosind portul serial:
	a. Adaugare produs: in consola seriala se va furniza un cod-produs care este hardcodat (deocamdata) in Arduino ce cunoaste triplete de forma cod-denumire-pret (hardcodati minim 10 produse). La fiecare adaugare noua se va afisa pe LCD denumirea, pretul produsului taxat pe moment si pretului final (al tuturor produselor comandate). - 2pt
	b. multiplicare produs adaugat anterior (utilizand butoanele din dotarea shieldului, gasiti o metoda sa faceti aceasta operatie). - 2pt
	c. eliminare completa a unui produs oarecare deja adaugat (tot din butoane). - 2pt
	d. eliberare bon (se vor afisa informatiile finale legate de comanda: produse, preturi individuale (sau pentru produse multiple), pret total. Informatiile vor fi transmise pe portul serial catre consola Arduino. - 2pt
16. Text care defileaza cu viteza reglabila de la dreapta la stanga, viteza se va modifica din butoanele de pe LCD "Welcome to DSFUM Text LCD Lab !!!" - 2pt
```