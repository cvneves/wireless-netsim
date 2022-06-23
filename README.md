A wireless network system simulator.

To compile/run:
```bash
mkdir build
cd build
cmake ..
make
./netsim.out $instance_name
```

To generate the output pdf:
First you will need Python 3.5+, [matplotlib](https://pypi.org/project/matplotlib/) and [Numpy](https://pypi.org/project/numpy/).

```bash
bash generate_graphs.sh $instance_name
```
