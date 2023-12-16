# Power consumption

## Test

Details

- The current implementation uses delay() as a sleep function between two different dataSet which does not cause a true deep sleep in the microcontroller. Because of this we added a theoretical part to the tests where we hypothesize how much the consumption would be if:
  - the sleep state between one dataset and another gave a consumption of approximately 0.46mA
  - The non sleep state give a consumption of 7.1mA
  - The dataset taking give a consumption of +1.958mA.
  - Opening and closing a file for writing data takes 230ms and takes 10ms each iteration using +2.5mA [obtained experimentally]
  - Opening and closing a file for writing data takes 6ms and takes 10ms each data using +2.5mA the whole time [obtained experimentally]
  - Sending a data using BLE take and use 1.22mA for 0.4ms
- With some tests it was noticed that the device has an initial transient, where consumption increases as time passes, quite long so the data was taken for 10 minutes and after this initial transient.
- Measurements conducted using an Otii Arc Pro for accuracy

### Test 1

One dataSet of one data every 10 seconds  

#### Theoretical

- - `working_time = dataSet * dataDistance = 1*1 = 1ms`  
- - `theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.46mA + 1ms * 9.058mA)/10001ms = 0.46mA`

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

- - `working_time = dataSet * dataDistance = 150*1 = 150ms`  
- - `theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (100000ms * 0.46mA + 150ms * 9.058mA)/100150ms = 0.4728mA`  

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

- - `working_time = dataSet * dataDistance = 150 * 1ms = 150ms`
- - `theoretical_consumption = (working_time * working_current)/(working_time) = (150ms * 9.058mA)/150ms = 9.058mA`  

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

- - `working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
- - `theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.46mA + 10000ms * 9.058mA)/20000ms = 4.759mA`  

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

- - `working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
- - `theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (100000ms * 0.46mA + 10000ms * 9.058mA)/110000ms = 1.24mA`  

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

- - `working_time = dataSet * dataDistance = 10000*10 = 100000ms`  
- - `theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.46mA + 100000ms * 9.058mA)/110000ms = 8.75mA`

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

- `working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
- `theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (10000ms * 0.46mA + 10000ms * 9.058mA)/20000ms = 4.759mA`  

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

- `working_time = dataSet * dataDistance = 10000*10 = 100000ms`  
- `theoretical_consumption = (sleeping_time * sleeping_current + working_time * working_current)/(sleeping_time + working_time) = (100000ms * 0.46mA + 100000ms * 9.058mA)/200000ms = 4.759mA`

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

- `working_time = dataSet * dataDistance = 150*1 = 150ms`  
- `saving_time = (file_opening+file_closing) * time_to_open  + iteration * iteration_time = (150+150)*230ms + 150 * 10 = 70500ms`  
- `theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (29500ms * 0.46mA + 150ms * 9.058mA + 70500ms * 9.6mA)/100150ms = 6.907mA`  

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

- `working_time = dataSet * dataDistance = 150*1 = 50ms`  
- `saving_time = (file_opening+file_closing) * time_to_open + iteration * iteration_time = (1+1) * 230 + 150 * 10 = 1960ms`  
- `theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (98040ms * 0.46mA + 150ms * 9.058mA + 1960ms * 9.6mA)/100150ms = 0.652mA`  

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

- `working_time = dataSet * dataDistance = 150*1 = 150ms`  
- `saving_time = (file_opening+file_closing) * time_to_open + iteration * iteration_time = (10+10) * 230ms + 10 * 10 = 4700ms`  
- `theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (95300ms * 0.46mA + 150ms * 9.058mA + 4700ms * 9.6mA)/100150ms = 0.902mA`  

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

- `working_time = dataSet * dataDistance = 150*1 = 150ms`  
- `saving_time = (file_opening+file_closing) * time_to_open + iteration * iteration_time= (1+1) * 230 + 10 * 10 = 560ms`  
- `theoretical_consumption = ( (sleeping_time-saving_time) * sleeping_current + working_time * working_current + saving_current * saving_time)/(sleeping_time + working_time) = (99560ms * 0.46mA + 150ms * 9.058mA + 560ms * 9.6mA)/100150ms = 0.524mA`  

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

- `working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
- `sending_time = dataSet*0.4 = 10000 * 0.4ms = 4000ms`  
- `theoretical_consumption = ( (sleeping_time-sending_time) * sleeping_current + working_time * working_current + sending_current * sending_time)/(sleeping_time + working_time) = (6000ms * 0.46mA + 10000ms * 9.058mA + 4000ms * 8.22mA)/20000ms = 6.31mA`  

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

