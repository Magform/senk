# Power consumption

## Test
Details
- The current implementation uses delay() as a sleep function between two different dataSet which does not cause a true deep sleep in the microcontroller. Because of this we added a theoretical part to the tests where we hypothesize how much the consumption would be if the sleep state between one dataset and another gave a consumption of approximately 0.2mA and 0.66mW and the dataset taking give a consumption of 9mA and 30mW.
- With some tests it was noticed that the device has an initial transient, where consumption increases as time passes, quite long so the data was taken for 10 minutes and after this initial transient.
- Measurements conducted using an Otii Arc Pro for accuracy

### Test 1
One dataSet of one data evry 10 seconds
#### Theoretical
`working_time = dataSet * dataDistance = 1*1 = 1ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 1ms * 9mA)/10001ms = 0.2009mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 1ms * 27.8mW)/10001ms = 0.6630mW`  
#### Pratical
##### Current
Max: 13.5mA  
AVG: 8.42mA  
Min: 5.17mA  
##### Power
Max: 44.3mW  
Avg: 27.8mW  
Min: 17.4mW  

### Test 2
One dataSet of 50 data with a distance of 1ms between the data evry 10sec
#### Theoretical
`working_time = dataSet * dataDistance = 50*1 = 50ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 50ms * 9mA)/10050ms = 0.2438mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 50ms * 30mW)/10050ms = 0.8060mW`  
#### Pratical
Transient of about 10 minutes
##### Current
Max: 13.6mA  
AVG: 8.45mA  
Min: 5.53mA  
##### Power
Max: 44.8mW  
Avg: 27.9mW  
Min: 18.7mW  

### Test 3
One dataSet of 10000 data with 1ms of distance between the data evry 10 seconds
#### Theoretical
`working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 10000ms * 9mA)/20000ms = 4.6mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 10000ms * 30mW)/20000ms = 15.33mW`  
#### Pratical
##### Current
Max: 13.6mA  
AVG: 8.54mA  
Min: 5.23mA  
##### Power
Max: 45.1mW  
Avg: 28.2mW  
Min: 17.6mW  

### Test 4

One dataSet of 10000 data with a distance of 1ms between the datata evry 100 seconds

### Test 5

One dataSet of 10000 data with a distance of 10ms between the data evry 10 seconds

### Test 6

One dataSet of 10000 data with a distance of 1ms between the data evry 10 seconds

### Test 7

One datSet of 10000 data with a distance of 10ms between the data evry 100sec

### Test 8

One dataSet of 50 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 1 dataPerIteration

### Test 9

One dataSet of 50 data with a distance of 1ms between the data evry 10sec
dataSaverKeepOpen enable and 1 dataPerIteration

### Test 10

One dataSet of 50 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration

### Test 11

One dataSet of 50 data with a distance of 1ms between the data evry 10sec
dataSaverKeepOpen enable and 15 dataPerIteration

### Test 12

One dataSet of 10000 data with 1ms of distance between the data evry 10 seconds
send DataSet enable

### Test 13

One dataSet of 10000 data with 1ms of distance between the data evry 10 seconds
send DataSetThread enable

### Test 14

One dataSet of 50 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration
enable dataSender with 50 dataToScan and scanTime of 10sec

### Test 15

One dataSet of 50 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration
enable dataSender with 5000 dataToScan and scanTime of 10sec

### Test 16

One dataSet of 50 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration
enable dataSender with 5000 dataToScan and scanTime of 1000sec

### Test 17

One dataSet of 50 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration
enable dataSender with 50 dataToScan and scanTime of 1000sec

### Test 18

One dataSet of 100 data with 1ms of distance between the data evry  0.1 seconds
send DataSetThread enable
dataSaver enable and 15 dataPerIteration
enable dataSender with 100 dataToScan evry 0.1 sec

## Conclusion

### Bigger vs smaller dataSet
T1 - T2 - T3

### Bigger vs smaller data_distance

### Bigger vs smaller distance_between_set

### Disable vs enable dataSaver

### Disable vs enable dataSaverKeepOpen

### Disable vs enable sendDataSet

### Disable vs enable sendDataSet Thread

### Disable vs enable dataSender

### Bigger vs smaller dataToScan

### Bigger vs smaller scanTime

### Bigger amout of power consumption
