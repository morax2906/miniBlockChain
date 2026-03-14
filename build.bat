@echo off
title Build miniBlockChain
echo [1/2] Dang kiem tra trinh bien dich...
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [LOI] Khong tim thay g++. Hay cai dat MinGW hoac MSYS2.
    pause
    exit /b
)

echo [2/2] Dang bien dich voi OpenSSL...
g++ *.cpp -o blockchain_app -lssl -lcrypto
if %errorlevel% neq 0 (
    echo [LOI] Bien dich that bai. Kiem tra xem ban da cai OpenSSL chua.
    pause
    exit /b
)

echo [OK] Bien dich thanh cong!
echo Dang khoi chay...
blockchain_app.exe
pause