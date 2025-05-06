#!/bin/bash

EXEC=./miniRT
MAPS_DIR=./scenes

# Styling
BOLD="\033[1m"
GREEN="\033[1;32m"
RED="\033[1;31m"
CYAN="\033[1;36m"
YELLOW="\033[1;33m"
MAGENTA="\033[1;35m"
NC="\033[0m"

describe_scene() {
	case "$1" in
		cylinder.rt)
			echo "🔎 Description : Un cylindre vertical centré, éclairé par une lumière ambiante et ponctuelle."
			;;
		exemple_scene.rt)
			echo "🔎 Description : Une scène simple d'exemple contenant plusieurs objets de base (plan, sphère, lumière)."
			;;
		given_subject_scene.rt)
			echo "🔎 Description : Scène fournie dans le sujet. Devrait afficher une sphère sur un plan, avec un éclairage classique."
			;;
		light.rt)
			echo "🔎 Description : Test de plusieurs lumières ponctuelles. Attendez-vous à un éclairage multiple avec des ombres douces."
			;;
		plane.rt)
			echo "🔎 Description : Un plan infini. On doit le voir remplir le fond avec un effet de sol."
			;;
		sphere.rt)
			echo "🔎 Description : Une simple sphère centrée dans la scène avec une lumière."
			;;
		spheres.rt)
			echo "🔎 Description : Plusieurs sphères alignées ou disposées dans la scène. On teste ici le rendu multiple."
			;;
		pride.rt)
			echo "🔎 Description : Scène custom avec plusieurs sphères colorées façon drapeau Pride 🌈"
			;;
		parsing.rt)
			echo "🔎 Description : Scène valide pour tester le parsing. Ne doit pas planter, doit s'afficher correctement."
			;;
		error.rt)
			echo "🔎 Description : Scène volontairement invalide pour tester les erreurs. Doit afficher une erreur mais lancer la scène."
			;;
		*)
			echo "🔎 Description indisponible pour ce fichier."
			;;
	esac
}

print_separator() {
	echo -e "${MAGENTA}------------------------------------------------------------${NC}"
}

run_test() {
	local file=$1
	local expected=$2
	local path="${MAPS_DIR}/${file}"

	print_separator
	echo -e "${CYAN}${BOLD}Testing ${file}${NC}"

	if [ ! -f "$path" ]; then
		echo -e "${RED}❌ File not found: $path${NC}\n"
		return
	fi

	describe_scene "$file"
	echo ""

	# Afficher le contenu de la map
	echo -e "${YELLOW}📄 Contenu de ${file}:${NC}"
	cat "$path"
	echo ""

	# Lancer miniRT et capturer la sortie
	output=$($EXEC "$path")
	echo ""
	echo -e "${MAGENTA}--- Sortie du programme ---${NC}"
	echo "$output"
	echo -e "${MAGENTA}---------------------------${NC}"

	if [ "$expected" = "ok" ]; then
		# Vérifier si la fenêtre a été créée
		if echo "$output" | grep -q "Window created successfully"; then
			echo -e "${GREEN}✅ PASSED (Scène lancée avec succès)${NC}\n"
		else
			echo -e "${RED}❌ FAILED (Pas de création de fenêtre détectée)${NC}\n"
		fi
	else
		# Scène censée échouer → on attend une erreur
		if echo "$output" | grep -qi "Error"; then
			echo -e "${GREEN}✅ PASSED (Erreur détectée et scène lancée)${NC}\n"
		else
			echo -e "${RED}❌ FAILED (Aucune erreur détectée alors qu'attendue)${NC}\n"
		fi
	fi
}

# ========= Lancer les tests =========

echo -e "${CYAN}${BOLD}🚀 Lancement des tests MiniRT...${NC}\n"

run_test cylinder.rt ok
run_test exemple_scene.rt ok
run_test given_subject_scene.rt ok
run_test light.rt ok
run_test plane.rt ok
run_test sphere.rt ok
run_test spheres.rt ok
run_test pride.rt ok
run_test 天宫.rt ok
run_test parsing.rt ok
run_test error.rt fail

print_separator
echo -e "${CYAN}${BOLD}✅ Tous les tests sont terminés.${NC}"
print_separator