- `working_time = dataSet * dataDistance = 10000*1 = 10000ms`  
- `sending_time = dataSet*0.4 = 10000 * 0.4ms = 4000ms`  
- `theoretical_consumption = ( (sleeping_time-sending_time) * sleeping_current + working_time * working_current + sending_current * sending_time)/(sleeping_time + working_time) = (6000ms * 0.46mA + 10000ms * 9.058mA + 4000ms * 8.22mA)/20000ms = 6.31mA`  

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

- `working_time = dataSet * dataDistance = 150 * 1ms = 150ms`  
- `saving_time = (file_opening + file_closing) * time_to_open + iteration * iteration_time = (10+10) * 230ms + 10 * 10= 4700ms`  
- `reading_and_sending_time = (file_opening + file_closing) * time_to_open + iteration * iteration_time + sending_data * sending_time = (1+1) * 6ms + 150 * 10 + 150 * 0.4ms = 1572ms`  
- `theoretical_consumption = ( (sleeping_time - saving_time - reading_and_sending_time) * sleeping_current + working_time * working_current + saving_time * saving_current + reading_and_sending_time * reading_and_sending_current)/(sleeping_time + working_time) = (3728 * 0.46 + 150 * 9.058 + 4700 * 9.6 + 1572 * 10.82)/10150ms = 6.42 mA`

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

- `working_time = dataSet * dataDistance = 150 * 1ms = 150ms`  
- `saving_time = (file_opening + file_closing) * time_to_open + iteration * iteration_time = (10+10) * 230ms + 10 * 10= 4700ms`  
- `reading_and_sending_time = (file_opening + file_closing) * time_to_open + iteration * iteration_time + sending_data * sending_time = (1+1) * 6ms + 150 * 10ms + 150 * 0.4ms = 1572ms`  
`reading_time = (file_opening + file_closing) * time_to_open = (99+99) * 6ms = 1188ms`  
- `theoretical_consumption = ( (sleeping_time - saving_time - reading_and_sending_time - reading_time) * sleeping_current + working_time * working_current + saving_time * saving_current + reading_and_sending_time * reading_and_sending_current + reading_time * reading_current)/(sleeping_time + working_time) = (2540ms * 0.46mA + 150ms * 9.058mA + 4700ms * 9.6mA + 1572ms * 10.82mA + 1188 * 9.6mA)/10150ms = 7.494 mA`

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

- `working_time = dataSet * dataDistance = 150 * 1ms = 150ms`  
- `saving_time = (file_opening + file_closing) * time_to_open + iteration * iteration_time = (10+10) * 230ms + 10 * 10 = 4700ms`  
- `reading_and_sending_time = (file_opening + file_closing) * time_to_open + iteration * iteration_time + sending_data * sending_time = (100+100) * 6ms + 15000 * 10ms + 15000 * 0.4ms = 16800ms`  
- `AVG_current_no_sending = ((sleeping_time - saving_time) * sleeping_current + working_time * working_current + saving_time * saving_current )/(sleeping_time+sending_time) = (5300ms * 0.46mA + 150ms * 9.058mA + 4700ms * 9.6mA)/(10150ms) = 4.82mA`  
- `teoretical_consumption = (1000000 * AVG_current_no_sending + reading_and_sending_time * reading_and_sending_current)(scanTime + reading_and_sending_time) = (1000000*4.82+ 16800 * 10.82 )/(1000000+16800) = 4.919mA`  

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

Conclusions were drawn from theoretical results but would not differ much if practical results were used instead

### Bigger vs Smaller DataSets
  
- **Test Scenarios**: Test 2 and Test 5 were used.
- **Observations**:
  - **Increased Consumption with Larger Datasets**: Larger datasets demonstrated higher power consumption due to prolonged active periods during data reading.

