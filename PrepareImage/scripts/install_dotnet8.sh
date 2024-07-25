#!/bin/bash
DIR_EXT="/extapps"
DIR_DOTNET8="${DIR_EXT}/dotnet-8"

mkdir ${DIR_DOTNET8}
cd ${DIR_DOTNET8}
wget https://packages.microsoft.com/config/ubuntu/24.04/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
dpkg -i packages-microsoft-prod.deb
apt update -y && apt install -y apt-transport-https
apt update -y && apt install -y dotnet-sdk-8.0

dotnet new console -o HelloWorld
cd HelloWorld
dotnet build
dotnet run
dotnet publish -c Release -r linux-x64
$(find bin/Release -name "HelloWorld" | grep publish | head -1)

