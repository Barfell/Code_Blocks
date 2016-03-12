echo 0 > /sys/class/gpio/gpio$1/value
echo GPIO$1:LOW
echo in > /sys/class/gpio/gpio$1/direction
echo GPIO$1:INPUT
echo $1 > /sys/class/gpio/unexport
echo GPIO$1 unexported