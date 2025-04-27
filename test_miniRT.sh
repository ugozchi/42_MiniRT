#!/bin/bash

EXEC=./miniRT
MAPS_DIR=./scenes

# Styling
BOLD="\033[1m"
GREEN="\033[1;32m"
RED="\033[1;31m"
CYAN="\033[1;36m"
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
		error.rt)
			echo "🔎 Description : Fichier invalide — votre programme doit afficher une erreur claire sans crasher."
			;;
		*)
			echo "🔎 Description indisponible pour ce fichier."
			;;
	esac
}

run_test() {
	local file=$1
	local expected=$2
	local path="${MAPS_DIR}/${file}"

	echo -e "${CYAN}Testing ${file}${NC}"

	if [ ! -f "$path" ]; then
		echo -e "${RED}File not found: $path${NC}"
		return
	fi

	$EXEC "$path" > /dev/null 2>&1 &
	pid=$!

	if [ "$expected" = "ok" ]; then
		echo -e "→ Scene affichée pendant 10 secondes...\n"
		describe_scene "$file"
		echo ""

		sleep 2

		if ps -p $pid > /dev/null; then
			kill $pid
			wait $pid 2>/dev/null
			status=$?
		else
			status=0  # il s'est terminé tout seul proprement
		fi
	else
		sleep 1
		wait $pid 2>/dev/null
		status=$?
	fi

	if [ "$expected" = "ok" ] && [ $status -eq 0 ]; then
		echo -e "${GREEN}✔️ PASSED${NC}\n"
	elif [ "$expected" = "fail" ] && [ $status -ne 0 ]; then
		echo -e "${GREEN}✔️ PASSED (failed as expected)${NC}\n"
	else
		echo -e "${RED}❌ FAILED${NC}\n"
	fi
}

# ========= Launch Tests =========

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
run_test error.rt ok

echo -e "${CYAN}${BOLD}✅ Tous les tests sont terminés.${NC}"
