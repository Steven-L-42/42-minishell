# Minishell
```c
#include <stdio.h>

int	show_contributor(const char* name, const char* github)
{
	if (!printf("👨‍💻 Contributor: %s | GitHub: %s\n", name, github))
		return (write(2, "Error!\n" 7), 1);
	return (0);
}

int	main(void)
{
	if (show_contributor("Jan", "https://github.com/Jano844"))
		return (1);
	if (show_contributor("Steven", "https://github.com/Steven-L-42"))
		return (1);
	return (0);
}

// expected output:
// 👨‍💻 Contributor: Jan | GitHub: https://github.com/Jano844
// 👨‍💻 Contributor: Steven | GitHub: https://github.com/ShiiikK
```
## Beschreibung
Minishell ist eine einfache Shell, die grundlegende Funktionen einer Shell implementiert.

## Funktionalitäten
- ✅ Zeigt einen Prompt beim Warten auf einen neuen Befehl an.
- ✅ Funktionierende History.
- ✅ Startet das richtige ausführbare Programm basierend auf der PATH-Variable oder einem relativen/absoluten Pfad.
- ✅ Vermeidet die Verwendung von mehr als einer globalen Variable, um ein empfangenes Signal anzuzeigen.
- ✅ Interpretiert keine ungeschlossenen Anführungszeichen oder unnötigen Sonderzeichen (\ oder ;).
- ✅ Behandelt einfache Anführungszeichen, um Metazeichen in der zitierten Sequenz zu verhindern.
- ✅ Behandelt doppelte Anführungszeichen, um Metazeichen in der zitierten Sequenz außer $ zu verhindern.
- ✅ Implementiert Umleitungen:
  - ✅ < für Eingabeumleitung.
  - ✅ > für Ausgabeumleitung.
  - ✅ << mit Begrenzer für Eingabelesen ohne Aktualisierung der History.
  - ✅ >> für Ausgabeumleitung im Anhänge-Modus.
- ✅ Implementiert Pipes (| Zeichen).
- ✅ Behandelt Umgebungsvariablen ($ gefolgt von einer Zeichenfolge), die sich zu ihren Werten ausdehnen sollten.
- ✅ Behandelt $? für den Exit-Status des zuletzt ausgeführten Vordergrund-Pipelines.
- ✅ Behandelt ctrl-C, ctrl-D und ctrl-\ wie in bash.

## Interaktiver Modus
- ✅ ctrl-C zeigt einen neuen Prompt in einer neuen Zeile an.
- ✅ ctrl-D beendet die Shell.
- ✅ ctrl-\ tut nichts.

## Eingebaute Befehle
- ✅ echo mit der Option -n
- ✅ cd mit nur einem relativen oder absoluten Pfad
- ✅ pwd ohne Optionen
- ✅ export ohne Optionen
- ✅ unset ohne Optionen
- ✅ env ohne Optionen oder Argumente
- ✅ exit ohne Optionen

## Umleitung erklärung
	•	Das > Zeichen ersetzt den Inhalt einer Datei.
		Wenn die Datei bereits existiert, wird ihr vorheriger Inhalt durch den neuen Text ersetzt.

	•	Das >> Zeichen hängt den neuen Text an den bereits vorhandenen Inhalt an.
		Wenn die Datei nicht existiert, wird sie erstellt.

	•	Das < Zeichen wird für die Eingabeumleitung verwendet.
		Es liest den Inhalt einer Datei und leitet ihn als Eingabe für einen Befehl oder ein Programm weiter.

	•	Das << Zeichen wird für das sogenannte "Here-Doc" oder "Here-Document" verwendet.
		Es ermöglicht das Einbetten von mehrzeiligem Text direkt in einem Skript oder einer Befehlszeile,
		ohne eine externe Datei zu erstellen.
