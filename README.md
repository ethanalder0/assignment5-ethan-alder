# assignment5-ethan-alder

## Compile and Run

```
gcc -o assignment5 assignment5.c
./assignment5 input_file [FCFS|RR|SJF] [time_quantum]
```

Example:

```
./assignment5 input1.txt FCFS
./assignment5 input1.txt SJF
./assignment5 input1.txt RR 5
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
Output\
FCFS:\
<img width="573" height="160" alt="image" src="https://github.com/user-attachments/assets/21d7ee4f-b752-4a7f-a062-78d97cf20584" />
\
SJF:\
<img width="567" height="157" alt="image" src="https://github.com/user-attachments/assets/9e7c75ee-b932-40d8-8861-80d795e80957" />
\
RR 5:\
<img width="482" height="346" alt="image" src="https://github.com/user-attachments/assets/1515f4ef-7247-4dc1-bf43-0858ccec9ab2" /> 
### Test 2 – CPU idle time (`input2.txt`)

```
3
1 2 3
2 4 2
3 10 1
```
Output:
\
FCFS:\
<img width="567" height="143" alt="image" src="https://github.com/user-attachments/assets/ddf2895d-4a56-4c90-8f96-8c64e72c32b5" />
\
SJF:\
<img width="572" height="140" alt="image" src="https://github.com/user-attachments/assets/44dcc731-7897-4f96-a30c-00c5bbba6a95" />
\
RR 5:\
<img width="487" height="255" alt="image" src="https://github.com/user-attachments/assets/2fcf1285-a954-4869-b5a9-bf95be5df513" /> 
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
\
FCFS:\
<img width="572" height="185" alt="image" src="https://github.com/user-attachments/assets/77c40906-7275-47cc-9e25-06ba7f105955" />
\
SJF:\
<img width="571" height="186" alt="image" src="https://github.com/user-attachments/assets/f6560c94-990d-4eb1-b37d-7584d8170e62" />
\
RR 5:\
<img width="481" height="355" alt="image" src="https://github.com/user-attachments/assets/f89c20fe-33b3-48fa-be64-70f7828ec648" /> 
