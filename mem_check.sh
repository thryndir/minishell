#!/bin/bash

# Fichiers temporaires
TEMP_DIR=$(mktemp -d)
ALLOC_FILE="$TEMP_DIR/alloc.txt"
FREE_FILE="$TEMP_DIR/free.txt"
MATCHED_FILE="$TEMP_DIR/matched.txt"
ERROR_FILE="$TEMP_DIR/error.txt"

# Nettoyage à la sortie
trap 'rm -rf "$TEMP_DIR"' EXIT

# Symboles pour une meilleure lisibilité
ALLOC_SYMBOL=">"
FREE_SYMBOL="+"
ERROR_SYMBOL="!"

# S'assurer que les fichiers existent
touch "$ALLOC_FILE" "$FREE_FILE" "$MATCHED_FILE" "$ERROR_FILE"

# Extraire les allocations et les free
while IFS= read -r line; do
    if [[ $line =~ (malloc|ft_calloc).*at\((0x[0-9a-fA-F]+)\) ]]; then
        addr="${BASH_REMATCH[2]}"
        echo "$addr|$line" >> "$ALLOC_FILE"
    elif [[ $line =~ ^free\((0x[0-9a-fA-F]+)\) ]]; then
        addr="${BASH_REMATCH[1]}"
        echo "$addr|$line" >> "$FREE_FILE"
    fi
done

# Vérifier si nous avons des allocations
if [ ! -s "$ALLOC_FILE" ]; then
    echo "Aucune allocation trouvée dans l'entrée."
    exit 0
fi

echo "=== PAIRES AVEC ERREURS ==="
echo ""

error_counter=1
normal_counter=1
total_leaks=0

# Premier passage : afficher les paires avec erreurs
while IFS='|' read -r addr alloc_line || [ -n "$addr" ]; do
    [ -z "$addr" ] && continue

    # Chercher les free correspondants
    free_lines=$(grep "^$addr|" "$FREE_FILE" | cut -d'|' -f2-)
    if [ -z "$free_lines" ]; then
        echo "Paire avec erreur #$error_counter"
        echo "$ALLOC_SYMBOL Allocation: $alloc_line"
        echo "   $ERROR_SYMBOL ERREUR: Aucun free trouvé pour cette allocation"
        echo "----------------------------"
        ((error_counter++))
        ((total_leaks++))
        echo "$addr" >> "$ERROR_FILE"
    fi
done < "$ALLOC_FILE"

echo ""
echo "=== PAIRES NORMALES ==="
echo ""

# Deuxième passage : afficher les paires normales
while IFS='|' read -r addr alloc_line || [ -n "$addr" ]; do
    [ -z "$addr" ] && continue

    # Vérifier si cette allocation avait une erreur
    if ! grep -q "^$addr$" "$ERROR_FILE"; then
        echo "Paire #$normal_counter"
        echo "$ALLOC_SYMBOL Allocation: $alloc_line"
        
        # Afficher les free correspondants
        free_lines=$(grep "^$addr|" "$FREE_FILE" | cut -d'|' -f2-)
        while IFS= read -r free_line; do
            echo "   $FREE_SYMBOL Libération: $free_line"
        done <<< "$free_lines"
        
        echo "----------------------------"
        ((normal_counter++))
    fi
done < "$ALLOC_FILE"

# Afficher le résumé
echo ""
echo "=== RÉSUMÉ ==="
echo "Total des allocations: $((normal_counter + total_leaks - 1))"
echo "Total des fuites mémoire: $total_leaks"