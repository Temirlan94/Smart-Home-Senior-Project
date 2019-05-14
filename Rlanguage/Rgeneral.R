#install.packages("DBI")
#install.packages("RMySQL")
#install.packages("ggplot2")
#install.packages("lubridate")
#install.packages("tidyverse")
library(ggplot2)
library(DBI)
library(RMySQL)
library(tidyverse)
library(lubridate)
#Database Connection and Retrivieng Values
#======================================================================
#======================================================================

con<-dbConnect(MySQL(),host="localhost",dbname="anildata",user="root",password="")
result=dbSendQuery (con,"select * from temphum")

#data=fetch(result,n=-1)
#temperature=subset(data,select=c(temperature))
#humidity=subset(data,select=c(humidity))


#Time stamps
#=====================================================================
#=====================================================================
#result2=dbSendQuery (con,"select * from temphum where user_id=12327")
#data2=fetch(result2,n=-1)
#dbClearResult(result2)
#print (data2)


#timeR=subset(data,select=c(created_date))
#print(timeR)

#yearR=format(as.Date(timeR$created_date,format="%Y-%m-%d %H:%M:%S"), "%Y")
#print(yearR)

#monthR=format(as.Date(timeR$created_date,format="%Y-%m-%d %H:%M:%S"), "%m")
#print(monthR)

#dayR=format(as.Date(timeR$created_date,format="%Y-%m-%d %H:%M:%S"), "%d")
#print(dayR)

#hoursR=format(as.POSIXct(timeR$created_date,format="%Y-%m-%d %H:%M:%S"), "%H")
#print(hoursR)

#minutesR=format(as.POSIXct(timeR$created_date,format="%Y-%m-%d %H:%M:%S"), "%M")
#print(minutesR)

#secondsR=format(as.POSIXct(timeR$created_date,format="%Y-%m-%d %H:%M:%S"), "%S")
#print(secondsR)





#Function to sum totalValues like (temperature,humidity)
#======================================================================
#======================================================================
calcSum<-function(x)
{
  resultCalc<-(sum(x))
  return(resultCalc)
}
#calcSum(temperature)
#calcSum(humidity)

tempVal=calcSum(data$temperature)
humVal=calcSum(data$humidity)
print(tempVal)
print(humVal)


#seperating date to parts
#======================================================================
#======================================================================
#datetxt=subset(data,select = c(created_date), header=TRUE, stringsAsFactors = FALSE, na.strings = 'NA', strip.white = TRUE)
#print(datetxt)
#datetxt$date <- as.POSIXct(datetxt$date,format = "%d/%m/%Y %H:%M:%S",tz=Sys.timezone())

#making data frames to write to database
#======================================================================
#======================================================================
temp.data<-data.frame(t=c(tempVal))
hum.data<-data.frame(t=c(humVal))

#dbWriteTable(con,"temp_sum", temp.data,overwrite=FALSE,append=TRUE)
#dbWriteTable(con,"hum_sum", temp.data,overwrite=FALSE,append=TRUE)


#plotingGraph humidityVsTemperature
#======================================================================
#======================================================================
png("tempVshumidity.png")
myplot=ggplot(data,aes(y = data$humidity,x = data$temperature)) + geom_line() +ggtitle("Temperature VS Humidity")
print(myplot)
dev.off()


data$month = format(as.Date(timeR$created_date), "%m")
dataMonth = as.numeric(format(as.Date(timeR$created_date), "%m"))

print(data$created_date)
print(data)

png("tempVstime.png")

myplot2=barplot(data$temperature,names.arg=data$sensor_id,xlab="sensor_id",ylab="Temperature",col="blue",main="Temperature chart",border="black")
print(myplot2)
dev.off()



#clear result set and closing connection with database
#======================================================================
#======================================================================
dbClearResult(result)
dbDisconnect(con)