# assignment5-ethan-alder

## Compile and Run

```
gcc -o assignment5 assignment5.c
./assignment5 input_file [FCFS|RR|SJF] [time_quantum]
```

Example:

```
./assignment5 input.1 FCFS
./assignment5 input.1 SJF
./assignment5 input.1 RR 5
```

## Test Cases

### Test 1 – Sample input (`input1.txt`)

```
4
0 0 12
1 2 4
2 3 1
3 4 2
```
Output:


### Test 2 – CPU idle time (`input2.txt`)

```
3
1 2 3
2 4 2
3 10 1
```
Output:


### Test 3 – Simultaneous arrivals and equal bursts (`input3.txt`)

```
5
1 0 3
2 1 3
3 1 1
4 2 1
5 3 2
```
Output:
