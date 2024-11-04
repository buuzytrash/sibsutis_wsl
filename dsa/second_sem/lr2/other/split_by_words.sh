#!/bin/sh
INFILE1=$1
INFILE2=$2
MINCHARS=2
#
# Выводим файл $INFILE | разбиваем поток строк на слова | удаляем из потока
# слова с длиной <= $MINCHARS | преобразуем слова потока в нижний регистр |
# сортируем слова | удаляем повторяющиеся слова
#
cat $INFILE1 | tr -s '[[:punct:][:space:]]' '\n' | grep -E ".{$MINCHARS}" | \
sed 's/[[:upper:]]*/\L&/' | sort | uniq > $INFILE2