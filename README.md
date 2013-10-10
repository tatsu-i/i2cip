## 対応ハードウェア

[I2C接続小型LCDモジュール](http://akizukidenshi.com/catalog/g/gP-06669/)

## セットアップ

modulesファイルをviで開く
````bash
$ sudo vi /etc/modules
````

次の二行を追加して上書き保存する
````bash
i2c-bcm2708 
i2c-dev
````
raspi-blacklist.confを開く
````bash
$ sudo vi /etc/modprobe.d/raspi-blacklist.conf
````

blacklist i2c-bcm2708の行をコメントアウトする
````
#blacklist i2c-bcm2708
````

カーネルモジュールをロードする
````bash
$ sudo modprobe i2c-bcm2708
````

ライブラリのインストール
````bash
$ ./install-wiringPi
````

ビルドとコピー
````bash
$ cd i2cip
$ make
$ sudo make install
$ sudo cp cron.d/i2cip /etc/cron.d/
$ sudo chmod 644 /etc/cron.d/i2cip
````

main.cは[こちら](http://junkroom2cyberrobotics.blogspot.jp/2012/08/raspberry-pi-i2c-2-i2c-lcd.html)ソースコードを改変しました。
