@echo off
setlocal enabledelayedexpansion
color 0B
echo =======================================================
echo    VERIFICACION E INSTALACION DE DEPENDENCIAS
echo =======================================================
echo.

:: 1. Verificar si Winget (gestor de paquetes de Windows) esta disponible
echo [*] Verificando Windows Package Manager (winget)...
winget --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Winget no esta instalado o no esta disponible.
    echo Por favor, instala "App Installer" desde la Microsoft Store.
    pause
    exit /b 1
)
echo [OK] Winget disponible.

:: 2. Verificar e instalar Python
echo.
echo [*] Verificando Python...
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [AVISO] Python no encontrado. Iniciando instalacion via winget...
    winget install -e --id Python.Python.3.12 --scope user --accept-package-agreements --accept-source-agreements
    if !errorlevel! neq 0 (
        echo [ERROR] Fallo la instalacion de Python. Intenta instalarlo manualmente.
        pause
        exit /b 1
    )
    echo [OK] Python instalado correctamente.
    echo [NOTA] Es posible que debas reiniciar la terminal o el equipo para que el comando "python" este disponible.
) else (
    echo [OK] Python ya esta instalado.
)

:: 3. Verificar e instalar GCC (MinGW)
echo.
echo [*] Verificando compilador GCC...
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [AVISO] GCC no encontrado. Iniciando instalacion de MinGW via winget...
    winget install -e --id Gnu.MinGW --accept-package-agreements --accept-source-agreements
    if !errorlevel! neq 0 (
        echo [ERROR] Fallo la instalacion de MinGW. Intenta instalarlo manualmente.
        pause
        exit /b 1
    )
    echo [OK] MinGW instalado correctamente.
    echo [IMPORTANTE] Para que el comando "gcc" funcione en la terminal actual,
    echo deberas agregar la ruta de MinGW a las variables de entorno PATH,
    echo o reiniciar la terminal/equipo.
) else (
    echo [OK] GCC ya esta instalado.
)

echo.
echo =======================================================
echo    VERIFICACION FINALIZADA
echo =======================================================
echo [*] Puedes ejecutar el script "ejecutar_todo.bat" para compilar y probar los ejercicios.
pause