## 対応ハードウェア

[I2C接続小型LCDモジュール](http://akizukidenshi.com/catalog/g/gP-06669/)

## セットアップ


````bash
$ sudo vi /etc/modules
````

Add these two lines

````bash
i2c-bcm2708 
i2c-dev
````

````bash
$ sudo vi /etc/modprobe.d/raspi-blacklist.conf
````

Comment out blacklist i2c-bcm2708

````
#blacklist i2c-bcm2708
````

Load kernel module

````bash
$ sudo modprobe i2c-bcm2708
````

Install library

````bash
$ ./install-wiringPi
````

Build and copy

````bash
$ cd i2cip
$ make
$ sudo make install
$ sudo cp cron.d/i2cip /etc/cron.d/
$ sudo chmod 644 /etc/cron.d/i2cip
````

main.cは[こちら](http://junkroom2cyberrobotics.blogspot.jp/2012/08/raspberry-pi-i2c-2-i2c-lcd.html)ソースコードを改変しました。
