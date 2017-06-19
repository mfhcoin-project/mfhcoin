Mfhcoin Core
-------------------

https://mfhcoin.info

* Ticker: MFH
* Block time: max 10 min
* Reward: 70 Coin
* Max coins: 300.000.000 Coins
* Premine: 10% (30.000.000 Coins)
* RPC: 1512
* P2P: 1511

Compiling
-------------------

UNIX
-------
```bash
apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libminiupnpc-dev
apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
```

```bash
./unix-build.sh
make
make install # optional
```

Win (depends)
-------
x86
```bash
cd depends
make HOST=i686-w64-mingw32 -j4
cd ..
./configure --prefix=`pwd`/depends/i686-w64-mingw32
make
```
x64
```bash
cd depends
make HOST=x86_64-w64-mingw32 -j4
cd ..
./configure --prefix=`pwd`/depends/x86_64-w64-mingw32
make
```
MacOS
-------
```bash
brew install automake berkeley-db4 libtool boost --c++11 miniupnpc openssl pkg-config homebrew/versions/protobuf260 --c++11 qt5 libevent
```
```bash
./autogen.sh
./configure
make

make check

make deploy
```
