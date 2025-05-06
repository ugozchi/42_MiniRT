#!/bin/bash

EXEC=./miniRT
MAPS_DIR=./scenes

BOLD="\033[1m"
GREEN="\033[1;32m"
RED="\033[1;31m"
CYAN="\033[1;36m"
YELLOW="\033[1;33m"
MAGENTA="\033[1;35m"
NC="\033[0m"

print_section() {
	echo -e "\n${MAGENTA}==================[ $1 ]==================${NC}\n"
}

run_and_check() {
	local title="$1"
	local objectif="$2"
	local scene="$3"
	local expected="$4"

	echo -e "${BOLD}${CYAN}📌 $title${NC}"
	echo -e "🔎 ${YELLOW}OBJECTIF :${NC} $objectif"

	if [ "$scene" != "" ]; then
		echo -e "📄 ${MAGENTA}FICHIER TESTÉ :${NC} ./scenes/$scene"

		if [ -f "./scenes/$scene" ]; then
			echo -e "\n${MAGENTA}--- CONTENU DE ${scene} ---${NC}"
			cat "./scenes/$scene"
			echo -e "${MAGENTA}-----------------------------${NC}"

			echo -e "\n🧠 ${YELLOW}CE QUE DOIT FAIRE LE PROGRAMME :${NC} $expected"

			echo -e "\n${CYAN}▶️ Lancement de la scène... Fermez la fenêtre pour continuer.${NC}"

			# Lancer et capturer sortie
			output=$($EXEC "./scenes/$scene")

			echo -e "\n${MAGENTA}[ SORTIE DU PROGRAMME ]${NC}\n"
			echo "$output"

			# echo -e "\n${GREEN}[ ] OK${NC}  ${RED}[ ] FAIL${NC}\n"
		else
			echo -e "${RED}❌ Scene file not found${NC}\n"
		fi
	else
		echo -e "\n${RED}❌ Pas de fichier associé${NC}\n"
	fi
}

echo -e "${CYAN}${BOLD}🚀 MINI RT - PLAN DE TESTS POUR SOUTENANCE${NC}"

# ============ CONFIGURATION FILE ============

print_section "Configuration file"

run_and_check "Fichier non .rt (format)" "Tester le rejet d'un fichier avec mauvaise extension" "error.format" "Afficher une erreur et quitter proprement"
run_and_check "Fichier invalide (parsing error)" "Tester un fichier mal formé qui doit afficher une erreur" "error.rt" "Afficher une erreur mais créer la fenêtre"
run_and_check "Fichier valide" "Vérifier que le parsing valide fonctionne" "parsing.rt" "Afficher la scène correctement"

# ============ TECHNICAL ELEMENTS DISPLAY ============

print_section "Technical elements of the display"

run_and_check "Ouverture de fenêtre" "Vérifier que la fenêtre s'ouvre" "exemple_scene.rt" "La fenêtre doit rester ouverte"
run_and_check "Cache/minimise/maximise" "Tester la stabilité de l'affichage" "exemple_scene.rt" "Pas de crash ou glitch"
run_and_check "Redimensionnement" "Redimensionner la fenêtre" "exemple_scene.rt" "Pas de crash ou glitch"
run_and_check "ESC / Croix rouge" "Fermer avec ESC ou croix rouge" "exemple_scene.rt" "Quitter proprement"

# ============ BASIC SHAPES ============

print_section "Basic Shapes"

run_and_check "Sphere simple" "Afficher une sphère basique" "sphere_basic.rt" "Sphère visible sans glitch"
run_and_check "Plan simple" "Afficher un plan basique" "plane_basic.rt" "Plan visible sans glitch"
run_and_check "Cylindre simple" "Afficher un cylindre basique" "cylinder_basic.rt" "Cylindre visible sans glitch"

# ============ TRANSLATIONS / ROTATIONS ============

print_section "Translations and Rotations"

run_and_check "Deux sphères (translation)" "Afficher deux sphères dont une déplacée" "sphere_translation.rt" "Les deux sphères visibles"
run_and_check "Cylindre rotation" "Cylindre pivoté à 90°" "cylinder_rotation.rt" "Visible correctement"

# ============ MULTI OBJECTS ============

print_section "Multi-objects"

run_and_check "Intersection" "Deux objets se croisent" "multi_intersect.rt" "Les intersections doivent être visibles"
run_and_check "Multiples objets" "Plusieurs objets similaires" "multi_objects.rt" "Tous visibles sans glitch"

# ============ CAMERA POSITIONS ============

print_section "Camera positions"

run_and_check "Camera X" "Camera orientée sur X" "camera_x.rt" "La scène visible correctement"
run_and_check "Camera Y" "Camera orientée sur Y" "camera_y.rt" "La scène visible correctement"
run_and_check "Camera Z" "Camera orientée sur Z" "camera_z.rt" "La scène visible correctement"
run_and_check "Camera random" "Camera dans une position random" "camera_random.rt" "La scène visible correctement"

# ============ BRIGHTNESS 1/2 ============

print_section "Brightness 1/2"

run_and_check "Side light sphere" "Sphère éclairée de côté" "light_side.rt" "Lumière latérale visible"
run_and_check "Translated sphere + light" "Sphère déplacée éclairée" "light_translation.rt" "Lumière latérale visible même déplacée"

# ============ BRIGHTNESS 2/2 (SHADOWS) ============

print_section "Brightness 2/2 (Shadows)"

run_and_check "Shadow simple" "Sphère projette ombre sur un plan" "shadow_simple.rt" "Ombre visible proprement"
run_and_check "Shadow complexe" "Scène complexe avec ombres" "shadow_complex.rt" "Toutes ombres visibles proprement"

echo -e "${CYAN}${BOLD}✅ Tous les tests sont terminés !${NC}"
