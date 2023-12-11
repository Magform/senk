# Power consumption

## Test
Details
- The current implementation uses delay() as a sleep function between two different dataSet which does not cause a true deep sleep in the microcontroller. Because of this we added a theoretical part to the tests where we hypothesize how much the consumption would be if:
    - the sleep state between one dataset and another gave a consumption of approximately 0.2mA and 0.66mW
    - the dataset taking give a consumption of 9mA and 30mW.
    - the dataset saving give a consumption of 10mA and 35mW for iteration/3 seconds
    - the dataset saving keeping the file open give a consumption of 10mA and 35mW for 3 seconds for every saving process
    - sending a data using BLE use 8mA, 28mW and it sends 3000 data/second
    - This theoretical part is a big aproximation so it's not accurate
- With some tests it was noticed that the device has an initial transient, where consumption increases as time passes, quite long so the data was taken for 10 minutes and after this initial transient.
- Measurements conducted using an Otii Arc Pro for accuracy

### Test 1
One dataSet of one data every 10 seconds  
#### Theoretical
`working_time = dataSet * dataDistance = 1*1 = 1ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 1ms * 9mA)/10001ms = 0.2009mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 1ms * 27.8mW)/10001ms = 0.6630mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-1)
##### Current
Max: 13.5mA  
AVG: 8.42mA  
Min: 5.17mA  
##### Power
Max: 44.3mW  
Avg: 27.8mW  
Min: 17.4mW  


### Test 2
One dataSet of 150 data with a distance of 1ms between the data every 100sec  
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 150ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (100000ms * 0.2mA + 150ms * 9mA)/100150ms = 0.2131mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (100000ms * 0.66mW + 150ms * 30mW)/100150ms = 0.7039mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-2)
##### Current
Max: 13.5mA  
AVG: 8.42mA  
Min: 5.48mA  
##### Power
Max: 44.5mW  
Avg: 27.8mW  
Min: 18.6mW  

### Test 3
One dataSet of 150 data with a distance of 1ms between the data continuosly  
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 150ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (150ms * 9mA)/150ms = 9mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (150ms * 30mW)/150ms = 30mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-3)
##### Current
Max: 13.1mA  
AVG: 8.33mA  
Min: 6.57mA  
##### Power
Max: 43.2mW  
Avg: 27.5mW  
Min: 21.7mW  

### Test 4
One dataSet of 10000 data with 1ms of distance between the data every 10 seconds  
#### Theoretical
`working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 10000ms * 9mA)/20000ms = 4.6mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 10000ms * 30mW)/20000ms = 15.33mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-4)
##### Current
Max: 13.6mA  
AVG: 8.54mA  
Min: 5.23mA  
##### Power
Max: 45.1mW  
Avg: 28.2mW  
Min: 17.6mW  

### Test 5
One dataSet of 10000 data with a distance of 1ms between the data every 100 seconds  
#### Theoretical
`working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (100000ms * 0.2mA + 10000ms * 9mA)/110000ms = 1mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (100000ms * 0.66mW + 10000ms * 30mW)/110000ms = 3.33mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-5)
##### Current
Max: 13.5mA  
AVG: 8.33mA  
Min: 5.39mA  
##### Power
Max: 44.5mW  
Avg: 27.5mW  
Min: 18.3mW  

### Test 6
One dataSet of 10000 data with a distance of 10ms between the data every 10 seconds  
#### Theoretical
`working_time = dataSet * dataDistance = 10000*10 = 100000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 100000ms * 9mA)/110000ms = 8.2mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 100000ms * 30mW)/110000ms = 27.33mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-6)
##### Current
Max: 13.6mA  
AVG: 8.51mA  
Min: 5.36mA  
##### Power
Max: 44.8mW  
Avg: 28.1mW  
Min: 18.1mW  

