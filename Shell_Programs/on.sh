echo $1 > /sys/class/gpio/export
echo GPIO$1 exported
echo out > /sys/class/gpio/gpio$1/direction
echo GPIO$1:OUTPUT
echo 1 > /sys/class/gpio/gpio$1/value
echo GPIO$1:HIGH