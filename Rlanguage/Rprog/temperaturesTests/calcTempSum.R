library(testthat) 
library(DBI)
library(RMySQL)

con<-dbConnect(MySQL(),host="localhost",dbname="temp",user="root",password="")
result=dbSendQuery (con,"select * from temp")

#-----------------------
#Taking columns from database
#-----------------------
data=fetch(result,n=-1)
temp=subset(data,select=c(temp))

dbClearResult(result)
dbDisconnect(con)

calcTempSum<-function(temp)
{
  tempSum<-(sum(temp))
  return(tempSum)
}


calcTempSum(temp)
  