### Test 7
One dataSet of 10000 data with a distance of 1ms between the data every 10 seconds  
#### Theoretical
`working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.2mA + 10000ms * 9mA)/20000ms = 4.6mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (10000ms * 0.66mW + 10000ms * 30mW)/20000ms = 15.33mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-7)
##### Current
Max: 14.1mA  
AVG: 8.51mA  
Min: 5.19mA  
##### Power
Max: 46.6mW  
Avg: 28.1mW  
Min: 17.5mW  

### Test 8
One datSet of 10000 data with a distance of 10ms between the data every 100sec  
#### Theoretical
`working_time = dataSet * dataDistance = 10000*10 = 100000ms`  
`theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (100000ms * 0.2mA + 100000ms * 9mA)/200000ms = 4.6mA`  
`theoretical_power = (sleeping_time * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (100000ms * 0.66mW + 100000ms * 30mW)/200000ms = 15.33mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-8)
##### Current
Max: 13.7mA  
AVG: 8.59mA  
Min: 5.59mA  
##### Power
Max: 45.4mW  
Avg: 28.4mW  
Min: 19.1mW  

### Test 9
One dataSet of 150 data with a distance of 1ms between the data every 100sec  
dataSaver enable and 1 dataPerIteration  
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 150ms`  
`saving_time = (dataSet/datePerIteration)*1000/3 = 150*333ms = 50000ms`   
`theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (50000ms * 0.2mA + 150ms * 9mA + 50000ms * 10mA)/100150ms = 5.10mA`  
`theoretical_power = ( (sleeping_time-saving_time) * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (50000ms * 0.66mW + 150ms * 30mW + 50000ms * 35mW)/100150ms = 17.848mW`  
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-9)
##### Current
Max: 18.3mA  
AVG: 7.36mA  
Min: 4.22mA  
##### Power
Max: 60.6mW  
Avg: 24.3mW  
Min: 14.2mW  

### Test 10
One dataSet of 150 data with a distance of 1ms between the data every 100sec  
dataSaverKeepOpen enable and 1 dataPerIteration  
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 50ms`  
`saving_time = 3000ms`   
`theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (97000ms * 0.2mA + 150ms * 9mA + 3000ms * 10mA)/100150ms = 0.51mA`  
`theoretical_power = ( (sleeping_time-saving_time) * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (97000ms * 0.66mW + 150ms * 30mW + 3000ms * 35mW)/100150ms = 1.733mW`   
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-10)
##### Current
Max: 14.9mA  
AVG: 5.99mA  
Min: 4.17mA  
##### Power
Max: 49.3mW  
Avg: 19.8mW  
Min: 13.9mW  

