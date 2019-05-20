#install.packages("DBI")
#install.packages("RMySQL")
#install.packages("ggplot2")
#install.packages("lubridate")

library(ggplot2)
library(DBI)
library(RMySQL)
library(lubridate)
#Database Connection and Retrivieng Values
#======================================================================
#======================================================================
con<-dbConnect(MySQL(),host="localhost",dbname="anildata",user="root",password="")
result=dbSendQuery (con,"select * from temphum")
data=fetch(result,n=-1)

#temperature=subset(data,select=c(temperature))
#humidity=subset(data,select=c(humidity))


#Function to sum totalValues like (temperature,humidity)
#======================================================================
#======================================================================
#calcSum<-function(x)
#{
  #resultCalc<-(sum(x))
 # return(resultCalc)
#}
#calcSum(temperature)
#calcSum(humidity)

tempVal=calcSum(data$temperature)
humVal=calcSum(data$humidity)
print(tempVal)
print(humVal)
print (mean(data$temperature))

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


#Taking Month,Year,Day
#======================================================================
#======================================================================
df$created_date<-as.Date(data$created_date)
df$Month<- months(df$created_date)
df$Year <- format(df$created_date,format="%y")
df$Day <- format(df$created_date,format="%d/%m/%y")

#Average temperature per year and month
#======================================================================
#======================================================================

avgTempMonth=aggregate(data$temperature ~ Month + Year , df , mean )
print(avgTempMonth)
dbWriteTable(con,"averagemonthtemp", avgTempMonth,overwrite=TRUE,append=FALSE)

#=====plot===========

result2=dbSendQuery (con,"select * from averagemonthtemp")
dataMonthTemp=fetch(result2,n=-1)
png("AvgtempMonthVstime.png")
myplot3=barplot(dataMonthTemp$`data$temperature`,names.arg=dataMonthTemp$Month,xlab="Month",ylab="Temperature",col="blue",main="Temperature chart",border="black",ylim=c(0,50))
print(myplot3)
dev.off()
dbClearResult(result2)

#Average temperature per year and day and year
#======================================================================
#======================================================================

avgTempDay=aggregate(data$temperature ~ Month + Day+Year , df , mean )
print(avgTempDay)
dbWriteTable(con,"averagedaytemp", avgTempDay,overwrite=TRUE,append=FALSE)
#=====plot===========

result3=dbSendQuery (con,"select * from averagedaytemp")
dataDayTemp=fetch(result3,n=-1)
png("AvgDayMonthTempVstime.png")
myplot3=barplot(dataDayTemp$`data$temperature`,names.arg=dataDayTemp$Day,xlab="Day",ylab="Temperature",col="blue",main="Temperature chart",border="black",ylim=c(0,70))
print(myplot3)
dev.off()
dbClearResult(result3)


#Average humidity per year and month
#======================================================================
#======================================================================
avgHumMonth=aggregate(data$humidity ~ Month + Year , df , mean )
print(avgHumMonth)
dbWriteTable(con,"averagehumiditymonth", avgHumMonth,overwrite=TRUE,append=FALSE)
#=====plot===========
result4=dbSendQuery (con,"select * from averagehumiditymonth")
dataMonthHum=fetch(result4,n=-1)
png("AvgHumidityMonthVstime.png")
myplot=barplot(dataMonthHum$`data$humidity`,names.arg=dataMonthHum$Month,xlab="Month",ylab="Humidity",col="blue",main="Humidity chart",border="black",ylim=c(0,70))
print(myplot)
dev.off()
dbClearResult(result4)

#Average humidity per year and day and year
#======================================================================
#======================================================================

avgHumDay=aggregate(data$humidity ~ Month + Day+Year , df , mean )
print(avgHumDay)
dbWriteTable(con,"averagedayhum", avgHumDay,overwrite=TRUE,append=FALSE)
#=====plot===========

result5=dbSendQuery (con,"select * from averagedayhum")
dataDayHum=fetch(result5,n=-1)
png("AvgHumidityDayMonthVstime.png")
myplot=barplot(dataDayHum$`data$humidity`,names.arg=dataDayHum$Day,xlab="Day",ylab="Humidity",col="blue",main="Temperature chart",border="black",ylim=c(0,70))
print(myplot)
dev.off()
dbClearResult(result5)


#clear result set and closing connection with database
#======================================================================
#======================================================================
dbClearResult(result)
dbDisconnect(con)