# raku

[![Build Status](https://travis-ci.org/boldenth/raku.svg?branch=master)](https://travis-ci.org/boldenth/raku)
[![Build status](https://ci.appveyor.com/api/projects/status/6bjdnebo0bjop5en?svg=true)](https://ci.appveyor.com/project/boldenth/raku)

## About

raku is a cross-platform image editing tool, designed specifically to export indexed png images
of various bit depths. For a rough list of outstanding features, see [TODO.md](TODO.md).

## Installing

raku is currently in a pre-release state, so if you want to use it you must build it yourself. 
To install raku, you will need Qt 5.11 or above.

#### macOS

The recommended way to install Qt is through [homebrew](https://brew.sh/).
```
xcode-select --install

brew update
brew upgrade
brew install qt

git clone https://github.com/boldenth/raku
cd raku

qmake
make

./raku.app/Contents/MacOS/raku
```

#### Linux

You need to install Qt 5. Qt 5.5 should be enough. You can check you Qt version
with `qtdiag`.

```
sudo apt-get install qt5-default
qmake
make
./raku
```

#### Windows

TODO
