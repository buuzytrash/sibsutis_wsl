count=0
for file in ~/third-year/1semestr/cpp/fts-mutuev-iv123s17/index/entries/*; do
    lines=$(wc -l <"$file")
    if ((lines > 2)); then
        ((count++))
    fi
done
echo "$count"