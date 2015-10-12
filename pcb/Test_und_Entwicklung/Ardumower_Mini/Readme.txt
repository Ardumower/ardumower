Die Platinen wurden erstellt für einen Miniardumover der für experimente an der Software in der Wohnung gedacht ist.
Als Grundlage  wurde ein Arduino Mega benötigt ein Sensor Megashield und ein Motortreiber.
Die Verbindungen von der Platine sind mit Steckverbinden zum Sensor Shield herzustellen.

Die Platine ist vorgesehen zur einseitigen Ätzung. (grünen Leiterbahnen)
Sollte eine 2 seitige Platine erstellt werden, sollten die roten Leiterbahnen besser verlegt werden
und im Querschnitt angepasst werden.
Bei den roten Leiterbahnen sind extra größere Löche (Durchkontaktierungen) vorgesehen, damit man 
die roten Leiterbahnen auf der Bestückungsseite als Drahtbrücken ausführen kann. 

Aus Platzgründen wurde auf Sicherungen und Schutzdioden verzichtet. 
Deswegen also Vorsicht mit verpolungen der Spannung

Ich benutze 3 16500 Lipo Akkus mit 3,7V
Der DC Wandler dient dazu den LN298 Motortreiber mit Spannung zu versorgen.
Die meisten Mini Motoren sind nur für ca 6V ausgelegt.

Die 1.0 Platine wurde von mir aufgebaut - enthielt aber ein paar Mängel die in der 1.1 Platine behoben sind.
Die 1.1 Platine ist ungetestet

Änderungen:
 Jumper für Spannungsauswahl BT Modul hinzugefügt
 Jumper für Key BT Modul hinzugefügt
 3V R-78e3.3-05 DC DC Modul hinzugefügt für Wlan Modul
 Jumper um Standby Diode zu deaktivieren (leuchtet sonst auch wenn der Arduino sich selber abschaltet)

