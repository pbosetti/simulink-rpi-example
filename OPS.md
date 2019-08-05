# Operations

## PREEMPT_RT patch

The Beaglebone black has a kernel `4.14.71-ti-r80` (result of `uname -a`). To install the `PREEMPT_RT` patch do the following:

```sh
$ sudo apt update
$ apt-cache search linux-image-4.14.71
# pick the closest image with the `rt` key in the name:
$ sudo apt install linux-image-4.14.71-ti-rt-r80
```

See [this page](https://elinux.org/EBC_Exercise_36_PREEMPT_RT) for details.

In Beaglebone black with PREEMPT_RT patch, the timing test gives:

```bash
$ sudo bin/rt 1000 1 # 1000 ticks every 1 ms
   Min: 0.000837s
   Max: 0.001187s
  Mean: 0.001000s
St.dev: 0.000014s
```
