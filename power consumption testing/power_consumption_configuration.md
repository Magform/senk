# Power consumption

## Test
Details
- The current implementation uses delay() as a sleep function between two different dataSet which does not cause a true deep sleep in the microcontroller. Because of this we added a theoretical part to the tests where we hypothesize how much the consumption would be if:
    - the sleep state between one dataset and another gave a consumption of approximately 0.2mA and 0.66mW
    - the dataset taking give a consumption of 9mA and 30mW.
    - the dataset saving give a consumption of 10mA and 35mW for iteration/3 seconds
    - the dataset saving keeping the file open give a consumption of 10mA and 35mW for 3 seconds for evry saving process
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


### Test 2 | REDO CHANGED 150 | 1 | 100
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
One dataSet of 10000 data with a distance of 1ms between the data evry 100 seconds
#### Theoretical
`working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (100000ms * 0.2mA + 10000ms * 9mA)/110000ms = 1mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (100000ms * 0.66mW + 10000ms * 30mW)/110000ms = 3.33mW`  
#### Pratical
##### Current
Max: 13.5mA  
AVG: 8.33mA  
Min: 5.39mA  
##### Power
Max: 44.5mW  
Avg: 27.5mW  
Min: 18.3mW  

### Test 5
One dataSet of 10000 data with a distance of 10ms between the data evry 10 seconds
#### Theoretical
`working_time = dataSet * dataDistance = 10000*10 = 100000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 100000ms * 9mA)/110000ms = 8.2mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 100000ms * 30mW)/110000ms = 27.33mW`  
#### Pratical
##### Current
Max: 13.6mA  
AVG: 8.51mA  
Min: 5.36mA  
##### Power
Max: 44.8mW  
Avg: 28.1mW  
Min: 18.1mW  

### Test 6
One dataSet of 10000 data with a distance of 1ms between the data evry 10 seconds
#### Theoretical
`working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 10000ms * 9mA)/20000ms = 4.6mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 10000ms * 30mW)/20000ms = 15.33mW`  
#### Pratical
##### Current
Max: 14.1mA  
AVG: 8.51mA  
Min: 5.19mA  
##### Power
Max: 46.6mW  
Avg: 28.1mW  
Min: 17.5mW  

### Test 7
One datSet of 10000 data with a distance of 10ms between the data evry 100sec
#### Theoretical
`working_time = dataSet * dataDistance = 10000*10 = 100000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (100000ms * 0.2mA + 100000ms * 9mA)/200000ms = 4.6mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (100000ms * 0.66mW + 100000ms * 30mW)/200000ms = 15.33mW`  
#### Pratical
##### Current
Max: 13.7mA  
AVG: 8.59mA  
Min: 5.59mA  
##### Power
Max: 45.4mW  
Avg: 28.4mW  
Min: 19.1mW  

### Test 8
One dataSet of 150 data with a distance of 1ms between the data evry 100sec
dataSaver enable and 1 dataPerIteration
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 150ms`  
`saving_time = (dataSet/datePerIteration)*1000/3 = 150*333ms = 50000ms`   
`theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (50000ms * 0.2mA + 150ms * 9mA + 50000ms * 10mA)/100150ms = 5.10mA`  
`theoretical_power = ( (sleeping_time-saving_time) * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (50000ms * 0.66mW + 150ms * 30mW + 50000ms * 35mW)/100150ms = 17.848mW`  
#### Pratical
##### Current
Max: 18.3mA  
AVG: 7.36mA  
Min: 4.22mA  
##### Power
Max: 60.6mW  
Avg: 24.3mW  
Min: 14.2mW  

### Test 9
One dataSet of 150 data with a distance of 1ms between the data evry 100sec
dataSaverKeepOpen enable and 1 dataPerIteration
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 50ms`  
`saving_time = 3000ms`   
`theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (97000ms * 0.2mA + 150ms * 9mA + 3000ms * 10mA)/100150ms = 0.51mA`  
`theoretical_power = ( (sleeping_time-saving_time) * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (97000ms * 0.66mW + 150ms * 30mW + 3000ms * 35mW)/100150ms = 1.733mW`   
#### Pratical
##### Current
Max: 14.9mA  
AVG: 5.99mA  
Min: 4.17mA  
##### Power
Max: 49.3mW  
Avg: 19.8mW  
Min: 13.9mW  

### Test 10
One dataSet of 150 data with a distance of 1ms between the data evry 100sec
dataSaver enable and 15 dataPerIteration
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 150ms`  
`saving_time = (dataSet/datePerIteration)*1000/3 = ms = 5000ms`   
`theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (95000ms * 0.2mA + 150ms * 9mA + 5000ms * 10mA)/100150ms = 0.702mA`  
`theoretical_power = ( (sleeping_time-saving_time) * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (95000ms * 0.66mW + 150ms * 30mW + 5000ms * 35mW)/100150ms = 2.418mW`   
#### Pratical
##### Current
Max: 17.1mA  
AVG: 6.04mA  
Min: 17.1mA  
##### Power
Max: 56.5mW  
Avg: 20mW  
Min: 13.9mW  

### Test 11
One dataSet of 150 data with a distance of 1ms between the data evry 100sec
dataSaverKeepOpen enable and 15 dataPerIteration
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 50ms`  
`saving_time = 3000ms`   
`theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (97000ms * 0.2mA + 150ms * 9mA + 3000ms * 10mA)/100150ms = 0.51mA`  
`theoretical_power = ( (sleeping_time-saving_time) * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (97000ms * 0.66mW + 150ms * 30mW + 3000ms * 35mW)/100150ms = 1.733mW` 
#### Pratical
##### Current
Max: 15.4mA  
AVG: 5.66mA  
Min: 3.86mA  
##### Power
Max: 51.1mW  
Avg: 18.7mW  
Min: 13.0mW  

### Test 12
One dataSet of 10000 data with 1ms of distance between the data evry 10 seconds
send DataSet enable
#### Theoretical

#### Pratical
##### Current
Max: 13.9mA  
AVG: 8.50mA  
Min: 5.18mA  
##### Power
Max: 45.8mW  
Avg: 28.0mW  
Min: 17.7mW  

### Test 13
One dataSet of 10000 data with 1ms of distance between the data evry 10 seconds
send DataSetThread enable
#### Theoretical

#### Pratical
##### Current
Max: mA  
AVG: mA  
Min: mA  
##### Power
Max: mW  
Avg: mW  
Min: mW  

### Test 14

One dataSet of 150 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration
enable dataSender with 150 dataToScan and scanTime of 10sec

### Test 15

One dataSet of 150 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration
enable dataSender with 15000 dataToScan and scanTime of 10sec

### Test 16

One dataSet of 150 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration
enable dataSender with 15000 dataToScan and scanTime of 1000sec

### Test 17

One dataSet of 150 data with a distance of 1ms between the data evry 10sec
dataSaver enable and 15 dataPerIteration
enable dataSender with 150 dataToScan and scanTime of 1000sec

### Test 18
MAX energy

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
