@echo off
setlocal enabledelayedexpansion
color 0B
echo =======================================================
echo    INSTALACION DE DEPENDENCIAS - CRISTIAN BOLIVAR
echo =======================================================
echo.

:: Los ejercicios usan solo la libreria estandar de Python y C,
:: por lo que no se requieren paquetes externos de pip.

echo [*] Verificando Windows Package Manager (winget)...
winget --version >nul 2>&1
if errorlevel 1 (
    echo [ERROR] Winget no esta disponible.
    echo Instala "App Installer" desde la Microsoft Store.
    pause
    exit /b 1
)
echo [OK] Winget disponible.
echo.

echo [*] Verificando Python 3...
python --version >nul 2>&1
if errorlevel 1 (
    echo [AVISO] Python no encontrado. Instalando Python 3.12...
    winget install -e --id Python.Python.3.12 --scope user --accept-package-agreements --accept-source-agreements
    if errorlevel 1 (
        echo [ERROR] No se pudo instalar Python.
        echo Instalalo manualmente desde https://www.python.org/downloads/
        pause
        exit /b 1
    )
    echo [OK] Python instalado.
    echo [NOTA] Cierra y abre la terminal para actualizar el PATH.
) else (
    for /f "tokens=*" %%v in ('python --version 2^>^&1') do echo [OK] %%v
)
echo.

echo [*] Verificando compilador GCC...
gcc --version >nul 2>&1
if errorlevel 1 (
    echo [AVISO] GCC no encontrado. Instalando WinLibs MinGW-w64...
    winget install -e --id BrechtSanders.WinLibs.MCF.UCRT --accept-package-agreements --accept-source-agreements
    if errorlevel 1 (
        echo [ERROR] No se pudo instalar GCC.
        echo Instalalo manualmente desde https://winlibs.com/
        pause
        exit /b 1
    )
    echo [OK] GCC instalado.
    echo [NOTA] Cierra y abre la terminal para actualizar el PATH.
) else (
    gcc --version | findstr /i "gcc"
)
echo.

echo =======================================================
echo    VERIFICACION FINAL
echo =======================================================
python --version
gcc --version | findstr /i "gcc"
echo.
echo [OK] Dependencias listas.
pause
