library(DBI)
library(RMySQL)

con<-dbConnect(MySQL(),host="localhost",dbname="temp",user="root",password="")
result=dbSendQuery (con,"select * from temp")


#-----------------------
#Taking columns from database
#-----------------------

data=fetch(result,n=-1)
humidity=subset(data,select=c(hum))

dbClearResult(result)
dbDisconnect(con)

calcHumSum<-function(humidity)
{
  humSum<-(sum(humidity))
  return(humSum)
}


calcHumSum(humidity)