### Test 11
One dataSet of 150 data with a distance of 1ms between the data every 100sec  
dataSaver enable and 15 dataPerIteration  
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 150ms`  
`saving_time = (dataSet/datePerIteration)*1000/3 = ms = 5000ms`   
`theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (95000ms * 0.2mA + 150ms * 9mA + 5000ms * 10mA)/100150ms = 0.702mA`  
`theoretical_power = ( (sleeping_time-saving_time) * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (95000ms * 0.66mW + 150ms * 30mW + 5000ms * 35mW)/100150ms = 2.418mW`   
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-11)
##### Current
Max: 17.1mA  
AVG: 6.04mA  
Min: 17.1mA  
##### Power
Max: 56.5mW  
Avg: 20mW  
Min: 13.9mW  

### Test 12
One dataSet of 150 data with a distance of 1ms between the data every 100sec
dataSaverKeepOpen enable and 15 dataPerIteration   
#### Theoretical
`working_time = dataSet * dataDistance = 150*1 = 50ms`  
`saving_time = 3000ms`   
`theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (97000ms * 0.2mA + 150ms * 9mA + 3000ms * 10mA)/100150ms = 0.51mA`  
`theoretical_power = ( (sleeping_time-saving_time) * sleeping_power + working_time * working_power)/(sleeping_time + working_time) = (97000ms * 0.66mW + 150ms * 30mW + 3000ms * 35mW)/100150ms = 1.733mW` 
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-12)
##### Current
Max: 15.4mA  
AVG: 5.66mA  
Min: 3.86mA  
##### Power
Max: 51.1mW  
Avg: 18.7mW  
Min: 13.0mW  

### Test 13
One dataSet of 10000 data with 1ms of distance between the data every 10 seconds  
send DataSet enable  
#### Theoretical
`working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
`sending_time = dataSet*1000/3000 = ms = 3333ms`   
`theoretical_consumption = ( (sleeping_time-sending_time) * sleeping_current + working_time * working_current + sending_current * saving_time)/(sleeping_time + working_time) = (6666ms * 0.2mA + 10000ms * 9mA + 3333ms * 8mA)/20000ms = 5.89mA`  
`theoretical_power = ( (sleeping_time-sending_time) * sleeping_power + working_time * working_power + sending_power * saving_time)/(sleeping_time + working_time) = (6666ms * 0.66mW + 10000ms * 30mW + 3333ms * 28mW)/20000ms = 19.886mW`   
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-13)
##### Current
Max: 13.9mA  
AVG: 8.50mA  
Min: 5.18mA  
##### Power
Max: 45.8mW  
Avg: 28.0mW  
Min: 17.7mW  

### Test 14
One dataSet of 10000 data with 1ms of distance between the data every 10 seconds  
send DataSetThread enable  
MAX_DATASET_DIMENSION reduced to 10 to give space for the Thread  
#### Theoretical
`working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
`sending_time = dataSet*1000/3000 = ms = 3333ms`   
`theoretical_consumption = ( sleeping_time * sleeping_current + working_time * working_current + sending_current * saving_time)/(sleeping_time + working_time + saving_time) = (10000ms * 0.2mA + 10000ms * 9mA + 3333ms * 8mA)/23333ms = 5.086mA`  
`theoretical_power = ( sleeping_time * sleeping_power + working_time * working_power + sending_power * saving_time)/(sleeping_time + working_time) = (10000ms * 0.66mW + 10000ms * 30mW + 3333ms * 28mW)/23333ms = 17.140mW` 
#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-14)
##### Current
Max: 14.3mA  
AVG: 8.51mA  
Min: 5.37mA  
##### Power
Max: 47.3mW  
Avg: 28.1mW  
Min: 18.3mW  

### Test 15
One dataSet of 150 data with a distance of 1ms between the data every 10sec  
dataSaver enable and 15 dataPerIteration    
enable dataSender with 150 dataToScan and scanTime of 10sec  
#### Theoretical

#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-15)
##### Current
Max: 17.8mA  
AVG: 7.8mA  
Min: 4.23mA  
##### Power
Max: 59mW  
Avg: 25.8mW  
Min: 14.2mW  

### Test 16
One dataSet of 150 data with a distance of 1ms between the data every 10sec  
dataSaver enable and 15 dataPerIteration  
enable dataSender with 15000 dataToScan and scanTime of 10sec  
#### Theoretical

#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-16)
##### Current
Max: 17.2mA  
AVG: 8.45mA  
Min: 4.30mA  
##### Power
Max: 56.7mW  
Avg: 27.9mW  
Min: 14.5mW  

### Test 17
One dataSet of 150 data with a distance of 1ms between the data every 10sec  
dataSaver enable and 15 dataPerIteration  
enable dataSender with 15000 dataToScan and scanTime of 1000sec  
#### Theoretical

#### Pratical
[image of the result](https://senk.nicolasferraresso.dev/#/power_consumption_image?id=test-17)
##### Current
Max: 17.9mA  
AVG: 7.29mA  
Min: 3.62mA  
##### Power
Max: 59.1mW  
Avg: 24.05mW  
Min: 12.2mW  

## Conclusion

### Bigger vs smaller dataSet

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
