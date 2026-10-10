REM run from the repository root
cd /d "%~dp0.."
REM remove temporary directory
rmdir /s /q scidavis\oldtranslations
REM copy old translation files
xcopy /i scidavis\translations\*.ts scidavis\oldtranslations\
REM run lupdate to generate new files
lupdate -noobsolete scidavis.pro
REM run python script to merge translated lines from old translations into new
python scripts\translation_updater.py scidavis\oldtranslations scidavis\translations
REM remove temporary directory
rmdir /s /q scidavis\oldtranslations