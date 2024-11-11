#!/bin/bash
set -e

echo "Step 1: Add Bazel distribution URI as a package source https://bazel.build/install/ubuntu#add-dis-uri"
apt install -y apt-transport-https curl gnupg
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel-archive-keyring.gpg
mv bazel-archive-keyring.gpg /usr/share/keyrings
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list

echo "Step 2: Install and update Bazel https://bazel.build/install/ubuntu#install-bazel"
apt update -y && apt install -y bazel
apt update -y && apt full-upgrade -y
bazel --version

