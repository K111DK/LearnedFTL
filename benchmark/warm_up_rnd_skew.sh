[SKEW RND WRITE]
ioengine=libaio
bsrange=4k
direct=1
iodepth=32
size=32G
numjobs=1
rw=randwrite
random_distribution=zipf:1.2
filename=/dev/nvme0n1
