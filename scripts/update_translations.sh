#!/bin/bash
# remove temporary directory
cd "$(dirname "$0")/.." || exit 1   # run from the repository root
rm -rf scidavis/oldtranslations
# (re)create temporary directory
mkdir scidavis/oldtranslations
# copy old translation files
cp scidavis/translations/*.ts scidavis/oldtranslations/
# run lupdate (Qt 6, override with LUPDATE=/path/to/lupdate) to generate new files
${LUPDATE:-lupdate} -noobsolete libscidavis/src scidavis/src -ts scidavis/translations/*.ts
# run python script to merge translated lines from old translations into new
python3 scripts/translation_updater.py scidavis/oldtranslations scidavis/translations
# remove temporary directory
rm -rf scidavis/oldtranslations