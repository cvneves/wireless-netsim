A wireless network system simulator.
You will need CMake 3.14+, Python 3.5+, [matplotlib](https://pypi.org/project/matplotlib/) and [Numpy](https://pypi.org/project/numpy/).

To compile/run:
```bash
mkdir output
mkdir graph
mkdir build
cd build
cmake ..
make
./netsim.out $instance_name
```

To generate the output pdf:

```bash
bash generate_graphs.sh $instance_name
```
