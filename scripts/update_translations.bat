REM run from the repository root
cd /d "%~dp0.."
REM remove temporary directory
rmdir /s /q scidavis\oldtranslations
REM copy old translation files
xcopy /i scidavis\translations\*.ts scidavis\oldtranslations\
REM run lupdate (Qt 6) to generate new files
for %%f in (scidavis\translations\*.ts) do lupdate -noobsolete libscidavis\src scidavis\src -ts %%f
REM run python script to merge translated lines from old translations into new
python scripts\translation_updater.py scidavis\oldtranslations scidavis\translations
REM remove temporary directory
rmdir /s /q scidavis\oldtranslations