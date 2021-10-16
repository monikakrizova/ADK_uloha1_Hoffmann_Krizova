# Aktualni stav :D 
Momentalne funguje zvyrazneni polygonu po pridani bodu (a stisku analyze), takze zadani splneno
--- jen je potreba zmenit cestu k txt souboru s polygony, zatim to tam je natvrdo (soubor draq.cpp radek 31)

TODO aby to bylo hezci:<br>
- zlepsit nacitani polygonu ze souboru (ted je na kazdem radku polygonu jeden bod s id, do polygonu se body postupne pidavaji dokud se nedojde k id 1)<br>
- udelat to, aby se pri kliknuti na Load polygon otevrelo okno pro vyber souboru

TODO pro maximalni pocet bodu:<br>
- Analýza polohy bodu (uvnitr/vne) metodou Ray Algorithm. +5b<br>
- Osetrení singulárního prípadu u Ray Algorithm: bod lezí na hrany polygonu. +5b<br>
- Osetrení singulárního prípadu u obou algoritm·: bod je totozný s vrcholem jednoho ci více polygon·. +2b<br>
- Zvýraznení vsech polygon· pro oba výse uvedené singulární prípady. +2b