### Bigger vs Smaller Data Distance
  
- **Test Scenarios**: Test 4 and Test 6 were examined.
- **Observations**:
  - **Impact of Data Point Intervals**: Higher intervals between data points showed higher power consumption due to increased working time during data reading.

### Bigger vs Smaller Distance Between Sets
  
- **Test Scenarios**: Test 2 and Test 3 were evaluated.
- **Observations**:
  - **Impact of Set Intervals**: Larger intervals between sets consistently showed lower power consumption, attributing this to increased sleeping times between data set processing.

### Disable vs Enable Data Saver
  
- **Test Scenarios**: Test 2, Test 9, and Test 11 were considered.
- **Observations**:
  - **Effect of Data Per Iteration**: Enabling `DATA_SAVER` with varying `DATA_PER_ITERATION` values showcased significant power differences, particularly highlighting the impact of slower saving processes with lower `DATA_PER_ITERATION`, because the slower part in the saving process is file opening and file closing that happend evry iteration.

### Disable vs Enable Data Saver Keep Open
  
- **Test Scenarios**: Test 2, Test 10, and Test 12 were examined.
- **Observations**:
  - **Optimizing File Handling**: Enabling `DATA_SAVER_KEEP_OPEN` showcased improved power efficiency, especially with lower `DATA_PER_ITERATION`, emphasizing the advantage of reduced file opening and closing frequencies.

### Data Saver vs Data Saver Keep Open
  
- **Test Scenarios**: Test 9, Test 10, Test 11, and Test 12 were scrutinized.
- **Observations**:
  - **File Operation Efficiency**: `DATA_SAVER_KEEP_OPEN` presented more power-efficient file handling compared to `DATA_SAVER`, especially noticeable with lower `DATA_PER_ITERATION`.
  - **Impact of Different Data Per Iteration**: The impact of the size of `DATA_PER_ITERATION` is a lot less significant using `DATA_SAVER_KEEP_OPEN` than when using `DATA_SAVER`.
  
### Disable vs Enable Send DataSet
  
- **Test Scenarios**: Test 4 and Test 13 were analyzed.
- **Observations**:
  - **Impact of Data Transmission**: Enabling data transmission slightly increased power consumption, primarily influenced by the volume of data to be sent.

### Disable vs Enable Send DataSet Thread
  
- **Test Scenarios**: Test 4 and Test 14 were reviewed.
- **Observations**:
  - **Marginal Power Impact**: Enabling data transmission via threads showcased a negligible difference in power consumption compared to not-thread transmission

### Send DataSet vs Send DataSet Thread
  
- **Test Scenarios**: Test 13 and Test 14 were compared.
- **Observations**:
  - **Similar Power Usage**: The choice between sending data through threads or not showcased marginal power differences, with both methods exhibiting similar power consumption levels.
  - **Difference in Max DataSet Dimension**: using `SEND_DATASET_THREAD` we are forced to reduce `MAX_DATASET_DIMENSION` a lot.
  - **Notable Difference about the Practice Tests**: when using `SEND_DATASET_THREAD`, although the average consumption remains almost the same, there are greater fluctuations.
  
### Disable vs Enable Data Sender
  
- **Test Scenarios**: Test 2, Test 11, Test 13, and Test 15 were investigated.
- **Observations**:
  - **Added Processing Overhead**: Enabling data sender increased power consumption, likely due to the additional processing involved in writing and reading the data from the internal storage.

### Bigger vs Smaller Data_to_Scan
  
- **Test Scenarios**: Test 15, Test 16, and Test 17 were examined.
- **Observations**:
  - **Impact of Scanning Data**: Scanning the file for non-existent or actual data showcased varying power consumption, with actual data transmission significantly affecting power usage.

### Bigger vs Smaller Scan Time
  
- **Test Scenarios**: Test 15, Test 16, and Test 17 were used.
- **Observations**:
  - **Balancing Scan Frequency and Data Read**: Adjusting scan times demonstrated the trade-off between longer intervals and more data read, showcasing a notable impact on power efficiency.
  - **Risk**: If the time to read and send all the data is bigger than the sleeping time we are likely to lose data.
  